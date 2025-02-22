#include "MeshAmalgamationBase.h"

class EqualNeighborHeuristic : public MeshAmalgamation {

protected:
    double _tol =0.000001;
public:
    EqualNeighborHeuristic(libMesh::Mesh &mesh, libMesh::EquationSystems &equation_system,
              std::string system_name)
      : MeshAmalgamation(mesh, equation_system, system_name) {}

  bool belongToCluster(libMesh::Elem *elem,
                       libMesh::Elem *neighbor_elem) override;
  void setTolerance(double tol){_tol =tol;}
};