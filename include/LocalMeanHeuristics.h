#ifndef LOCALMEANHEURISTICS_H
#define LOCALMEANHEURISTICS_H

#include "MeshAmalgamationBase.h"

class LocalMeanHeuristics : public MeshAmalgamation {
protected:
  double _tol = .00001;

public:
  LocalMeanHeuristics(libMesh::EquationSystems &equation_system,
                      const std::string system_name,
                      const std::string variable_name)
      : MeshAmalgamation(equation_system, system_name, variable_name) {}

  virtual double calculateMetrics(libMesh::Elem *elem) override;
  bool belongToCluster(libMesh::Elem *elem, libMesh::Elem *neighbor_elem);
  void setTolerance(double tol) { _tol = tol; }
};

#endif
