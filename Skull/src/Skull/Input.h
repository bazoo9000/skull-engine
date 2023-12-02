#pragma once
// il facem sa mearga pentru orice window din orice OS
// il facem static

#include "Core.h"

namespace Skull 
{
	class SKULL_API Input 
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0; // baiatul principal care ne permite sa definim pe orice platforma
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
	
	private:
		static Input* s_Instance;
	};
}