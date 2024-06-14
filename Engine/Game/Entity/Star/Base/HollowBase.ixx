module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

export module StarRealm.Entity.Star.HollowBase;

import FatPound.Win32.Direct3D11.Graphics;
import FatPound.Win32.Direct3D11.Pipeline;

import std;

export namespace fatpound::starrealm::entity::star
{
	class HollowBase final
	{
	public:
		template <class Base>
		static void Init()
		{
			Base::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::Topology>(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP));
		}

		static auto GenerateIndices(std::size_t vertex_count) -> std::vector<unsigned short int>;


	protected:


	private:
	};
}