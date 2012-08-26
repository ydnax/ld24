#include "LevelLoader.hpp"
#include <iostream>
namespace ld24{
using namespace std;
using namespace picppgl;
LevelLoader::LevelLoader(Level *lvl, string data):
        levelObject(lvl),
        r(this, mainwindow::boxes),
        row(0), column(0),
        sky(50,50), 
        wall("resources/gfx/tiles/bluegreenRaw.png",50,50){
    for(char c:data){
        switch(c){
            case '\n':newline();break;
            case 'w': walltile();break;
            case 's': skytile();break;
            default:error();break;
        }
    }
    cerr<<"W:  "<<maxwidth<<endl;
    mwindow->setWorldSizeW(maxwidth);
}
void LevelLoader::draw(Image& target){
    for(auto &&el:tiles){
        target.apply(el.img, el.x, el.y);
    }
}

void LevelLoader::newline(){
    row++;
    column=0;
}

void LevelLoader::skytile(){
    column++;
}

void LevelLoader::walltile(){
    obstacles.push_back({{column*tilelength, row*tilelength}, tilelength, tilelength});
    tiles.push_back({wall, column*tilelength, row*tilelength});
    auto w=column*tilelength+tilelength;
    maxwidth=w>maxwidth?w:maxwidth;
    column++;
}

void LevelLoader::error(){
    cerr<<"level parse error after tile "<<column<<", "<<row<<endl;
    std::exit(1);
}

}