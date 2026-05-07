CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2
TARGET = chess
SOURCES = main.cpp Game.cpp Board.cpp Piece.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET) chess.exe
