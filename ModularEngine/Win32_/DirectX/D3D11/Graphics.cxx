module;

#include <FatWin32_.hpp>

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
    Graphics::Graphics(::HWND hWnd, const SizeInfo& dimensions)
        :
        m_width_(dimensions.width),
        m_height_(dimensions.height)
    {
        {
            const auto& scdesc = factory::SwapChain::CreateDESC<Graphics::s_msaaQuality_>(hWnd, m_width_, m_height_);
            factory::Device::CreateWithSwapChain(m_pDevice_, m_pSwapChain_, m_pImmediateContext_, scdesc);
        }

        ToggleAltEnterMode_();

        pipeline::system::RenderTarget::SetDefault<s_msaaQuality_>(m_pDevice_, m_pSwapChain_, m_pImmediateContext_, m_pTarget_, m_pDSV_, m_width_, m_height_);
        pipeline::system::DepthStencil::SetDefault(m_pDevice_, m_pImmediateContext_);
        pipeline::system::Viewport::SetDefault(m_pImmediateContext_, m_width_, m_height_);

        if constexpr (s_rasterizationEnabled_)
        {
            pipeline::system::Rasterizer::SetDefault(m_pDevice_, m_pImmediateContext_);
        }
    }

    auto Graphics::GetProjectionXM() const noexcept -> ::dx::XMMATRIX
    {
        return m_projection_;
    }
    auto Graphics::GetCameraXM() const noexcept -> ::dx::XMMATRIX
    {
        return m_camera_;
    }

    void Graphics::BeginFrame() noexcept
    {
        ClearBuffer_(0.0f, 0.0f, 0.25f);
    }
    void Graphics::EndFrame()
    {
        HRESULT hr;

        hr = m_pSwapChain_->Present(1u, 0u);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("The Graphics Device Failed to Present/Draw!");
        }
    }
    void Graphics::DrawIndexed(UINT count) noexcept(IN_RELEASE)
    {
        m_pImmediateContext_->DrawIndexed(count, 0u, 0);
    }

    void Graphics::SetProjection(const dx::XMMATRIX& projection) noexcept
    {
        m_projection_ = projection;
    }
    void Graphics::SetCamera(const dx::XMMATRIX& camera) noexcept
    {
        m_camera_ = camera;
    }

    void Graphics::ToggleAltEnterMode_()
    {
        ::wrl::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
        m_pDevice_->QueryInterface(__uuidof(IDXGIDevice), &pDXGIDevice);

        ::wrl::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
        pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), &pDXGIAdapter);

        ::wrl::ComPtr<IDXGIFactory> pIDXGIFactory = nullptr;
        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), &pIDXGIFactory);

        DXGI_SWAP_CHAIN_DESC desc = {};
        m_pSwapChain_->GetDesc(&desc);

        const auto& hWnd = desc.OutputWindow;

        static UINT flag = 0u;

        static constexpr UINT magic_value = static_cast<UINT>(DXGI_MWA_NO_ALT_ENTER);

        if ((flag bitand magic_value) not_eq 0u)
        {
            flag &= ~magic_value;
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

        m_pImmediateContext_->ClearRenderTargetView(m_pTarget_.Get(), colors.data());
        m_pImmediateContext_->ClearDepthStencilView(m_pDSV_.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
    }
}