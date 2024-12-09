#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <pxr/pxr.h>
#include <pxr/usd/usd/stage.h>  
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/sdf/assetPath.h>
#include <pxr/usd/usd/primRange.h> 

namespace fs = std::filesystem;
using namespace pxr;

void PrintPrimInfo(const UsdPrim& prim, std::ofstream& outputFile) {
    outputFile << "Prim: " << prim.GetPath() << ", Type: " << prim.GetTypeName() << std::endl;

    if (prim.IsA<UsdGeomMesh>()) {
        UsdGeomMesh mesh(prim);

        UsdAttribute pointsAttr = mesh.GetPointsAttr();
        VtVec3fArray points;
        if (pointsAttr.Get(&points)) {
            outputFile << "Points: ";
            for (const auto& point : points) {
                outputFile << "(" << point[0] << ", " << point[1] << ", " << point[2] << ") ";
            }
            outputFile << std::endl;
        }

        UsdAttribute normalsAttr = mesh.GetNormalsAttr();
        VtVec3fArray normals;
        if(normalsAttr.Get(&normals)) {
            outputFile << "Normals: ";
            for (const auto& normal : normals) {
                outputFile << "(" << normal[0] << ", " << normal[1] << ", " << normal[2] << ") ";
            }
            outputFile << std::endl;
        }

        UsdAttribute faceVertexCountsAttr = mesh.GetFaceVertexCountsAttr();
        VtIntArray faceVertexCounts;
        if (faceVertexCountsAttr.Get(&faceVertexCounts)) {
            outputFile << "Face Vertex Counts: ";
            for (const auto& count : faceVertexCounts) {
                outputFile << count << " ";
            }
            outputFile << std::endl;
        }

        UsdAttribute faceVertexIndicesAttr = mesh.GetFaceVertexIndicesAttr();
        VtIntArray faceVertexIndices;
        if (faceVertexIndicesAttr.Get(&faceVertexIndices)) {
            outputFile << "Face Vertex Indices: ";
            for (const auto& index : faceVertexIndices) {
                outputFile << index << " ";
            }
            outputFile << std::endl;
        }

        // Currently only the assumption is that only 1 usda or usdc file is parsed. Multi-file setup not considered
        // UV coordinates, joint indices, and joint weights are not yet handled
    }
}

void PrintUsdFileContent(const std::string& usdFilePath, const std::string& outputFilePath) {
    UsdStageRefPtr stage = UsdStage::Open(usdFilePath);
    if (!stage) {
        std::cerr << "Failed to open USD file: " << usdFilePath << std::endl;
        return;
    }

    std::cout << "Successfully loaded USD file: " << usdFilePath << std::endl;

    // Open the output file
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputFilePath << std::endl;
        return;
    }

    auto range = stage->Traverse();
    for (UsdPrim prim : range) {
        PrintPrimInfo(prim, outputFile);
    }

    outputFile.close();
    std::cout << "Output written to: " << outputFilePath << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <path_to_usd_file> <output_folder>" << std::endl;
        return 1;
    }

    std::string usdFilePath = argv[1];
    std::string outputFilePath = argv[2];

    PrintUsdFileContent(usdFilePath, outputFilePath);

    return 0;
}
