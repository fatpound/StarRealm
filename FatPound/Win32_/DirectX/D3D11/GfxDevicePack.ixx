module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Graphics.DevicePack;

import std;

export namespace fatpound::win32::d3d11
{
    struct GfxDevicePack final
    {
        ::Microsoft::WRL::ComPtr<ID3D11Device>        m_pDevice           = nullptr;
        ::Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pImmediateContext = nullptr;
    };
}