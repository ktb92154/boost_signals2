// boost_signals2.cpp : Defines the entry point for the console application.
//
#pragma warning (disable : 4996)
#include "stdafx.h"
#include <iostream>
#include <boost/signals2.hpp>
#include <boost/thread.hpp>

void print_args(float x, float y)
{
  std::cout << "The arguments are " << x << " and " << y << std::endl;
}

void print_sum(float x, float y)
{
  std::cout << "The sum is " << x + y << std::endl;
}

void print_product(float x, float y)
{
  std::cout << "The product is " << x * y << std::endl;
}

void print_difference(float x, float y)
{
  std::cout << "The difference is " << x - y << std::endl;
}

void print_quotient(float x, float y)
{
  std::cout << "The quotient is " << x / y << std::endl;
}


int main(){
  // Signal with no arguments and a void return value
  boost::signals2::signal<void (float, float)> sig2;

  sig2.connect(&print_args);
  sig2.connect(&print_sum);
  sig2.connect(&print_product);
  sig2.connect(&print_difference);
  sig2.connect(&print_quotient);

  // slots are invoked this order:
  // 1) ungrouped slots connected with boost::signals2::at_front
  // 2) grouped slots according to ordering of their groups
  // 3) ungrouped slots connected with boost::signals2::at_back
  // Call all of the slots
  sig2(5., 3.);
  std::cin.get();
  return 0;
}