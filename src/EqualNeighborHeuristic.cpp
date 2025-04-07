#include "EqualNeighborHeuristic.h"

bool EqualNeighborHeuristic::belongToCluster(libMesh::Elem *elem,
                                             libMesh::Elem *neighbor_elem) {
  return std::abs(getMetricData(elem) -
                          getMetricData(neighbor_elem)) < _tol;
}

double EqualNeighborHeuristic::calculateMetrics(libMesh::Elem *elem){
    return getElementDataFromMesh(elem,_variable_index);
}
