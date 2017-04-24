CC = gcc
CXX = g++ 
DEBUG = -g3 -O0 
CFLAGS = -I. -I./src $(DEBUG) -stdlib=libc++
CXXFLAGS = $(DEBUG) -stdlib=libc++ -std=c++14 
CDFLAGS = -arch x86_64
OUT = bin

LDFLAGS = -L./src -L/usr/local/include -L./src/libs \
		 	 		-lconfig++ -stdlib=libc++ -lc++


		 

CXXSOURCES = 	$(wildcard src/*.cpp) \
							$(wildcard src/configManager/*.cpp) \

OBJECTS = $(SOURCES:.c=.o) $(CXXSOURCES:.cpp=.o)

pokey: $(OBJECTS) 	 
	@mkdir -p $(OUT)
	$(CXX) $(CXXSOURCES) -o $(OUT)/simhub $(CXXFLAGS) $(LDFLAGS) $(CDFLAGS)
	dsymutil $(OUT)/simhub

clean:
	-rm -rf bin/simhub.dSYM/
	-rm -f src/*.o src/*.a src/simhub
	-rm -f src/encoder/*.o
	-rm -f src/pin/*.o
	-rm -f src/cli/*.o
	-rm -f src/device/pokey/pokey.o
	-rm -f src/config/config.o

all: clean pokey

install: clean all
	mkdir -p logs
	touch logs/log
	brew install --HEAD libuv
	brew install libcli
	$(shell mkdir -p $(OUT))
