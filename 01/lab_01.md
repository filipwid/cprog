# Lab 01


## Dependencies


Create a file *ABmain.cpp* in 01 with the following content
```C++
class A {
  B * b;
  int method(int x) { return x; }
};

struct B {
  A a;
  int memberfunction(int x) { return x; }
};

int main() {
  A a;
  B b;
  int x = b.memberfunction( 3 );
}
```

The file does not compile because the compiler does not know what *struct B* is when compiling *class A*. 
Solve this by doing a forward declaration of *B* by writing *struct B;* at the top of the file. Compile the program. 

Change the type of member variables *a* and *b* and make *b* an object and *a* a pointer.

```C++
struct B;
class A {
  B b;
  int method(int x) { return x; }
};

struct B {
  A * a;
  int memberfunction(int x) { return x; }
};
// ....
```

Compile the program. Note the compile error message you get. A class
forward instruction is not enough. To compile *class A* the compiler
now needs to know the layout of *struct B* as defined in the struct
definition in order to compile.

### header files and implementation files

Put the above code in header and implementation files, in total there should be 5 files. The implementation files are as follows:

1. a main file *mainAB.cpp* with the following content
```C++
#include "A.h"
#include "B.h"
int main() {
  A a;
  B b;
  int x = b.memberfunction( 3 );
}
```

2. implementation file *A.cpp*
```C++
#include "A.h"
int A::method(int x) { return x; }
```

3. implementation file *B.cpp*
```C++
#include "B.h"
int B::memberfunction(int x) { return x; }
```

