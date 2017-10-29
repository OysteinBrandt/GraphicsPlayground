#pragma once

#include <GL/glew.h>
#include "Geometry.h"
#include "Renderable.h"
#include <vector>
#include "DllHelper.h"

#include <Math/Vec3.h>

namespace engine::render
{
	class OBR_API Renderer
	{
		std::vector<Geometry> m_geometries;
		std::vector<Renderable> m_renderables;

		GLuint m_vertexBufferID;
		GLuint m_indexBufferID;
		static const unsigned int MAX_BUFFER_SIZE = 1024;

		void initialize(); // TODO: Make public, and use from caller?

	public:
		Renderer();
		~Renderer();

		Renderer operator=(const Renderer&) = delete;
		Renderer& opearator(const Renderer&) = delete;

		const Geometry& addGeometry(const std::vector<math::Vec3> &vertices,
																				const std::vector<unsigned short> &indices,
																				GLenum renderMode);
		Renderable& addRenderable(const Geometry& geometry);

		void render();
	};
}