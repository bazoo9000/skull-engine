#include "skpch.h"
#include "OpenGLContext.h"

#include <Skull/Log.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Skull {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: m_WindowHandle(windowHandle) {
		SK_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SK_CORE_ASSERT(status, "Failed to initialize Glad!");

		SK_CORE_INFO("OpenGL renderer:");
		SK_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		SK_CORE_INFO("  Renderer: {0}",(const char*)glGetString(GL_RENDERER));
		SK_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}