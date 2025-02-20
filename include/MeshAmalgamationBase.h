#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>

#include "libmesh/dof_map.h"
#include "libmesh/elem.h"
#include "libmesh/equation_systems.h"
#include "libmesh/exodusII_io.h"
#include "libmesh/libmesh.h"
#include "libmesh/linear_implicit_system.h"
#include "libmesh/mesh.h"
#include "libmesh/mesh_generation.h"
#include "libmesh/numeric_vector.h"
#include "libmesh/system.h"

using namespace libMesh;

class MeshAmalgamation {

private:
protected:
  std::string _variable_name;
  unsigned int _extra_element_integer_index;
  unsigned int _variable_index;
  std::string _system_name;

  libMesh::Mesh &_mesh;
  libMesh::EquationSystems &_equation_system;
  LinearImplicitSystem &_system =
      _equation_system.add_system<LinearImplicitSystem>(_system_name);
  DofMap &_dof_map = _system.get_dof_map();

public:
  MeshAmalgamation(libMesh::Mesh &mesh,
                   libMesh::EquationSystems &equation_system,
                   std::string system_name);

  double getElementDataFromMesh(const libMesh::Elem *elem);
  void addVariablesToSystem(const std::string variable_name);
  virtual bool belongToCluster(libMesh::Elem *elem,
                               libMesh::Elem *neighbor_elem) = 0;
  void findCluster();
  void captureClusterID();
  void printSystemInformation();
  void writeOutputData(std::string output_file_name);
};

void createMesh(libMesh::Mesh &mesh, int nx, int ny);
void createMesh(libMesh::Mesh &mesh, int nx, int ny, int nz);