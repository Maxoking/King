#include "kngpch.h"
#include "Model.h"



namespace King {
  namespace graphics {
    std::unordered_map<std::string, ModelRessource> Model::s_loadedModels = std::unordered_map<std::string, ModelRessource>();

    Model::Model(std::string path)
    {
      if (s_loadedModels.find(path) != s_loadedModels.end()) {
        for(int i = 0; i < s_loadedModels.at(path).m_meshes.size(); i++)
          m_modelRessource.m_meshes.push_back(s_loadedModels.at(path).m_meshes[i]) ;
      }
      else {
        KING_TRACE("Loading new Model " + path);
        loadModel(path);
      }

      
    }

    void Model::loadModel(std::string path)
    {
      Assimp::Importer importer;
      const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
      if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
      {
        KING_CORE_ERROR("ASSIMP Error!");
        return;
      }
      std::string directory = path.substr(0, path.find_last_of('/'));

      processNode(scene->mRootNode, scene);
      s_loadedModels.emplace(path, m_modelRessource);
      return;
    }


    void Model::processNode(aiNode *node, const aiScene *scene)
    {
      // process all the node's meshes (if any)
      for (unsigned int i = 0; i < node->mNumMeshes; i++)
      {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_modelRessource.m_meshes.push_back(processMesh(mesh, scene));
      }
      // then do the same for each of its children
      for (unsigned int i = 0; i < node->mNumChildren; i++)
      {
        processNode(node->mChildren[i], scene);
      }
    }

    Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
    {/*
      std::vector<GLfloat> vertices;
      std::vector<GLfloat> normals; */
      std::vector<GLuint> indices;

      std::vector<glm::vec3> vertices;
      std::vector<glm::vec3> normals;
      std::vector<glm::vec2> texCoords;


      for (unsigned int i = 0; i < mesh->mNumVertices; i++)
      {
       
       /*vertices.push_back(mesh->mVertices[i].x);
       vertices.push_back(mesh->mVertices[i].y);
       vertices.push_back(mesh->mVertices[i].z);*/
        vertices.push_back({ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });

      }

      for (unsigned int i = 0; i < mesh->mNumVertices; i++)
      {

        /*normals.push_back(mesh->mNormals[i].x);
        normals.push_back(mesh->mNormals[i].y);
        normals.push_back(mesh->mNormals[i].z);*/

        normals.push_back(glm::normalize(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z )));

      }


      for (unsigned int i = 0; i < mesh->mNumVertices; i++)
      {

        /*normals.push_back(mesh->mNormals[i].x);
        normals.push_back(mesh->mNormals[i].y);
        normals.push_back(mesh->mNormals[i].z);*/

          texCoords.push_back({ mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
       
      }
    
      
     

      // process indices
      for (unsigned int i = 0; i < mesh->mNumFaces; i++)
      {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
          indices.push_back(face.mIndices[j]);
      }

      //normalstest
      std::vector<GLfloat> verticesWithNormalsAndTexCoords;
      for (unsigned int i = 0; i < vertices.size(); i++) {
        verticesWithNormalsAndTexCoords.push_back(vertices[i].x);
        verticesWithNormalsAndTexCoords.push_back(vertices[i].y);
        verticesWithNormalsAndTexCoords.push_back(vertices[i].z);
        verticesWithNormalsAndTexCoords.push_back(normals[i].x);
        verticesWithNormalsAndTexCoords.push_back(normals[i].y);
        verticesWithNormalsAndTexCoords.push_back(normals[i].z);
        verticesWithNormalsAndTexCoords.push_back(texCoords[i].x);
        verticesWithNormalsAndTexCoords.push_back(texCoords[i].y);
      }

      return Mesh(verticesWithNormalsAndTexCoords, indices);
    }

    Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices)
    {
      m_vertices = vertices;
      m_indices = indices;
      setUpMesh();
    }

    void Mesh::setUpMesh()
    {
      m_vao.reset(new VertexArray());
      graphics::BufferLayout layout = {
        {graphics::ShaderDataType::Vec3, "a_position"},
        {graphics::ShaderDataType::Vec3, "a_normal"},
        {graphics::ShaderDataType::Vec2, "a_uvCoord"}
      };

      std::shared_ptr<graphics::Buffer> vbo(new graphics::Buffer(&m_vertices[0], m_vertices.size() * sizeof(GLfloat)));
      vbo->setLayout(layout);

      //m_vao->addBufferWithLayout(vbo);
      m_vao->addBufferWithLayout(vbo);
      std::shared_ptr<graphics::IndexBuffer> ibo(new graphics::IndexBuffer(&m_indices[0], m_indices.size()));
      m_vao->setIBO(ibo);
      
    }

  }//namespace ends!
}/////////////