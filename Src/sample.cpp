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

PYBIND11_MODULE(sample, m)
{
	m.doc() = "Sample for PyBind11";
	m.def("subtract", &subtract, "A subtract function");
	m.def("add", &add, "A sum function");
}

