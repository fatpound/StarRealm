module;

export module StarRealm.Entity.Star.Style.Type;

import StarRealm.Entity.Star.Style.Base;

import :Base;

export import :Filled;
export import :Hollow;

export namespace starrealm::entity::star::style
{
    template <class C>
    concept Type = Style<C, type::Base_>;
}