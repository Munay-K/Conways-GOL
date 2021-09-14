#include "simulation.h"
#include "ui.h"
#include "world.h"
#include <ctime>

int main() {
  srand(time(0));
  World world(70, 70, true, 420);
  Simulation *sim = new Simulation(world);
  SimMenu menu(sim);

  menu.display();
}
