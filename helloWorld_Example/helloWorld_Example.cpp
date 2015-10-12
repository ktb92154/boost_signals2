// boost_signals2.cpp : Defines the entry point for the console application.
//

/* Be sure to add the following in order use BOOST libs correctly
1. Properties -> VC++ Directories -> Include Directories -> C:\%40Development_Zone\boost_1_58_0\stage\lib;
2. Properties -> C/C++ -> General -> Additional Include Directories -> C:\%40Development_Zone\boost_1_58_0;
3. Required for <boost/thread.hpp>
   Properties -> Linker -> General -> Additional Library Directories -> C:\%40Development_Zone\boost_1_58_0\stage\lib;
*/

#pragma warning (disable : 4996)
#include "stdafx.h"
#include <iostream>
#include <boost/signals2.hpp>

struct HelloWorld
{
  void operator()() const
  {
    std::cout << "Hello, World!" << std::endl;
  }
};

struct Hello
{
  void operator()() const
  {
    std::cout << "Hello" << std::endl;
  }
};

struct World
{
  void operator()() const
  {
    std::cout << ", World!" << std::endl;
  }
};

struct GoodMorning
{
  void operator()() const
  {
    std::cout << "... and good morning!" << std::endl;
  }
};


int main(){
  // Signal with no arguments and a void return value
  boost::signals2::signal<void ()> sig;

  // Connect a HelloWorld slot
  sig.connect(1, World());  // connect with group 1
  sig.connect(0, Hello());  // connect with group 0


    // by default slots are connected at the end of the slot list
  sig.connect(GoodMorning());


  // slots are invoked this order:
  // 1) ungrouped slots connected with boost::signals2::at_front
  // 2) grouped slots according to ordering of their groups
  // 3) ungrouped slots connected with boost::signals2::at_back
  // Call all of the slots
  sig();
  std::cin.get();
  return 0;
}