#include "LocalMeanHeuristics.h"
#include "libmesh/elem.h"

bool LocalMeanHeuristics::belongToCluster(libMesh::Elem *elem,
                                          libMesh::Elem *neighbor_elem) {

  return std::abs(getElementDataFromMesh(elem,_synthetic_variable_index) -getElementDataFromMesh(neighbor_elem,_metric_variable_index)) < _tol;
}

double LocalMeanHeuristics::calculateMetrics(libMesh::Elem *elem){

    double local_score = 0;
    unsigned int number_of_active_neighbor = 0;
    for (unsigned int side = 0; side < elem->n_sides(); side++) {
        const libMesh::Elem *current_elem = elem->neighbor_ptr(side);
        if (current_elem) {
            local_score += getElementDataFromMesh(current_elem,_synthetic_variable_index);
            number_of_active_neighbor++;
        }
    }

    return local_score / number_of_active_neighbor;
}
