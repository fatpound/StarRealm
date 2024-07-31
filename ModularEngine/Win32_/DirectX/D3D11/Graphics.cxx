module;

#include "../../FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "D3DCompiler")

module FatPound.Win32.D3D11.Graphics;

namespace dx = DirectX;
namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11
{
    Graphics::Graphics(const Window& wnd)
        :
        Graphics(wnd.GetHwnd(), SizeInfo{ wnd.GetClientWidth<UINT>(), wnd.GetClientHeight<UINT>()})
    {

    }
    Graphics::Graphics(HWND hWnd, const SizeInfo& dimensions)
        :
        width_(dimensions.width),
        height_(dimensions.height)
    {
        DXGI_SWAP_CHAIN_DESC scd = {};
        scd.BufferDesc.Width = width_;
        scd.BufferDesc.Height = height_;
        scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        scd.BufferDesc.RefreshRate.Numerator = 0u;
        scd.BufferDesc.RefreshRate.Denominator = 0u;
        scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        scd.SampleDesc.Count = Graphics::msaa_quality_;
        scd.SampleDesc.Quality = 0u;
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        scd.BufferCount = 1u;
        scd.OutputWindow = hWnd;
        scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        scd.Flags = 0u;

        static constinit UINT swapCreateFlags;

        if constexpr (IN_RELEASE)
        {
            scd.Windowed = false;
            swapCreateFlags = 0u;
        }
        else
        {
            scd.Windowed = true;
            swapCreateFlags = D3D11_CREATE_DEVICE_DEBUG;
        }

        HRESULT hr;

        hr = D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            swapCreateFlags,
            nullptr,
            0u,
            D3D11_SDK_VERSION,
            &scd,
            &pSwapChain_,
            &pDevice_,
            nullptr,
            &pImmediateContext_
        );

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create the Device and SwapChain!\n"
                "Consider decreasing MSAA_QUALITY by half...");
        }

        ToggleAltEnterMode_();

        wrl::ComPtr<ID3D11Texture2D> pBackBufferTexture = nullptr;
        hr = pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBufferTexture);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT get the buffer from SwapChain!");
        }

        hr = pDevice_->CreateRenderTargetView(pBackBufferTexture.Get(), nullptr, &pTarget_);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create RenderTargetView!");
        }

        D3D11_DEPTH_STENCIL_DESC dsDesc = {};
        dsDesc.DepthEnable = true;
        dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

        wrl::ComPtr<ID3D11DepthStencilState> pDSState;
        hr = pDevice_->CreateDepthStencilState(&dsDesc, &pDSState);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create DepthStencilState!");
        }

        pImmediateContext_->OMSetDepthStencilState(pDSState.Get(), 1u);
        
        const auto& descDepth = factory::Texture2D::CreateDESC<Graphics::msaa_quality_>(width_, height_);
        
        wrl::ComPtr<ID3D11Texture2D> pDepthStencil = nullptr;
        hr = pDevice_->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);
        
        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create Texture2D!");
        }

        const auto& descDSV = factory::DepthStencilView::CreateDESC<Graphics::msaa_quality_>();
        factory::DepthStencilView::Init(pDevice_, pDepthStencil, pDSV_, descDSV);

        pImmediateContext_->OMSetRenderTargets(1u, pTarget_.GetAddressOf(), pDSV_.Get());

        if constexpr (Graphics::rasterization_enabled_)
        {
            pipeline::system::Rasterizer::SetDefault(pDevice_, pImmediateContext_);
        }

        pipeline::system::Viewport::SetDefault(pImmediateContext_, width_, height_);
    }

    auto Graphics::GetProjectionXM() const noexcept -> dx::XMMATRIX
    {
        return projection_;
    }
    auto Graphics::GetCameraXM() const noexcept -> dx::XMMATRIX
    {
        return camera_;
    }

    void Graphics::BeginFrame() noexcept
    {
        ClearBuffer_(0.0f, 0.0f, 0.25f);
    }
    void Graphics::EndFrame()
    {
        HRESULT hr;

        hr = pSwapChain_->Present(1u, 0u);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("The Graphics Device Failed to Present/Draw!");
        }
    }
    void Graphics::DrawIndexed(UINT count) noexcept(IN_RELEASE)
    {
        pImmediateContext_->DrawIndexed(count, 0u, 0);
    }

    void Graphics::SetProjection(const dx::XMMATRIX& projection) noexcept
    {
        projection_ = projection;
    }
    void Graphics::SetCamera(const dx::XMMATRIX& camera) noexcept
    {
        camera_ = camera;
    }

    void Graphics::ToggleAltEnterMode_()
    {
        wrl::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
        pDevice_->QueryInterface(__uuidof(IDXGIDevice), &pDXGIDevice);

        wrl::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
        pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), &pDXGIAdapter);

        wrl::ComPtr<IDXGIFactory> pIDXGIFactory = nullptr;
        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), &pIDXGIFactory);

        DXGI_SWAP_CHAIN_DESC desc = {};
        pSwapChain_->GetDesc(&desc);

        const auto& hWnd = desc.OutputWindow;

        static UINT flag = 0u;

        static constexpr UINT magic_value = static_cast<UINT>(DXGI_MWA_NO_ALT_ENTER);

        if ((flag bitand magic_value) not_eq 0u)
        {
            flag &= ~(magic_value);
        }
        else
        {
            flag |= magic_value;
        }

        pIDXGIFactory->MakeWindowAssociation(hWnd, flag);
    }
    void Graphics::ClearBuffer_(const float& red, const float& green, const float& blue) noexcept
    {
        const std::array<float, 4> colors{ red, green, blue, 1.0f };

        pImmediateContext_->ClearRenderTargetView(pTarget_.Get(), colors.data());
        pImmediateContext_->ClearDepthStencilView(pDSV_.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
    }
}