#include <iostream>
#include <string>
#include <pxr/pxr.h>
#include <pxr/usd/usd/stage.h>  
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/sdf/assetPath.h>
#include <pxr/usd/usd/primRange.h> 

using namespace pxr;

void PrintPrimInfo(const UsdPrim& prim) {
    std::cout << "Prim: " << prim.GetPath() << ", Type: " << prim.GetTypeName() << std::endl;

    if (prim.IsA<UsdGeomMesh>()) {
        UsdGeomMesh mesh(prim);

        UsdAttribute pointsAttr = mesh.GetPointsAttr();
        VtVec3fArray points;
        if (pointsAttr.Get(&points)) {
            std::cout << "Points: ";
            for (const auto& point : points) {
                std::cout << "(" << point[0] << ", " << point[1] << ", " << point[2] << ") ";
            }
            std::cout << std::endl;
        }

        UsdAttribute faceVertexCountsAttr = mesh.GetFaceVertexCountsAttr();
        VtIntArray faceVertexCounts;
        if (faceVertexCountsAttr.Get(&faceVertexCounts)) {
            std::cout << "Face Vertex Counts: ";
            for (const auto& count : faceVertexCounts) {
                std::cout << count << " ";
            }
            std::cout << std::endl;
        }

        UsdAttribute faceVertexIndicesAttr = mesh.GetFaceVertexIndicesAttr();
        VtIntArray faceVertexIndices;
        if (faceVertexIndicesAttr.Get(&faceVertexIndices)) {
            std::cout << "Face Vertex Indices: ";
            for (const auto& index : faceVertexIndices) {
                std::cout << index << " ";
            }
            std::cout << std::endl;
        }

        // Print other attributes as needed
        // (like normals, geomBindTransform, jointIndices, jointWeights, etc.)
    }
}

void PrintUsdFileContent(const std::string& usdFilePath) {
    UsdStageRefPtr stage = UsdStage::Open(usdFilePath);
    if (!stage) {
        std::cerr << "Failed to open USD file: " << usdFilePath << std::endl;
        return;
    }

    std::cout << "Successfully loaded USD file: " << usdFilePath << std::endl;

    auto range = stage->Traverse();
    for (UsdPrim prim : range) {
        PrintPrimInfo(prim);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_usd_file>" << std::endl;
        return 1;
    }

    std::string usdFilePath = argv[1];

    PrintUsdFileContent(usdFilePath);

    return 0;
}
