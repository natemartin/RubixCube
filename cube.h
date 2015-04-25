#include <array>
#include <map>

class Cube {
 private:
  int cube_data[6][9];
  void TurnFace(int face, int adj1, int edge1, int adj2, int edge2, int adj3, int edge3, int adj4, int edge4);
  std::array<int, 3> GetEdge(int face, int edge);
  void PutEdge(int face, int edge, std::array<int, 3> new_edge);
  const std::map<int, std::array<int, 3>> edge_to_idx_map =
      {{0, {{0,1,2}}}, {1, {{2,5,8}}}, {2, {{6,7,8}}}, {3, {{6,3,0}}}};
 public:
  void RotateFace(int face, int modifier);
  void PrintCube();
  void Scramble(int steps);
  Cube();
};
