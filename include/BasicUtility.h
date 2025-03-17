#ifndef BASICUTILITY_H
#define BASICUTILITY_H

#include "libmesh/dof_map.h"
#include "libmesh/elem.h"
#include "libmesh/equation_systems.h"
#include "libmesh/libmesh.h"
#include "libmesh/linear_implicit_system.h"
#include "libmesh/mesh.h"
#include "libmesh/numeric_vector.h"
#include "libmesh/system.h"

void PopulateSyntheticData(libMesh::Mesh &mesh,
                      libMesh::EquationSystems &equation_system,
                      const std::string system_name,
                      const std::string variable_name,
                      double (*CalculateData)(const libMesh::Point&),
                      bool needs_re_init=false) ;

#endif
