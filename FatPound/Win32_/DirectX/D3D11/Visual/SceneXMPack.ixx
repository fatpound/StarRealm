module;

#include <FatWin32_Settings.hpp>

#include <DirectXMath.h>

export module FatPound.Win32.D3D11.Visual.SceneXMPack;

import FatPound.Util;

import std;

export namespace fatpound::win32::d3d11::visual
{
    class SceneXMPack final
    {
    public:
        auto GetCameraXM() const noexcept -> ::DirectX::XMMATRIX
        {
            return m_camera_;
        }
        auto GetProjectionXM() const noexcept -> ::DirectX::XMMATRIX
        {
            return m_projection_;
        }

        void SetCameraXM(const ::DirectX::XMMATRIX& camera) noexcept
        {
            m_camera_ = camera;
        }
        void SetProjectionXM(const ::DirectX::XMMATRIX& projection) noexcept
        {
            m_projection_ = projection;
        }


    protected:


    private:
        ::DirectX::XMMATRIX m_camera_;
        ::DirectX::XMMATRIX m_projection_;
    };
}