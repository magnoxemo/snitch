#include "libmesh/libmesh.h"
#include "libmesh/mesh_generation.h"
#include <cmath>
#include <cstdlib>

#include "BasicUtility.h"
#include "LocalMeanHeuristics.h"

double f(const libMesh::Point &point) {
  // x = point (0)
  // y = point (1)
  return point(0) * point(0) / 100 - 2 * point(0) * point(1) / 100 -
         sin(exp(point(0)) - 4 * cos(point(0) * point(0)));
}

int main(int argc, char **argv) {

  std::string name_of_the_system = "polynomial_solution_field";
  std::string populated_variable_name = "polynomial_data";

  libMesh::LibMeshInit init(argc, argv);
  libMesh::Mesh mesh(init.comm());
  BuildMesh(argv, mesh);

  libMesh::EquationSystems equation_system(mesh);
  PopulateSyntheticData(equation_system, name_of_the_system,
                        populated_variable_name, f);

  LocalMeanHeuristics quadratic_field(equation_system, name_of_the_system,
                                      populated_variable_name);
  quadratic_field.setTolerance(0.1);
  quadratic_field.findCluster();
  quadratic_field.captureClusterID();
  quadratic_field.writeOutputData("output.e");

  return 0;
}