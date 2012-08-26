#ifndef picppgl_Resources_Image_hpp
#define picppgl_Resources_Image_hpp
#include <string>
using std::string;
namespace picppgl{

struct ImageData;
class Image{
private:
    ImageData *data;
public:
    struct Color{int r,g,b;};
    explicit Image(string path);
    explicit Image(int w, int h);
    explicit Image(ImageData*);
    explicit Image(string text,int fontsize, Color fg={255,255,255}, Color bg={0,0,0});
    Image(const Image& other);
    Image & operator= (const Image &other);
    explicit Image(string path, int w, int h);
    explicit Image(int w, int h, int r, int b, int g, ImageData *context);
    ~Image();
    void resize(int width, int height);
    void apply(Image &what, int x, int y);
    Image Copy(int x, int y, int w, int h);
    int w()const;
    int h()const;
    void flip();
};


}

#endif