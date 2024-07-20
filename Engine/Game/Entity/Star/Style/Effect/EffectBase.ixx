module;

export module StarRealm.Entity.Star.Style.EffectBase;

import StarRealm.Entity.Star.StyleBase;

import std;

export namespace starrealm::entity::star
{
    template <class C>
    struct __declspec(empty_bases) StyleEffect
    {

    };

    template <class C>
    concept Effect = Style<C, StyleEffect>;
}