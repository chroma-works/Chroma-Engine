#pragma once

#include <chroma/geometry/Mesh.h>

namespace Chroma
{
    class AssetImporter
    {
    public:
        static Mesh* ImportMesh(const char *file_name);

    private:

    };
}