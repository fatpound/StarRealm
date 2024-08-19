module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "D3DCompiler")

export module FatPound.Win32.D3D11.Graphics;

import FatPound.Win32.D3D11.Graphics.Resource;
import FatPound.Win32.D3D11.Pipeline.Element;
import FatPound.Win32.D3D11.Pipeline.System;
import FatPound.Win32.D3D11.Pipeline.StaticBindableVec;
import FatPound.Win32.D3D11.Factory;

import FatPound.Math;
import FatPound.Util;

import std;

namespace dx = DirectX;
namespace wrl = Microsoft::WRL;

using NAMESPACE_UTIL::Color;

struct __declspec(empty_bases) SEmpty_
{

};

export namespace fatpound::win32::d3d11
{
    template <bool Framework = false>
    class Graphics final : public std::conditional_t<Framework, NAMESPACE_PIPELINE::StaticBindableVec<Graphics<Framework>>, SEmpty_>
    {
    public:
        struct FullScreenQuad final
        {
            struct Vertex final
            {
                float x;
                float y;
                float z;

                float u;
                float v;
            };

            inline static const std::vector<Vertex> vertices =
            {
                Vertex{ -1.0f,  1.0f,  0.5f,  0.0f,  0.0f },
                Vertex{  1.0f,  1.0f,  0.5f,  1.0f,  0.0f },
                Vertex{  1.0f, -1.0f,  0.5f,  1.0f,  1.0f },
                Vertex{ -1.0f,  1.0f,  0.5f,  0.0f,  0.0f },
                Vertex{  1.0f, -1.0f,  0.5f,  1.0f,  1.0f },
                Vertex{ -1.0f, -1.0f,  0.5f,  0.0f,  1.0f }
            };
        };
        struct SizeInfo final
        {
            unsigned int width;
            unsigned int height;
        };


    public:
        explicit Graphics(HWND hWnd, const SizeInfo& dimensions)
            :
            m_width_(dimensions.width),
            m_height_(dimensions.height)
        {
            InitCommon_(hWnd);
            
            pipeline::system::DepthStencil::SetDefault(m_gfxres_);

            if constexpr (s_rasterizationEnabled_)
            {
                pipeline::system::Rasterizer::SetDefault(m_gfxres_);
            }
        }
        explicit Graphics(HWND hWnd, const SizeInfo& dimensions) requires(Framework)
            :
            m_width_(dimensions.width),
            m_height_(dimensions.height)
        {
            InitCommon_(hWnd);

            pipeline::system::ShaderResource::SetDefault<s_msaaQuality_>(m_gfxres_, m_width_, m_height_);
            pipeline::system::Sampler::SetDefault(m_gfxres_);

            m_gfxres_.m_pSysBuffer = static_cast<Color*>(_aligned_malloc(sizeof(Color) * m_width_ * m_height_, 16u));

            if (m_gfxres_.m_pSysBuffer == nullptr) [[unlikely]]
            {
                throw std::runtime_error("Could NOT allocate memory for sysBuffer");
            }
            
            InitFramework_();
        }

        explicit Graphics() = delete;
        explicit Graphics(const Graphics& src) = delete;
        explicit Graphics(Graphics&& src) = delete;

        Graphics& operator = (const Graphics& src) = delete;
        Graphics& operator = (Graphics&& src) = delete;
        ~Graphics() noexcept = default;
        ~Graphics() noexcept(false) requires(Framework)
        {
            if (m_gfxres_.m_pSysBuffer != nullptr) [[likely]]
            {
                _aligned_free(m_gfxres_.m_pSysBuffer);
                m_gfxres_.m_pSysBuffer = nullptr;
            }

            if (m_gfxres_.m_pImmediateContext != nullptr) [[likely]]
            {
                m_gfxres_.m_pImmediateContext->ClearState();
            }
        }


    public:
        template <NAMESPACE_MATH::Number N>
        auto GetWidth() const noexcept
        {
            return static_cast<N>(m_width_);
        }
        template <NAMESPACE_MATH::Number N>
        auto GetHeight() const noexcept
        {
            return static_cast<N>(m_height_);
        }

        auto GetDevice() -> ID3D11Device*
        {
            return m_gfxres_.m_pDevice.Get();
        }
        auto GetImmediateContext() -> ID3D11DeviceContext*
        {
            return m_gfxres_.m_pImmediateContext.Get();
        }

        auto GetProjectionXM() const noexcept -> ::DirectX::XMMATRIX requires(not Framework)
        {
            return m_projection_;
        }
        auto GetCameraXM()     const noexcept -> ::DirectX::XMMATRIX requires(not Framework)
        {
            return m_camera_;
        }

        void BeginFrame() noexcept
        {
            ClearBuffer_(0.0f, 0.0f, 0.0f);
        }
        void BeginFrame() noexcept requires(Framework)
        {
            std::memset(reinterpret_cast<void*>(m_gfxres_.m_pSysBuffer), 0u, sizeof(Color) * m_width_ * m_height_);
        }
        void EndFrame()
        {
            const auto hr = m_gfxres_.m_pSwapChain->Present(1u, 0u);

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::runtime_error("The Graphics Device Failed to Present/Draw!");
            }
        }
        void EndFrame() requires(Framework)
        {
            HRESULT hr = m_gfxres_.m_pImmediateContext->Map(
                m_gfxres_.m_pSysBufferTexture.Get(),
                0u,
                D3D11_MAP_WRITE_DISCARD,
                0u,
                &m_gfxres_.m_mappedSysBufferTexture
            );

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::exception("Could NOT Map the ImmediateContext!");
            }

