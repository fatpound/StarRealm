module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

export module FatPound.Util.CameraController;

import FatPound.Util.Camera;
import FatPound.Win32;

export namespace fatpound::util
{
	class CameraController final
	{
	public:
		CameraController(Camera& camera, NAMESPACE_IO::Mouse& mouse, const NAMESPACE_IO::Keyboard& keyboard);

		CameraController() = delete;
		CameraController(const CameraController& src) = delete;
		CameraController& operator = (const CameraController& src) = delete;

		CameraController& operator = (CameraController&& src) = delete;
		CameraController(CameraController&& src) = delete;
		~CameraController() noexcept = default;


	public:
		void Update();


	protected:


	private:
		::DirectX::XMFLOAT2 last_position_;

		Camera& camera_;

		NAMESPACE_IO::Mouse& mouse_;
		const NAMESPACE_IO::Keyboard& keyboard_;

		bool engaged_ = false;

		static constexpr float zoom_increment_ = 0.01f;
	};
}