all: main.cpp ExpandedMonitor.cpp
	g++ main.cpp ExpandedMonitor.cpp -pthread
