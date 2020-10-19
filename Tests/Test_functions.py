from time import sleep
import functions as func


if __name__ == "__main__":
    obj = func.Object()
    sleep(1)
    del obj

    # Test policy
    func.getObject()  # With 'copy' policy, Python delete RValue object after this call
    clone = func.getObject()
    clone.print()  # With 'copy' policy, 'clone' object is deleted by garbage collection of Python

    # Python objects as arguments
    func.printDict({"nam": 24, "my": 40})

    # Python args as arguments
    func.testArgs(1, 2, 3, 45, 6, 7, 9)

    # Python kwargs only
    func.kw_only_default(x=4, y=5)

    # Python args kwargs mixed
    func.kw_mixed(2, y=4, z=7)

    # Revisit default argument
    func.storeObject(func.Object())
    # help(func.storeObject)
    # help(func.storeObjectArgv)

    # On-converting arguments
    print(func.float_only(5.53))
    # print(func.float_only(5)) # Raise TypeError
    print(func.float_prefered(5.53))
    print(func.float_prefered(5))  # Implemented normal

    # Allow/Prohibiting None arguments
    func.has_print(None)

    obj = func.Object()
    func.has_print(obj)
