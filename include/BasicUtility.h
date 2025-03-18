#ifndef BASICUTILITY_H
#define BASICUTILITY_H

#include "libmesh/equation_systems.h"
#include "libmesh/mesh.h"

void PopulateSyntheticData(libMesh::Mesh &mesh,
                           libMesh::EquationSystems &equation_system,
                           const std::string system_name,
                           const std::string variable_name,
                           double (*CalculateData)(const libMesh::Point &),
                           bool needs_re_init = false);

#endif
