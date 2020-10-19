from classes import Animal, Dog, call_go


class Cat(Animal):
    def go(self, n_times):
        return "meow! " * n_times


class Dachshund(Dog):
    def __init__(self, name):
        Dog.__init__(self)
        self.name = name

    def bark(self):
        return "Yap!"

    def go(self, n_times):
        print(Dog.go(self, n_times))
        return "Yummy"


if __name__ == "__main__":
    dog = Dog()
    print(call_go(dog))

    # Override Virtual function
    cat = Cat()
    print(call_go(cat))
    dachshund = Dachshund("Mia")
    print(dachshund.bark())
    print(dachshund.go(3))
