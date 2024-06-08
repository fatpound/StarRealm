module;

#include "../../FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

export module Direct3D11.Graphics;

import std;

namespace fatpound::win32::d3d11::pipeline
{
    class Bindable;
}

export namespace fatpound::win32::d3d11
{
    class Graphics final
    {
        friend class pipeline::Bindable;

    public:
        Graphics(HWND hWnd, std::size_t width, std::size_t height);

        Graphics() = delete;
        Graphics(const Graphics& src) = delete;
        Graphics& operator = (const Graphics& src) = delete;
        Graphics(Graphics&& src) = delete;
        Graphics& operator = (Graphics&& src) = delete;
        ~Graphics() = default;


    public:
        auto GetProjectionXM() const noexcept -> DirectX::XMMATRIX;
        auto GetCameraXM()     const noexcept -> DirectX::XMMATRIX;

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

        const std::size_t width_;
        const std::size_t height_;
    };
}