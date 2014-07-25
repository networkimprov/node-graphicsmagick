all: graphiscsmagick_lode.so

graphiscsmagick_lode.so: src/graphicsmagick_lode.cc
	gcc -o graphicsmagick_lode.so -pthread -fpic -shared -Wl,-soname,graphicsmagick_lode.so src/graphicsmagick_lode.cc -lm -lc -Inode_modules/lode/src -Wall $(shell GraphicsMagick++-config --cppflags --cxxflags --ldflags --libs)
