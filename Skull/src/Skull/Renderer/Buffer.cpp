#include "skpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Skull/Log.h"

namespace Skull 
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) 
	{
		switch (Renderer::GetCurrentAPI()) 
		{
			case RendererAPI::API::None:   SK_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		SK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) 
	{
		switch (Renderer::GetCurrentAPI()) 
		{
			case RendererAPI::API::None:   SK_CORE_ASSERT(false, "RendererAPI::None is not supported yet."); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}

		SK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}