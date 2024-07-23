module;

#include "../../FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

#define MSAA_QUALITY 8u

#pragma comment(lib, "d3d11")
#pragma comment(lib, "D3DCompiler")

module FatPound.Win32.D3D11.Graphics;

namespace dx = DirectX;
namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11
{
    Graphics::Graphics(HWND hWnd, const SizeInfo& dimensions)
        :
        width_(dimensions.width),
        height_(dimensions.height)
    {
        DXGI_SWAP_CHAIN_DESC scd = {};
        scd.BufferDesc.Width = 0u;
        scd.BufferDesc.Height = 0u;
        scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        scd.BufferDesc.RefreshRate.Numerator = 0u;
        scd.BufferDesc.RefreshRate.Denominator = 0u;
        scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        scd.SampleDesc.Count = MSAA_QUALITY;
        scd.SampleDesc.Quality = 0u;
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        scd.BufferCount = 1u;
        scd.OutputWindow = hWnd;
        scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        scd.Flags = 0u;

#if IN_RELEASE

        scd.Windowed = FALSE;
        constexpr UINT swapCreateFlags = 0u;
#else
        scd.Windowed = TRUE;
        constexpr UINT swapCreateFlags = D3D11_CREATE_DEVICE_DEBUG;

#endif // IN_RELEASE

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
            &pContext_
        );

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create the Device and SwapChain!\n"
                "Consider decreasing MSAA_QUALITY by half...");
        }

        wrl::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
        wrl::ComPtr<ID3D11Texture2D> pBackBufferTexture = nullptr;

        hr = pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBufferTexture);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT get the buffer from SwapChain!");
        }

        D3D11_TEXTURE2D_DESC backBufferDesc = {};
        backBufferDesc.SampleDesc.Count = MSAA_QUALITY;
        backBufferDesc.SampleDesc.Quality = 0u;

        pBackBufferTexture->GetDesc(&backBufferDesc);

        hr = pDevice_->CreateRenderTargetView(pBackBufferTexture.Get(), nullptr, &pTarget_);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create RenderTargetView!");
        }

        wrl::ComPtr<ID3D11DepthStencilState> pDSState;

        D3D11_DEPTH_STENCIL_DESC dsDesc = {};
        dsDesc.DepthEnable = TRUE;
        dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

        hr = pDevice_->CreateDepthStencilState(&dsDesc, &pDSState);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create DepthStencilState!");
        }

        pContext_->OMSetDepthStencilState(pDSState.Get(), 1u);

        wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
        
        D3D11_TEXTURE2D_DESC descDepth = {};
        descDepth.Width = backBufferDesc.Width;
        descDepth.Height = backBufferDesc.Height;
        descDepth.MipLevels = 1u;
        descDepth.ArraySize = 1u;
        descDepth.Format = DXGI_FORMAT_D32_FLOAT;
        descDepth.SampleDesc.Count = MSAA_QUALITY;
        descDepth.SampleDesc.Quality = 0u;
        descDepth.Usage = D3D11_USAGE_DEFAULT;
        descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        
        hr = pDevice_->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);
        
        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create Texture2D!");
        }

        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
        descDSV.Format = DXGI_FORMAT_D32_FLOAT;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
        descDSV.Texture2D.MipSlice = 0u;
        
        hr = pDevice_->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &pDSV_);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create DepthStencilView!");
        }

        pContext_->OMSetRenderTargets(1u, pTarget_.GetAddressOf(), pDSV_.Get());

        if constexpr (rasterization_enabled_)
        {
            pipeline::system::Rasterizer::SetDefault(pDevice_, pContext_);
        }

        pipeline::system::Viewport::SetDefault(pContext_, width_, height_);
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
        pContext_->DrawIndexed(count, 0u, 0);
    }

    void Graphics::SetProjection(const dx::XMMATRIX& projection) noexcept
    {
        projection_ = projection;
    }
    void Graphics::SetCamera(const dx::XMMATRIX& camera) noexcept
    {
        camera_ = camera;
    }

    void Graphics::ClearBuffer_(const float& red, const float& green, const float& blue) noexcept
    {
        const std::array<float, 4> colors{ red, green, blue, 1.0f };

        pContext_->ClearRenderTargetView(pTarget_.Get(), colors.data());
        pContext_->ClearDepthStencilView(pDSV_.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
    }
}