#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

#include "libmesh/mesh_generation.h"
#include "libmesh/libmesh.h"
#include "EqualNeighborHeuristic.h"

class testEqualNeighborHeuristic:public EqualNeighborHeuristic{
public:
    testEqualNeighborHeuristic(libMesh::Mesh &mesh,
                            libMesh::EquationSystems &equation_system,
                            std::string system_name): EqualNeighborHeuristic(mesh, equation_system, system_name) {}

    void populateRandomData(){
        std::vector<libMesh::dof_id_type> dof_indices;
        for (const auto &elem : _mesh.element_ptr_range()) {
            _dof_map.dof_indices(elem, dof_indices);
            int random_int = rand() % 5;
            _system.solution->set(dof_indices[0], random_int);
        }
        _system.solution->close();
    }
};

int main(int argc, char **argv){

    libMesh::LibMeshInit init(argc, argv);
    libMesh::Mesh mesh(init.comm());
    unsigned int nx = 5;
    unsigned int ny = 5;
    libMesh::MeshTools::Generation::build_square(mesh, nx, ny, -10.0, 10.0, -10.0,10.0);
    libMesh::EquationSystems equation_system(mesh);

    testEqualNeighborHeuristic demo (mesh,equation_system,"EqualNeighborHeuristic_field");
    demo.addVariableToSystem("random_data");
    demo.populateRandomData();
    demo.findCluster();
    demo.captureClusterID();
    demo.writeOutputData("testEqualNeighborHeuristic.e");
}

