#include <iostream>
#include <string>

struct Greeter {
  static void sayHello(std::string name) {
    std::cout << "Hello, " << name << "!\n";
  }

  int multiply(int a, int b) { return a * b; }
};

#include "nbind/nbind.h"

NBIND_CLASS(Greeter) {
  construct<>();
  method(sayHello);
  method(multiply);
}
