all:
	swig -c++ -python BigClass.i
	g++ -fPIC -c BigClass.cpp
	g++ -fPIC -c Struct.cpp
	g++ -fPIC -c BigClass_wrap.cxx -I/usr/include/python2.7 
	g++ -shared BigClass.o Struct.o BigClass_wrap.o -o _BigClass.so