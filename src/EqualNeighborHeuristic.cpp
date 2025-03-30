#include "EqualNeighborHeuristic.h"

bool EqualNeighborHeuristic::belongToCluster(libMesh::Elem *elem,
                                             libMesh::Elem *neighbor_elem) {
  return std::abs(getElementDataFromMesh(elem,_metric_variable_index) -
                  getElementDataFromMesh(neighbor_elem,_metric_variable_index)) < _tol;
}

double EqualNeighborHeuristic::calculateMetrics(libMesh::Elem *elem){
    return getElementDataFromMesh(elem,_synthetic_variable_index);
}
