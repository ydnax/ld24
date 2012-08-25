#include "Level.hpp"
namespace picppgl{

void Level::update(int ticks){
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
bool Level::hasWon(){
    return winfun();
}
Level::~Level(){
    objects.realDelete();
    for(auto &&obj: objects.data()){
        delete obj;
    }
}

}