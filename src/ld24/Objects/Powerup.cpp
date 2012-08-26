#include "Powerup.hpp"
#include <sstream>
#include <string>
#include <pic-gl/Util/tools.hpp>

#include <iostream>
using namespace std;
namespace ld24{
Powerup::Powerup(Level *lvl, int x, int y, Powerup::Effect effect):
    levelObject(lvl),
    x(x),y(y),
    r(this, mainwindow::powerups),
    ef(effect){
        for (int i = 0; i < 24; ++i){
            stringstream s;
            s<<"resources/gfx/powerups/bite-anim"<<i<<".png";
            images.emplace_back(Image(s.str(), 50, 50));
        }
    powerups.add(this);
}

void Powerup::update(int ticks){
    chCount+=ticks;
    if(chCount>animationSpeed){
        chCount=0;
        imgIndex++;
        imgIndex=imgIndex%images.size();
    }
}

Powerup::Effect Powerup::Use(){
    auto ret=ef;
    lvl->addGcFun([&](){delete this;});//delay deletion to avoid crash in update loop
    return ret;
}

Powerup::~Powerup(){
    powerups.element_delete(this);
}

Powerup::PowerCont powerups;

}