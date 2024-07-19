module;

export module StarRealm.Entity.Star.Style.TypeBase;

import std;

export namespace fatpound::starrealm::entity::star
{
    template <class C>
    struct __declspec(empty_bases) StyleType
    {

    };

    template <class C>
    concept Type = std::derived_from<C, StyleType<C>>;
}