from access_py_lib import makeDirectory
import os

if __name__=="__main__":
	dir = os.path.dirname(os.path.realpath(__file__))
	makeDirectory(dir, "hello//world")