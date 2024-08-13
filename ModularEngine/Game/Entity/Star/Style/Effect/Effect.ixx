module;

export module StarRealm.Entity.Star.Style:Effect;

export import StarRealm.Entity.Star.StyleBase;

export import StarRealm.Entity.Star.Style.EffectBase;

export import StarRealm.Entity.Star.Style.Effect.Blend;
export import StarRealm.Entity.Star.Style.Effect.SingleColor;
export import StarRealm.Entity.Star.Style.Effect.MultiColor;

export namespace starrealm::entity::star::style
{
    template <class C>
    concept Effect = Style<C, EffectBase_>;
}