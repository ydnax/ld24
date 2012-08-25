#ifndef ld24_objects_powerup_hpp
#define ld24_objects_powerup_hpp
#include <array>
#include <iostream>
#include <pic-gl/Gameflow/Level.hpp>
#include <pic-gl/Ui/gfx_object.hpp>
#include <pic-gl/Ui/main_window.hpp>
#include <pic-gl/Helpers/GfxRegister.hpp>
#include <pic-gl/Util/boxtools.hpp>
#include <pic-gl/Util/lazy_delete_vector.hpp>
#include <ld24/Objects/Player.hpp>

namespace ld24{
using namespace picppgl;
class Powerup:public levelObject, gfxobject{
public:
    typedef lazyDeleteVector<Powerup*> PowerCont;
    typedef std::function<void(Player*)> Effect;
private:
    int x,y;
    std::vector<Image> images;
    GfxRegister r;
    int imgIndex=0;
    const int animationSpeed=100;
    int chCount=0;
    Effect ef;
public:
    Powerup(Level *lvl, int x, int y, Effect effect);
    virtual void draw(Image &target)override{
        auto img=images[imgIndex];
        target.apply(img, x, y);
    }
    objinfo getInfo()const{
        auto img=images[imgIndex];
        return {{x,y},img.w(), img.h()};
    }
    virtual void update(int ticks)override;
    Effect Use();
    virtual ~Powerup();
};
extern Powerup::PowerCont powerups;

}
#endif