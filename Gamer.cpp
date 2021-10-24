#include "Gamer.hpp"
#include <string>

using namespace std;

Gamer::Gamer()
{
  heart = 20;
  money = 200;
}

void Gamer::reduse_health(int quantity, Window* window)
 {
   heart -= quantity;
   if(heart <= DEATH)
   {
     while(true)
     {
       window->clear();
       window->draw_img("./Assets/background.png", Rectangle(0,0,1366,1024));
       window->show_text("YOU LOSE!", Point(370, 430), BLACK,"./Assets/HECK.TTF", 150);
        window->play_sound_effect("./extra/sounds/thunder_05.wav");

        window->update_screen();
     }
   }
 }

void Gamer::reduse_money(int quantity)
{
  money -= quantity;
}

void Gamer::show_heart_money(Window* window)
{
  window->show_text(to_string(heart), Point(170, 30), BLACK,
   "./Assets/HECK.TTF", 65);

  window->show_text(to_string(heart), Point(170, 30), WHITE,
   "./Assets/HECK.TTF", 63);
   window->draw_img("./Assets/health.png", Rectangle(80, 20, 90, 90));

   window->draw_img("./Assets/hud_money.png", Rectangle(280, 20, 90, 90));
   window->show_text(to_string(money), Point(370, 30), WHITE,
    "./Assets/HECK.TTF", 63);
    window->show_text("Programming By Farhad Ghanbari",
    Point(1068, 128), BLACK,"./Assets/OpenSans.ttf", 14);
    window->show_text("Programming By Farhad Ghanbari",
    Point(1070, 130), YELLOW,"./Assets/OpenSans.ttf", 14);

}
