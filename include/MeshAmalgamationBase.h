#include <cstdlib>
#include <vector>
#include <stdexcept>

#include "libmesh/dof_map.h"
#include "libmesh/elem.h"
#include "libmesh/equation_systems.h"
#include "libmesh/libmesh.h"
#include "libmesh/linear_implicit_system.h"
#include "libmesh/mesh.h"
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
  unsigned int _number_of_colors= 12;

  libMesh::Mesh &_mesh;
  libMesh::EquationSystems &_equation_system;
  LinearImplicitSystem &_system;
  DofMap &_dof_map;

  double getElementDataFromMesh(const libMesh::Elem *elem);
  void addVariableToSystem(const std::string variable_name);

public:
  MeshAmalgamation(libMesh::Mesh &mesh,
                   libMesh::EquationSystems &equation_system,
                   std::string system_name);

  virtual bool belongToCluster(libMesh::Elem *elem,
                               libMesh::Elem *neighbor_elem) = 0;
  virtual void findCluster();
  void captureClusterID();
  void printSystemInformation();
  void writeOutputData(std::string output_file_name);
  void setNumberOfColors(unsigned int number_of_colors);
};
