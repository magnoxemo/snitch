#include "ThresholdHeuristics.h"

bool ThresholdHeuristics::belongToCluster(libMesh::Elem *elem,
                                          libMesh::Elem *neighbor_elem,
                                          bool value_crosses_threshold) {
  return value_crosses_threshold
             ? ((getElementDataFromMesh(elem) > _threshold &&
                 getElementDataFromMesh(neighbor_elem) > _threshold))
             : ((getElementDataFromMesh(elem) < _threshold &&
                 getElementDataFromMesh(neighbor_elem) < _threshold));
}

void ThresholdHeuristics::findCluster(bool value_crosses_threshold) {

  int not_visited = -1;
  _extra_element_integer_index =
      _mesh.add_elem_integer(_variable_name, not_visited);

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

        if (neighbor_elem && neighbor_elem->get_extra_integer(
                                 _extra_element_integer_index) == not_visited) {
          if (belongToCluster(current_elem, neighbor_elem,
                              value_crosses_threshold)) {
            neighbor_elem->set_extra_integer(_extra_element_integer_index,
                                             cluster_id);
            neighbor_stack.push(neighbor_elem);
          }
        }
      }
    }
  }
}