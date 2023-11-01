#pragma once

#include <string>

namespace Skull {

	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc); // ii temporar cu string
		~Shader(); // o sa fie virtual pt ziua cand o sa pun DirectX si restu

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID;
	};
}