#ifndef SIMULATION_H
#define SIMULATION_H

#include "generation.h"
#include "world.h"
#include <iostream>
#include <vector>

class Simulation {
private:
  World m_world;
  int m_gen_number;
  std::vector<Generation *> m_generations;

public:
  Simulation(World wld) : m_world(wld) { m_gen_number = 1; }
  ~Simulation() {
    for (auto &gen : m_generations) {
      delete gen;
    }
  };

  void print(World wld, Generation &gen) {
    system("clear");
    wld.print();
    std::cout << '\n';
    gen.print();
  }

  void run_step() {
    Generation gen(m_world, m_gen_number);
    m_gen_number++;
    print(m_world, gen);
    m_world.evolve();
  }

  void run_step(bool save) {
    Generation *gen = new Generation(m_world, m_gen_number);
    if (save == true) {
      save_gen(gen);
    };
    m_gen_number++;
    print(m_world, *gen);
    m_world.evolve();
  }

  void save_gen(Generation *gen) { m_generations.push_back(gen); }
};

#endif
