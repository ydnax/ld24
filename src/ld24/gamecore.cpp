#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <thread>
#include <sstream>
#include <pic-gl/Ui/main_window.hpp>
#include <ld24/RealLevelLoader.hpp>
#include <ld24/Objects/Player.hpp>
//#include <ld24/Objects/ShiftImage.hpp>
#include <ld24/Objects/ImgObj.hpp>
#include "gamecore.hpp"


using namespace std;
using namespace ld24;
namespace picppgl{
//using namespace ld24;
gamecore::gamecore(){
    window=new mainwindow("resources/gfx/background/deepsea-tileable.jpg", 800, 600);

}
    
void gamecore::gameloop(){
    RealLevelLoader rll{};
    ifstream t("levels.txt");
    string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
    auto levels=rll.parse(str);
    auto level=levels[0]();
    auto bgimg1=Image{"resources/gfx/background/deepsea-horizontalmoving.png"};
    bgimg1.resize(bgimg1.w(), 400);
    auto bgimg2=Image{bgimg1.w(), 200};
    for(int i=0;i<10;i++){
        new ImgObj(level, i*bgimg1.w(), 0, bgimg1, mainwindow::bg);
        new ImgObj(level, i*bgimg2.w(), 400, bgimg2, mainwindow::bg);
    }

    Player player{level, 50,50};
    player.setObstacles(level->getObstacles());
    player.respawn();
    timer.start();
    while(! player.exit()){
        window->render();
        level->update(timer.get_dticks());
    }
    std::cout<<"all levels played. game over"<<std::endl;
}

}