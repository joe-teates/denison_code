# Program doubly-linked list operations according to the specification in chapter 10 of the textbook. For
# these purposes, Nil should be represented by a nullptr, not a sentinel node. Your implementation
# should match the provided header file list.hpp. Your makefile should produce an object file list.o
# when run with the command make double.

# • Program singly-linked list operations. This implementation should also match the provided header file
# list.hpp. Simply ignore the prev pointer in the Node. Your makefile should produce an object file
# list.o when run with the command make single.

# • Program a test suite for the implementations. Given the dependency list.o implementing the header
# file list.hpp, your makefile should produce an executable file tests when run with the command
# make tests. This executable should run your test suite on the definitions given in list.o and print
# the results to standard output. The results should clearly indicate whether all tests passed or not


double: list.cpp
	g++ -c list.cpp

single: single_list.cpp
	g++ -c single_list.cpp -o list.o

tests: list.o
	g++ testing.cpp list.o -o tests

clean:
	rm tests list.o