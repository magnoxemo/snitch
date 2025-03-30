#include "ThresholdHeuristics.h"

bool ThresholdHeuristics::belongToCluster(libMesh::Elem *elem,
                                          libMesh::Elem *neighbor_elem) {
  return _value_crosses_threshold
             ? ((getElementDataFromMesh(elem,_metric_variable_index) > _threshold &&
                 getElementDataFromMesh(neighbor_elem,_metric_variable_index) > _threshold))
             : ((getElementDataFromMesh(elem,_metric_variable_index) < _threshold &&
                 getElementDataFromMesh(neighbor_elem,_metric_variable_index) < _threshold));
}

double ThresholdHeuristics::calculateMetrics(libMesh::Elem *elem){
    return getElementDataFromMesh(elem,_synthetic_variable_index);
}