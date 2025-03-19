#include "libmesh/libmesh.h"

#include "BasicUtility.h"
#include "EqualNeighborHeuristic.h"

double LinearFunction(double x){
    return x; //we can change that to any line we want
}

double CalculateStep (const libMesh::Point & p){
    double dstep = 0.5;
    double x = p(0);
    double y = p(1);
    double score =  (y-LinearFunction(x))/dstep;
    return score;
}

int main(int argc, char **argv) {
    std::string name_of_the_system = "step_function";
    std::string populated_variable_name = "step_function_data";

    libMesh::LibMeshInit init(argc, argv);
    libMesh::Mesh mesh(init.comm());
    BuildMesh(argv, mesh);

    libMesh::EquationSystems equation_system(mesh);
    PopulateSyntheticData(equation_system, name_of_the_system,
                          populated_variable_name, CalculateStep);

    EqualNeighborHeuristic demo(equation_system, name_of_the_system,
                                populated_variable_name);
    demo.setTolerance(0.001);
    demo.findCluster();
    demo.captureClusterID();
    demo.writeOutputData("output.e");
}
