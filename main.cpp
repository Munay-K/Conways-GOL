#include "simulation.h"
#include "ui.h"
#include "world.h"
#include <ctime>

int main() {
  srand(time(0));
  MainMenu menu;
  menu.display();
}
