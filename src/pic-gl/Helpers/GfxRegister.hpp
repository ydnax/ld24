#ifndef fgengine_gfxregister_hpp
#define fgengine_gfxregister_hpp
#include <pic-gl/Ui/main_window.hpp>

namespace picppgl{
class GfxRegister{
        gfxobject *obj_;
        mainwindow::layer l_;
    public:
        GfxRegister(gfxobject *obj, mainwindow::layer la):obj_(obj), l_(la){
            mwindow->addLay(obj_, l_);
        }
        ~GfxRegister(){
            mwindow->remLay(obj_, l_);
        }
};

}
#endif