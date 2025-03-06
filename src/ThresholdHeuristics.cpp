#include "ThresholdHeuristics.h"

bool ThresholdHeuristics::belongToCluster(
    libMesh::Elem *elem, libMesh::Elem *neighbor_elem) {
    return ((getElementDataFromMesh(elem) > _standard_deviation_tolerance &&
             getElementDataFromMesh(neighbor_elem) > _standard_deviation_tolerance));
}
