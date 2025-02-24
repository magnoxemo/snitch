#ifndef LOCALMEANHEURISTICS_H
#define LOCALMEANHEURISTICS_H

#include "MeshAmalgamationBase.h"


class LocalMeanHeuristics : public MeshAmalgamation {
protected:
    double _tol= .00001;
public:
    LocalMeanHeuristics(libMesh::Mesh &mesh, libMesh::EquationSystems &equation_system,std::string system_name):
            MeshAmalgamation(mesh, equation_system, system_name) {}
    bool belongToCluster(libMesh::Elem *elem,libMesh::Elem *neighbor_elem);
    void setTolerance(double tol){_tol =tol;}
};

#endif
