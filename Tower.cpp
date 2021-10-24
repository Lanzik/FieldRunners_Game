#include "Tower.hpp"

Arrow::Arrow(place current_place_, Enemy* enemy)
{
  current_place = current_place_;
  target = enemy;
  existence = 1;
}

void Arrow::follow_target()
{
  if(target->get_current_place().x - current_place.x > 40)
  {
    current_place.x += 30;
  }
  else if(target->get_current_place().x - current_place.x < -40)
  {
    current_place.x -= 30;
  }
  if(target->get_current_place().y - current_place.y < -40)
  {
    current_place.y -= 30;
  }
  else if(target->get_current_place().y - current_place.y > 40)
  {
    current_place.y += 30;
  }
}

void Arrow::hit_target(int damage_, Window* window)
{
  target->hit(damage_);
  window->draw_img("./Assets/explosion_add.png",Rectangle(current_place.x,current_place.y,64,64));
}

void Arrow::remove()
{
  existence = 0;
}

bool Arrow::arrive_target()
{
return(sqrt(pow(current_place.x - target->get_current_place().x,2) +
  pow(current_place.y - target->get_current_place().y,2)) <= 40);
}

bool Tower::check_distance(Point place_point_, Enemy* enemy, int distance)
{
  return (sqrt(pow((place_point_.x*60 + 120) - (enemy->get_current_place().x),2) +
  pow((place_point_.y*60 + 175) - (enemy->get_current_place().y),2)) <= distance);
}

bool Tower::fire_possible(Enemy* enemy, int counter, Gamer* gamer)
{
  return (check_distance(place_point, enemy, TOWER_DISTANCE)
   && (counter%fire_speed == 0)
  && enemy->check_alive(gamer));
}

Gatling::Gatling(Point place_point_, Gamer* gamer)
{
  damage = 35;
  buy_price = 55;
  level = 1;
  place_point.x = (place_point_.x - 120)/60;
  place_point.y = (place_point_.y - 175)/60;
  fire_speed = 10;
  gamer->reduse_money(buy_price);
}

void Gatling::upgrade_tower(Window* window, Gamer* gamer)
{
  damage += 35;
  level++;
  gamer->reduse_money(40);
  window->play_sound_effect("./extra/sounds/tower_upgrade.wav");
}

void Gatling::create_arrow(Enemy* enemy)
{
  place arrow_place;
  arrow_place.x = (place_point.x)*60 + 150;
  arrow_place.y = (place_point.y)*60 + 205;
  arrows.push_back(Arrow(arrow_place, enemy));
}

void Gatling::move_arrow(Window* window)
{
  for(int i = 0; i < arrows.size(); i++)
  {
    if(!arrows[i].arrive_target() && arrows[i].get_existence())
    {

      window->fill_circle(Point(arrows[i].get_current_place().x,
      arrows[i].get_current_place().y), 5, RED);
      window->play_sound_effect("./extra/sounds/tower_gatling_fire_loop_03.wav");

      arrows[i].follow_target();
    }
    else if(arrows[i].get_existence())
    {
        arrows[i].hit_target(damage, window);
      arrows[i].remove();
    }
  }
}

void Gatling::draw(Window* window)
{
  window->draw_img("./Assets/towers/gattling" + to_string(level) + ".png",
  Rectangle(place_point.x*60 + 90,place_point.y*60 + 150,116,132));
}

Missile::Missile(Point place_point_, Gamer* gamer, vector<Enemy*> enemies_)
{
  damage = 75;
  buy_price = 70;
  level = 1;
  place_point.x = (place_point_.x - 120)/60;
  place_point.y = (place_point_.y - 175)/60;
  fire_speed = 30;
  enemies = enemies_;
  gamer->reduse_money(buy_price);
}

void Missile::upgrade_tower(Window* window, Gamer* gamer)
{
  damage += 75;
  level++;
  gamer->reduse_money(40);
  window->play_sound_effect("./extra/sounds/tower_upgrade.wav");
}

void Missile::draw(Window* window)
{
  window->draw_img("./Assets/towers/missile" + to_string(level) + ".png",
  Rectangle(place_point.x*60 + 90,place_point.y*60 + 150,103,102));
}

void Missile::create_arrow(Enemy* enemy)
{
  place arrow_place;
  arrow_place.x = place_point.x*60 + 120;
  arrow_place.y = place_point.y*60 + 175;
  arrows.push_back(Arrow(arrow_place, enemy));
}

void Missile::hit_enemies(Arrow arrow)
{
  Point arrow_place;
  arrow_place.x = (arrow.get_current_place().x - 120)/60;
  arrow_place.y = (arrow.get_current_place().y - 175)/60;
  for(int i = 0; i < enemies.size(); i++)
  if(check_distance(arrow_place, enemies[i], MISSILE_DISTANCE))
    enemies[i]->hit(damage);

}

void Missile::move_arrow(Window* window)
{
  for(int i = 0; i < arrows.size(); i++)
  {
    if(!arrows[i].arrive_target() && arrows[i].get_existence())
    {
      window->draw_img("./Assets/projectile_missile_00000.png",
      Rectangle(arrows[i].get_current_place().x,arrows[i].get_current_place().y,32,64));
      window->play_sound_effect("./extra/sounds/tower_rocket_fire_02.wav");
      arrows[i].follow_target();
    }
    else if(arrows[i].get_existence())
    {
      arrows[i].hit_target(damage, window);
      hit_enemies(arrows[i]);
      arrows[i].remove();
    }
  }
}

Tesla::Tesla(Point place_point_, Gamer* gamer)
{
  damage = 700;
  buy_price = 120;
  level = 1;
  place_point.x = (place_point_.x - 120)/60;
  place_point.y = (place_point_.y - 175)/60;
  fire_speed = 15;
  gamer->reduse_money(buy_price);
}

void Tesla::upgrade_tower(Window* window, Gamer* gamer)
{
  damage += 1000;
  level++;
  gamer->reduse_money(40);
  window->play_sound_effect("./extra/sounds/tower_upgrade.wav");
}

void Tesla::draw(Window* window)
{
  window->draw_img("./Assets/towers/tesla" + to_string(level) + ".png",
  Rectangle(place_point.x*60 + 115,place_point.y*60 + 120,66,122));
}

void Tesla::create_arrow(Enemy* enemy)
{
  place arrow_place;
  arrow_place.x = place_point.x*60 + 120;
  arrow_place.y = place_point.y*60 + 175;
  arrows.push_back(Arrow(arrow_place, enemy));
}

void Tesla::move_arrow(Window* window)
{
  for(int i = 0; i < arrows.size(); i++)
  {
    for(int i = 0; i < arrows.size(); i++)
    {
      if(!arrows[i].arrive_target() && arrows[i].get_existence())
      {
        window->draw_img("./Assets/lightning.png",
        Rectangle(arrows[i].get_current_place().x,
         arrows[i].get_current_place().y, 20, 50));;
         window->play_sound_effect("./extra/sounds/lightning_zap_03.wav");
        arrows[i].follow_target();
      }
      else if(arrows[i].get_existence())
      {
        arrows[i].hit_target(damage, window);
        arrows[i].remove();
      }
    }
  }
}
