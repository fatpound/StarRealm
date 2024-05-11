module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>

#include <cassert>

#if _MSVC_LANG == 202002L
#ifndef NDEBUG
#include <array>
#endif // !NDEBUG
#endif // _MSVC_LANG == 202002L

#define RASTERIZATION_ENABLED

#define MSAA_QUALITY 16u

#pragma comment(lib, "d3d11")
#pragma comment(lib, "D3DCompiler")

module D3D11Graphics;

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

namespace fatpound::win32::d3d11
{
    Graphics::Graphics(HWND hWnd, std::size_t width, std::size_t height)
        :
        screen_width_(width),
        screen_height_(height)
    {
        assert(hWnd != nullptr);

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

#ifdef NDEBUG

        scd.Windowed = FALSE;
        constexpr UINT swapCreateFlags = 0u;
#else
        scd.Windowed = TRUE;
        constexpr UINT swapCreateFlags = D3D11_CREATE_DEVICE_DEBUG;

#endif // NDEBUG

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
            throw std::runtime_error("Could NOT create the Device and SwapChain!");
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

#pragma region Z-BUFFER

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

#pragma endregion

#ifdef RASTERIZATION_ENABLED

        wrl::ComPtr<ID3D11RasterizerState> pRasterState;

        D3D11_RASTERIZER_DESC rasterDesc = {};
        rasterDesc.FillMode = D3D11_FILL_SOLID;
        rasterDesc.CullMode = D3D11_CULL_BACK;
        rasterDesc.FrontCounterClockwise = false;
        rasterDesc.DepthBias = 0;
        rasterDesc.DepthBiasClamp = 0.0f;
        rasterDesc.SlopeScaledDepthBias = 0.0f;
        rasterDesc.DepthClipEnable = true;
        rasterDesc.ScissorEnable = false;
        rasterDesc.MultisampleEnable = true;
        rasterDesc.AntialiasedLineEnable = true;

        hr = pDevice_->CreateRasterizerState(&rasterDesc, &pRasterState);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create RasterizerState!");
        }

        pContext_->RSSetState(pRasterState.Get());

#endif // RASTERIZATION_ENABLED

        D3D11_VIEWPORT vp = {};
        vp.Width = static_cast<FLOAT>(screen_width_);
        vp.Height = static_cast<FLOAT>(screen_height_);
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0.0f;
        vp.TopLeftY = 0.0f;

        pContext_->RSSetViewports(1u, &vp);
    }

    dx::XMMATRIX Graphics::GetProjectionXM() const noexcept
    {
        return projection_;
    }
    dx::XMMATRIX Graphics::GetCameraXM() const noexcept
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