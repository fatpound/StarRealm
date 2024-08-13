module;

export module StarRealm.Entity.Star.Style.TypeBase;

import StarRealm.Entity.Star.StyleBase;

export namespace starrealm::entity::star
{
    template <class C>
    struct __declspec(empty_bases) StyleType_
    {

    };

    template <class C>
    concept Type = Style<C, StyleType_>;
}