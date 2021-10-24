#include <iostream>
#include "functions.hpp"
#include "Gamer.hpp"
using namespace std;

int main()
{
  Window* window = new Window(1366,1024,"FieldRunners");
  vector<Enemy*> enemies;
  vector<Tower*> towers;
  vector<Arrow*> arrows;
  vector<int> waves;
  vector<Point> route;
  Point click_position;
  int counter = 0;
  int last_event = 0;
  int wave_number = 1;
  Gamer* gamer = new Gamer();
  get_input(route, enemies, waves);
  while(true)
  {
    counter++;
    draw(window, route, enemies, counter, waves, towers, click_position, wave_number, gamer);
    update(window, click_position, towers, last_event, enemies, gamer);
    delay(100);

  }
  delete(window);
}
