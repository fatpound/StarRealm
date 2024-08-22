module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Graphics.ResourcePack;

import FatPound.Util;

import std;

export namespace fatpound::win32::d3d11
{
    struct GraphicsResourcePack final
    {
        ::Microsoft::WRL::ComPtr<IDXGISwapChain>         m_pSwapChain        = nullptr;
        ::Microsoft::WRL::ComPtr<ID3D11Device>           m_pDevice           = nullptr;
        ::Microsoft::WRL::ComPtr<ID3D11DeviceContext>    m_pImmediateContext = nullptr;
        ::Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pTarget           = nullptr;
        ::Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDSV              = nullptr;

        [[maybe_unused]] ::Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pSysBufferTexture = nullptr;

        [[maybe_unused]] D3D11_MAPPED_SUBRESOURCE m_mappedSysBufferTexture = {};

        [[maybe_unused]] NAMESPACE_UTIL::Color* m_pSysBuffer = nullptr;
    };
}