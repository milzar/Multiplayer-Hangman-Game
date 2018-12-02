#Makefile
# disable all warnings
CXXFLAGS += -w

output: server.cpp client.cpp wrapper.h GameData.h
		g++ server.cpp GameData.cpp wrapper.cpp -lncurses  -o server
		g++ client.cpp GameData.cpp wrapper.cpp -lncurses -o client
