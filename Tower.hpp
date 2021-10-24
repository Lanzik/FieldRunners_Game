#ifndef __TOWER_H__
#define __TOWER_H__

#include "./src/rsdl.hpp"
#include "Enemy.hpp"

class Arrow
{
public:
  Arrow(place current_place_, Enemy* enemy);
  place get_current_place(){return current_place;}
  int get_existence(){return existence;}
  virtual void follow_target();
  virtual void remove();
  bool arrive_target();
  virtual void hit_target(int damage_, Window* window);
protected:
place current_place;
int existence;
Enemy* target;
};

class Tower
{
public:
  virtual void draw(Window* window) = 0;
  virtual void create_arrow(Enemy* enemy) = 0;
  virtual void move_arrow(Window* window) = 0;
  virtual void upgrade_tower(Window* window, Gamer* gamer) = 0;
  bool fire_possible(Enemy* enemy, int counter, Gamer* gamer);
  bool check_distance(Point place_point_, Enemy* enemy, int distance);
  Point get_place_point(){return place_point;}
protected:
  int damage;
  int buy_price;
  int level;
  Point place_point;
  vector<Arrow> arrows;
  int fire_speed;
};

class Gatling : public Tower
{
public:
  Gatling(Point place_point_, Gamer* gamer);
  void draw(Window* window);
  void create_arrow(Enemy* enemy);
  void move_arrow(Window* window);
  void upgrade_tower(Window* window, Gamer* gamer);
private:
};

class Missile : public Tower
{
public:
  Missile(Point place_point_, Gamer* gamer, vector<Enemy*> enemies_);
  void draw(Window* window);
  void create_arrow(Enemy* enemy);
  void move_arrow(Window* window);
  void hit_enemies(Arrow arrow);
  void upgrade_tower(Window* window, Gamer* gamer);


private:
  vector<Enemy*> enemies;

};

class Tesla : public Tower
{
public:
  Tesla(Point place_point_, Gamer* gamer);
  void draw(Window* window);
  void create_arrow(Enemy* enemy);
  void move_arrow(Window* window);
  void upgrade_tower(Window* window, Gamer* gamer);


private:

};

#endif
