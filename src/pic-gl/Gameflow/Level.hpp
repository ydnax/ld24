#ifndef picppgl_Gameflow_Level_hpp
#define picppgl_Gameflow_Level_hpp
#include <string>
#include <vector>
#include <functional>
#include <pic-gl/Util/lazy_delete_vector.hpp>
#include <pic-gl/Util/tools.hpp>
#include <pic-gl/Util/boxtools.hpp>

using std::string;
namespace picppgl{
class Level;

class levelObject;
class Level{
public:
    typedef std::function<void()> gcFun;
    typedef std::vector<objinfo> boxcont;
private:
    lazyDeleteVector<levelObject*> objects;
    std::vector<gcFun> gcFuns;
    boxcont obstacles;
    point spawn={50,50};
public:
    Level(){}
    void update(int);
    void addGcFun(gcFun f){gcFuns.push_back(f);}
    void addObstacle(objinfo obj){obstacles.push_back(obj);}
    boxcont getObstacles()const{return obstacles;}
    void addObj(levelObject*);
    void delObj(levelObject*);
    void Spawn(point nval){spawn=nval;}
    point Spawn(){return spawn;}
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