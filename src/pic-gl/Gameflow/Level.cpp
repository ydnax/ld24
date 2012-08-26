#include "Level.hpp"
namespace picppgl{

void Level::update(int ticks){
    for(auto &&f:gcFuns)
        f();
    gcFuns.clear();
    objects.realDelete();
    for(auto &&obj: objects.data()){
        obj->update(ticks);
    }
}
void Level::addObj(levelObject *o){
    objects.add(o);
}
void Level::delObj(levelObject *o){
    objects.element_delete(o);
}
Level::~Level(){
    objects.realDelete();
    for(auto &&obj: objects.data()){
        delete obj;
    }
}

}