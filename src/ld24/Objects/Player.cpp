#include "Player.hpp"
#include <ld24/Objects/Powerup.hpp>
#include <SDL/SDL.h>

namespace ld24{
Player::Player(Level *lvl, int x, int y):
        levelObject(lvl),
        x(x),y(y),xx(x),xy(y),xspeed(0), yspeed(0),
        images{{Image("resources/gfx/microbe_ani1_m.png", 100, 50),
                Image("resources/gfx/microbe_ani2_m.png", 100, 50),
                Image("resources/gfx/microbe_ani4_m.png", 100, 50)
        }},
        r(this, mainwindow::player){
}

bool Player::exit(){
    SDL_Event event;
    while( SDL_PollEvent( &event ) ) {
        if( event.type == SDL_QUIT )
            return true;
    }
    return false;
}

void Player::update(int ticks){
    Uint8 *keystates = SDL_GetKeyState( NULL );
    if( keystates[ SDLK_UP ] && canjump ){
        yspeed+=-1*jumpspeed*ticks/1000.;
    }
    if( keystates[ SDLK_LEFT ] ){
        xspeed =-1*(movespeed+up_walkspeed)*ticks/1000.;
        chCount+=ticks;
    }else if( keystates[ SDLK_RIGHT ] ){
        xspeed = (movespeed+up_walkspeed)*ticks/1000.;
        chCount+=ticks;
    }else{
        xspeed=0;
    }

    yspeed+=gravity*ticks/1000.;
    if(yspeed>maxdown){
        yspeed=maxdown;
    }

    /*
    while(udChk(ticks)){
        int dpx=yspeed*ticks/1000.;
        if( (dpx>5)||(dpx<-5)){
            yspeed/=1.5;
        }else{
            yspeed=0;
        }
        
    } //*/

    if(udChk(ticks)){
        yspeed=0;
    }
    if(rlChk(ticks)){
        xspeed=0;
    }
    xx=xx+xspeed*ticks/1000.;
    x=xx;
    xy=xy+yspeed*ticks/1000.;
    y=xy;


    if(chCount>animationSpeed){
        chCount=0;
        imgIndex++;
        imgIndex=imgIndex%images.size();
    }
    checkPowerups();
}

bool Player::udChk(int ticks){
    auto img=images[imgIndex];
    float ny=xy+yspeed*ticks/1000.;
    for(auto &&box:obstacles){
        if(boxCollide({{int(xx+0.5),int(ny+0.5)},img.w(), img.h()}, box)){
            canjump=true;
            return true;
        }
    }
    canjump=false;
    return false;
}

bool Player::rlChk(int ticks){
    auto img=images[imgIndex];
    float nx=xx+xspeed*ticks/1000.;
    for(auto &&box:obstacles){
        if(boxCollide({{int(nx+0.5),int(xy+0.5)},img.w(), img.h()}, box)){
            return true;
        }
            
    }
    return false;
}

void Player::checkPowerups(){
    auto img=images[imgIndex];
    powerups.realDelete();
    for(auto i : powerups.data()){
        if(boxCollide({{x,y},img.w(), img.h()}, i->getInfo())){
            i->Use()(this);
        }
    }
}


}