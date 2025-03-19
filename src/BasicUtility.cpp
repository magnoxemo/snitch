#include "BasicUtility.h"

#include "libmesh/dof_map.h"
#include "libmesh/elem.h"
#include "libmesh/libmesh.h"
#include "libmesh/linear_implicit_system.h"
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
