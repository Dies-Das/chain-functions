#include <comp.hpp>
#include <python_comp.hpp>

#include "my_coefficient.hpp"

float my_function(float x) { return x * x; }

namespace ngcomp {
  void ExploreMesh (shared_ptr<MeshAccess> mesh);
}


PYBIND11_MODULE(cf_comp, m) {
  cout << "Loading cf_comp" << endl;

  m.def("CF_Comp",
        [](shared_ptr<ngcomp::GridFunctionCoefficientFunction> f,shared_ptr<ngfem::CoefficientFunction> g) -> shared_ptr<ngfem::CoefficientFunction>
        { return make_shared<ngfem::CF_Comp>(f,g); },
        "Chain GridFunctionCoefficientFunction with CoefficientFunction",
        py::arg("f"),
        py::arg("g"));
  m.def("CF_Comp",
        [](shared_ptr<ngcomp::GridFunction> f,shared_ptr<ngfem::CoefficientFunction> g) -> shared_ptr<ngfem::CoefficientFunction>
        { return make_shared<ngfem::CF_Comp>(dynamic_pointer_cast<ngcomp::GridFunctionCoefficientFunction>(f),g); },
        "Chain GridFunctionCoefficientFunction with CoefficientFunction",
        py::arg("f"),
        py::arg("g"));
}
