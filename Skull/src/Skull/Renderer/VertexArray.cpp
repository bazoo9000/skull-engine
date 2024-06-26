#include "skpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Skull 
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:   SK_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		SK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}