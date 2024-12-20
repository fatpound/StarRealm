module;

export module StarRealm.Entity.Star.Style.Type;

import StarRealm.Entity.Star.Style.Base;

export import :Base;

export import :Filled;
export import :Hollow;

export namespace starrealm::entity::star::style
{
    template <typename T>
    concept Type = Style<T, type::Base_>;
}

module : private;