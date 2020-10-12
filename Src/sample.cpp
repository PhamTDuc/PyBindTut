#include <pybind11/pybind11.h>

namespace py = pybind11;


int subtract(int a, int b)
{
	return a - b;
}


PYBIND11_MODULE(sample, m)
{
	m.doc() = "Sample for PyBind11";
	m.def("subtract", &subtract, "A subtract function");
}

