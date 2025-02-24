#include "EqualNeighborHeuristic.h"

bool EqualNeighborHeuristic::belongToCluster(libMesh::Elem *elem,
                                  libMesh::Elem *neighbor_elem) {
  return std::abs(getElementDataFromMesh(elem)-getElementDataFromMesh(neighbor_elem))<_tol;
}
