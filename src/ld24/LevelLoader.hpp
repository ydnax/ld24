#ifndef ld24_levelloader_hpp
#define ld24_levelloader_hpp
#include <tuple>
#include <string>
#include <vector>
#include <pic-gl/Util/boxtools.hpp>
#include <pic-gl/Resources/Image.hpp>

namespace ld24{

class LevelLoader{
public:
    typedef std::vector<picppgl::objinfo> boxcont;
    typedef std::tuple<boxcont, picppgl::Image> lvlInfo;
private:
    boxcont obstacles;
    const int tilelength=50;
    int row, column;
    int maxlength;//for resizing
    void newline();
    void skytile();
    void walltile();
    void addtile(picppgl::Image);
    void error();
    picppgl::Image levelmap, sky, wall;
public:
    LevelLoader();
    lvlInfo parseLevel(std::string data);
};

}
#endif