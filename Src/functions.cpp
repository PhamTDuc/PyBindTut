#include <string>
#include <iostream>
#include<pybind11/pybind11.h>

namespace py = pybind11;

class Object
{
private:
	int data;
public:
	Object(){py::print("Initialize object");}
	Object(const Object&){py::print("Copy Constructor");}
	Object(Object&&){py::print("Move Constructor");}
	virtual ~Object(){py::print("Delete Object");}
	void print(){py::print("Hello from pybind");}
};


Object* getObject()
{
	static Object* obj = new Object();
	return obj;
}


void printDict(py::dict dict)
{
	for(auto item : dict)
	{
		std::cout << "Key:"<<std::string(py::str(item.first))<<" value = "<< std::string(py::str(item.second))<<"\n";
	}
	std::cout<<"\n";
}

void testArgs(py::args args)
{
	int sum = 0;
	int value; 
	for(auto arg:args)
	{	
		value = arg.cast<int>();
		sum += value;
	}

	std::cout << "Sum is " << sum<<'\n'; 
}

void kw_only_default(int x, int y, int z)
{
	py::print("Sum of all x, y, z ", x + y + z);
}


PYBIND11_MODULE(functions, m)
{
	m.doc() = "This function module to test everything about function in pybind11";
	py::class_<Object> object(m, "Object");
					   object.def(py::init<>())
					   		 .def("print", &Object::print);

	// Return value policy 
	m.def("getObject", &getObject, py::return_value_policy::copy);

	// Python object as arguments
	m.def("printDict", &printDict);

	// Python Args
	m.def("testArgs", &testArgs);

	//Python Kwargs Only
	m.def("kw_only_default", &kw_only_default, py::kw_only(), py::arg("x") = 0, py::arg("y") = 0, py::arg("z") = 0);
	m.def("kw_mixed", &kw_only_default, py::arg() = 0, py::kw_only(), py::arg("y") = 0, py::arg("z") = 0);
}
