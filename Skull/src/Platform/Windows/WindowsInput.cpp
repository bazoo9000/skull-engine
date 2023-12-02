#include "skpch.h"
#include "WindowsInput.h"

#include "Skull/Application.h"
#include <GLFW/glfw3.h>

namespace Skull 
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode) 
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl() 
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl() 
	{
		auto[x, y] = GetMousePositionImpl(); // merge doar din c++17 in sus
		return x;
	}

	float WindowsInput::GetMouseYImpl() 
	{
		auto[x, y] = GetMousePositionImpl(); // merge doar din c++17 in sus
		return y;
	}
}