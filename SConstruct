from os import walk
VariantDir('build', 'src/')
env = Environment()
ragel_s=Builder( action     = 'ragel $SOURCE -o $TARGET', 
                 suffix     = '.cpp',
                 src_suffix = '.ragel.cpp')
ragel_i=Builder( action     = 'ragel -p -V $SOURCE | dot -Tpng > $TARGET', 
                 suffix     = '.png',
                 src_suffix = '.ragel.cpp')

env.Append(  BUILDERS = {'Ragel' : ragel_s, 'RagelImage': ragel_i})
env.Replace( CXX      = "clang++" )
env.Append(  CXXFLAGS = "-stdlib=libc++ -fcolor-diagnostics")
env.Append(  CCFLAGS  = '-pedantic -Wall -Wextra -Werror -std=c++11 -ferror-limit=2' )
env.Append(  LIBS     = ['c++','SDL', 'SDL_image', 'SDL_gfx', 'SDL_mixer', 'SDL_ttf',] )
env.Append(  CPPPATH  = 'build' )
debug = int(ARGUMENTS.get('debug', 0))
if debug==1:
    env.SetOption('num_jobs', 1)
    env.Append(LINKFLAGS = '-faddress-sanitizer ')
    env.Append(CCFLAGS   = '-faddress-sanitizer -fcatch-undefined-behavior -g -ggdb -O0')  
else:
    env.SetOption('num_jobs', 4)
    env.Append(CCFLAGS = '-O3  -mmmx  -msse  -msse2 -msse3')
sources=[str(y).replace('src', 'build', 1) for x in (Glob(dir[0]+'/*.cpp') for dir in walk('src')) for y in x]
sources=[a for a in sources if (a.find('ragel')==-1)]
parserpath='build/ld24/RealLevelLoader'
parser=env.Ragel(parserpath)
#env.RagelImage(parserpath)
sources.append(parser)
env.Program('game.bin', sources)
