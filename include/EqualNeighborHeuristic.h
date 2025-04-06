#ifndef EQUALNEIGHBORHEURISTICS_H
#define EQUALNEIGHBORHEURISTICS_H

#include "MeshAmalgamationBase.h"

class EqualNeighborHeuristic : public MeshAmalgamation {

protected:
  double _tol = 0.000001;

public:
  EqualNeighborHeuristic(libMesh::EquationSystems &equation_system,
                         const std::string system_name,
                         const std::string variable_name)
      : MeshAmalgamation(equation_system, system_name, variable_name) {}

  virtual double calculateMetrics(libMesh::Elem *elem) override;
  bool belongToCluster(libMesh::Elem *elem,
                       libMesh::Elem *neighbor_elem) override;
  void setTolerance(double tol) { _tol = tol; }
};

#endif