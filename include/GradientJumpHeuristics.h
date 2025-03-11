#ifndef GRADIENTJUMPHEURISTICS_H
#define GRADIENTJUMPHEURISTICS_H

#include "ThresholdHeuristics.h"

class GradientJumpHeuristics : public ThresholdHeuristics {
private:
protected:
    double _jump_tolerance = 0.001;

public:
    GradientJumpHeuristics((libMesh::Mesh &mesh,
                            libMesh::EquationSystems &equation_system,
                            const std::string system_name,
                            const std::string variable_name)
            : ThresholdHeuristics(mesh, equation_system, system_name, variable_name) {}
    bool belongToCluster(libMesh::Elem *elem,
                         libMesh::Elem *neighbor_elem) override;
    double calculateGradientJump(libMesh::Elem *elem);
    void setJumpTolerance(double jump_tolerance) {
        _jump_tolerance = jump_tolerance;}
    double calculateDistance(libMesh::Point &p1,libMesh::Point &p2);
};

#endif