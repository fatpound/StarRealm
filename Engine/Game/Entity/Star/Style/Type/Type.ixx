module;

export module StarRealm.Entity.Star.Style:Type;

export import StarRealm.Entity.Star.Style.Type.FilledBase;
export import StarRealm.Entity.Star.Style.Type.HollowBase;

import std;

export namespace fatpound::starrealm::entity::star
{
    template <class C>
    concept Type =
        std::same_as<C, FilledBase>
        or
        std::same_as<C, HollowBase>;
}