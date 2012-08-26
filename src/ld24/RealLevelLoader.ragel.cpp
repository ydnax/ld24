%%{
machine level_gen;
action number_start{number_start();}
action number_push{number_push(fc);}
action number_end{number_end();} 

action version_number{version_number();}

action xvar{xvar();}
action yvar{yvar();}

action str_start{str_start();}
action str_push{str_push(fc);}
action str_end{str_end();}

action set_dir{setDirection(fc);}

action level_end{level_finish();}
action line_incr{linecount++;}


action spawn{spawn();}
action finish{finish();}
action wall{wall();}
action spike{spike();}
action powerup{powerup();}
action pu_speed{pu_speed();}
action pu_jump{pu_jump();}

action perr{error("Syntax Error");}
action end{end();}

number  = digit+ >number_start $number_push %number_end ;
eol     = ' '* . '\n';
xvar    = number %xvar;
yvar    = number %yvar;
pos     = xvar . ','.' '* . yvar;
string  = '"'%str_start . any+$str_push :> '"'%str_end;

dir = ('^'|'v'|'<'|'>')%set_dir;

version = ('VERSION:' . ' '  . number)%version_number;

spawn = ('spawn'.' '+.pos)%spawn;
finish = ('finish'.' '+.pos)%finish;
spike = ('spike'.' '+.pos)%spike;
wall = ('wall'.' '+ . pos . ' '+ . dir . ' '+ .number)%wall;
pu_j = 'jump'  %pu_jump;
pu_s = 'speed' %pu_speed;
powerup = ('powerup'.' '+.pos.' '+.(pu_j|pu_s).' '+.number)%powerup;


levelend = 'END LEVEL'%level_end;
comment = '--'.(any*--'\n');

line = (' '*.(spawn|finish|spike|wall|powerup|comment|levelend)?.comment?.eol)%line_incr;

mainx=wall;
main:=( version.eol+.
        line*
    )%/end %/level_end $!perr; 
}%%

#include <iostream>
#include <ld24/Objects/ImgObj.hpp>
#include <ld24/Objects/Powerup.hpp>
#include "RealLevelLoader.hpp" 
using namespace std;
namespace ld24{
void RealLevelLoader::number_start(){
    nbuf.str("");
}
void RealLevelLoader::number_push(char c){
    nbuf<<c;
}
void RealLevelLoader::number_end(){
    numcache=stoi(nbuf.str());
}
void RealLevelLoader::xvar(){
    xcache=numcache;
}
void RealLevelLoader::yvar(){
    ycache=numcache;
}
void RealLevelLoader::str_start(){
    strbuf.str("");
}
void RealLevelLoader::str_push(char c){
    strbuf<<c;
}
void RealLevelLoader::str_end(){
    strcache=strbuf.str();
}
void RealLevelLoader::version_number(){
    int levelversion=numcache;
    if(levelversion!=1){
        cerr<<"INVALID LEVEL VERSION"<<endl;
        exit(1);
    }
}
void RealLevelLoader::setDirection(char c){
    cout<<"set direction: "<<c<<endl;
    switch(c){
        case '^':direction=up;break;
        case 'v':direction=down;break;
        case '<':direction=left;break;
        case '>':direction=right;break;
        default:direction=right;cerr<<"invalid direction oO"<<endl;break;
    }
}    

void RealLevelLoader::error(string msg){
    cerr<<"PARSING ERROR: "<<msg<<endl<<"Line: "<<linecount<<endl;
    exit(1);
}

void RealLevelLoader::end(){
    cout<<"parsed all levels :)"<<endl;
}

void RealLevelLoader::level_finish(){
    cout<<"level finish"<<endl;
    if(lcomps.empty())
        return;
    auto _lcomps=lcomps;
    auto lgen =     [=]()->Level*{
        auto lvl=new Level{};
        for(auto &&element:_lcomps){
            element(lvl);
        }
        return lvl;
    };
    lcache.push_back(lgen);
    lcomps={};
}

void RealLevelLoader::spawn(){
    cerr<<"spawn not implemented yet :("<<endl;
}
void RealLevelLoader::finish(){
    cerr<<"finish not implemented yet :("<<endl;
}

void RealLevelLoader::wall(){
    auto xcache_    = xcache;
    auto ycache_    = ycache;
    auto numcache_  = numcache;
    auto direction_ = direction;

    lcomps.push_back([=](Level *lvl){
        int cx=xcache_;
        int cy=ycache_;
        int steps=numcache_;
        Image tile("resources/gfx/tiles/bluegreenRaw.png",50,50);
        while(steps>0){
            int x=50*cx;
            int y=50*cy;
            //cout<<"new img x,y "<<x<<" "<<y<<endl;
            new ImgObj(lvl, x, y, tile);
            lvl->addObstacle({{x,y},50,50});
            switch(direction_){
                default:cerr<<"direction undefined"<<endl;break;
                case up     :cy--;break;
                case down   :cy++;break;
                case left   :cx--;break;
                case right  :cx++;break;
            }
            steps--;
        }
    });
}
void RealLevelLoader::spike(){
    cerr<<"spike not implemented yet :("<<endl;
}
void RealLevelLoader::powerup(){
    int x=xcache;
    int y=ycache;
    int strength=numcache;
    lcomps.push_back([=](Level *lvl){
    std::vector<Image> images;
    std::function<void(Player*)> effect;
        if(powertype==speed){
            for (int i = 0; i < 24; ++i){
                stringstream s;
                s<<"resources/gfx/powerups/faster-anim"<<i<<".png";
                images.emplace_back(Image(s.str(), 50, 50));
            }
            effect=[=](Player* pl){pl->up_walkspeed+=strength;};
        }else if(powertype==jump){
            for (int i = 0; i < 24; ++i){
                stringstream s;
                s<<"resources/gfx/powerups/higherjump-ani"<<i<<".png";
                images.emplace_back(Image(s.str(), 50, 50));
            }
            effect=[=](Player* pl){pl->up_canjump=strength;cerr<<"enable"<<endl;};
        }
        cout<<"new powerup @"<<x<<" "<<y<<endl;
        new ld24::Powerup{lvl, x*50, y*50, images, effect};
    });



    

}
void RealLevelLoader::pu_speed(){
    powertype=speed;
}
void RealLevelLoader::pu_jump(){
    powertype=jump;
}

RealLevelLoader::T_Levels RealLevelLoader::parse(string data){
//ignore warnings by ragel generated sourcecode.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
        auto d   = const_cast<char*>(data.c_str()); //fix to string iterators
        auto p   = d;
        auto pe  = d+data.length();
        auto eof = pe;
        int cs   = 0;
        %%write data;
        %%write init;
        %%write exec;
#pragma clang diagnostic pop
        return lcache;

}


}
/*
wall x,y richtung länge --kommentar
wall 0,10 v 20 --boden
spawn 0,0
powerup 10,9 jump 1
powerup 15,8 speed 10
finish 20,9//*/