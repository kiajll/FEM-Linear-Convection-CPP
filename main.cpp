#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <gmsh.h>
#include <fstream>
using namespace std;
//int main() {
//    std::cout << "Testing terminal output!" << std::endl;
//    return 0;
//}

//int main() {
//    std::vector<Eigen::Vector2d> nodes = { {0, 0}, {1, 0}, {1, 1}, {0, 1} };
//    std::cout << "Nodes (x, y):" << std::endl;
//    for (size_t i = 0; i < nodes.size(); ++i) {
//        std::cout << "Node " << i + 1 << ": (" << nodes[i][0] << ", " << nodes[i][1] << ")" << std::endl;
//    }
//    return 0;
//}

  Define a structure to represent a 2D mesh
struct Mesh {
    std::vector<Eigen::Vector2d> nodes;
    std::vector<std::vector<int>> elements;    Each element consists of node indices
};

 Function to generate a simple mesh using Gmsh

Mesh generateMesh() {
    Mesh mesh;
    std::cout << "Starting Gmsh initialization..." << std::endl;
    gmsh::initialize();
    std::cout << "Gmsh initialization completed" << std::endl;

    std::cout << "Gmsh initialized successfully." << std::endl;

    gmsh::model::add("adaptive_mesh");
    
     Add points and lines for a square mesh
    gmsh::model::geo::addPoint(0, 0, 0, 1, 1);
    gmsh::model::geo::addPoint(1, 0, 0, 1, 2);
    gmsh::model::geo::addPoint(1, 1, 0, 1, 3);
    gmsh::model::geo::addPoint(0, 1, 0, 1, 4);
    
    gmsh::model::geo::addLine(1, 2, 1);
    gmsh::model::geo::addLine(2, 3, 2);
    gmsh::model::geo::addLine(3, 4, 3);
    gmsh::model::geo::addLine(4, 1, 4);
    
    gmsh::model::geo::addCurveLoop({1, 2, 3, 4}, 1);
    gmsh::model::geo::addPlaneSurface({1}, 1);
    
    gmsh::model::geo::synchronize();
    
     Mesh refinement settings
    gmsh::model::mesh::generate(2);
    
     Export the nodes and elements into our mesh structure
    std::vector<std::size_t> nodeTags;
    std::vector<double> coords;
    std::vector<double> parametricCoords;   Parametric coordinates placeholder

    gmsh::model::mesh::getNodes(nodeTags, coords, parametricCoords);

    for (size_t i = 0; i < coords.size(); i += 3) {
        mesh.nodes.push_back(Eigen::Vector2d(coords[i], coords[i + 1]));
    }

    std::vector<std::size_t> elementTags;
    std::vector<std::size_t> nodeTagList;

    gmsh::model::mesh::getElementsByType(2, elementTags, nodeTagList);

    for (size_t i = 0; i < nodeTagList.size(); i += 3) {
        mesh.elements.push_back({
            static_cast<int>(nodeTagList[i] - 1),
            static_cast<int>(nodeTagList[i + 1] - 1),
            static_cast<int>(nodeTagList[i + 2] - 1)
        });
    }

     Print Nodes to Console
    std::cout << "Nodes (x, y):" << std::endl;
    for (size_t i = 0; i < mesh.nodes.size(); ++i) {
        std::cout << "Node " << i + 1 << ": (" << mesh.nodes[i][0] << ", " << mesh.nodes[i][1] << ")" << std::endl;
    }

     Print Elements to Console
    std::cout << "Elements (node indices):" << std::endl;
    for (size_t i = 0; i < mesh.elements.size(); ++i) {
        std::cout << "Element " << i + 1 << ": ("
                  << mesh.elements[i][0] << ", "
                  << mesh.elements[i][1] << ", "
                  << mesh.elements[i][2] << ")" << std::endl;
    }

    gmsh::write("C:/Users/kiara/Desktop/output_mesh2.msh");
    std::ofstream outfile("C:/Users/kiara/Desktop/solution.txt");

     Move finalize to the very end
    gmsh::finalize();
    return mesh;
}

