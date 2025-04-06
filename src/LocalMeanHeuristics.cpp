#include "LocalMeanHeuristics.h"
#include "libmesh/elem.h"

bool LocalMeanHeuristics::belongToCluster(libMesh::Elem *elem,
                                          libMesh::Elem *neighbor_elem) {

  return std::abs(getVariableData(elem) -getMetricData(neighbor_elem)) < _tol;
}

double LocalMeanHeuristics::calculateMetrics(libMesh::Elem *elem){

    double local_score = 0;
    unsigned int number_of_active_neighbor = 0;
    for (unsigned int side = 0; side < elem->n_sides(); side++) {
        const libMesh::Elem *current_elem = elem->neighbor_ptr(side);
        if (current_elem) {
            local_score += getVariableData(current_elem);
            number_of_active_neighbor++;
        }
    }

    return local_score / number_of_active_neighbor;
}
