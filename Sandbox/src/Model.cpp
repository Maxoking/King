#include "kngpch.h"
#include "Model.h"

namespace King {
  namespace graphics {
    //GLfloat * Model::loadModel(std::string path)
    //{
    //  Assimp::Importer importer;
    //  const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    //  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    //  {
    //    KING_CORE_ERROR("ASSIMP Error!");
    //    return nullptr;
    //  }
    //  std::string directory = path.substr(0, path.find_last_of('/'));

    //  processNode(scene->mRootNode, scene);

    //  return nullptr;
    //}


    //void Model::processNode(aiNode *node, const aiScene *scene)
    //{
    //  // process all the node's meshes (if any)
    //  for (unsigned int i = 0; i < node->mNumMeshes; i++)
    //  {
    //    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    //    m_meshes.push_back(processMesh(mesh, scene));
    //  }
    //  // then do the same for each of its children
    //  for (unsigned int i = 0; i < node->mNumChildren; i++)
    //  {
    //    processNode(node->mChildren[i], scene);
    //  }
    //}

    //Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
    //{
    //  std::vector<GLfloat> vertices;
    //  std::vector<unsigned int> indices;

    //  for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    //  {
    //   
    //   vertices.push_back(mesh->mVertices[i].x);
    //   vertices.push_back(mesh->mVertices[i].y);
    //   vertices.push_back(mesh->mVertices[i].z);
    //  }
    //  // process indices
    //  for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    //  {
    //    aiFace face = mesh->mFaces[i];
    //    for (unsigned int j = 0; j < face.mNumIndices; j++)
    //      indices.push_back(face.mIndices[j]);
    //  }

    //  return Mesh(vertices, indices);
    //}

    //Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices)
    //{
    //  m_vertices = vertices;
    //  m_indices = indices;
    //}

    //void Mesh::setUpMesh()
    //{
    //  m_vao.reset(new VertexArray());
    //  graphics::BufferLayout layout = {
    //    {graphics::ShaderDataType::Vec3, "a_position"},
    //  };

    //  std::shared_ptr<graphics::Buffer> vbo(new graphics::Buffer(&m_vertices[0], sizeof(m_vertices)));
    //  vbo->setLayout(layout);

    //  m_vao->addBufferWithLayout(vbo);
    //  std::shared_ptr<graphics::IndexBuffer> ibo(new graphics::IndexBuffer(&m_indices[0], m_indices.size()));
    //  m_vao->setIBO(ibo);
    //}

  }//namespace ends!
}/////////////