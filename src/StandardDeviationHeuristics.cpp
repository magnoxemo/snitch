#include "StandardDeviationHeuristics.h"

bool StandardDeviationHeuristics::belongToCluster(
    libMesh::Elem *elem, libMesh::Elem *neighbor_elem) {
    if ((getElementDataFromMesh(elem) > _standard_deviation_tolerance &&
        getElementDataFromMesh(neighbor_elem) > _standard_deviation_tolerance)){
        return true;
    }
    else{
        return false;
    }
}
