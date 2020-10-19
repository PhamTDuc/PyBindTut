#include <string>
#include <pybind11/pybind11.h>

namespace py = pybind11;

class Animal
{
public:
	virtual ~Animal(){}
	virtual std::string go(int n_times) const = 0;
};

// Overriding virtual functions: 
// Extend 'Animal' class in python with 'PyAnimal' class helper
// however, that the above is sufficient for allowing python classes to extend Animal, but not Dog
class PyAnimal : public Animal
{
public:
	using Animal::Animal;

	// Trampline (need one for each virtual function)
	std::string go(int n_times) const override
	{
		PYBIND11_OVERLOAD_PURE(
			std::string,
			Animal,
			go, 
			n_times
		);
	}
};

class Dog : public Animal
{
public:
	std::string go(int n_times) const  
	{
		std::string result;
		for(int i=0; i<n_times;++i)
			result += "woof! ";
		return result;
	}
};

std::string call_go(const Animal *animal)
{
	return animal->go(4);
}



PYBIND11_MODULE(classes, m)
{
	py::class_<Animal, PyAnimal> (m, "Animal")
		.def(py::init<>())
		.def("go", &Animal::go);

	py::class_<Dog, Animal> (m, "Dog")
		.def(py::init<>())
		.def("go", &Dog::go);

	m.def("call_go", &call_go);
}