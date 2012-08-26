#include "main_window.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <pic-gl/Resources/Image.hpp>
#include <pic-gl/Ui/gfx_object.hpp>
#include <pic-gl/Util/tools.hpp>
namespace picppgl{

mainwindow::mainwindow(std::string bgpath, int w, int h, int bbp):
        vsurface_(reinterpret_cast<ImageData*>(SDL_SetVideoMode(w, h, bbp, SDL_HWSURFACE ))),
        background( bgpath, w, h),
        world(10000,1000),
        layers(layer::__count),
        h(h), w(w),
        ccx_(w/2), ccy_(h/2){
    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();
    SDL_WM_SetCaption( "fastgame", NULL );
    mwindow=this;
}

void mainwindow::render(){
    world.apply(background,ccx_-(background.w()/2),ccy_-(background.h()/2));
    for(auto &&layer: layers){
        layer.realDelete();
        for(auto &&obj: layer.data()){
            obj->draw(world);
        }
    }
    auto dr=world.Copy(ccx_-(w/2),ccy_-(h/2), w, h);
    vsurface_.apply(dr,0,0);
    vsurface_.flip();
}

void mainwindow::remLay(gfxobject* obj, const layer lay){
    layers[lay].element_delete(obj);
}

void mainwindow::setWorldSizeW(int w){
    world=Image{w, world.h()};
}

void mainwindow::setWorldSizeH(int h){
    world=Image{world.w(), h};
}

mainwindow *mwindow=NULL;

}
