#include "kngpch.h"
#include "Renderable2D.h"


namespace King {
	namespace graphics {
		Renderable2D::Renderable2D(glm::vec3 position, glm::vec2 size, Shader* shader) : m_position(position), m_size(size), m_shader(shader)
		{
			m_vao = new VertexArray();
			GLfloat vertices[] =
			{
				0,  0,   0, //links unten
				0,  size.y,   0, //links oben
				size.x,  0,   0, //rechts unten
				size.x,  size.y,   0, //rechts oben
			};
			
			m_vao->addBuffer(new Buffer(vertices, 4* 3, 3), 0);

			GLuint indices[] =
			{
				0, 1, 2,
				3, 1, 2
			};

			m_ibo = new IndexBuffer(indices, 6);

		}
	}
}
