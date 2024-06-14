module;

#include "../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

export module StarRealm.Entity.Star.BlendBase;

import StarRealm.Entity.Star;

import FatPound.Win32.Direct3D11.Graphics;
import FatPound.Win32.Direct3D11.Pipeline;
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

		template <class Base>
		static void Init(NAMESPACE_D3D11::Graphics& gfx)
		{
			auto pvs = std::make_unique<NAMESPACE_PIPELINE::VertexShader>(gfx, L"VSColorBlend.cso");
			auto pvsbc = pvs->GetBytecode();
			Base::AddStaticBind_(std::move(pvs));
			Base::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::PixelShader>(gfx, L"PSColorBlend.cso"));

			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "Color",    0, DXGI_FORMAT_R8G8B8A8_UNORM,  0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};

			Base::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::InputLayout>(gfx, ied, pvsbc));
		}


	protected:


	private:
	};
}