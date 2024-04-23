#include "skpch.h"
#include "Renderer.h"

namespace Skull 
{
	void Renderer::BeginScene()
	{
		// nimic
	}

	void Renderer::EndScene()
	{
		// nimic
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}