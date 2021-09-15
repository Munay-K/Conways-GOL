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
    get_max_size();
    int pos = 0;
    for (auto i : options) {
      pos++;
      std::cout << "| " << pos << '.' << i;
      for (int j = 0; j <= max_size - i.length(); ++j) {
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
  int max_size = 0;
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

      std::cout << "\nContinue(1), Save Gen(2), Quit(3):  ";
      std::cin >> chosen_option;

      switch (chosen_option) {
      case 1: {
        break;
      }
      case 2: {
        m_sim->run_step(true);
        break;
      }
      case 3: {
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
      sleep(0.3);
    }
  }

public:
  SimMenu(Simulation *sim) : m_sim(sim) {
    options = {"Step simulation", "continuous_simulation"};
  }

  bool display() {
    system("clear");
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

class MainMenu : protected Menu {
private:
  World *m_world;
  int height = 0;
  int width = 0;

  void create_world() {
    if (m_world != NULL) {
      char is_continue;
      std::cout << "\003[1;31m WARNING: \033[0m Current World will be destroy, "
                   "continue? (Y/N): ";
      std::cin >> is_continue;

      if (!is_continue)
        return;
    }

    std::cout << "Specify size \"Y,X\": ";
    std::cin >> height;
    width = height;

    options = {"Defined alive cells", "Completly Random",
               "Random with X cells alive", "Quit"};
    short chosen_option;
    bool is_running = true;

    while (is_running) {
      system("clear");
      print();
      std::cout << "choose an option: ";
      std::cin >> chosen_option;

      switch (chosen_option) {
      case 1: {
        m_world = new World(height, width);
        add_cells_prompt();
        break;
      }
      case 2: {
        m_world = new World(height, width, true);
        break;
      }
      case 3: {
        initial_random();
        break;
      }
      case 4: {
        return;
        break;
      }
      }
    }
  }

  void initial_random() {
    int starting_cells = 0;
    std::cout << "How many cells should be alive? (less than " << height * width
              << "): ";
    std::cin >> starting_cells;

    m_world = new World(height, width, true, starting_cells);
    return;
  }
  void add_cells_prompt() {
    bool is_running = true;

    while (is_running) {
      std::string input;
      short pos = 0;
      std::string temp;
      int values[2]{};

      std::cout << "write coordinates \"Y,X\" or \"Q\" for quit: ";
      std::cin >> input;

      for (auto character : input) {
        if (character != ',' && character != '\n') {
          if (character == 'Q') {
            return;
          }
          temp += character;
        } else {
          values[pos] = std::stoi(temp);
          pos++;
        }
      }

      if (values[0] <= height && values[1] <= width && values[0] >= 0 &&
          values[1] >= 0) {
        m_world->add_life(values[0], values[1]);
      }
    }
  }

  void show_world() {
    if (m_world == NULL) {
      std::cout << "There's no current world saved.\n";
    } else {
      m_world->print();
      std::cout << "Press any key to continue.\n";
      std::cin;
    }
  }

  void start_simulation() {
    if (m_world == NULL) {
      std::cout << "There's no current world saved.\n";
    } else {
      Simulation *sim = new Simulation(m_world);
      SimMenu menu(sim);
      menu.display();
    }
  }

public:
  bool display() {
    system("clear");
    options = {"Create new World", "Show World", "Simulation", "Saved stats",
               "Quit"};
    short chosen_option;
    bool is_running = true;

    while (is_running) {
      system("clear");
      options = {"Create new World", "Show World", "Simulation", "Saved stats",
                 "Quit"};
      print();
      std::cout << "choose an option: ";
      std::cin >> chosen_option;

      switch (chosen_option) {
      case 1: {
        create_world();
        break;
      }
      case 2: {
        show_world();
        break;
      }
      case 3: {
        start_simulation();
        break;
      }
      case 4: {
        break;
      }
      case 5: {
        return true;
        break;
      }
      }
    }
    return true;
  }
};

#endif
