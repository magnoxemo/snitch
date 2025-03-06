#include "libmesh/libmesh.h"
#include "libmesh/mesh_generation.h"
#include <cmath>
#include <cstdlib>
#include "ThresholdHeuristics.h"

#define alpha 0.01
#define sigma_t_fuel 0.0332
#define sigma_t_mod 0.052

double mean(libMesh::Point &point) {
    if (sqrt(point(0)*point(0)+point(1)*point(1))<5){
        return exp(-sigma_t_fuel*sqrt(point(0)*point(0)+point(1)*point(1)));
    }
    else{
        return exp(-sigma_t_mod*sqrt(point(0)*point(0)+point(1)*point(1)));
    }
}
double standard_dev(libMesh::Point &point) {

    if (sqrt(point(0)*point(0)+point(1)*point(1))<5){
        return alpha*pow(sigma_t_fuel,-sigma_t_fuel*sqrt(point(0)*point(0)+point(1)*point(1)));
    }
    else{
        return alpha*pow(sigma_t_mod,-sigma_t_mod*sqrt(point(0)*point(0)+point(1)*point(1)));
    }
}

void PopulateStochasticField(libMesh::Mesh &mesh,
                             libMesh::EquationSystems &equation_system,
                             const std::string system_name,
                             const std::string variable_name,
                             const std::string std_variable_name,
                             bool needs_re_init = false) {

    libMesh::LinearImplicitSystem &system = equation_system.add_system<libMesh::LinearImplicitSystem>(system_name);

    system.add_variable(variable_name, libMesh::CONSTANT, libMesh::MONOMIAL);
    system.add_variable(std_variable_name, libMesh::CONSTANT, libMesh::MONOMIAL);
    const unsigned int variable_index = system.variable_number(variable_name);
    const unsigned int std_variable_index = system.variable_number(std_variable_name);

    if (needs_re_init) {
        equation_system.reinit();
    } else {
        equation_system.init();
    }

    libMesh::DofMap &dof_map = system.get_dof_map();
    std::vector<libMesh::dof_id_type> dof_indices;
    for (const auto &elem : mesh.element_ptr_range()) {
        dof_map.dof_indices(elem, dof_indices);
        libMesh::Point p = elem->vertex_average();
        system.solution->set(dof_indices[variable_index], mean(p));
        system.solution->set(dof_indices[std_variable_index], standard_dev(p));
    }
    system.solution->close();
}

int main(int argc, char **argv) {

    std::string name_of_the_system = "polynomial_solution_field";
    std::string populated_variable_name = "polynomial_data";
    std::string populated_std_variable_name = "std_data";
    libMesh::LibMeshInit init(argc, argv);
    libMesh::Mesh mesh(init.comm());
    unsigned int nx = 100;
    unsigned int ny = 100;

    libMesh::MeshTools::Generation::build_square(mesh, nx, ny, -10, 10.0, -10.0,
                                                 10.0);
    libMesh::EquationSystems equation_system(mesh);
    PopulateStochasticField(mesh, equation_system, name_of_the_system,
                            populated_variable_name,populated_std_variable_name);

    ThresholdHeuristics std_field(mesh, equation_system, name_of_the_system,
                                                populated_std_variable_name);
    std_field.setTolerance(0.06);
    std_field.findCluster();
    std_field.setNumberOfColors(23);
    std_field.captureClusterID();
    std_field.writeOutputData("output.e");

    return 0;
}