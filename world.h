#ifndef WORLD_H
#define WORLD_H

#include <ctime>
#include <iostream>
#include <vector>

class World {
private:
  int m_height = 0;
  int m_width = 0;
  int m_alive = 0;
  int m_died = 0;
  int m_born = 0;
  std::vector<std::vector<bool>> m_grid;

public:
  World(int h, int w) : m_height(h), m_width(w) {
    m_grid.resize(m_height, std::vector<bool>(m_width, false));
  }

  World(int h, int w, bool randomize, int starting_cells)
      : m_height(h), m_width(w) {
    bool value;
    int x, y;
    m_grid.resize(m_height, std::vector<bool>(m_width, false));
    if (randomize == true) {
      while (starting_cells > 0) {
        y = random() % m_height;
        x = random() % m_width;
        m_grid[y][x] = 1;
        starting_cells--;
      }
    } else {
      for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
          std::cout << "cell [" << x << "][" << y << "] value :";
          std::cin >> value;
          m_grid[y][x] = value;
        }
      }
    }
  }

  void evolve() {
    update_stats('e');
    for (int y = 0; y < m_height; ++y) {
      for (int x = 0; x < m_width; ++x) {
        auto neightbors = count_neightbors(m_grid, x, y);
        auto cell = m_grid[y][x];
        if (cell == true && (neightbors < 2 || neightbors > 3)) {
          cell = false;
          update_stats('d');
        } else if (cell == false && neightbors == 3) {
          cell = true;
          update_stats('b');
        }
      }
    }
  }

  void update_stats(char option) {
    // cell died
    if (option == 'd') {
      m_died++;
      m_alive--;
    }
    // cell born
    if (option == 'b') {
      m_alive++;
      m_born++;
    }
    // new generation evolving
    if (option == 'e') {
      m_died = 0;
      m_born = 0;
    }
  }

  int count_neightbors(std::vector<std::vector<bool>> grid, int x, int y) {
    int counter = 0;
    for (int i = -1; i < 2; ++i) {
      for (int j = -1; j < 2; ++j) {
        int row = (x + i + m_height) % m_height;
        int col = (y + j + m_width) % m_width;
        counter += m_grid[col][row];
      }
    }
    return counter;
  }

  void print() {
    for (auto row : m_grid) {
      for (auto cell : row) {
        if (cell == true) {
          std::cout << "██";
        } else {
          std::cout << "░░";
        }
      }
      std::cout << '\n';
    }
  }

  int get_alive() { return m_alive; }
  int get_died() { return m_died; }
  int get_born() { return m_born; }
};

#endif
