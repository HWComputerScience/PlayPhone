all:
	g++ -std=c++11 -c -I./PracticalSocket -I./Examples -I./rapidjson -I./rapidjson/internal -I./rapidjson/error \
	-I./PlayPhone -I'javaconfig Headers' PlayPhone/*.cpp PracticalSocket/*.cpp Examples/*.cpp Java\ Wrapper/*.cxx -Wall -fPIC
	mkdir -p Build
	g++ -shared -o ./Build/libplayphone.so *.o

clean:
	rm *.o
