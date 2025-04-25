module;

export module StarRealm.Entity.Star.Style.Color;

export import :Blend;
export import :Single;
export import :Multi;

import :Base;

import std;

export namespace starrealm::entity::star_style
{
    template <typename T>
    concept Color = std::derived_from<T, color::Base<T>>;
}

module : private;
