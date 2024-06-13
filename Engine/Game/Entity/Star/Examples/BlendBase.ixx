module;

#include <DirectXMath.h>

export module StarRealm.Entity.Star.BlendBase;

import StarRealm.Entity.Star;

import FatPound.Util.Color;

import std;

export namespace fatpound::starrealm::entity::star
{
	class BlendBase final
	{
	public:
		struct Vertex final
		{
			DirectX::XMFLOAT3 pos;

			fatpound::util::Color color;
		};


	public:
		template <bool with_centre = true>
		static auto GenerateVertices(DirectX::XMFLOAT2 radius, DirectX::XMFLOAT3 position, std::size_t flare_count)
		{
			std::vector<BlendBase::Vertex> vertices;

			vertices.reserve(flare_count * 2u + 1u);

			std::minstd_rand mrng(std::random_device{}());
			std::uniform_int_distribution<int> rgb_dist(0, 255);

			// IDEA: Star::Make could be a coroutine

			std::vector<DirectX::XMFLOAT3> star_vertices;

			if constexpr (with_centre)
			{
				star_vertices = Star::MakeWithCentre(radius, position, flare_count);
			}
			else
			{
				star_vertices = Star::Make(radius, position, flare_count);
			}

			for (const auto& vertex : star_vertices)
			{
				vertices.emplace_back(
					vertex,
					fatpound::util::Color(
						static_cast<unsigned char>(rgb_dist(mrng)),
						static_cast<unsigned char>(rgb_dist(mrng)),
						static_cast<unsigned char>(rgb_dist(mrng)),
						255
					)
				);
			}

			return vertices;
		}


	protected:


	private:
	};
}