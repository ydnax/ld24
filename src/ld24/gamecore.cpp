#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <thread>
#include <sstream>
#include <pic-gl/Ui/main_window.hpp>
#include <pic-gl/Gameflow/Level.hpp>
#include <ld24/Objects/LevelLoader.hpp>
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

    
string lstr=
R"LVL(ssssssssss
ssssssssss
sssssss
sssssssssswssw
ssssswssswwwswsssssssssswwsssssssswwwwwsswwswswswswwwwwwwssssss
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww)LVL";
    Level level([](){return false;});
    auto ll=LevelLoader{&level, lstr};
    timer.start();
    Player player{&level, 50,50};
    player.setObstacles(ll.getBoxes());
    std::vector<Image> images;
    for (int i = 0; i < 24; ++i){
        stringstream s;
        s<<"resources/gfx/powerups/higherjump-ani"<<i<<".png";
        images.emplace_back(Image(s.str(), 50, 50));
    }
    new Powerup{&level, 200, 180, images, [](Player *pl){pl->up_canjump=true;} };
    while(! player.exit()){
        window->render();
        level.update(timer.get_dticks());
    }
    std::cout<<"all levels played. game over"<<std::endl;
}

}