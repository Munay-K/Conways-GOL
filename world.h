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
      m_alive = starting_cells;
      while (starting_cells > 0) {
        y = random() % m_height;
        x = random() % m_width;
        m_grid[y][x] = 1;
        starting_cells--;
      }
    } else if (starting_cells > 0) {
      std::cout
          << "\003[1;31mWARNING:\033[0mBad usage of random world generator";
    }
  }

  World(int h, int w, bool randomize) : m_height(h), m_width(w) {
    bool value;

    if (randomize == true) {
      m_grid.resize(m_height, std::vector<bool>());

      for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
          value = random() % 2;
          m_grid[y].push_back(value);
        }
      }
    } else {
      m_grid.resize(m_height, std::vector<bool>(m_width, false));
    }
  }

  void evolve() {
    update_stats(3);
    for (int y = 0; y < m_height; ++y) {
      for (int x = 0; x < m_width; ++x) {
        auto neightbors = count_neightbors(y, x);
        auto cell = m_grid[y][x];
        if (cell == true && (neightbors < 2 || neightbors > 3)) {
          cell = false;
          update_stats(1);
        } else if (cell == false && neightbors == 3) {
          cell = true;
          update_stats(2);
        }
      }
    }
  }

  void add_life(int h, int w) { m_grid[h][w] = true; }

  void update_stats(short option) {
    switch (option) {
    // cell died
    case 1: {
      m_died++;
      m_alive--;
    }
    // cell born
    case 2: {
      m_alive++;
      m_born++;
    }
    // new generation evolving
    case 3: {
      m_died = 0;
      m_born = 0;
    }
    }
  }

  int count_neightbors(int y, int x) {
    int counter = 0;
    for (int i = -1; i < 2; ++i) {
      for (int j = -1; j < 2; ++j) {
        int row = (y + i + m_height) % m_height;
        int col = (x + j + m_width) % m_width;
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
