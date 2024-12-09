#include <tinyusdz.hh>

#include <iostream>
#include <fstream> 
#include <string>

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_usd_file> <output_file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = argv[1]; 
    std::string outputFilename = argv[2]; 

    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "ERROR: Unable to open output file: " << outputFilename << std::endl;
        return EXIT_FAILURE;
    }

    tinyusdz::Stage stage; 
    std::string warn;
    std::string err;

    bool ret = tinyusdz::LoadUSDFromFile(filename, &stage, &warn, &err);

    if (warn.size()) {
        std::cout << "WARN: " << warn << "\n";
        outputFile << "WARN: " << warn << "\n"; 
    }

    if (!ret) {
        if (!err.empty()) {
            std::cerr << "ERR: " << err << "\n"; 
            outputFile << "ERR: " << err << "\n"; 
        }
        return EXIT_FAILURE;
    }

    outputFile << "Successfully loaded USD file: " << filename << "\n\n";
    outputFile << "Stage(Scene graph):\n";
    // outputFile << tinyusdz::to_string(stage) << "\n\n";

    outputFile << "Root Prims:\n";
    for (const tinyusdz::Prim &root_prim : stage.root_prims()) {
        outputFile << "Prim Path: " << root_prim.absolute_path().full_path_name() << "\n";
        for (const tinyusdz::Prim& child : root_prim.children()) { 
            
        }
    }

    outputFile.close();
    std::cout << "Output written to: " << outputFilename << std::endl;

    return EXIT_SUCCESS;
}
