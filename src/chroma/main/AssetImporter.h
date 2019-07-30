#pragma once

#include <chroma/geometry/Mesh.h>


namespace Chroma
{

    class AssetImporter
    {
    public:
        static Mesh* LoadMeshFromOBJ(const std::string& file_name);

    private:
    };
}