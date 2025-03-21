#include <cmath>
#include <cstdlib>

#include "libmesh/libmesh.h"

#include "BasicUtility.h"
#include "ThresholdHeuristics.h"

#define ALPHA 0.01
#define SIGMA_T_FUEL 0.0332
#define SIGMA_T_MOD 0.052

double standard_dev(const libMesh::Point &point) {

  double r = sqrt(point(0) * point(0) + point(1) * point(1));
  double sigma = SIGMA_T_FUEL;

  if (r > 5)
    sigma = SIGMA_T_MOD;

  return ALPHA * pow(sigma, -sigma * r);
}

int main(int argc, char **argv) {

  std::string name_of_the_system = "polynomial_solution_field";
  std::string populated_variable_name = "polynomial_data";
  std::string populated_std_variable_name = "std_data";

  libMesh::LibMeshInit init(argc, argv);
  libMesh::Mesh mesh(init.comm());
  BuildMesh(argv, mesh);

  libMesh::EquationSystems equation_system(mesh);

  PopulateSyntheticData(equation_system, name_of_the_system,
                        populated_std_variable_name, standard_dev);

  ThresholdHeuristics std_field(equation_system, name_of_the_system,
                                populated_std_variable_name);
  std_field.setThreshold(0.06);
  // default is true but setting this here for an example
  std_field.setComparisonMode(true);
  std_field.findCluster();
  std_field.setNumberOfColors(23);
  std_field.captureClusterID();
  std_field.writeOutputData("output.e");

  return 0;
}