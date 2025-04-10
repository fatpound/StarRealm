module;

export module StarRealm.Entity.Star.Style.Base;

import std;

export namespace starrealm::entity::star
{
    template
    <
        typename T,
        template <typename S> typename StyleBase_
    >
    concept Style = ::std::derived_from<T, StyleBase_<T>>;
}

module : private;
