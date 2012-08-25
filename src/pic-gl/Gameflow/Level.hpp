#ifndef picppgl_Gameflow_Level_hpp
#define picppgl_Gameflow_Level_hpp
#include <string>
#include <vector>
#include <functional>
#include <pic-gl/Util/lazy_delete_vector.hpp>
#include <pic-gl/Util/tools.hpp>

using std::string;
namespace picppgl{
class Level;

class levelObject;
class Level{
public:
    typedef std::function<bool()> winCondition;
    typedef std::function<void()> gcFun;
private:
    lazyDeleteVector<levelObject*> objects;
    winCondition winfun;
    point screencenter;
    std::vector<gcFun> gcFuns;
public:
    Level(winCondition wc):winfun(wc){}
    void setWinFun(winCondition wc){winfun=wc;}
    void update(int);
    void addGcFun(gcFun f){gcFuns.push_back(f);}
    void addObj(levelObject*);
    void delObj(levelObject*);
    bool hasWon();
    void screenCenter(point nval){screencenter=nval;}
    point screenCenter()const{return screencenter;}
    ~Level();
};
class levelObject{
protected:
    Level* lvl;
public:
    levelObject(Level *l):lvl(l){
        lvl->addObj(this);
    }
    virtual void update(int)=0;
    virtual ~levelObject(){
        lvl->delObj(this);
    }
};

}
#endif