int main() {
    Mesh mesh = generateMesh();
    return 0;
}
//#include <iostream>
//#include <vector>
//#include <Eigen/Dense>
//#include <gmsh.h>
//#include <fstream>
//
//// Define a structure to represent a 2D mesh
//struct Mesh {
//    std::vector<Eigen::Vector2d> nodes;
//    std::vector<std::vector<int>> elements;  // Each element consists of node indices
//};
//
//// Function to generate a simple mesh using Gmsh
//Mesh generateMesh() {
//    Mesh mesh;
//
//    // Try to initialize Gmsh and create the model
//    try {
//        gmsh::initialize();
//        std::cout << "Gmsh initialization completed" << std::endl;
//
//        gmsh::model::add("adaptive_mesh");
//
//        // Add points and lines for a square mesh
//        gmsh::model::geo::addPoint(0, 0, 0, 1, 1);
//        gmsh::model::geo::addPoint(1, 0, 0, 1, 2);
//        gmsh::model::geo::addPoint(1, 1, 0, 1, 3);
//        gmsh::model::geo::addPoint(0, 1, 0, 1, 4);
//
//        gmsh::model::geo::addLine(1, 2, 1);
//        gmsh::model::geo::addLine(2, 3, 2);
//        gmsh::model::geo::addLine(3, 4, 3);
//        gmsh::model::geo::addLine(4, 1, 4);
//
//        gmsh::model::geo::addCurveLoop({1, 2, 3, 4}, 1);
//        gmsh::model::geo::addPlaneSurface({1}, 1);
//
//        gmsh::model::geo::synchronize();
//
//        // Mesh refinement settings
//        gmsh::model::mesh::generate(2);
//
//        // Export the nodes and elements into our mesh structure
//        std::vector<std::size_t> nodeTags;
//        std::vector<double> coords;
//        std::vector<double> parametricCoords;   // Parametric coordinates placeholder
//
//        gmsh::model::mesh::getNodes(nodeTags, coords, parametricCoords);
//
//        for (size_t i = 0; i < coords.size(); i += 3) {
//            mesh.nodes.push_back(Eigen::Vector2d(coords[i], coords[i + 1]));
//        }
//
//        std::vector<std::size_t> elementTags;
//        std::vector<std::size_t> nodeTagList;
//
//        gmsh::model::mesh::getElementsByType(2, elementTags, nodeTagList);
//
//        for (size_t i = 0; i < nodeTagList.size(); i += 3) {
//            mesh.elements.push_back({
//                static_cast<int>(nodeTagList[i] - 1),
//                static_cast<int>(nodeTagList[i + 1] - 1),
//                static_cast<int>(nodeTagList[i + 2] - 1)
//            });
//        }
//
//        // Print Nodes to Console
//        std::cout << "Nodes (x, y):" << std::endl;
//        for (size_t i = 0; i < mesh.nodes.size(); ++i) {
//            std::cout << "Node " << i + 1 << ": (" << mesh.nodes[i][0] << ", " << mesh.nodes[i][1] << ")" << std::endl;
//        }
//
//        // Print Elements to Console
//        std::cout << "Elements (node indices):" << std::endl;
//        for (size_t i = 0; i < mesh.elements.size(); ++i) {
//            std::cout << "Element " << i + 1 << ": ("
//                      << mesh.elements[i][0] << ", "
//                      << mesh.elements[i][1] << ", "
//                      << mesh.elements[i][2] << ")" << std::endl;
//        }
//
//        // Write mesh to file
//        gmsh::write("C:/Users/kiara/Desktop/output_mesh2.msh");
//        std::ofstream outfile("C:/Users/kiara/Desktop/solution.txt");
//
//        // Finalize Gmsh
//        gmsh::finalize();
//
//    } catch (const std::exception &e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//
//    return mesh;
//}
//
//int main() {
//    Mesh mesh = generateMesh();
//    return 0;
//}
