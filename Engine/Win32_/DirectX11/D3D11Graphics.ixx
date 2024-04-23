module;

#include "../FatWin32_.hpp"

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>

export module D3D11Graphics;

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
#endif // NDEBUG

namespace fatpound::starrealm
{
    class Bindable;
}

export namespace fatpound::dx11
{
    class D3DGraphics final
    {
        friend class fatpound::starrealm::Bindable;

    public:
        D3DGraphics(HWND hWnd, std::size_t width, std::size_t height);

        D3DGraphics() = delete;
        D3DGraphics(const D3DGraphics& src) = delete;
        D3DGraphics(D3DGraphics&& src) = delete;
        D3DGraphics& operator = (const D3DGraphics& src) = delete;
        D3DGraphics& operator = (D3DGraphics&& src) = delete;
        ~D3DGraphics() = default;


    public:
        DirectX::XMMATRIX GetProjectionXM() const noexcept;
        DirectX::XMMATRIX GetCameraXM() const noexcept;

        void BeginFrame(float red, float green, float blue);
        void EndFrame();
        void DrawIndexed(UINT count) noexcept(!IS_DEBUG);

        void SetProjection(const DirectX::XMMATRIX& projection) noexcept;
        void SetCamera(const DirectX::XMMATRIX& camera) noexcept;


    protected:


    private:
        void ClearBuffer_(float red, float green, float blue) noexcept;


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
