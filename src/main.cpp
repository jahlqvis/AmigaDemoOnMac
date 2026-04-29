#include "app.hpp"

#include <exception>
#include <iostream>

int main() {
  try {
    App app;
    if (!app.initialize()) {
      std::cerr << "Initialization failed\n";
      return 1;
    }

    app.run();
    app.shutdown();
    return 0;
  } catch (const std::exception& ex) {
    std::cerr << "Fatal error: " << ex.what() << "\n";
    return 1;
  }
}
