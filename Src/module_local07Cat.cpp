#include <iostream>
#include <pybind11/pybind11.h>
#include "module_local07LIB.h"

namespace py = pybind11;

namespace pets
{
	class Cat: public Pet
	{
	public:
		Cat(std::string &name):Pet(name){}
	};
}

PYBIND11_MODULE(cat, m)
{
	m.doc() = "Module-local Cat class bindings";
	py::class_<pets::Pet>(m, "Pet", py::module_local())
		// .def(py::init<std::string&>())
		.def("getName", &pets::Pet::getName);

	py::class_<pets::Cat, pets::Pet>(m, "Cat")
		.def(py::init<std::string&>());
}