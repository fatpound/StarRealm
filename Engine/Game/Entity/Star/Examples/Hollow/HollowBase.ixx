module;

export module StarRealm.Entity.Star.HollowBase;

import std;

export namespace fatpound::starrealm::entity::star
{
	class HollowBase final
	{
	public:
		static auto GenerateIndices(std::size_t vertex_count) -> std::vector<unsigned short int>
		{
			std::vector<unsigned short int> indices;
			indices.reserve(vertex_count + 1u);

			for (std::size_t i = 0u; i < vertex_count; ++i)
			{
				indices.emplace_back(static_cast<unsigned short int>(i));
			}

			indices.emplace_back(static_cast<unsigned short int>(0u));

			return indices;
		}


	protected:


	private:
	};
}