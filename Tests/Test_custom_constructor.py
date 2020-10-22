from custom_constructor import Example, Pet


example = Example(521)
print(example.get())
example_02 = Example("Hello the world")
print(example_02.get())

class Dog(Pet):
	def print(self):
		print("Hello the world")

dog = Dog(100)
print("Number get from dog:", dog.get())
dog.print()