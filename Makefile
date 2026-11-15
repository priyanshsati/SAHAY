CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17 -I/usr/include/cppconn
LDFLAGS = -lmysqlcppconn

all: bin/sahay_route bin/sahay_cli

bin/sahay_route: cpp/Database.cpp cpp/Sahay.cpp cpp/main.cpp
	mkdir -p bin
	$(CXX) $(CXXFLAGS) cpp/Database.cpp cpp/Sahay.cpp cpp/main.cpp -o bin/sahay_route $(LDFLAGS)
	@echo "Build complete: bin/sahay_route"

bin/sahay_cli: cpp/Database.cpp cpp/Sahay.cpp cpp/cli.cpp
	mkdir -p bin
	$(CXX) $(CXXFLAGS) cpp/Database.cpp cpp/Sahay.cpp cpp/cli.cpp -o bin/sahay_cli $(LDFLAGS)
	@echo "Build complete: bin/sahay_cli"

clean:
	rm -rf bin build tests/test_c_dsa

run: bin/sahay_cli
	./bin/sahay_cli

test: bin/sahay_route
	./tests/test_scenarios.sh

.PHONY: all clean run test
