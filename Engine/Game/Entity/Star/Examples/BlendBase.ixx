module;

#include <DirectXMath.h>

export module StarRealm.Entity.Star.BlendBase;

import FatPound.Util.Color;

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


	protected:


	private:
	};
}