Write the two headerfiles *A.h* and *B.h* containing the class
definition. Use a forward declaration and, if needed, include the
class definition of the other
class. Do use
[include guards](https://en.wikipedia.org/wiki/Include_guard) or
[pragma once](https://en.wikipedia.org/wiki/Pragma_once) to avoid
multiple includes.

Compile the programs one by one
```
> g++ -c A.cpp
> g++ -c B.cpp
> g++ mainAB.cpp A.o B.o
```

or alltogether

```
> g++ -c mainAB.cpp A.cpp B.cpp
```


#### g++ compiler questions

Put questions and answers in a file _inquiry.md_.

#### Where can you find the manual to g++?

####  What is the purpose of _-Wall_ and _-g_, when passed as arguments to _g++_?

#### What is the difference between an object file, and an executable?

#### What in the example above is a forward declaration?

#### Why is it not possible to have class A containing a B object and B containing an A object? 

`class A { B b; };`
`class B { A a; };`


## Assignment: an improved world of hello

_hello, world_ is a classic program that dates back to 1974, first published
in a paper titled _Programming in C: A tutorial_. The program has one
simple purpose; to print "_hello, world_".

Since the typical implementation is trivial, your task is to write a more
versatile alternative, having the following semantics:

```
> ./hello
Hello, world!
> ./hello "DD1387"
Hello, DD1387!
> ./hello "KTH" 3
Hello, KTH KTH KTH!
> ./hello "KTH" 0
> ./hello "KTH" 2
Hello, KTH KTH!
> ./hello "Malcom X" NaN
error: 2nd argument must be an integral greater than zero!
> ./hello kth dd1387 3
error: Too many arguments!
```

_This assignment is not an exercise in object-oriented programming (OOP), but
a mere introduction to the fundamental parts of C/C++_

### Files

Create the following files under the directory 01 in your personal cprog Git repository.

_main.cpp_:

```cpp
#include <utility> // std::pair
#include "hello.h"
int main (int argc, char* argv[]) {
  std::pair<const char *, int> p = parse_args (argc ,argv);
  if (p.second != -1)
    hello (p.first, p.second);
}
```

_hello.h_:
```cpp
#include <utility>  // std::pair

void hello (const char * name, int count);
std::pair<const char *, int> parse_args (int argc, char * argv[]);
```

_hello.cpp_:
```cpp
#include <iostream>

#include "hello.h"

void hello (const char * name, int count) {
  // TODO
}

std::pair<const char *, int> parse_args (int argc, char * argv[]) {
  // TODO
  return std::make_pair ("TODO", 1);
}
```

### Requirements

* _main.cpp_ contains the definition of the applications _main_-function.
There is no need for you to modify this file, but please make sure that
you understand what is written in it.

* _hello.cpp_ has a corresponding _.h_-header that contains
_forward-declarations_ for the functions you are to implement.

* This header, _hello.h_, is included (_#include_) by
_main.cpp_, and should be included by _hello.cpp_.

* _hello.cpp_ shall be compiled separately, resulting in an
object file that is to be linked into the resulting executable.

* You shall implement a function named _parse\_args_ in a separate
_translation unit_ named _hello.cpp_.
This function is responsible for parsing/interpreting the command line
arguments passed to the application, and shall return a
[_std::pair_](http://en.cppreference.com/w/cpp/utility/pair)
with what to print, and how many times to print it.

* _parse\_args_ shall handle all input errors by returning _-1_
as the second value of the returned _std::pair_, as well as printing
a suitable error message on _stderr_.

* You shall implement a function named _hello_ in a separate
_translation unit_ named _hello.cpp_ (i.e. the same file that
shall contain the implementation of _parse_args_).

* _hello_ is responsible for printing the _hello world_-string on
_stdout_ with the following semantics;

* If the value _zero_ is passed as the second parameter,
    nothing shall be printed.

* If a value greater than _zero_ is passed as the second argument
(_count_), _"Hello, "_ shall be printed followed by
_count_ space-delimited occurrences of the first argument.
The output shall end with an exclamation mark, followed by a new-line.
*Note*: hello ("KTH", 3)* shall print _Hello, KTH KTH KTH!_ (see the
  previous example invocations of the program for more information).

* Correct output from your program shall be printed through
_std::cout_, whereas potential error diagnostics (detected by
_parse\_args_) shall be printed through _std::cerr_.

* ~~Your implementation, _hello.cpp_, [shall be uploaded to, and approved by, _Kattis_](https://kth.kattis.com/problems/kth.cprog.helloworld).~~

* ~~For us to be able to grade your Hello World program you must register on kattis (cprog22) by clicking the link [_I am a student taking this course and I want to register for it on Kattis_](https://kth.kattis.com/courses/DD1388/cprog22). Then click on the "Hello World" assignment, and then on "Join the Session".~~

### Hints

* The argument named _argc_ to _main_ will contain the number of
arguments passed to your application. Remember that the name of the
executable counts to this number.

* The second argument, _argv_, will provide access to the individual
arguments passed to your application.

* _std::atoi_ from _<cstdlib>_ can be used to convert a
_char const *_ to an integer. If the function is unable to interpret
the data as an integer, it will return _0_.




#### Hello world questions

#### What is the purpose of _std::cout_, _std::cerr_, and _std::clog_, respectively?

#### How does #include work?



## Unit testing

Create a file _count_if_followed_by.cpp_ with the following content

```cpp
// .-------------------------------------------------------
// |        count_if_followed_by (data, len, a, b);
// |
// | About: Returns the number of occurances of
// |        a followed by b in the range [data, data+len).
// '-------------------------------------------------------

int count_if_followed_by (char const * p, int len, char a, char b) {
  int        count = 0;
  char const * end = p + len;

  while (p != end) {
    if (*p == a && *(p+1) == b)
      count += 1;

    ++p;
  }

  return count;
}
```

Create a corresponding header file _count_if_followed_by.h_
```cpp
int count_if_followed_by (char const * p, int len, char a, char b);
```

### Task

There is an intentional bug in the definition of
_count_if_followed_by_; it will potentially access one element outside
the range specified.  Collectively, bugs of this sort is most often referred to
as "_off-by-one errors_".

```C++
// expected: result == 0
// outcome: result == 1 (!!!)

char const data[4] = {'G','G','X','G'};
int  const result  = count_if_followed_by (data, 3, 'X', 'G');
```

You are to write tests using a unit test framework. You may use google
test framework or cxxtest. Below are instructions for cxxtest.

### Requirements

* Implement at least three (3) different tests of your own that tests
the correct, and incorrect, behavior of _count_if_followed_by_.

### _cxxtest_ a unit test framework

A unit test framework, such as [_cxxtest_](https://cxxtest.com/), allows a
developer to specify constraints, and the expected behavior, of an
implementation that he/she would like to test.

These rules are later used to generate _unit tests_. These unit
tests will test to see that an implementation behaves as it shall (according to
the previously stated specification).

The steps associated with using a unit test framework for C++ typically
includes the following:

* Specify the constraints and requirements that you would like to test.

* Ask the unit test framework to generate a _test runner_ having
semantics associated with your specifications.

* Compile the _test runner_ into an executable.

* Invoke the executable to commence testing.

### Installing cxxtest

cxxtest needs python installed on your system.

Download cxxtest-4.4.zip or  cxxtest-4.4.tar.gz

You may extract them anywhere but the instructions assume you extract
the files in your $HOME folder.

### Writing a test

Create a file _mytest.h_ with the following content:

```c++
// mytest.h
#include <cxxtest/TestSuite.h>
#include "count_if_followed_by.h"

class MyTestSuite : public CxxTest::TestSuite 
{
public:
  void testCount_if_followed_by( void )
  {
    char const data[4] = {'a','b','a','b'};
    int  const result  = count_if_followed_by (data, 3, 'b', 'a');
    
    TS_ASSERT( result == 1 );
  }
};
```

The cxxtest parser will assume that any member function name that
begins with _test_ is a test.

Asking _cxxtest_ to generate test code called _myrunner.cpp_ from the contents of _mytest.h_
file can be accomplished through the following:

```
> python3 $HOME/cxxtest-4.4/bin/cxxtestgen --error-printer -o myrunner.cpp mytest.h
```

Before we can execute our test, the test code in _myrunner.cpp__ must itself
be compiled it into an executable. This includes linking it together with an
object file that contains our implementation.

Create an object file of our implementation:

```
> g++ -c -o count_if_followed_by.o count_if_followed_by.cpp
```

Compile our _test runner_, and link it with the object file:

```
> g++ -o mytest_runner myrunner.cpp -I$HOME/cxxtest-4.4 count_if_followed_by.o
```

The test can be run by invoking _./mytest_runner_.

*Note: You may simplify the task of generating, and compiling,
test runners by writing a new rule inside your makefile*

### What to test

It is important to test boundary conditions. For linked list and
trees, the empty list, a list with one item, the last item. For
arrays, the first and last (size) index).

Remember to [test that exceptions are thrown](https://cxxtest.com/guide.html#testAssertions) according to lab specifications.

#### unit test questions

#### Why is it important to test the boundary conditions of an implementation, especially in the case of _count_if_followed_by_?

#### Describe how your testcase tests if a pointer is accessing an element outside the range specified


### Good luck
