CF = -Wall --std=c++14 -O2 -I/usr/include/glm -I/usr/include/SDL2
LF = -Wall --std=c++14 -lSDL2 -lSDL2_image

CXX = g++
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=obj/%.o)
TRG = sudal

all: $(TRG)


obj/%.o: src/%.cpp Makefile
	@mkdir -p obj/
	$(CXX) $(CF) $< -c -o $@


$(TRG): $(OBJ) Makefile
	$(CXX) $(OBJ) -o $@ $(LF)


clean:
	rm -rf obj/ $(TRG)


android:
	cd android-project && ../../android-ndk-r16/ndk-build

android-install: android
	cd android-project && ant debug install

android-run: android-install
	cd android-project && adb shell am start -a android.intenon.MAIN -n com.sdl.game/com.sdl.game.MySDLActivity

