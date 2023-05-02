from ctypes import cdll
import os
libPath = os.path.dirname(os.path.abspath(
    __file__)) + os.path.sep + './libpycall.so'
lib = cdll.LoadLibrary(libPath)


class Foo(object):
    def __init__(self):
        self.obj = lib.Foo_new()

    def bar(self):
        lib.Foo_bar(self.obj)


f = Foo()
f.bar()
