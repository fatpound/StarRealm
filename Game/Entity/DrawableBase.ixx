module;

#ifdef FATLIB_BUILDING_WITH_MSVC
#include <_macros/Namespaces.hxx>

#include <cassert>
#endif

export module StarRealm.Entity.DrawableBase;

#ifdef FATLIB_BUILDING_WITH_MSVC

import StarRealm.Entity.Drawable;

import FatPound;

import std;

export namespace starrealm::entity
{
    /// @brief A template base class for drawable objects that manages static index buffers and bindable resources
    /// 
    /// @tparam CRTP type
    /// 
    template <typename T>
    class DrawableBase : public Drawable
    {
    public:
        explicit DrawableBase()                        = default;
        explicit DrawableBase(const DrawableBase&)     = delete;
        explicit DrawableBase(DrawableBase&&) noexcept = delete;

        auto operator = (const DrawableBase&)     -> DrawableBase& = delete;
        auto operator = (DrawableBase&&) noexcept -> DrawableBase& = delete;
        virtual ~DrawableBase() noexcept override                  = default;


    public:
        static auto IsStaticInitialized_() noexcept -> bool
        {
            return not tl_bindable_vec_.empty();
        }
        static void AddStaticBind_(std::unique_ptr<FATSPACE_D3D11::pipeline::Bindable> bind)
        {
            assert(typeid(*bind) not_eq typeid(FATSPACE_D3D11::pipeline::IndexBuffer));

            tl_bindable_vec_.push_back(std::move<>(bind));
        }


    protected:
        virtual void AddStaticIndexBuffer_(std::unique_ptr<FATSPACE_D3D11::pipeline::IndexBuffer> idxbuf) final
        {
            assert(m_pCIndexBuffer_ == nullptr);

            m_pCIndexBuffer_ = idxbuf.get();

            tl_bindable_vec_.push_back(std::move<>(idxbuf));
        }
        virtual void SetIndexBufferFromStatic_() noexcept final
        {
            assert(m_pCIndexBuffer_ == nullptr);
        
            for (const auto& bind : GetStaticBinds_())
            {
                const auto* const ptr = dynamic_cast<FATSPACE_D3D11::pipeline::IndexBuffer*>(bind.get());
        
                if (ptr not_eq nullptr)
                {
                    m_pCIndexBuffer_ = ptr;
        
                    return;
                }
            }
        
            assert(m_pCIndexBuffer_ not_eq nullptr);
        }


    private:
        virtual auto GetStaticBinds_() const noexcept -> const BindableVec_t& override
        {
            return tl_bindable_vec_;
        }


    private:
        inline static thread_local std::vector<BindablePtr_t> tl_bindable_vec_;
    };
}

#endif

module : private;
