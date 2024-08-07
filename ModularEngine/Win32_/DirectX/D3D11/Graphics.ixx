module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Graphics;

import FatPound.Win32.D3D11.Pipeline.System;
import FatPound.Win32.D3D11.Factory;

import FatPound.Math;

import std;

namespace fatpound::win32::d3d11::pipeline
{
    class Bindable;
}

export namespace fatpound::win32::d3d11
{
    class Graphics final
    {
        friend pipeline::Bindable;

    public:
        struct SizeInfo final
        {
            unsigned int width;
            unsigned int height;
        };


    public:
        Graphics(HWND hWnd, const SizeInfo& dimensions);

        Graphics() = delete;
        Graphics(const Graphics& src) = delete;
        Graphics& operator = (const Graphics& src) = delete;

        Graphics(Graphics&& src) = delete;
        Graphics& operator = (Graphics&& src) = delete;
        ~Graphics() noexcept = default;


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

        auto GetProjectionXM() const noexcept -> ::DirectX::XMMATRIX;
        auto GetCameraXM()     const noexcept -> ::DirectX::XMMATRIX;

        void BeginFrame() noexcept;
        void EndFrame();
        void DrawIndexed(UINT count) noexcept(IN_RELEASE);

        void SetProjectionXM(const ::DirectX::XMMATRIX& projection) noexcept;
        void SetCameraXM(const ::DirectX::XMMATRIX& camera) noexcept;


    protected:


    private:
        void ToggleAltEnterMode_();

        void ClearBuffer_(const float& red, const float& green, const float& blue) noexcept;


    private:
        ::Microsoft::WRL::ComPtr<ID3D11Device>           m_pDevice_           = nullptr;
        ::Microsoft::WRL::ComPtr<IDXGISwapChain>         m_pSwapChain_        = nullptr;
        ::Microsoft::WRL::ComPtr<ID3D11DeviceContext>    m_pImmediateContext_ = nullptr;
        ::Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pTarget_           = nullptr;
        ::Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDSV_              = nullptr;

        ::DirectX::XMMATRIX m_projection_;
        ::DirectX::XMMATRIX m_camera_;

        const decltype(SizeInfo::width)  m_width_;
        const decltype(SizeInfo::height) m_height_;

        static constexpr auto s_msaaQuality_ = 8u;

        static constexpr bool s_rasterizationEnabled_ = true;
    };
}