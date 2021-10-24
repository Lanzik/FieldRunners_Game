#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "./src/rsdl.hpp"
#include <vector>
#include "definitions.hpp"
#include "Gamer.hpp"

using namespace std;

struct place
{
  float x;
  float y;
};

class Enemy
{
public:
  void run(vector<Point> route, vector<Enemy*> enemies, vector<int> waves, Window* window);
  bool end_route(vector<Point> route, Gamer* gamer, Window* window);
  place get_current_place(){return current_place;}
  void hit(int damage);
  void reset_counter_picture(int quantity);
  bool reach_next_place();
  bool find_current_place(Point place_number);
  void next_replace(Point next_number_place);
  bool check_alive(Gamer* gamer);
  void draw_bar(Window* window, int initial_health);
  int lost_blood_bar(int initial_health);
  int blood_bar(int initial_health);
  virtual void render_picture(Window* window, string direction) = 0;

protected:
  float health;
  int reward;
  int hurt;
  place current_place;
  place next_place;
  int counter_picture;
  float velocity;
  int wave_number;
  int existence;
};

class Runner : public Enemy
{
public:
  Runner(place current_place_, place next_place_, int wave_number_);
  void render_picture(Window* window, string direction);
private:
};

class Stubborn_Runner : public Enemy
{
public:
  Stubborn_Runner(place current_place_, place next_place_, int wave_number_);
  void render_picture(Window* window, string direction);
};

class Super_Trooper : public Enemy
{
public:
  Super_Trooper(place current_place_, place next_place_, int wave_number_);
  void render_picture(Window* window, string direction);
private:

};

class Scrambler : public Enemy
{
public:
  Scrambler(place current_place_, place next_place_, int wave_number_);
  void render_picture(Window* window, string direction);
private:

};

#endif
