#ifndef __GAMER_H__
#define __GAMER_H__

#include "./src/rsdl.hpp"
#include "definitions.hpp"
#include <vector>

class Gamer
{
public:
  Gamer();
  void reduse_health(int quantity, Window* window);
  void show_heart_money(Window* window);
  void reduse_money(int quantity);
private:
  int heart;
  int money;
};

#endif
