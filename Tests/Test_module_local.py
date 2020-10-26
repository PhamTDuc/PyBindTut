from dog import Dog
from cat import Cat # Error here if py::module_local() not provided

if __name__=="__main__":
	# pet = Pet("Doggy") # Error 'cause no binding provided
	dog = Dog("doggy")
	cat = Cat("Jimmy")
	print(dog.getName())
	print(cat.getName())

