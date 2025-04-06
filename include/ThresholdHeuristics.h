#ifndef THRESHOLDHEURISTICS_H
#define THRESHOLDHEURISTICS_H

#include "MeshAmalgamationBase.h"

class ThresholdHeuristics : public MeshAmalgamation {

private:
  double _threshold = 0.05;

protected:
  bool _value_crosses_threshold = true;

public:
  ThresholdHeuristics(libMesh::EquationSystems &equation_system,
                      const std::string system_name,
                      const std::string variable_name)
      : MeshAmalgamation(equation_system, system_name, variable_name) {}

  virtual double calculateMetrics (libMesh::Elem *elem) override;
  virtual bool belongToCluster(libMesh::Elem *elem,
                               libMesh::Elem *neighbor_elem) override;
  void setThreshold(double threshold) { _threshold = threshold; }
  void setComparisonMode(bool value_crosses_threshold) {
    _value_crosses_threshold = value_crosses_threshold;
  }
};

#endif