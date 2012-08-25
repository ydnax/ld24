from os import walk
VariantDir('build', 'src/')
env = Environment()
env.Replace( CXX      = "clang++" )
env.Append(  CXXFLAGS = "-stdlib=libc++ -fcolor-diagnostics")
env.Append(  CCFLAGS  = '-pedantic -Wall -Wextra -Werror -std=c++11 -ferror-limit=2' )
env.Append(  LIBS     = ['c++','SDL', 'SDL_image', 'SDL_gfx', 'SDL_mixer', 'SDL_ttf',] )
env.Append(  CPPPATH  = 'build' )
debug = ARGUMENTS.get('debug', 0)
if int(debug)==1:
    env.SetOption('num_jobs', 1)
    env.Append(LINKFLAGS = '-faddress-sanitizer ')
    env.Append(CCFLAGS   = '-faddress-sanitizer -fcatch-undefined-behavior -g -ggdb -O0')  
else:
    env.SetOption('num_jobs', 4)
    env.Append(CCFLAGS = '-O3  -mmmx  -msse  -msse2 -msse3')
sources=[str(y).replace('src', 'build', 1) for x in (Glob(dir[0]+'/*.cpp') for dir in walk('src')) for y in x]
env.Program('game.bin', sources)
