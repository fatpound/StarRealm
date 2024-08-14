module;

export module StarRealm.Entity.Star.Style.Base;

import std;

export namespace starrealm::entity::star
{
    template
    <
        class C,
        template <class S> class StyleBase_
    >
    concept Style = std::derived_from<C, StyleBase_<C>>;
}