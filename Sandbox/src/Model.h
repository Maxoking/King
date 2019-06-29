#pragma once
#include "King/Core.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "glad/glad.h"
#include "glm/common.hpp"
#include "glm/glm.hpp"

#include "King/Graphics/Buffers/VertexArray.h"

namespace King {
  namespace graphics {
   /* class Mesh {
    private:
      std::vector<GLfloat> m_vertices;
      std::vector<GLuint> m_indices;
      std::shared_ptr<VertexArray> m_vao;
    public:
      Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices);
      void setUpMesh();
    };

    class KING_API Model {
    private:
      std::vector<Mesh> m_meshes;
    public:
      GLfloat* loadModel(std::string path);
      void processNode(aiNode * node, const aiScene * scene);
      Mesh processMesh(aiMesh * mesh, const aiScene * scene);
    };*/

  }
}
