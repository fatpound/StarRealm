module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Graphics.Resource;

import std;

export namespace fatpound::win32::d3d11
{
    struct GfxResource final
    {
        ::Microsoft::WRL::ComPtr<ID3D11Device>           m_pDevice           = nullptr;
        ::Microsoft::WRL::ComPtr<IDXGISwapChain>         m_pSwapChain        = nullptr;
        ::Microsoft::WRL::ComPtr<ID3D11DeviceContext>    m_pImmediateContext = nullptr;
        ::Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pTarget           = nullptr;
        ::Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDSV              = nullptr;
    };
}  