#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <thread>
#include <pic-gl/Ui/main_window.hpp>
#include <pic-gl/Gameflow/Level.hpp>
#include <ld24/LevelLoader.hpp>
#include <ld24/Objects/Player.hpp>
#include "gamecore.hpp"


using namespace std;
using namespace ld24;
namespace picppgl{
//using namespace ld24;
gamecore::gamecore(){
    window=new mainwindow("resources/gfx/bg.png", 800, 600);

}
    
void gamecore::gameloop(){

    auto ll=LevelLoader{};
string lstr=
R"LVL(ssssssssss
ssssssssss
sssssss
ssssssss
ssssssssss
wwwwwwwwww)LVL";
    auto li=ll.parseLevel(lstr);
    auto limg=get<1>(li);
    window->setBackground(limg);
    Level level([](){return false;});
    timer.start();
    Player player{&level, 50,50};
    while(! player.exit()){
        window->render();
        level.update(timer.get_dticks());
        std::chrono::milliseconds dura( 33 );
        std::this_thread::sleep_for( dura );
    }
    std::cout<<"all levels played. game over"<<std::endl;
}

}