module;

#include "../../FatWin32_.hpp"

#include <DirectXMath.h>
#include <wrl.h>

export module D3D11Graphics;

export import <d3d11.h>;
export import <d3dcompiler.h>;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#ifdef NDEBUG
import std.core;
import std.memory;
#else
import <cmath>;
import <cstdint>;
import <cstdlib>;
/**/
import <vector>;
import <string>;
import <memory>;
//
import <array>;
import <sstream>;
import <stdexcept>;
#endif // NDEBUG
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32::d3d11
{
    class Graphics final
    {
        friend class Bindable;

    public:
        Graphics(HWND hWnd, std::size_t width, std::size_t height);

        Graphics() = delete;
        Graphics(const Graphics& src) = delete;
        Graphics& operator = (const Graphics& src) = delete;
        Graphics(Graphics&& src) = delete;
        Graphics& operator = (Graphics&& src) = delete;
        ~Graphics() = default;


    public:
        DirectX::XMMATRIX GetProjectionXM() const noexcept;
        DirectX::XMMATRIX GetCameraXM() const noexcept;

        void BeginFrame() noexcept;
        void EndFrame();
        void DrawIndexed(UINT count) noexcept(IN_RELEASE);

        void SetProjection(const DirectX::XMMATRIX& projection) noexcept;
        void SetCamera(const DirectX::XMMATRIX& camera) noexcept;


    protected:


    private:
        void ClearBuffer_(const float& red, const float& green, const float& blue) noexcept;


    private:
        DirectX::XMMATRIX projection_;
        DirectX::XMMATRIX camera_;

        Microsoft::WRL::ComPtr<ID3D11Device>              pDevice_    = nullptr;
        Microsoft::WRL::ComPtr<IDXGISwapChain>            pSwapChain_ = nullptr;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext>       pContext_   = nullptr;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView>    pTarget_    = nullptr;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView>    pDSV_       = nullptr;

        const std::size_t screen_width_;
        const std::size_t screen_height_;
    };
}