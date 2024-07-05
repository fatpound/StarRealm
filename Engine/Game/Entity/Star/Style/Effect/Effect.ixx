module;

export module StarRealm.Entity.Star.Style:Effect;

export import StarRealm.Entity.Star.Style.Effect.BlendBase;
export import StarRealm.Entity.Star.Style.Effect.SingleColorBase;
export import StarRealm.Entity.Star.Style.Effect.MultiColorBase;

import std;

export namespace fatpound::starrealm::entity::star
{
    template <class C>
    concept Effect =
        std::same_as<C, BlendBase>
        or
        std::same_as<C, SingleColorBase>
        or
        std::same_as<C, MultiColorBase>;
}