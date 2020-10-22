#include <string>
#include <pybind11/pybind11.h>

namespace py = pybind11;

class Example
{
private:
	int data; 
	Example(int value):data(value){}
public:
	static Example create(int value){return Example(value);}
	Example(double){py::print("Example argument with double");}; 
	Example(int, int){py::print("Example argument with 2 integers");};
	Example(std::string&);


	int get() const {return data;}
};

class Pet
{
private:
	int data; 
public: 
	Pet(int value): data(value){}
	int get() {return data;}
	virtual void print() const= 0;
	virtual ~Pet() = default; 
};

class PyPet: public Pet 
{
public:
	using Pet::Pet;
	PyPet(Pet &&base): Pet(std::move(base)){}
	void print() const override {PYBIND11_OVERLOAD_PURE(void, Pet, print,);}
};


PYBIND11_MODULE(custom_constructor, m)
{
	m.doc() = "Custom Constructor demo";
	py::class_<Example>(m, "Example")
		.def(py::init(&Example::create), py::arg() = 0)
		.def(py::init([](std::string&){py::print("Example argument with String"); return Example::create(0);}))
		.def("get", &Example::get);

	py::class_<Pet, PyPet>(m, "Pet")
		.def(py::init<int>())
		.def("get", &Pet::get)
		.def("print", &Pet::print);

}