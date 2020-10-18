#include <pybind11/pybind11.h>

namespace py = pybind11;


int subtract(int a, int b)
{
	return a*b+3;
}

int add(int a, int b)
{
	return a + b*2;
}

int mix(int a, int b, int c)
{
	return a + b * c;
}


struct Pet
{
public:
	int value_public;
	Pet(const std::string &name): name(name){}
	void setName(const std::string &name){this->name = name;}
	const std::string& getName() const {return name;}
	const int& getValue() const {return value;}
private:
	std::string name;
	int value = 223;
};

PYBIND11_MODULE(sample, m)
{
	m.doc() = "Sample for PyBind11";
	py::object name =  py::cast("Pham Trung Duc");
	m.attr("NAME") = name;
	m.attr("PI") = 3.14159265;
	m.def("subtract", &subtract, "A subtract function", py::arg("a") = 3, py::arg("b") = 100);
	m.def("add", &add, "A sum function");

	using namespace pybind11::literals; // Using namespace Literals to shorten the syntax
	m.def("mixture", &mix, "A mix function", "a"_a, "b"_a, "c"_a=24);

	py::class_<Pet>(m, "Pet", py::dynamic_attr()) // Dynamci flags to use dynamic attribute
		.def(py::init<const std::string&>())
		.def("setName", &Pet::setName)
		.def("getName", &Pet::getName)
		.def_property_readonly("value", &Pet::getValue)
		.def("__repr__",[](const Pet& pet){return "<sample.Pet named " + pet.getName() + ">";})
		.def_readwrite("value", &Pet::value_public); // Attribute as property 
}

