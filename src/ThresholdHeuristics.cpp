#include "ThresholdHeuristics.h"

bool ThresholdHeuristics::belongToCluster(libMesh::Elem *elem,
                                          libMesh::Elem *neighbor_elem) {
  return _value_crosses_threshold
             ? ((getMetricData(elem) > _threshold &&
                  getMetricData(neighbor_elem) > _threshold))
             : ((getMetricData(elem) < _threshold &&
                  getMetricData(neighbor_elem) < _threshold));
}

double ThresholdHeuristics::calculateMetrics(libMesh::Elem *elem){
    return getElementDataFromMesh(elem,_variable_index);
}