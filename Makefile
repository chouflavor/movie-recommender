# Makefile 수정본
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET   = Movie_app
OBJS     = main.o Movie.o user.o rating.o # 👈 변경됨

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp Movie.h user.h rating.h
	$(CXX) $(CXXFLAGS) -c $<

Movie.o: Movie.cpp Movie.h
	$(CXX) $(CXXFLAGS) -c $<

user.o: user.cpp user.h 
	$(CXX) $(CXXFLAGS) -c $<

rating.o: rating.cpp rating.h 
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean run
clean:
	rm -f $(OBJS) $(TARGET)
run: $(TARGET)
	./$(TARGET)