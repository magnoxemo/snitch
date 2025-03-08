#include "libmesh/libmesh.h"
#include "libmesh/mesh_generation.h"
#include <cmath>
#include <cstdlib>

#include "LocalMeanHeuristics.h"

double f(libMesh::Point &point) {
  // x = point (0)
  // y = point (1)
  return point(0) * point(0) / 100 - 2 * point(0) * point(1) / 100 -
         sin(exp(point(0)) - 4 * cos(point(0) * point(0)));
}

void PopulatePolynomialField(libMesh::Mesh &mesh,
                             libMesh::EquationSystems &equation_system,
                             const std::string system_name,
                             const std::string variable_name,
                             bool needs_re_init = false) {

  libMesh::LinearImplicitSystem &system =
      equation_system.add_system<libMesh::LinearImplicitSystem>(system_name);

  system.add_variable(variable_name, libMesh::CONSTANT, libMesh::MONOMIAL);
  if (needs_re_init) {
    equation_system.reinit();
  } else {
    equation_system.init();
  }

  libMesh::DofMap &dof_map = system.get_dof_map();
  std::vector<libMesh::dof_id_type> dof_indices;
  for (const auto &elem : mesh.element_ptr_range()) {
    dof_map.dof_indices(elem, dof_indices);
    libMesh::Point p = elem->vertex_average();
    system.solution->set(dof_indices[0], f(p));
  }
  system.solution->close();
}

int main(int argc, char **argv) {

  std::string name_of_the_system = "polynomial_solution_field";
  std::string populated_variable_name = "polynomial_data";

  libMesh::LibMeshInit init(argc, argv);
  libMesh::Mesh mesh(init.comm());
  unsigned int nx = 500;
  unsigned int ny = 500;

  libMesh::MeshTools::Generation::build_square(mesh, nx, ny, -10.0, 10.0, -10.0,
                                               10.0);
  libMesh::EquationSystems equation_system(mesh);
  PopulatePolynomialField(mesh, equation_system, name_of_the_system,
                          populated_variable_name);

  LocalMeanHeuristics quadratic_field(mesh, equation_system, name_of_the_system,
                                      populated_variable_name);
  quadratic_field.setTolerance(0.1);
  quadratic_field.findCluster();
  quadratic_field.captureClusterID();
  quadratic_field.writeOutputData("output.e");

  return 0;
}
