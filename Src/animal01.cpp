#include <memory>
#include <string>
#include <pybind11/pybind11.h>

namespace py = pybind11;
class Animal
{
public:
	Animal(const std::string &name): name(name){}
	virtual ~Animal() = default;
	const std::string& getName() const {return this->name;}
	void setName(const std::string &name)
	{
		this->name = name;
	}
protected:
	std::string name;
};


class Dog: public Animal
{
public:
	Dog(const std::string &name): Animal(name){}
	std::string bark() const {return "Woof!!";}
	const char* jump(){return "Jumping jumping jumping";}
	const char* jump(int height){std::string jumper= "Jumping to " + std::to_string(height); return jumper.c_str();}
};


class Pet: public Animal 
{
public:
	enum class Kind {Dog=0, Cat, Pig};
	Pet(const std::string &name, Kind type): Animal(name), type(type){}
	Kind getKind(){return type;}
private:
	Kind type;
};

PYBIND11_MODULE(animal, m)
{
	m.doc() = "Animal inheritance class";
	py::class_<Animal>(m, "Animal")
		.def(py::init<const std::string&>())
		.def_property("name", &Animal::getName, &Animal::setName);

	py::class_<Dog, Animal>(m, "Dog")
		.def(py::init<const std::string&>())
		.def("bark", &Dog::bark, "This dog can bark") // Add helper description to function 
		.def("add_dog",[](const Animal &animal){return std::unique_ptr<Animal>(new Dog("Dog_Noname"));})
		.def("jump",(const char* (Dog::*)()) &Dog::jump, "Default jump")
		.def("jump",(const char* (Dog::*)(int))&Dog::jump, "Jump which a specific height");


	py::class_<Pet> pet(m, "Pet");

	pet.def(py::init<const std::string&, Pet::Kind>())
		.def_property_readonly("type", &Pet::getKind);

	py::enum_<Pet::Kind> (pet, "Kind")
		.value("Dog", Pet::Kind::Dog)
		.value("Cat", Pet::Kind::Cat)
		.value("Pig", Pet::Kind::Pig);
		// .export_values();
}