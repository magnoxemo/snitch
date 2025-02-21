#include "MeshAmalgamationBase.h"


MeshAmalgamation::MeshAmalgamation(libMesh::Mesh &mesh,
                                   libMesh::EquationSystems &equation_system,
                                   const std::string system_name)
    : _mesh(mesh), _equation_system(equation_system),
      _system_name(system_name) {
    _system= _equation_system.add_system<LinearImplicitSystem>(_system_name);
    _dof_map = _system.get_dof_map();

}

void MeshAmalgamation::findCluster() {

    int not_visited = -1;
    _extra_element_integer_index = _mesh.add_elem_integer(_variable_name, not_visited);

    std::stack<libMesh::Elem *> neighbor_stack;

    for (auto &elem : _mesh.element_ptr_range()) {
        if (elem->get_extra_integer(_extra_element_integer_index) != not_visited) {
            continue;
        }
        int cluster_id = elem->id();
        neighbor_stack.push(elem);
        elem->set_extra_integer(_extra_element_integer_index, cluster_id);

        while (!neighbor_stack.empty()) {
            libMesh::Elem *current_elem = neighbor_stack.top();
            neighbor_stack.pop();

            for (unsigned int s = 0; s < current_elem->n_sides(); s++) {
                libMesh::Elem *neighbor_elem = current_elem->neighbor_ptr(s);

                if (neighbor_elem && neighbor_elem->get_extra_integer(_extra_element_integer_index) == not_visited) {
                    if (belongToCluster(current_elem, neighbor_elem)) {
                        neighbor_elem->set_extra_integer(_extra_element_integer_index, cluster_id);
                        neighbor_stack.push(neighbor_elem);
                    }
                }
            }
        }
    }
}

void MeshAmalgamation::addVariableToSystem(const std::string variable_name) {

    if (_variable_name.empty()){
        _variable_name = variable_name;
    }else{
        throw std::invalid_argument("variable name has been set already!");
    }
  _system.add_variable(_variable_name, CONSTANT, MONOMIAL);
  _variable_index = _system.variable_number(variable_name);
  _equation_system.init();
}

void MeshAmalgamation::captureClusterID() {

  LinearImplicitSystem &local_system =
      _equation_system.add_system<LinearImplicitSystem>("cluster_id");
  local_system.add_variable("cluster_id", CONSTANT, MONOMIAL);
  _equation_system.reinit();

  DofMap &local_dof_map = local_system.get_dof_map();

  for (const auto &elem : _mesh.element_ptr_range()) {
    std::vector<dof_id_type> local_dof_indices;
    local_dof_map.dof_indices(elem, local_dof_indices);
    int cluster_id = elem->get_extra_integer(_extra_element_integer_index) % _number_of_colors;
    local_system.solution->set(local_dof_indices[0], cluster_id);
  }

  local_system.solution->close();
}

void MeshAmalgamation::writeOutputData(std::string output_file_name) {
  ExodusII_IO(_mesh).write_discontinuous_equation_systems(output_file_name,
                                                          _equation_system);
}

void MeshAmalgamation::printSystemInformation() {
  _mesh.print_info();
  _equation_system.print_info();
}

double MeshAmalgamation::getElementDataFromMesh(const libMesh::Elem *elem) {

  std::vector<dof_id_type> dof_indices;
  std::vector<double> solution_value(1);

  _dof_map.dof_indices(elem, dof_indices, _variable_index);
  _system.solution->get(dof_indices, solution_value);

  return static_cast<double>(solution_value[0]);
}

void MeshAmalgamation::setNumberOfColors(unsigned int number_of_colors){
    _number_of_colors = number_of_colors;
}