            Color* pDst = static_cast<Color*>(m_gfxres_.m_mappedSysBufferTexture.pData);

            const auto& dstPitch = m_gfxres_.m_mappedSysBufferTexture.RowPitch / sizeof(Color);
            const auto& srcPitch = m_width_;
            const auto& rowBytes = srcPitch * sizeof(Color);

            for (auto y = 0u; y < m_height_; ++y)
            {
                std::memcpy(
                    static_cast<void*>(&pDst[y * dstPitch]),
                    static_cast<void*>(&m_gfxres_.m_pSysBuffer[y * srcPitch]),
                    rowBytes
                );
            }

            m_gfxres_.m_pImmediateContext->Unmap(m_gfxres_.m_pSysBufferTexture.Get(), 0u);
            m_gfxres_.m_pImmediateContext->Draw(6u, 0u);

            hr = m_gfxres_.m_pSwapChain->Present(1u, 0u);

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::exception("SwapChain could NOT Present and Draw its contents!");;
            }
        }

        void PutPixel(int x, int y, Color color) noexcept requires(Framework)
        {
            assert(x >= 0);
            assert(x < static_cast<int>(m_width_));
            assert(y >= 0);
            assert(y < static_cast<int>(m_height_));

            m_gfxres_.m_pSysBuffer[m_width_ * y + x] = color;
        }
        void DrawIndexed(UINT count) requires(not Framework)
        {
            m_gfxres_.m_pImmediateContext->DrawIndexed(count, 0u, 0);
        }

        void SetProjectionXM(const ::DirectX::XMMATRIX& projection) noexcept requires(not Framework)
        {
            m_projection_ = projection;
        }
        void SetCameraXM(const ::DirectX::XMMATRIX& camera)         noexcept requires(not Framework)
        {
            m_camera_ = camera;
        }


    protected:


    private:
        void InitCommon_(HWND hWnd)
        {
            {
                const auto& scdesc = factory::DeviceAndSwapChain::CreateDESC<s_msaaQuality_>(hWnd, m_width_, m_height_);
                factory::DeviceAndSwapChain::Create(m_gfxres_, scdesc);
            }

            ToggleAltEnterMode_();

            pipeline::system::RenderTarget::SetDefault<s_msaaQuality_>(m_gfxres_, m_width_, m_height_);
            pipeline::system::Viewport::SetDefault(m_gfxres_, m_width_, m_height_);
        }
        void InitFramework_() requires(Framework)
        {
            using SBinds = NAMESPACE_PIPELINE::StaticBindableVec<Graphics<Framework>>;
            
            auto pvs = std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexShader>(GetDevice(), L"VSFrameBuffer.cso");
            auto pvsbc = pvs->GetBytecode();
            
            SBinds::AddStaticBind_(std::move(pvs));
            SBinds::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::element::PixelShader>(GetDevice(), L"PSFrameBuffer.cso"));
            SBinds::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::element::VertexBuffer>(GetDevice(), FullScreenQuad::vertices));
            SBinds::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::element::Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
            
            const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                {
                    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
                }
            };
            
            SBinds::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::element::InputLayout>(GetDevice(), ied, pvsbc));
            
            auto pDevice = GetDevice();
            auto pImmediateContext = GetImmediateContext();

            auto& sbinds = SBinds::GetStaticBinds_();

            for (auto& sbind : sbinds)
            {
                sbind->Bind(pDevice, pImmediateContext);
            }
        }

        void ToggleAltEnterMode_()
        {
            ::wrl::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
            m_gfxres_.m_pDevice->QueryInterface(__uuidof(IDXGIDevice), &pDXGIDevice);

            ::wrl::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
            pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), &pDXGIAdapter);

            ::wrl::ComPtr<IDXGIFactory> pIDXGIFactory = nullptr;
            pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), &pIDXGIFactory);

            DXGI_SWAP_CHAIN_DESC desc = {};
            m_gfxres_.m_pSwapChain->GetDesc(&desc);

            const auto& hWnd = desc.OutputWindow;

            static UINT flag = 0u;

            static constexpr auto magic_value = static_cast<UINT>(DXGI_MWA_NO_ALT_ENTER);

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

        void ClearBuffer_(const float red, const float green, const float blue)
        {
            const std::array<float, 4> colors{ red, green, blue, 1.0f };

            m_gfxres_.m_pImmediateContext->ClearRenderTargetView(m_gfxres_.m_pTarget.Get(), colors.data());
            m_gfxres_.m_pImmediateContext->ClearDepthStencilView(m_gfxres_.m_pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
        }


    private:
        GfxResource m_gfxres_;

        [[maybe_unused]] ::DirectX::XMMATRIX m_projection_;
        [[maybe_unused]] ::DirectX::XMMATRIX m_camera_;

        const decltype(SizeInfo::width)  m_width_;
        const decltype(SizeInfo::height) m_height_;

        static constexpr auto s_msaaQuality_ = 8u;

        static constexpr bool s_rasterizationEnabled_ = true;
    };
}