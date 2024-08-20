module;

#include <DirectXMath.h>

export module FatPound.Win32.D3D11.Pipeline.StaticBindableVec;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Pipeline.Element;

import std;

export namespace fatpound::win32::d3d11::pipeline
{
    template <typename T>
    class StaticBindableVec
    {
    public:
        explicit StaticBindableVec() = default;
        explicit StaticBindableVec(const StaticBindableVec& src) = delete;
        explicit StaticBindableVec(StaticBindableVec&& src) = delete;

        StaticBindableVec& operator = (const StaticBindableVec& src) = delete;
        StaticBindableVec& operator = (StaticBindableVec&& src) = delete;
        ~StaticBindableVec() noexcept = default;


    protected:
        static auto& GetStaticBinds_() noexcept
        {
            return m_static_binds_;
        }

        static bool IsStaticInitialized_() noexcept(IN_RELEASE)
        {
            return not m_static_binds_.empty();
        }

        static void AddStaticBind_(std::unique_ptr<Bindable> bind) noexcept(IN_RELEASE)
        {
            assert("*Must* use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(element::IndexBuffer));

            m_static_binds_.push_back(std::move(bind));
        }


    protected:
        inline static std::vector<std::unique_ptr<Bindable>> m_static_binds_ = {};


    private:
    };
}