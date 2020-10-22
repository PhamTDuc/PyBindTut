#include <pybind11/pybind11.h>

namespace py = pybind11;

class Animal {
public:
    virtual std::string go(int n_times) const = 0;
    virtual std::string name() const { return "unknown"; }
};

class Dog : public Animal {
public:
    std::string go(int n_times) const override {
        std::string result;
        for (int i=0; i<n_times; ++i)
            result += bark() + " ";
        return result;
    }
    virtual std::string bark() const { return "woof!"; }
};

// When combining virtual methods with inheritance, 
// you need to be sure to provide an override for each method for which you want to allow overrides from derived python classes (NOT SURE)
class PyAnimal: public Animal
{
public:
	using Animal::Animal;
	std::string go(int n_times) const override {PYBIND11_OVERLOAD_PURE(std::string, Animal, go, n_times);}
	std::string name() const override {PYBIND11_OVERLOAD(std::string, Animal, name,);}
};

class PyDog: public Dog
{
public:
	using Dog::Dog;
	std::string go(int n_times) const override {PYBIND11_OVERLOAD(std::string, Dog, go, n_times);}
	std::string name() const override {PYBIND11_OVERLOAD(std::string, Dog, name,);}
	std::string bark() const override {PYBIND11_OVERLOAD(std::string, Dog, bark,) ;}
};

PYBIND11_MODULE(classes_combined, m)
{
	py::class_<Animal, PyAnimal>(m, "Animal")
		.def(py::init<>())
		.def("go", &Animal::go)
		.def("name", &Animal::name);


	py::class_<Dog, PyDog>(m, "Dog")
		.def(py::init<>())
		.def("go", &Dog::go)
		.def("name", &Dog::name)
		.def("bark", &Dog::bark);
}