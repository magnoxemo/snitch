#include <cmath>
#include "libmesh/mesh_generation.h"
#include "libmesh/libmesh.h"
#include "LocalMeanHeuristics.h"


double f(double x, double y) {
    return x*x/100-2*x*y/100-sin(exp(x)-4*cos(x*y));
}


class testLocalMeanHeuristics:public LocalMeanHeuristics{
public:
    testLocalMeanHeuristics(libMesh::Mesh &mesh,
                            libMesh::EquationSystems &equation_system,
                            std::string system_name): LocalMeanHeuristics(mesh, equation_system, system_name) {}
    void populatePolynomialField(double (*f)(double,double));
};


void testLocalMeanHeuristics::populatePolynomialField(double (*f)(double,double)){
    std::vector<libMesh::dof_id_type> dof_indices;
    for (const auto &elem : _mesh.element_ptr_range()) {
        _dof_map.dof_indices(elem, dof_indices);
        libMesh::Point p = elem->vertex_average();
        double result = f(p(0), p(1));
        _system.solution->set(dof_indices[0], result);
    }
    _system.solution->close();
}




int main(int argc, char **argv){


    libMesh::LibMeshInit init(argc, argv);
    libMesh::Mesh mesh(init.comm());
    unsigned int nx = 500;
    unsigned int ny = 500;


    libMesh::MeshTools::Generation::build_square(mesh, nx, ny, -10.0, 10.0, -10.0,
                                                 10.0);
    libMesh::EquationSystems equation_system(mesh);


    testLocalMeanHeuristics quadratic_field (mesh, equation_system, "testLocalMeanHeuristics");
    quadratic_field.addVariableToSystem("quadratic_field");
    quadratic_field.populatePolynomialField(&f);
    quadratic_field.setTolerance(0.1);
    quadratic_field.findCluster();
    quadratic_field.captureClusterID();
    quadratic_field.writeOutputData("output.e");

    return 0;
}
