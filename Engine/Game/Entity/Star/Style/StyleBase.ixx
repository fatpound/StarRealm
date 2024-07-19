module;

export module StarRealm.Entity.Star.StyleBase;

import std;

export namespace fatpound::starrealm::entity::star
{
    template <
        class C,
        template <class> class StyleBase
    >
    concept Style = std::derived_from<C, StyleBase<C>>;
}