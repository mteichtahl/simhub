UNAME := $(shell uname)
CC = gcc
CXX = g++ 
DEBUG = -g3 -O0 
CFLAGS = -I. -I./src $(DEBUG) -stdlib=libc++
CXXFLAGS = $(DEBUG) -stdlib=libc++ -std=c++14 
CDFLAGS = -arch x86_64
OUT = bin
LOG = logs

LDFLAGS = -L./src -L/usr/local/include -L./src/libs \
		 	 		-lconfig++ -stdlib=libc++ -lc++ \
					-lzlog -lpthread

CXXSOURCES = 	$(wildcard src/*.cpp) \
							$(wildcard src/configManager/*.cpp) \
							$(wildcard src/log/*.cpp) \

OBJECTS = $(SOURCES:.c=.o) $(CXXSOURCES:.cpp=.o)

simhub: $(OBJECTS) 	 
	$(CXX) $(CXXSOURCES) -o $(OUT)/simhub $(CXXFLAGS) $(LDFLAGS) $(CDFLAGS)
	@echo Generating debug symbols
	dsymutil $(OUT)/simhub
ifeq ($(UNAME),Darwin)
	@echo creating OS X intellisense tags
	gtags
endif

clean:
	-rm -rf bin/simhub.dSYM/
	-rm -f src/*.o src/*.a src/simhub
	-rm -f src/encoder/*.o
	-rm -f src/pin/*.o
	-rm -f src/cli/*.o
	-rm -f src/device/pokey/pokey.o
	-rm -f src/config/config.o

all: clean simhub

install: clean all
	$(shell mkdir -p $(OUT))
	$(shell mkdir -p $(LOGS))
	touch logs/log
