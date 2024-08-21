module;

#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

export module FatPound.Util.CameraController;

import FatPound.Util.Camera;
import FatPound.Win32.IO;

export namespace fatpound::util
{
	class CameraController final
	{
	public:
		explicit CameraController(Camera& camera, NAMESPACE_IO::Mouse& mouse, const NAMESPACE_IO::Keyboard& keyboard) noexcept;

		explicit CameraController() = delete;
		explicit CameraController(const CameraController& src) = delete;
		explicit CameraController(CameraController&& src) = delete;

		CameraController& operator = (const CameraController& src) = delete;
		CameraController& operator = (CameraController&& src) = delete;
		~CameraController() noexcept = default;


	public:
		auto operator <=> (const CameraController& rhs) const = delete;
		bool operator ==  (const CameraController& rhs) const = delete;


	public:
		void Update() noexcept;


	protected:


	private:
		::DirectX::XMFLOAT2 last_position_{};

		Camera& camera_;

		NAMESPACE_IO::Mouse& mouse_;
		const NAMESPACE_IO::Keyboard& keyboard_;

		bool engaged_ = false;

		static constexpr float s_zoomIncrement_ = 0.1f;
	};
}