module;

export module StarRealm.Entity.Star.Style:Type;

export import StarRealm.Entity.Star.StyleBase;

export import StarRealm.Entity.Star.Style.TypeBase;

export import StarRealm.Entity.Star.Style.Type.Filled;
export import StarRealm.Entity.Star.Style.Type.Hollow;

export namespace starrealm::entity::star::style
{
    template <class C>
    concept Type = Style<C, TypeBase_>;
}