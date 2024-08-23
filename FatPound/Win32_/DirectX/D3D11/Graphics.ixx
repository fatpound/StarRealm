module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "D3DCompiler")

export module FatPound.Win32.D3D11.Graphics;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import FatPound.Win32.D3D11.Pipeline;
import FatPound.Win32.D3D11.Visual;
import FatPound.Win32.D3D11.Factory;

import FatPound.Math;
import FatPound.Util;

import std;

namespace dx = DirectX;
namespace wrl = Microsoft::WRL;

using NAMESPACE_UTIL::Color;
using NAMESPACE_UTIL::ScreenSizeInfo;

export namespace fatpound::win32::d3d11
{
    template <bool Framework = false>
    class Graphics final
    {
    public:
        explicit Graphics(const HWND hWnd, const ScreenSizeInfo& dimensions)
            :
            m_dimensions_{ dimensions }
        {
            InitCommon_(hWnd);
            
            pipeline::system::DepthStencil::SetDefault(m_res_pack_);

            if constexpr (s_rasterizationEnabled_)
            {
                pipeline::system::Rasterizer::SetDefault(m_res_pack_);
            }
        }
        explicit Graphics(const HWND hWnd, const ScreenSizeInfo& dimensions) requires(Framework)
            :
            m_dimensions_{ dimensions }
        {
            InitCommon_(hWnd);

            pipeline::system::ShaderResource::SetDefault<s_msaaQuality_>(m_res_pack_, m_dimensions_);
            pipeline::system::Sampler::SetDefault(m_res_pack_);

            m_res_pack_.m_pSysBuffer = static_cast<Color*>(_aligned_malloc(sizeof(Color) * m_dimensions_.m_width * m_dimensions_.m_height, 16u));

            if (m_res_pack_.m_pSysBuffer == nullptr) [[unlikely]]
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
            if (m_res_pack_.m_pSysBuffer != nullptr) [[likely]]
            {
                _aligned_free(m_res_pack_.m_pSysBuffer);
                m_res_pack_.m_pSysBuffer = nullptr;
            }

            if (m_res_pack_.m_pImmediateContext != nullptr) [[likely]]
            {
                m_res_pack_.m_pImmediateContext->ClearState();
            }
        }


    public:
        auto operator <=> (const Graphics& rhs) const = delete;
        bool operator ==  (const Graphics& rhs) const = delete;


    public:
        auto GetViewXM() noexcept -> visual::ViewXM&
        {
            return m_viewXM_;
        }

        auto GetDevice() noexcept -> ID3D11Device*
        {
            return m_res_pack_.m_pDevice.Get();
        }
        auto GetImmediateContext() noexcept -> ID3D11DeviceContext*
        {
            return m_res_pack_.m_pImmediateContext.Get();
        }

        auto GetCameraXM()     const noexcept -> ::DirectX::XMMATRIX requires(not Framework)
        {
            return GetViewXM().GetCameraXM();
        }
        auto GetProjectionXM() const noexcept -> ::DirectX::XMMATRIX requires(not Framework)
        {
            return GetViewXM().GetProjectionXM();
        }

        void SetCameraXM(const ::DirectX::XMMATRIX& camera)         noexcept requires(not Framework)
        {
            GetViewXM().SetCameraXM(camera);
        }
        void SetProjectionXM(const ::DirectX::XMMATRIX& projection) noexcept requires(not Framework)
        {
            GetViewXM().SetProjectionXM(projection);
        }

        void BeginFrame() noexcept
        {
            ClearBuffer_(0.0f, 0.0f, 0.0f);
        }
        void BeginFrame() noexcept requires(Framework)
        {
            std::memset(static_cast<void*>(m_res_pack_.m_pSysBuffer), 0u, sizeof(Color) * m_dimensions_.m_width * m_dimensions_.m_height);
        }
        void EndFrame()
        {
            const auto hr = m_res_pack_.m_pSwapChain->Present(1u, 0u);

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::runtime_error("The Graphics Device Failed to Present/Draw!");
            }
        }
        void EndFrame() requires(Framework)
        {
            HRESULT hr = GetImmediateContext()->Map(
                m_res_pack_.m_pSysBufferTexture.Get(),
                0u,
                D3D11_MAP_WRITE_DISCARD,
                0u,
                &m_res_pack_.m_mappedSysBufferTexture
            );

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::exception("Could NOT Map the ImmediateContext!");
            }

            Color* pDst = static_cast<Color*>(m_res_pack_.m_mappedSysBufferTexture.pData);

            const auto& dstPitch = m_res_pack_.m_mappedSysBufferTexture.RowPitch / sizeof(Color);
            const auto& srcPitch = m_dimensions_.m_width;
            const auto& rowBytes = srcPitch * sizeof(Color);

            for (auto y = 0u; y < m_dimensions_.m_height; ++y)
            {
                std::memcpy(
                    static_cast<void*>(&pDst[y * dstPitch]),
                    static_cast<void*>(&m_res_pack_.m_pSysBuffer[y * srcPitch]),
                    rowBytes
                );
            }

            GetImmediateContext()->Unmap(m_res_pack_.m_pSysBufferTexture.Get(), 0u);
            GetImmediateContext()->Draw(6u, 0u);

