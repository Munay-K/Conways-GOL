#ifndef SIMULATION_H
#define SIMULATION_H

#include "generation.h"
#include "world.h"
#include <iostream>
#include <vector>

class Simulation {
private:
  World *m_world;
  int m_gen_number = 1;
  std::vector<Generation *> m_generations;

public:
  Simulation(World *wld) : m_world(wld) {}
  ~Simulation() {
    for (auto &gen : m_generations) {
      delete gen;
    }
  };

  void print_saved_gen(int pos) {
    auto gen_world = m_generations[pos]->get_world();
    gen_world.print();
    std::cout << '\n';
    m_generations[pos]->print();
  }

  void run_step() {
    Generation gen(*m_world, m_gen_number);
    m_world->print_grid();
    m_world->evolve();
    gen.update_stats(m_world);
    std::cout << "Gen: " << m_gen_number << '\n';
    m_world->print_stats();
    m_gen_number++;
  }

  void run_step(bool save) {
    Generation *gen = new Generation(*m_world, m_gen_number);
    m_world->print_grid();
    m_world->evolve();
    gen->update_stats(m_world);
    std::cout << "Gen: " << m_gen_number << '\n';
    m_world->print_stats();

    m_gen_number++;
    if (save == true) {
      save_gen(gen);
    }
  }

  void save_gen(Generation *gen) { m_generations.push_back(gen); }
};

#endif
