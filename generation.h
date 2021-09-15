#ifndef GENERATION_H
#define GENERATION_H

#include "world.h"
#include <iostream>

class Generation {
public:
  Generation(World wld, int gen) : m_world(wld) {
    m_stats[0] = gen;
    m_stats[1] = wld.get_alive();
    m_stats[2] = wld.get_died();
    m_stats[3] = wld.get_born();
  }

  void print() {
    std::cout << "Gen: " << m_stats[0] << '\n';
    std::cout << "Cells Alive: " << m_stats[1] << '\n';
    std::cout << "Total died: " << m_stats[2] << '\n';
    std::cout << "Total born: " << m_stats[3] << '\n';
  }

private:
  World m_world;
  int m_stats[4]{}; // number,alive, died, born
};

#endif
