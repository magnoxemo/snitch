#include "GradientJumpHeuristics.h"

bool GradientJumpHeuristics::belongToCluster(libMesh::Elem *elem,
                                          libMesh::Elem *neighbor_elem) {
    double jump_diff = std::abs(calculateGradientJump(elem) -
                                calculateGradientJump(neighbor_elem));
    return _value_crosses_threshold
           ? ((jump_diff < _jump_tolerance) &&
              (getElementDataFromMesh(elem) > _threshold &&
               getElementDataFromMesh(neighbor_elem) > _threshold))
           : ((jump_diff < _jump_tolerance) &&
              (getElementDataFromMesh(elem) < _threshold &&
               getElementDataFromMesh(neighbor_elem) < _threshold));
}

double GradientJumpHeuristics::calculateGradientJump(libMesh::Elem *elem) {
    double j_e = 0;
    libMesh::Point p_e = elem->vertex_average();
    double element_solution = getElementDataFromMesh(elem);
    for (unsigned int s = 0; s < elem->n_sides(); s++) {
        libMesh::Elem *current_elem = elem->neighbor_ptr(s);
        if (current_elem) {
            libMesh::Point p_s = current_elem->vertex_average();
            j_e +=std::abs((element_solution - getElementDataFromMesh(current_elem)) /
                             (calculateDistance(p_e, p_s)));
        }
    }

    return j_e;
}

double GradientJumpHeuristics::calculateDistance(libMesh::Point &p1,
                                              libMesh::Point &p2) {
    return sqrt((p1(0) - p2(0)) * (p1(0) - p2(0)) +
                (p1(1) - p2(1)) * (p1(1) - p2(1)));
}