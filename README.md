# AString
A simple quest to make a better "String" data type in C++.

This project is rather simple, using a similar model to the standard
"string" class, I want to add more functionality with integral types like
int, float, and double.

I want to add the full functionality of overloaded operators for:
                  Appending; 
                  Concatenation; 
                  Equality; 
                  Assignment; 
                  Retrieval and modification of a char in the AStringBuffer object
                  
In the end I would like to have an AString object that points to a single AStringBuffer
instance. It would be useful in preventing unneccesary copying when two AStringBuffers
are alike. I also want to allow for use of static data on strings <64 characters in size 
(including /0).

In a nutshell, I would like to make an easy, efficient, portable, and stable alternative
to C++'s standard std::string class. Although this is not a unique project, I am trying
to create a tool that I can understand fully and is useful to almost all applications.
