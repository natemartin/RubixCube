#include <iostream>
#include <array>
#include <random>
#include <functional>
#include <sys/time.h>

#include "cube.h"

void Cube::Scramble(int steps) {
  struct timeval current_time;
  gettimeofday(&current_time, NULL);
  std::minstd_rand generator(current_time.tv_usec);
  std::uniform_int_distribution<int> distribution(0,5);
  auto get_num = std::bind(distribution, generator);
  for(int i = 0; i < steps; i++) {
    RotateFace(get_num(), get_num() % 3);
  }
}

void Cube::PutEdge(int face, int edge, std::array<int, 3> new_edge) {
  auto edge_indicies = edge_to_idx_map.at(edge);
  cube_data[face][edge_indicies[0]] = new_edge[0];
  cube_data[face][edge_indicies[1]] = new_edge[1];
  cube_data[face][edge_indicies[2]] = new_edge[2];
}

std::array<int, 3> Cube::GetEdge(int face, int edge) {
  std::array<int, 3> ret;
  auto edge_indicies = edge_to_idx_map.at(edge);
  ret[0] = cube_data[face][edge_indicies[0]];
  ret[1] = cube_data[face][edge_indicies[1]];
  ret[2] = cube_data[face][edge_indicies[2]];
  return ret;
}

// Helper method to turn the face of the cube, assumes counter clockwise twist.
void Cube::TurnFace(int face, int adj1, int edge1, int adj2, int edge2, int adj3, int edge3, int adj4, int edge4) {
  // Rotate the face itself
  int old_face[9];
  std::copy(std::begin(cube_data[face]), std::end(cube_data[face]), std::begin(old_face));
  cube_data[face][0] = old_face[6];
  cube_data[face][1] = old_face[3];
  cube_data[face][2] = old_face[0];
  cube_data[face][3] = old_face[7];
  cube_data[face][5] = old_face[1];
  cube_data[face][6] = old_face[8];
  cube_data[face][7] = old_face[5];
  cube_data[face][8] = old_face[2];

  // Rotate edges
  auto e1 = GetEdge(adj1, edge1);
  auto e2 = GetEdge(adj2, edge2);
  auto e3 = GetEdge(adj3, edge3);
  auto e4 = GetEdge(adj4, edge4);
  PutEdge(adj1, edge1, e2);
  PutEdge(adj2, edge2, e3);
  PutEdge(adj3, edge3, e4);
  PutEdge(adj4, edge4, e1);
}

void Cube::RotateFace(int face, int modifier) {
  //Break rotate into a primitive rotation
  for(int i = 0; i <= modifier; i++) {
    switch(face) {
      case 0:
        TurnFace(0,1,0,2,0,3,0,4,0);
        break;
      case 1:
        TurnFace(1,0,2,2,3,5,0,4,1);
        break;
      case 2:
        TurnFace(2,1,1,0,1,3,3,5,1);
        break;
      case 3:
        TurnFace(3,0,0,2,1,4,3,5,2);
        break;
      case 4:
        TurnFace(4,0,3,3,1,1,3,5,3);
        break;
      case 5:
        TurnFace(5,1,2,2,2,3,2,4,2);
        break;
    }
  }
}

void Cube::PrintCube() {
  for(int i = 0; i < 6; i++) {
    std::cout << std::endl << "Face: " << i;
    for(int j = 0; j < 9; j++) {
      if(j % 3 == 0) std::cout << std::endl;
      std::cout << cube_data[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

Cube::Cube() {
  for(int i = 0; i < 6; i++) {
    std::fill_n(cube_data[i], 9, i);
  }
}
