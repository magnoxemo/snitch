#include <ctime>
#include <random>

#include "RandomField.h"

void RandomField::populateRandomIntegers(int limit, int seed) {

  srand(seed);
  std::vector<dof_id_type> dof_indices;
  for (const auto &elem : _mesh.element_ptr_range()) {
    _dof_map.dof_indices(elem, dof_indices);
    int random_int = rand() % limit;
    _system.solution->set(dof_indices[0], limit - random_int);
  }
  _system.solution->close();
}
bool RandomField::belongToCluster(libMesh::Elem *elem,
                                  libMesh::Elem *neighbor_elem) {
  // TODO Come up with more robust heuristics
  double element_solution = getElementDataFromMesh(elem);
  double neighbor_solution = getElementDataFromMesh(neighbor_elem);
  return (static_cast<int>(element_solution) ==
          static_cast<int>(neighbor_solution));
}
