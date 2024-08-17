module;

export module StarRealm.Entity.Star.Style.Effect;

import :Base;

import StarRealm.Entity.Star.Style.Base;

export import :Blend;
export import :Color.Single;
export import :Color.Multi;

export namespace starrealm::entity::star::style
{
    template <class C>
    concept Effect = Style<C, effect::Base_>;
}