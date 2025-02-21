#include "MeshAmalgamationBase.h"

class RandomField : public MeshAmalgamation {

public:
  RandomField(libMesh::Mesh &mesh, libMesh::EquationSystems &equation_system,
              std::string system_name)
      : MeshAmalgamation(mesh, equation_system, system_name) {}
  void populateRandomIntegers(int limit = 5, int seed = 2133);
  bool belongToCluster(libMesh::Elem *elem,
                       libMesh::Elem *neighbor_elem) override;
};