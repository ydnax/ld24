#include "Player.hpp"
#include <SDL/SDL.h>
namespace ld24{
Player::Player(Level *lvl, int x, int y):
        levelObject(lvl),
        x(x),y(y),xx(x),yy(y),
        img("resources/gfx/player.png",100,50),
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

void Player::update(int){
    x=xx+0.5;
    y=yy+0.5;
}


}