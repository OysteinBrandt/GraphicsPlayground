#include "Renderer.h"
#include <cassert> //TODO: Replace
#include "Shader.h"

namespace engine::render
{

Renderer::Renderer() : m_vertexBufferID(-1), m_indexBufferID(-1)
{
	// TODO: Find a solution to the problem of returning pointer/reference to vector elements, as they will be invalidated when the size increases!!!
	m_geometries.reserve(2);  // TODO: This is a temp solution
	m_renderables.reserve(3); // TODO: This is a temp solution
	initialize();
}

Renderer::~Renderer()
{
	glDisableVertexAttribArray(0);

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


	// http://www.informit.com/articles/article.aspx?p=2033340&seqNum=3
	// TODO: Consider using 'Packed Data Formats for Vertex Attributes'
	// eg. GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV
	/*
		"represent four-component data represented as ten bits for each of the first three components and two for the last, 
		packed in reverse order into a single 32-bit quantity (a GLuint). GL_BGRA could just have easily been called GL_ZYXW"
	*/
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	errorCode = glGetError();
	assert(errorCode == 0);
}

Geometry* Renderer::addGeometry(
	const std::vector<math::Vec3> &vertices,
	const std::vector<unsigned short> &indices,
	GLenum renderMode)
{
	// TODO: Find a solution to the problem of returning pointer/reference to vector elements, as they will be invalidated when the size increases!!!
	return &m_geometries.emplace_back(vertices, indices, renderMode);
}

Renderable* Renderer::addRenderable(Geometry *geometry, Shader *shader)
{
	return &m_renderables.emplace_back(*geometry, shader);
}

math::Mat4 Renderer::aspectCorrectionMatrix(float width, float height) const
{
	float aspectRatio = width / height;

	if (aspectRatio > 1)
		return math::Mat4::scale(1.0f / aspectRatio, 1.0f, 0.f);
	else
		return math::Mat4::scale(1.0f, aspectRatio, 0.f);
}

void Renderer::render(float width, float height)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// TODO: Require fixed size or add flags for resizable/fixed. Ie. do not calculate matrix every frame if not needed.
	const auto aspectMatrix = aspectCorrectionMatrix(width, height);

	for (const auto &renderable : m_renderables)
	{
		const auto &vertices = renderable.geometry().vertices();
		const auto &indices = renderable.geometry().indices();
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLushort) * indices.capacity(), indices.data());
		
		std::vector<math::Vec3> transformedVerts;
		transformedVerts.reserve(vertices.size());
		for (const auto &vertex : vertices)
			transformedVerts.push_back(aspectMatrix * renderable.m_matrix * vertex);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(math::Vec3) * transformedVerts.capacity(), transformedVerts.data());

		const auto* shader = renderable.shader();
		if (shader != nullptr)
			shader->bind();

		const GLenum renderMode = renderable.geometry().renderMode();
		glDrawElements(renderMode, indices.size(), GL_UNSIGNED_SHORT, 0);

		if (shader != nullptr)
			shader->unbind();
	}
}

}