module;

export module StarRealm.Entity.Star.Style.Effect;

export import :Base;

import StarRealm.Entity.Star.Style.Base;

export import :Blend;
export import :Color.Single;
export import :Color.Multi;

export namespace starrealm::entity::star::style
{
    template <typename T>
    concept Effect = Style<T, effect::Base_>;
}

module : private;