#ifndef THRESHOLDHEURISTICS_H
#define THRESHOLDHEURISTICS_H
#include "MeshAmalgamationBase.h"
class ThresholdHeuristics : public MeshAmalgamation {
private:
  double _standard_deviation_tolerance =0.05;

protected:
public:
    ThresholdHeuristics(libMesh::Mesh& mesh,
                              libMesh::EquationSystems &equation_system,
                              const std::string system_name,
                              const std::string variable_name)
      : MeshAmalgamation(mesh, equation_system, system_name, variable_name) {}
  bool belongToCluster(libMesh::Elem *elem,
                       libMesh::Elem *neighbor_elem) override;
  void setTolerance(double tol) { _standard_deviation_tolerance = tol; }

};

#endif
