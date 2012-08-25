#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <thread>
#include <pic-gl/Ui/main_window.hpp>
#include <pic-gl/Gameflow/Level.hpp>
#include "gamecore.hpp"


using namespace std;
namespace picppgl{
//using namespace ld24;
gamecore::gamecore(){
    window=new mainwindow("resources/gfx/bg.png", 800, 600);

}
    
void gamecore::gameloop(){
    Level level([](){return false;});
    timer.start();
    while(true){
        window->render();
        level.update(timer.get_dticks());
        std::chrono::milliseconds dura( 33 );
        std::this_thread::sleep_for( dura );
    }
    std::cout<<"all levels played. game over"<<std::endl;
}

}