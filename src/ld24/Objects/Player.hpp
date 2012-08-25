#ifndef ld24_objects_player_hpp
#define ld24_player_hpp
#include <pic-gl/Gameflow/Level.hpp>
#include <pic-gl/Ui/gfx_object.hpp>
#include <pic-gl/Ui/main_window.hpp>
#include <pic-gl/Helpers/GfxRegister.hpp>
#include <array>
#include <iostream>

namespace ld24{
using namespace picppgl;
class Player:public levelObject, gfxobject{
    int x,y;
    float xx, yy;
    Image img;
    GfxRegister r;
public:
    Player(Level *lvl, int x, int y);
    bool exit();
    virtual void draw(Image &target)override{
        target.apply(img, x+(img.w()/2), y+(img.h()/2));
    }

    virtual void update(int ticks)override;

    virtual ~Player(){}
};

}
#endif