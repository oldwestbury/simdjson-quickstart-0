all: quickstart quickstart2 project


quickstart:
	g++ quickstart.cpp simdjson.cpp -o quickstart
quickstart2:
	g++ quickstart2.cpp simdjson.cpp -o quickstart2
project:
	g++ project.cpp simdjson.cpp -o project


