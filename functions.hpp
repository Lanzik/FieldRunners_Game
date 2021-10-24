#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "./src/rsdl.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include "Gamer.hpp"
#include <sstream>
#include <vector>

using namespace std;

#define NUMBER_TYPE_ENEMY 4
#define ZERO 0
#define SUPER_TROOPER 2
#define STUBBORN_RUNNER 1
#define RUNNER 0

void draw(Window* window, vector<Point> route, vector<Enemy*> enemies,
     int &counter, vector<int> waves, vector<Tower*> towers, Point click_position,
      int &wave_number, Gamer* gamer);
void draw_tower(Window* window, vector<Tower*> towers);
void fire_tower(vector<Tower*> towers,vector<Enemy*> enemies, int counter, Gamer* gamer);
void draw_arrow(Window* window, vector<Tower*> towers);
bool calculate_wave_number(vector<int> waves, vector<Enemy*> enemies, int wave_number
     , vector<Point> route, Gamer* gamer, Window* window);
void run_enemy(Window* window, vector<Point> route, vector<Enemy*> enemies,
     int counter, vector<int> waves, int wave_number, Gamer* gamer);

void update(Window* window, Point &click_position, vector<Tower*> &towers, int &last_event
, vector<Enemy*> enemies, Gamer* gamer);
void create_wave(vector<int> &waves, vector<int> number_enemies);
void create_enemies_wave(vector<int> number_enemies, vector<Enemy*> &enemies,
   vector<Point> route, int wave_number);
void get_input(vector<Point> &route, vector<Enemy*> &enemies, vector<int> &waves);
void upgrade_tower(Point click_position, vector<Tower*> towers, Window* window, Gamer* gamer);
Point coordinate_to_number(Point point);

#endif
