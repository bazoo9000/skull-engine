#include "skpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Skull
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}