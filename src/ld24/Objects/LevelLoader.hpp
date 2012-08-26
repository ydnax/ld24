#ifndef ld24_levelloader_hpp
#define ld24_levelloader_hpp
#include <tuple>
#include <string>
#include <vector>
#include <pic-gl/Util/boxtools.hpp>
#include <pic-gl/Resources/Image.hpp>
#include <pic-gl/Ui/gfx_object.hpp>
#include <pic-gl/Ui/main_window.hpp>
#include <pic-gl/Helpers/GfxRegister.hpp>
#include <pic-gl/Gameflow/Level.hpp>

namespace ld24{
using namespace picppgl;
class LevelLoader:public levelObject, gfxobject{
public:
    typedef std::vector<picppgl::objinfo> boxcont;
    typedef std::tuple<boxcont, picppgl::Image> lvlInfo;
private:
    struct tile{
        Image img;
        int x,y;
    };
    GfxRegister r;
    std::vector<tile> tiles;
    boxcont obstacles;
    int row, column;
    picppgl::Image sky, wall;
    const int tilelength=50;
    int maxwidth=1;
    void newline();
    void skytile();
    void walltile();
    void error();
public:
    LevelLoader(Level *lvl, std::string data);
    boxcont getBoxes()const{return obstacles;}
    virtual void update(int) override{}
    virtual void draw(Image&) override;
    virtual ~LevelLoader(){}
};

}
#endif