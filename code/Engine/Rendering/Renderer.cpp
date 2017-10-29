#include "Renderer.h"
#include <cassert> //TODO: Replace


namespace engine::render
{

Renderer::Renderer() : m_vertexBufferID(-1), m_indexBufferID(-1)
{
	initialize();
}

Renderer::~Renderer()
{
	if (m_vertexBufferID != -1)
		glDeleteBuffers(1, &m_vertexBufferID);

	if (m_indexBufferID != -1)
		glDeleteBuffers(1, &m_indexBufferID);
}

void Renderer::initialize()
{
	GLenum errorCode = glewInit();
	assert(errorCode == 0);

	glGenBuffers(1, &m_vertexBufferID);
	glGenBuffers(1, &m_indexBufferID);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);

	glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	errorCode = glGetError();
	assert(errorCode == 0);
}

const Geometry& Renderer::addGeometry(
	const std::vector<math::Vec3> &vertices,
	const std::vector<unsigned short> &indices,
	GLenum renderMode)
{
	return m_geometries.emplace_back(vertices, indices, renderMode);
}

Renderable& Renderer::addRenderable(const Geometry& geometry)
{
	return m_renderables.emplace_back(geometry);
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const auto &renderable : m_renderables)
	{
		const auto &vertices = renderable.geometry().vertices();
		const auto &indices = renderable.geometry().indices();
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices.data());
		
		std::vector<math::Vec3> transformedVerts;
		transformedVerts.reserve(vertices.size());
		for (const auto &vertex : vertices)
			transformedVerts.push_back(renderable.m_matrix * vertex);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(transformedVerts), transformedVerts.data());

		const GLenum renderMode = renderable.geometry().renderMode();
		glDrawElements(renderMode, vertices.size(), GL_UNSIGNED_SHORT, 0);
	}
}

}