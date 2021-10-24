#include "functions.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include <numeric>

bool calculate_wave_number(vector<int> waves, vector<Enemy*> enemies, int wave_number
, vector<Point> route, Gamer* gamer, Window* window)
{
  for(int i = 0; i < accumulate(waves.begin(), waves.begin() + wave_number, 0); i++)
  {
    if(!enemies[i]->end_route(route, gamer, window) && enemies[i]->check_alive(gamer))
    {
      return false;
    }
  }
  return true;
}

void run_enemy(Window* window, vector<Point> route, vector<Enemy*> enemies,
     int counter, vector<int> waves, int wave_number, Gamer* gamer)
{
  for(int i = 0;
   i <= counter/5 && i < accumulate(waves.begin(), waves.begin() + wave_number, 0); i++)
  {
    if(!enemies[i]->end_route(route, gamer, window) && enemies[i]->check_alive(gamer))
      enemies[i]->run(route, enemies, waves, window);
  }

}


void fire_tower(vector<Tower*> towers,vector<Enemy*> enemies, int counter, Gamer* gamer)
{
  for(int i = 0; i < towers.size(); i++)
  {
    for(int j = 0; j < enemies.size(); j++)
    {
      if(towers[i]->fire_possible(enemies[j], counter, gamer))
      {
        towers[i]->create_arrow(enemies[j]);
       break;
      }
    }
  }
}

void draw_arrow(Window* window, vector<Tower*> towers)
{
  for(int i = 0; i < towers.size(); i++)
  {
    towers[i]->move_arrow(window);
  }
}

void draw(Window* window, vector<Point> route, vector<Enemy*> enemies,
     int &counter, vector<int> waves, vector<Tower*> towers, Point click_position,
      int &wave_number, Gamer* gamer)
{
  window->clear();
  window->draw_img("./Assets/background.png", Rectangle(0,0,1366,1024));
  gamer->show_heart_money(window);
  if(calculate_wave_number(waves, enemies, wave_number, route, gamer, window))
  {
    wave_number++;
    counter = 45;
  }
  run_enemy(window, route, enemies, counter, waves, wave_number, gamer);
  draw_tower(window, towers);
  fire_tower(towers, enemies, counter, gamer);
  draw_arrow(window, towers);
  window->update_screen();
}

void draw_tower(Window* window, vector<Tower*> towers)
{
  vector<Enemy*> enemies;
  for(int i = 0; i < towers.size(); i++)
  {
  towers[i]->draw(window);
  }
}

void update(Window* window, Point &click_position, vector<Tower*> &towers,int &last_event
,vector<Enemy*> enemies, Gamer* gamer)
{
  while(window->has_pending_event())
  {
    Event event = window->poll_for_event();
    switch(event.get_type())
    {
      case Event::EventType::QUIT:
      exit(0);
      break;
      case Event::EventType::LCLICK:
      click_position = event.get_mouse_position();
      last_event = 1;
      break;
      case Event::KEY_PRESS:
      if (event.get_pressed_key() == 'g' && last_event == 1)
      {
         Gatling* new_gatling = new Gatling(click_position, gamer);
         towers.push_back(new_gatling);
      }
      else if (event.get_pressed_key() == 'm' && last_event == 1)
      {
        Missile* new_missile = new Missile(click_position, gamer, enemies);
        towers.push_back(new_missile);
      }
      else if (event.get_pressed_key() == 't' && last_event == 1)
      {
        Tesla* new_tesla = new Tesla(click_position, gamer);
        towers.push_back(new_tesla);
      }
      else if (event.get_pressed_key() == 'u' && last_event == 1)
      {
        upgrade_tower(click_position, towers, window, gamer);
      }
      last_event = 2;
      break;
    }
  }
}
void upgrade_tower(Point click_position, vector<Tower*> towers, Window* window, Gamer* gamer)
{
  click_position = coordinate_to_number(click_position);
  for(int i = 0; i < towers.size(); i++)
  {
    if(towers[i]->get_place_point().x == click_position.x &&
     towers[i]->get_place_point().y == click_position.y)
       towers[i]->upgrade_tower(window, gamer);
  }

}
Point coordinate_to_number(Point point)
{
  point.x = (point.x - 120)/60;
  point.y = (point.y - 175)/60;
  return point;
}
void create_wave(vector<int> &waves, vector<int> number_enemies)
{
  int number_enemy_wave = ZERO;
  for(int i = 0; i < NUMBER_TYPE_ENEMY; i++)
  {
    number_enemy_wave += number_enemies[i];
  }
  waves.push_back(number_enemy_wave);
}

void create_enemies_wave(vector<int> number_enemies, vector<Enemy*> &enemies,
   vector<Point> route, int wave_number)
{
  for(int i = 0; i < NUMBER_TYPE_ENEMY; i++)
  {
    for(int j = 0; j < number_enemies[i]; j++)
    {
      place current_place, next_place;
      if(i == RUNNER)
      {
        current_place.x = 120 + 60 * route[0].x;
        current_place.y =  160 + 60 * route[0].y;
        next_place.x = 120 + 60 * route[1].x;
        next_place.y = 160 + 60 * route[1].y;
        Runner* runner = new Runner(current_place, next_place, wave_number);
        enemies.push_back(runner);
      }
      else if(i == STUBBORN_RUNNER)
      {
        current_place.x = 120 + 60 * route[0].x;
        current_place.y =  160 + 60 * route[0].y;
        next_place.x = 120 + 60 * route[1].x;
        next_place.y = 160 + 60 * route[1].y;
        Stubborn_Runner* stubborn_runner = new Stubborn_Runner(current_place, next_place, wave_number);
        enemies.push_back(stubborn_runner);
      }
      else if(i == SUPER_TROOPER)
      {
        current_place.x = 120 + 60 * route[0].x;
        current_place.y =  160 + 60 * route[0].y;
        next_place.x = 120 + 60 * route[1].x;
        next_place.y = 160 + 60 * route[1].y;
        Super_Trooper* super_trooper = new Super_Trooper(current_place, next_place, wave_number);
        enemies.push_back(super_trooper);
      }
      else
      {
        current_place.x = 120 + 60 * route[0].x;
        current_place.y =  160 + 60 * route[0].y;
        next_place.x = 120 + 60 * route[1].x;
        next_place.y = 160 + 60 * route[1].y;
        Scrambler* scrambler = new Scrambler(current_place, next_place, wave_number);
        enemies.push_back(scrambler);
      }
    }
  }
}

void get_input(vector<Point> &route, vector<Enemy*> &enemies, vector<int> &waves)
{
  string input;
  int x, y;
  Point place;
  stringstream convert;

  getline(cin, input);
  convert << input;
  while(!convert.eof())
  {
    convert >> x >> y;
    place = Point(x,y);
    route.push_back(place);
  }
  convert.str("");
  convert.clear();

  int one_type_enemies;


  while(getline(cin, input))
  {
    vector<int> number_enemies;
    convert << input;
    while(!convert.eof())
    {
      convert >> one_type_enemies;
      number_enemies.push_back(one_type_enemies);
    }
    create_wave(waves, number_enemies);
    create_enemies_wave(number_enemies, enemies, route, waves.size());
    convert.str("");
    convert.clear();
  }
}
