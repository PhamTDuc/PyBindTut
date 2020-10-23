from dog import Dog
from cat import Cat # Error here

if __name__=="__main__":
	# pet = Pet("Doggy") # Error 'cause no binding provided
	dog = Dog("doggy")
	print(dog.getName())

