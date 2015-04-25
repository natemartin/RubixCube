#include <iostream>

#include "cube.h"

using namespace std;

void interactive(Cube& cube) {
  while(true) {
    std::cout << "Enter cube face + modifier" << std::endl;
    int x, y;
    std::cin >> x;
    std::cin >> y;
    cube.RotateFace(x, y);
    cube.PrintCube();
  }
}

int main() {
  Cube cube;
  cube.PrintCube();
  cube.Scramble(100);
  cube.PrintCube();
}
