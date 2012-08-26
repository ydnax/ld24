#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <thread>
#include <sstream>
#include <pic-gl/Ui/main_window.hpp>
#include <pic-gl/Gameflow/Level.hpp>
#include <ld24/Objects/LevelLoader.hpp>
#include <ld24/RealLevelLoader.hpp>
#include <ld24/Objects/Player.hpp>
#include <ld24/Objects/Powerup.hpp>
#include "gamecore.hpp"


using namespace std;
using namespace ld24;
namespace picppgl{
//using namespace ld24;
gamecore::gamecore(){
    window=new mainwindow("resources/gfx/background/deepsea-tileable.jpg", 800, 600);

}
    
void gamecore::gameloop(){
    timer.start();
    RealLevelLoader rll{};
    auto levels=rll.parse("VERSION: 1\nwall 0,10 > 10 \nwall 10,9 > 9 \npowerup 9,9 jump 1\n");
    auto level=levels[0]();
    Player player{level, 50,50};
    player.setObstacles(level->getObstacles());
    while(! player.exit()){
        window->render();
        level->update(timer.get_dticks());
    }
    std::cout<<"all levels played. game over"<<std::endl;
}

}