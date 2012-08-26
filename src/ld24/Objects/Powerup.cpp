#include "Powerup.hpp"
#include <sstream>
#include <string>
#include <pic-gl/Util/tools.hpp>

#include <iostream>
using namespace std;
namespace ld24{
Powerup::Powerup(Level *lvl, int x, int y, std::vector<Image> imgs, Powerup::Effect effect):
    levelObject(lvl),
    x(x),y(y),
    images(imgs),
    r(this, mainwindow::powerups),
    ef(effect){
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