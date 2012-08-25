#ifndef ld24_objects_player_hpp
#define ld24_objects_player_hpp
#include <array>
#include <iostream>
#include <array>
#include <pic-gl/Gameflow/Level.hpp>
#include <pic-gl/Ui/gfx_object.hpp>
#include <pic-gl/Ui/main_window.hpp>
#include <pic-gl/Helpers/GfxRegister.hpp>
#include <pic-gl/Util/boxtools.hpp>

namespace ld24{
using namespace picppgl;
class Player:public levelObject, gfxobject{
public:
    typedef std::vector<picppgl::objinfo> boxcont;
private:
    int x,y;
    float xx, xy;
    float xspeed, yspeed;
    std::array<Image, 3> images;
    GfxRegister r;
    boxcont obstacles;
    int imgIndex=0;
    const int animationSpeed=100;
    int chCount=0;
    bool canjump=false;

    const int gravity=100;
    const int jumpspeed=4000;
    const int movespeed=1200;
    const float maxdown=4000;
    bool udChk(int ticks);
    bool rlChk(int ticks);
    
    void checkPowerups();
public:
    bool up_canjump=false;
    int  up_walkspeed=0;
public:
    Player(Level *lvl, int x, int y);
    bool exit();
    void setObstacles(boxcont nval){obstacles=nval;}
    virtual void draw(Image &target)override{
        auto img=images[imgIndex];
        target.apply(img, x, y);
    }

    virtual void update(int ticks)override;

    virtual ~Player(){}
};

}
#endif