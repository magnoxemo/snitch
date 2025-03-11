#include "GradientJumpHeuristics.h"
#include "libmesh/libmesh.h"
#include "libmesh/mesh_generation.h"
#include <cmath>
#include <cstdlib>

#define alpha 0.01
#define sigma_t_fuel 0.0332
#define sigma_t_mod 0.052

double mean(libMesh::Point &point){

    double x = point(0);
    double y = point(1);

    double cell_size = 4.0; // Distance between pin centers
    double pin_radius = 1.0; // Radius of the fuel region
    double cladding_inner_radius = 1.0; // Inner radius of cladding
    double cladding_outer_radius = 1.2; // Outer radius of cladding

    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            double center_x = i * cell_size;
            double center_y = j * cell_size;
            double dx = x - center_x;
            double dy = y - center_y;
            double distance_from_center = sqrt(dx * dx + dy * dy);

            if (distance_from_center < pin_radius) {
                return  pow(exp(sigma_t_fuel), -sigma_t_fuel * distance_from_center/24);
            } else if (distance_from_center >= cladding_inner_radius && distance_from_center < cladding_outer_radius) {
                return alpha+exp(-sigma_t_fuel / 10 * distance_from_center);
            }
        }
    }

    return exp(-sigma_t_mod * sqrt(point(0) * point(0) + point(1) * point(1)));
}

double standard_dev(libMesh::Point &point) {
    double x = point(0);
    double y = point(1);

    double cell_size = 4.0; // Distance between pin centers
    double pin_radius = 1.0; // Radius of the fuel region
    double cladding_inner_radius = 1.0; // Inner radius of cladding
    double cladding_outer_radius = 1.2; // Outer radius of cladding

    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            double center_x = i * cell_size;
            double center_y = j * cell_size;
            double dx = x - center_x;
            double dy = y - center_y;
            double distance_from_center = sqrt(dx * dx + dy * dy);

            if (distance_from_center < pin_radius) {
                return alpha * pow(sigma_t_fuel, -sigma_t_fuel * distance_from_center);
            } else if (distance_from_center >= cladding_inner_radius && distance_from_center < cladding_outer_radius) {
                return exp(-sigma_t_fuel / 100 * distance_from_center);
            }
        }
    }

    return exp(-20 * sigma_t_mod * sqrt(x * x + y * y));
}

void PopulateStochasticField(libMesh::Mesh &mesh,
                             libMesh::EquationSystems &equation_system,
                             const std::string system_name,
                             const std::string variable_name,
                             const std::string std_variable_name,
                             bool needs_re_init = false) {

    libMesh::LinearImplicitSystem &system =
            equation_system.add_system<libMesh::LinearImplicitSystem>(system_name);

    system.add_variable(variable_name, libMesh::CONSTANT, libMesh::MONOMIAL);
    system.add_variable(std_variable_name, libMesh::CONSTANT, libMesh::MONOMIAL);
    const unsigned int variable_index = system.variable_number(variable_name);
    const unsigned int std_variable_index =
            system.variable_number(std_variable_name);

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
    unsigned int nx = 500;
    unsigned int ny = 500;

    libMesh::MeshTools::Generation::build_square(mesh, nx, ny, -10, 10.0, -10.0,
                                                 10.0);
    libMesh::EquationSystems equation_system(mesh);
    PopulateStochasticField(mesh, equation_system, name_of_the_system,
                            populated_variable_name, populated_std_variable_name);

    GradientJumpHeuristics pseudo_flux_field(mesh, equation_system, name_of_the_system, populated_variable_name);
    pseudo_flux_field.setThreshold(0.9);
    pseudo_flux_field.setComparisonMode(true);
    pseudo_flux_field.setJumpTolerance(0.001);
    pseudo_flux_field.findCluster();
    pseudo_flux_field.setNumberOfColors(23);
    pseudo_flux_field.captureClusterID();
    pseudo_flux_field.writeOutputData("output.e");

    return 0;
}