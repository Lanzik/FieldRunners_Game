#include "Enemy.hpp"

bool Enemy::end_route(vector<Point> route, Gamer* gamer, Window* window)
{
  if ((int)((current_place.x - 120)/60) == route[route.size() - 1].x &&
  (int)((current_place.y - 120)/60) == route[route.size() - 1].y)
  {
    if(health != 0)
    gamer->reduse_health(hurt, window);
    health = 0;
    return true;
  }
  else
  return false;
}

void Enemy::hit(int damage)
{
  health -= damage;
}

bool Enemy::check_alive(Gamer* gamer)
{
  if(health <= DEATH)
  {
    if(existence == ALIVE)
    {
      gamer->reduse_money(-reward);
      existence = DEATH;
    }
    return false;
  }
  return true;
}

void Enemy::reset_counter_picture(int quantity)
{
  if(counter_picture == quantity)
  counter_picture = 1;
}

bool Enemy::reach_next_place()
{
  if(velocity == SCRAMBLER_VELOCITY)
  return ((current_place.x - next_place.x) <= 9 && (current_place.x - next_place.x) >= 0
   && (current_place.y - next_place.y) <= 9 && (current_place.y - next_place.y) >= 0);
  else
  return (current_place.x == next_place.x && current_place.y == next_place.y);
}

bool Enemy::find_current_place(Point place_number)
{
  return(place_number.x == (int)(current_place.x - 120)/60 &&
   place_number.y == (int)(current_place.y - 160)/60);
}

void Enemy::next_replace(Point next_number_place)
{
  next_place.x = 120 + 60*next_number_place.x;
  next_place.y = 160 + 60*next_number_place.y;
}

void Enemy::run(vector<Point> route, vector<Enemy*> enemies, vector<int> waves, Window* window)
{
  string direction = RIGHT;
  if(reach_next_place())
  {
    for(int i = 0; i < route.size(); i++)
    {
      if(find_current_place(route[i]))
      {
        next_replace(route[i+1]);
        render_picture(window, direction);
      }
    }
  }
  else
  {
    if(next_place.x > current_place.x)
    {
      direction = RIGHT;
      current_place.x += velocity;
      render_picture(window, direction);
    }
    else if(next_place.y > current_place.y)
    {
      direction = DOWN;
      current_place.y += velocity;
      render_picture(window, direction);
    }
    else
    {
      direction = UP;
      current_place.y -= velocity;
      render_picture(window, direction);
    }
  }
}

int Enemy::lost_blood_bar(int initial_health)
{
  return (((initial_health - health)*40)/initial_health);
}

int Enemy::blood_bar(int initial_health)
{
  return ((health*40)/initial_health);
}

void Enemy::draw_bar(Window* window, int initial_health)
{
  window->fill_rect(Rectangle(current_place.x,current_place.y-RAISE_HEIGHT,
    lost_blood_bar(initial_health), HEIGHT_BLOOD_BAR), RED);
  window->fill_rect(Rectangle(current_place.x + lost_blood_bar(initial_health),current_place.y-RAISE_HEIGHT,
    blood_bar(initial_health), HEIGHT_BLOOD_BAR), GREEN);
}

Runner::Runner(place current_place_, place next_place_, int wave_number_)
{
  health = (0.9 + 0.1 * wave_number_) * INITIAL_HEALTH_RUNNER;
  reward = 6;
  hurt = 1;
  current_place = current_place_;
  next_place = next_place_;
  counter_picture = 1;
  velocity = 5;
  existence = ALIVE;
  wave_number = wave_number_;
}

void Runner::render_picture(Window* window, string direction)
{
  window->draw_img("./extra/new/runner/" + direction + to_string(counter_picture) + ".png",
  Rectangle(current_place.x,current_place.y,41,61));
  draw_bar(window, INITIAL_HEALTH_RUNNER);
  counter_picture++;
  reset_counter_picture(FIVE_PICTURES);
}

Stubborn_Runner::Stubborn_Runner(place current_place_, place next_place_, int wave_number_)
{
  health = (0.9 + 0.1 * wave_number_) * INITIAL_HEALTH_STUBBORN;
  reward = 10;
  hurt = 4;
  current_place = current_place_;
  next_place = next_place_;
  counter_picture = 1;
  velocity = 3;
  existence = ALIVE;
  wave_number = wave_number_;
}

void Stubborn_Runner::render_picture(Window* window, string direction)
{
  window->draw_img("./extra/new/stubborn_runner/" + direction + to_string(counter_picture) + ".png",
  Rectangle(current_place.x,current_place.y,50,75));
  draw_bar(window, INITIAL_HEALTH_STUBBORN);
  counter_picture++;
  reset_counter_picture(FIVE_PICTURES);
}

Super_Trooper::Super_Trooper(place current_place_, place next_place_, int wave_number_)
{
  health = (0.9 + 0.1 * wave_number_) * INITIAL_HEALTH_SUPERTROOPER;
  reward = 8;
  hurt = 4;
  current_place = current_place_;
  next_place = next_place_;
  counter_picture = 1;
  velocity = 2.5;
  existence = ALIVE;
  wave_number = wave_number_;
}

void Super_Trooper::render_picture(Window* window, string direction)
{
  window->draw_img("./extra/new/super_trooper/" + direction + to_string(counter_picture) + ".png",
  Rectangle(current_place.x,current_place.y,67,77));
  draw_bar(window, INITIAL_HEALTH_SUPERTROOPER);
  counter_picture++;
  reset_counter_picture(FIVE_PICTURES);
}

Scrambler::Scrambler(place current_place_, place next_place_, int wave_number_)
{
  health = (0.9 + 0.1 * wave_number_) * INITIAL_HEALTH_SCRAMBLER;
  reward = 4;
  hurt = 2;
  current_place = current_place_;
  next_place = next_place_;
  counter_picture = 1;
  velocity = 9;
  existence = ALIVE;
  wave_number = wave_number_;
}

void Scrambler::render_picture(Window* window, string direction)
{
  if(direction == "right/")
  window->draw_img("./extra/new/scrambler/right/" + to_string(counter_picture) + ".png",
  Rectangle(current_place.x,current_place.y,82,58));
  else
  window->draw_img("./extra/new/scrambler/" + direction + to_string(counter_picture) + ".png",
  Rectangle(current_place.x,current_place.y,40,75));
  draw_bar(window, INITIAL_HEALTH_SCRAMBLER);
  counter_picture++;
  reset_counter_picture(TWO_PICTURES);
}
