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
}