            hr = m_res_pack_.m_pSwapChain->Present(1u, 0u);

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::exception("SwapChain could NOT Present and Draw its contents!");;
            }
        }

        void PutPixel(int x, int y, Color color) noexcept requires(Framework)
        {
            assert(x >= 0);
            assert(x < static_cast<int>(m_dimensions_.m_width));
            assert(y >= 0);
            assert(y < static_cast<int>(m_dimensions_.m_height));

            m_res_pack_.m_pSysBuffer[m_dimensions_.m_width * y + x] = color;
        }


    public:
        template <NAMESPACE_MATH::Number N>
        auto GetWidth() const noexcept
        {
            return static_cast<N>(m_dimensions_.m_width);
        }

        template <NAMESPACE_MATH::Number N>
        auto GetHeight() const noexcept
        {
            return static_cast<N>(m_dimensions_.m_height);
        }


    protected:


    private:
        struct FullScreenQuad_ final
        {
            struct Vertex final
            {
                float x;
                float y;
                float z;

                float u;
                float v;
            };

            inline static constexpr std::vector<Vertex> vertices =
            {
                Vertex{ -1.0f,  1.0f,  0.5f,  0.0f,  0.0f },
                Vertex{  1.0f,  1.0f,  0.5f,  1.0f,  0.0f },
                Vertex{  1.0f, -1.0f,  0.5f,  1.0f,  1.0f },
                Vertex{ -1.0f,  1.0f,  0.5f,  0.0f,  0.0f },
                Vertex{  1.0f, -1.0f,  0.5f,  1.0f,  1.0f },
                Vertex{ -1.0f, -1.0f,  0.5f,  0.0f,  1.0f }
            };
        };


    private:
        void InitCommon_(const HWND hWnd)
        {
            {
                const auto& scdesc = factory::DeviceAndSwapChain::CreateDESC<s_msaaQuality_>(hWnd, m_dimensions_);
                factory::DeviceAndSwapChain::Create(m_res_pack_, scdesc);
            }

            ToggleAltEnterMode_();

            pipeline::system::RenderTarget::SetDefault<s_msaaQuality_, Framework>(m_res_pack_, m_dimensions_);
            pipeline::system::Viewport::SetDefault(m_res_pack_, m_dimensions_);
        }
        void InitFramework_() requires(Framework)
        {
            std::vector<std::unique_ptr<NAMESPACE_PIPELINE::Bindable>> binds;

            InitFrameworkBinds_(binds);

            const auto pImmediateContext = GetImmediateContext();

            for (auto& sbind : binds)
            {
                sbind->Bind(pImmediateContext);
            }
        }
        void InitFrameworkBinds_(auto& binds) requires(Framework)
        {
            auto pvs = std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexShader>(GetDevice(), L"VSFrameBuffer.cso");
            auto pvsbc = pvs->GetBytecode();

            binds.push_back(std::move(pvs));
            binds.push_back(std::make_unique<NAMESPACE_PIPELINE::element::PixelShader>(GetDevice(), L"PSFrameBuffer.cso"));
            binds.push_back(std::make_unique<NAMESPACE_PIPELINE::element::VertexBuffer>(GetDevice(), FullScreenQuad_::vertices));
            binds.push_back(std::make_unique<NAMESPACE_PIPELINE::element::Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

            {
                const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
                {
                    {
                        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
                    }
                };

                binds.push_back(std::make_unique<NAMESPACE_PIPELINE::element::InputLayout>(GetDevice(), ied, pvsbc));
            }
        }

        void ToggleAltEnterMode_()
        {
            ::wrl::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
            m_res_pack_.m_pDevice->QueryInterface(__uuidof(IDXGIDevice), &pDXGIDevice);

            ::wrl::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
            pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), &pDXGIAdapter);

            ::wrl::ComPtr<IDXGIFactory> pIDXGIFactory = nullptr;
            pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), &pIDXGIFactory);

            DXGI_SWAP_CHAIN_DESC desc = {};
            m_res_pack_.m_pSwapChain->GetDesc(&desc);

            const auto& hWnd = desc.OutputWindow;

            static UINT flag = 0u;

            static constexpr auto magic_value = static_cast<UINT>(DXGI_MWA_NO_ALT_ENTER);

            if ((flag bitand magic_value) not_eq 0u)
            {
                flag and_eq ~magic_value;
            }
            else
            {
                flag or_eq magic_value;
            }

            pIDXGIFactory->MakeWindowAssociation(hWnd, flag);
        }

        void ClearBuffer_(const float red, const float green, const float blue)
        {
            const std::array<float, 4> colors{ red, green, blue, 1.0f };

            m_res_pack_.m_pImmediateContext->ClearRenderTargetView(m_res_pack_.m_pTarget.Get(), colors.data());
            m_res_pack_.m_pImmediateContext->ClearDepthStencilView(m_res_pack_.m_pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
        }


    private:
        GraphicsResourcePack m_res_pack_;

        visual::ViewXM m_viewXM_;

        const ScreenSizeInfo m_dimensions_;

        static constexpr auto s_msaaQuality_ = std::conditional_t<Framework, std::integral_constant<UINT, 1u>, std::integral_constant<UINT, 8u>>::value;

        static constexpr auto s_rasterizationEnabled_ = std::conditional_t<Framework, std::false_type, std::true_type>::value;
    };
}