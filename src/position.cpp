#include "position.hpp"

#include <stdexcept>

Position voisine(const Position& pos, int index) {
    Position res = pos;

    switch (index) {
      // 0: up, 1: right, 2: down, 3: left
        case 0:
            res.first--;
            break;
        case 1:
            res.second++;
            break;
        case 2:
            res.first++;
            break;
        case 3:
            res.second--;
            break;
        default:
            break;
    }

    return res;
}


std::ostream& operator<<(std::ostream& out, const Position& pos) {
  out << "{" << pos.first << "," << pos.second << "}" ;
  return out ;
}
