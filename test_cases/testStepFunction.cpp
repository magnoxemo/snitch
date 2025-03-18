#include "BasicUtility.h"
#include "EqualNeighborHeuristic.h"

#include "libmesh/libmesh.h"
#include "libmesh/mesh_generation.h"

double CalculateStep_x(const libMesh::Point &p) {
  double dx = 0.5;
  double x = p(0);
  return int(x) / dx;
}

int main(int argc, char **argv) {
  std::string name_of_the_system = "step_function";
  std::string populated_variable_name = "step_function_data";

  libMesh::LibMeshInit init(argc, argv);
  libMesh::Mesh mesh(init.comm());
  unsigned int nx = 10;
  unsigned int ny = 10;
  libMesh::MeshTools::Generation::build_square(mesh, nx, ny, -10.0, 10.0, -10.0,
                                               10.0);
  libMesh::EquationSystems equation_system(mesh);
  PopulateSyntheticData(mesh, equation_system, name_of_the_system,
                        populated_variable_name, CalculateStep_x);

  EqualNeighborHeuristic demo(mesh, equation_system, name_of_the_system,
                              populated_variable_name);
  demo.setTolerance(0.001);
  demo.findCluster();
  demo.captureClusterID();
  demo.writeOutputData("output.e");
}
