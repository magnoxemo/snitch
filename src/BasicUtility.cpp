#include "BasicUtility.h"

void PopulateSyntheticData(libMesh::Mesh &mesh,
                      libMesh::EquationSystems &equation_system,
                      const std::string system_name,
                      const std::string variable_name,
                      double (*CalculateData)(const libMesh::Point&),
                      bool needs_re_init) {

    libMesh::LinearImplicitSystem& system =
            equation_system.add_system<libMesh::LinearImplicitSystem>(system_name);

    system.add_variable(variable_name, libMesh::CONSTANT, libMesh::MONOMIAL);
    if (needs_re_init){
        equation_system.reinit();
    }
    else{
        equation_system.init();
    }

    libMesh::DofMap &dof_map = system.get_dof_map();
    std::vector<libMesh::dof_id_type> dof_indices;
    for (const auto &elem : mesh.element_ptr_range()) {
        dof_map.dof_indices(elem, dof_indices);
        libMesh::Point p = elem->vertex_average();
        double score = CalculateData(p);
        system.solution->set(dof_indices[0], score );
    }
    system.solution->close();
}
