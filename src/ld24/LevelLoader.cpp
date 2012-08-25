#include "LevelLoader.hpp"
#include <iostream>
namespace ld24{
using namespace std;
using namespace picppgl;
LevelLoader::LevelLoader():
        row(0), column(0), maxlength(-1),
        levelmap(0,50),
        sky(0,0), 
        wall(0,0){}


LevelLoader::lvlInfo LevelLoader::parseLevel(string data){
    for(char c:data){
        switch(c){
            case '\n':newline();break;
            case 'w':walltile();break;
            case 's':skytile();break;
            default:error();break;
        }
    }
    return {obstacles, levelmap};
}
void LevelLoader::newline(){
    row++;
    column=0;
    Image newi{levelmap.w(), levelmap.h()+tilelength};
    newi.apply(levelmap,0,0);
    levelmap=newi;
}
void LevelLoader::skytile(){
    addtile(sky);
    column++;
}
void LevelLoader::walltile(){
    addtile(wall);
    obstacles.push_back({{column*tilelength, row*tilelength}, tilelength, tilelength});
    column++;
}
void LevelLoader::addtile(picppgl::Image tile){
    if(maxlength<column){
        maxlength=column;
        Image newi{tilelength*(maxlength+1), levelmap.h()};
        newi.apply(levelmap,0,0);
        levelmap=newi;
    }
    levelmap.apply(tile, column*tilelength, row*tilelength);
}

void LevelLoader::error(){
    cerr<<"level parse error after tile "<<column<<", "<<row<<endl;
    std::exit(1);
}

}