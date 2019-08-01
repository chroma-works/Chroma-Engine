#pragma once

#include <chroma/geometry/Mesh.h>
#include <chroma/renderer/Texture.h>


namespace Chroma
{

    class AssetImporter
    {
    public:
        static Mesh* LoadMeshFromOBJ(const std::string& file_name);

        Texture * LoadTexture(const std::string & file_name);

    private:
    };
}