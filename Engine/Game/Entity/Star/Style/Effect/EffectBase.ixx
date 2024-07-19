module;

export module StarRealm.Entity.Star.Style.EffectBase;

import std;

export namespace fatpound::starrealm::entity::star
{
    template <class C>
    struct __declspec(empty_bases) StyleEffect
    {

    };

    template <class C>
    concept Effect = std::derived_from<C, StyleEffect<C>>;
}