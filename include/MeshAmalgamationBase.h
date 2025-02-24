#ifndef MeshAmalgamation
#define MeshAmalgamation

#include <cstdlib>
#include <vector>
#include <stdexcept>

namespace libMesh {
    class DofMap;
    class Elem;
    class EquationSystems;
    class LinearImplicitSystem;
    class Mesh;
    class NumericVector;
    class System;
}

class MeshAmalgamation{

private:
protected:
  std::string _variable_name;
  unsigned int _extra_element_integer_index;
  unsigned int _variable_index;
  std::string _system_name;
  unsigned int _number_of_colors= 12;

  libMesh::Mesh &_mesh;
  libMesh::EquationSystems &_equation_system;
  libMesh::LinearImplicitSystem &_system;
  libMesh::DofMap &_dof_map;

  double getElementDataFromMesh(const libMesh::Elem *elem);

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
  void addVariableToSystem(const std::string variable_name);
};
