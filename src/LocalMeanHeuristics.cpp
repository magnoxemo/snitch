#include "LocalMeanHeuristics.h"

bool LocalMeanHeuristics::belongToCluster(libMesh::Elem *elem,libMesh::Elem *neighbor_elem){

    double local_score =0;
    unsigned int number_of_active_neighbor =0;
    for (unsigned int side =0;side< neighbor_elem->n_sides();side++){
        const libMesh::Elem *current_elem = neighbor_elem->neighbor_ptr(side);
        if (current_elem){
            local_score+=getElementDataFromMesh(current_elem);
            number_of_active_neighbor+=1;
        }
    }

    return std::abs(getElementDataFromMesh(elem) - local_score/number_of_active_neighbor)<_tol;
}
