#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

#include "BasicUtility.h"
#include "EqualNeighborHeuristic.h"

#include "libmesh/libmesh.h"

#define RANDOM_NUMBER_RANGE 5;

double CalculateRandomData(const libMesh::Point &p) {
  return rand() % RANDOM_NUMBER_RANGE;
}

int main(int argc, char **argv) {
  // declaring the system name and variable_name
  // variable_name would be the variable based on which heuristics would be done
  std::string name_of_the_system = "random_solution_field";
  std::string populated_variable_name = "random_data";

  // preparing the mesh and the data
  libMesh::LibMeshInit init(argc, argv);
  libMesh::Mesh mesh(init.comm());
  BuildMesh(argv, mesh);
  libMesh::EquationSystems equation_system(mesh);

  PopulateSyntheticData(equation_system, name_of_the_system,
                        populated_variable_name, CalculateRandomData);

  // actual clustering process
  EqualNeighborHeuristic demo(equation_system, name_of_the_system,
                              populated_variable_name);
  demo.setTolerance(0.001);
  demo.findCluster();
  demo.captureClusterID();
  demo.writeOutputData("output.e");
}
