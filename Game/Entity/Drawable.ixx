module;

#ifdef FATLIB_BUILDING_WITH_MSVC
#include <_macros/Namespaces.hxx>

#include <DirectXMath.h>

#include <cassert>
#endif

export module StarRealm.Entity.Drawable;

#ifdef FATLIB_BUILDING_WITH_MSVC

import <d3d11.h>;

import FatPound;

import std;

namespace dx = DirectX;

export namespace starrealm::entity
{
    /// @brief Abstract base class representing an object that can be drawn using Direct3D 11, supporting bindable resources and transformation
    ///
    class Drawable
    {
    public:
        using BindablePtr_t = std::unique_ptr<FATSPACE_D3D11::pipeline::Bindable>;
        using BindableVec_t = std::vector<BindablePtr_t>;


    public:
        explicit Drawable()                    = default;
        explicit Drawable(const Drawable&)     = delete;
        explicit Drawable(Drawable&&) noexcept = delete;

        auto operator = (const Drawable&)     -> Drawable& = delete;
        auto operator = (Drawable&&) noexcept -> Drawable& = delete;
        virtual ~Drawable() noexcept                       = default;


    public:
        virtual auto GetTransformXM() const noexcept -> dx::XMMATRIX = 0;

        virtual void Update(const float delta_time) noexcept = 0;

        virtual void Draw(ID3D11DeviceContext* const pImmediateContext) const final
        {
            for (auto& bindable : m_binds_)
            {
                bindable->Bind(pImmediateContext);
            }

            for (auto& static_bindable : this->GetStaticBinds_())
            {
                static_bindable->Bind(pImmediateContext);
            }

            pImmediateContext->DrawIndexed(m_pCIndexBuffer_->GetCount(), 0U, 0);
        }

        
    protected:
        virtual void AddBind_(std::unique_ptr<FATSPACE_D3D11::pipeline::Bindable> bind) final
        {
            assert(typeid(*bind) not_eq typeid(FATSPACE_D3D11::pipeline::IndexBuffer));

            m_binds_.push_back(std::move<>(bind));
        }
        virtual void AddIndexBuffer_(std::unique_ptr<FATSPACE_D3D11::pipeline::IndexBuffer> idxbuf) final
        {
            assert(m_pCIndexBuffer_ == nullptr);

            m_pCIndexBuffer_ = idxbuf.get();

            m_binds_.push_back(std::move<>(idxbuf));
        }


    protected:
        const FATSPACE_D3D11::pipeline::IndexBuffer* m_pCIndexBuffer_{};


    private:
        virtual auto GetStaticBinds_() const -> const BindableVec_t& = 0;


    private:
        BindableVec_t m_binds_;
    };
}

#endif

module : private;
