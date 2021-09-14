#ifndef UI_H
#define UI_H

#include "simulation.h"
#include "world.h"
#include <iostream>
#include <unistd.h>
#include <vector>

class Menu {
public:
  void get_max_size() {
    for (auto i : options) {
      if (max_size < i.length()) {
        max_size = i.length();
      }
    }
  }

  void print_border() {
    for (int i = 0; i < max_size + 6; ++i) {
      std::cout << '*';
    }
    std::cout << '\n';
  }

  void print_options() {
    int j = 0;
    for (auto i : options) {
      j++;
      std::cout << "| " << j << '.' << i;
      for (int k = 0; k <= max_size - i.length(); ++k) {
        std::cout << ' ';
      }
      std::cout << "|" << '\n';
    }
  }

  void print() {
    print_border();
    print_options();
    print_border();
  }

protected:
  int max_size;
  std::vector<std::string> options;
};

class SimMenu : protected Menu {
private:
  Simulation *m_sim;

  void step_simulation() {
    bool is_running = true;
    short chosen_option;
    while (is_running) {
      m_sim->run_step();

      std::cout << "\nContinue(0), Save Gen(1), Quit(2):  ";
      std::cin >> chosen_option;

      switch (chosen_option) {
      case 0: {
        break;
      }
      case 1: {
        m_sim->run_step(true);
        break;
      }
      case 2: {
        is_running = false;
        break;
      }
      }
    }
  }

  void continuous_simulation() {
    short chosen_option;
    bool is_running = true;
    while (is_running) {
      m_sim->run_step();
      sleep(0.4);
    }
  }

public:
  SimMenu(Simulation *sim) : m_sim(sim) { options = {"Step simulation"}; }

  bool display() {
    short chosen_option;

    print();
    std::cout << "choose an option: ";
    std::cin >> chosen_option;

    switch (chosen_option) {
    case 1: {
      step_simulation();
      break;
    }
    case 2: {
      continuous_simulation();
      break;
    }
    }
    return true;
  }
};

#endif
