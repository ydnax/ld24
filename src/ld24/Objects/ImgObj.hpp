#ifndef ld24_objects_imgobj_hpp
#define ld24_objects_imgobj_hpp
#include <pic-gl/Gameflow/Level.hpp>
#include <pic-gl/Ui/gfx_object.hpp>
#include <pic-gl/Ui/main_window.hpp>
#include <pic-gl/Helpers/GfxRegister.hpp>


namespace ld24{
using namespace picppgl;
class ImgObj:public levelObject, gfxobject{
private:
    GfxRegister r;
    int x,y;
    Image img;
public:
    ImgObj(Level *lvl, int x, int y, Image i):
        levelObject(lvl),
        r(this, mainwindow::boxes),x(x),y(y), img(i){}

    virtual void draw(Image &target)override{
        target.apply(img, x, y);
    }
    virtual void update(int)override{};
    virtual ~ImgObj(){}
};


}
#endif