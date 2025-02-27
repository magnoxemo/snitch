#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

#include "libmesh/mesh_generation.h"
#include "libmesh/libmesh.h"
#include "EqualNeighborHeuristic.h"

void PopulateRandomIntegers(libMesh::Mesh &mesh, libMesh::LinearImplicitSystem &system) {
    libMesh::DofMap &dof_map = system.get_dof_map();
    std::vector<libMesh::dof_id_type> dof_indices;
    for (const auto &elem : mesh.element_ptr_range()) {

        dof_map.dof_indices(elem, dof_indices);
        int random_int = rand() % 5;
        system.solution->set(dof_indices[0], 5 - random_int);
    }
    system.solution->close();
}

void AddVariableToSystem(libMesh::EquationSystems &equation_system,
                          libMesh::LinearImplicitSystem &system, std::string var_name,
                          bool needs_re_init = false) {
    system.add_variable(var_name, libMesh::CONSTANT, libMesh::MONOMIAL);
    if (!needs_re_init) {
        equation_system.init();
    } else {
        equation_system.reinit();
    }
}
int main(int argc, char **argv){
    //preparing the mesh and the data
    libMesh::LibMeshInit init(argc, argv);
    libMesh::Mesh mesh(init.comm());
    unsigned int nx = 5;
    unsigned int ny = 5;
    libMesh::MeshTools::Generation::build_square(mesh, nx, ny, -10.0, 10.0, -10.0,10.0);
    libMesh::EquationSystems equation_system(mesh);
    libMesh::LinearImplicitSystem &system =equation_system.add_system<libMesh::LinearImplicitSystem>("random_solution_field");
    AddVariableToSystem(equation_system,system,"random_data");
    PopulateRandomIntegers(mesh,system);

    //actual clustering process
    /* Now the framework presumes I have the mesh and equation_system
     * and I am fully aware what is the name and type of the system (for now we are only allowing LinearImplicitSystem)
     * which solution field (name of the variable) should be */
    EqualNeighborHeuristic demo (mesh,equation_system,"random_solution_field","random_data");
    demo.findCluster();
    demo.captureClusterID();
    demo.writeOutputData("output.e");
}

