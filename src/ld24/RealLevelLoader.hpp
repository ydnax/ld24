#ifndef ld24_real_levelloader_hpp
#define ld24_real_levelloader_hpp

#include <string>
#include <sstream>
#include <tuple>
#include <pic-gl/Gameflow/Level.hpp>


namespace ld24{
using namespace picppgl;
class RealLevelLoader{
    private:
        typedef std::function<void(picppgl::Level*)> lvlElement;
        typedef std::vector<lvlElement> lvlComponents;
        typedef std::function<picppgl::Level*()> LvlFun;
    public:
        typedef std::vector<LvlFun> T_Levels;
private:
    enum t_dir{up, down, left, right}; 
    enum t_powerup{speed, jump};
    t_dir direction=right;
    t_powerup powertype=speed;
    std::stringstream nbuf;
    std::stringstream strbuf;
    int numcache;
    int xcache, ycache;
    int linecount=1;
    std::string strcache;
    lvlComponents lcomps;
    T_Levels lcache;
    void number_start();
    void number_push(char c);
    void number_end();
    void xvar();
    void yvar();
    void str_start();
    void str_push(char c);
    void str_end();
    void version_number();
    void setDirection(char c);
    void error(string msg);
    void end();
    void level_finish();
    void spawn();
    void finish();
    void wall();
    void spike();
    void powerup();
    void pu_speed();
    void pu_jump();
public:
    RealLevelLoader(){}
    T_Levels parse(std::string data);

};
}
#endif