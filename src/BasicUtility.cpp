#include "BasicUtility.h"

#include "libmesh/dof_map.h"
#include "libmesh/elem.h"
#include "libmesh/libmesh.h"
#include "libmesh/linear_implicit_system.h"
#include "libmesh/mesh_generation.h"
#include "libmesh/numeric_vector.h"
#include "libmesh/system.h"


void PopulateSyntheticData(libMesh::EquationSystems &equation_system,
                           const std::string system_name,
                           const std::string variable_name,
                           double (*CalculateData)(const libMesh::Point &)) {

  libMesh::MeshBase &mesh = equation_system.get_mesh();
  libMesh::LinearImplicitSystem &system =
      equation_system.add_system<libMesh::LinearImplicitSystem>(system_name);

  system.add_variable(variable_name, libMesh::CONSTANT, libMesh::MONOMIAL);
  system.add_variable("metrics", libMesh::CONSTANT, libMesh::MONOMIAL);

  const unsigned int variable_index = system.variable_number(variable_name);
  if (system.is_initialized()) {
    equation_system.reinit();
  } else {
    equation_system.init();
  }

  libMesh::DofMap &dof_map = system.get_dof_map();
  std::vector<libMesh::dof_id_type> dof_indices;

  for (const auto &elem : mesh.element_ptr_range()) {
    dof_map.dof_indices(elem, dof_indices);
    libMesh::Point p = elem->vertex_average();
    double score = CalculateData(p);
    system.solution->set(dof_indices[variable_index], score);
  }

  system.solution->close();
}

void Build2DMesh(char **argv, libMesh::Mesh &mesh) {

    unsigned int nx = std::atoi(argv[1]);
    unsigned int ny = std::atoi(argv[2]);
    double lower_left_x = std::atof(argv[3]);
    double upper_left_x = std::atof(argv[4]);
    double lower_left_y = std::atof(argv[5]);
    double upper_left_y = std::atof(argv[6]);

    libMesh::MeshTools::Generation::build_square(
            mesh, nx, ny, lower_left_x, upper_left_x, lower_left_y, upper_left_y);
}

void Build1DMesh(char **argv, libMesh::Mesh &mesh) {

    unsigned int nx = std::atoi(argv[1]);
    double left_x = std::atof(argv[3]);
    double right_x = std::atof(argv[4]);

    libMesh::MeshTools::Generation::build_line(
            mesh, nx, left_x, right_x,libMesh::EDGE2 );
}
