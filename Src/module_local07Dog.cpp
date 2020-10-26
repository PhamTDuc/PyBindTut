#include <iostream>
#include <pybind11/pybind11.h>
#include "module_local07LIB.h"

namespace py = pybind11;

namespace pets
{
	class Dog: public Pet
	{
	public:
		Dog(std::string &name):Pet(name){}
	};
}

PYBIND11_MODULE(dog, m)
{
	m.doc() = "Module-local Dog class bindings";
	py::class_<pets::Pet>(m, "Pet", py::module_local())
		// .def(py::init<std::string&>())
		.def("getName", &pets::Pet::getName);

	py::class_<pets::Dog, pets::Pet>(m, "Dog")
		.def(py::init<std::string&>());
}