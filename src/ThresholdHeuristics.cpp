#include "ThresholdHeuristics.h"

bool ThresholdHeuristics::belongToCluster(libMesh::Elem *elem,
                                          libMesh::Elem *neighbor_elem) {
  return _value_crosses_threshold
             ? ((getElementDataFromMesh(elem) > _threshold &&
                 getElementDataFromMesh(neighbor_elem) > _threshold))
             : ((getElementDataFromMesh(elem) < _threshold &&
                 getElementDataFromMesh(neighbor_elem) < _threshold));
}