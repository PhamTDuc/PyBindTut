#include <pybind11/pybind11.h>

namespace py = pybind11;

class Example
{
private:
	int data; 
	Example(int value):data(value){}
public:
	static Example create(int value){retrun Example(value);}
	int get() const {return data;}
};


PYBIND11_MODULE(custom_constructor, m)
{
	m.doc() = "Custom Constructor demo";
	py::class_<Example>(m, "Example")
		.def(py::init(&Example::create), py::arg() = 0);
		.def("get", Example::get);
}