all:
	swig -c++ -java Java\ Wrapper/openpad.i
	g++ -std=c++11 -c -I./PracticalSocket -I./Examples -I./rapidjson -I./rapidjson/internal -I./rapidjson/error \
	-I./PlayPhone -I/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/include \
	-I/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/include/darwin PlayPhone/*.cpp PracticalSocket/*.cpp \
	Example/*.cpp Java\ Wrapper/*.cxx -Wall -fPIC
	mkdir -p Build
	g++ -dynamiclib *.o -o ./Build/libopenpad.jnilib

clean:
	rm *.o
