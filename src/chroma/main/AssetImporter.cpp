#include "AssetImporter.h"

#include <thirdparty/OBJ_loader/OBJ_Loader.h>
#include <chroma/main/Log.h>


namespace Chroma
{
    Mesh* AssetImporter::LoadMeshFromOBJ(const std::string& file_name)
    {
        Mesh* mesh = new Mesh();

        objl::Loader Loader;

        // Load .obj File
        bool loadout = Loader.LoadFile(file_name);
        if (loadout)
        {
            objl::Mesh curMesh = Loader.LoadedMeshes[0];
            for (int j = 0; j < curMesh.Vertices.size(); j++)
            {
                mesh->m_vertex_positions.push_back(glm::vec3(curMesh.Vertices[j].Position.X, 
                    curMesh.Vertices[j].Position.Y, 
                    curMesh.Vertices[j].Position.Z ));
                mesh->m_vertex_normals.push_back(glm::vec3(curMesh.Vertices[j].Normal.X, 
                    curMesh.Vertices[j].Normal.Y,
                    curMesh.Vertices[j].Normal.Z));
                mesh->m_vertex_texcoords.push_back(glm::vec2(curMesh.Vertices[j].TextureCoordinate.X, 
                    curMesh.Vertices[j].TextureCoordinate.Y ));
            }

            mesh->m_indices = curMesh.Indices;

        }

        return mesh;
    }

    Texture* AssetImporter::LoadTexture(const std::string& file_name)
    {
        return new Texture(file_name);
    }
}