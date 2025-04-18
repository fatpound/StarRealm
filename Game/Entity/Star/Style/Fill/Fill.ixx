module;

export module StarRealm.Entity.Star.Style.Fill;

export import :Filled;
export import :Hollow;

import :Base;

import std;

export namespace starrealm::entity::star_style
{
    template <typename T>
    concept Fill = ::std::derived_from<T, fill::Base<T>>;
}

module : private;
