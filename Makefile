CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g -Isrc
TARGET   = movie_recommender
SRCDIR   = src

OBJS     = $(SRCDIR)/main.o $(SRCDIR)/Movie.o $(SRCDIR)/User.o $(SRCDIR)/Rating.o \
           $(SRCDIR)/MovieManager.o $(SRCDIR)/UserManager.o $(SRCDIR)/RatingManager.o \
           $(SRCDIR)/MovieSystem.o $(SRCDIR)/Recommender.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRCDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/MovieSystem.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.cpp -o $@

$(SRCDIR)/Movie.o: $(SRCDIR)/Movie.cpp $(SRCDIR)/Movie.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Movie.cpp -o $@

$(SRCDIR)/User.o: $(SRCDIR)/User.cpp $(SRCDIR)/User.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/User.cpp -o $@

$(SRCDIR)/Rating.o: $(SRCDIR)/Rating.cpp $(SRCDIR)/Rating.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Rating.cpp -o $@

$(SRCDIR)/MovieManager.o: $(SRCDIR)/MovieManager.cpp $(SRCDIR)/MovieManager.h $(SRCDIR)/Movie.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/MovieManager.cpp -o $@

$(SRCDIR)/UserManager.o: $(SRCDIR)/UserManager.cpp $(SRCDIR)/UserManager.h $(SRCDIR)/User.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/UserManager.cpp -o $@

$(SRCDIR)/RatingManager.o: $(SRCDIR)/RatingManager.cpp $(SRCDIR)/RatingManager.h $(SRCDIR)/Rating.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/RatingManager.cpp -o $@

$(SRCDIR)/Recommender.o: $(SRCDIR)/Recommender.cpp $(SRCDIR)/Recommender.h $(SRCDIR)/MovieManager.h $(SRCDIR)/RatingManager.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Recommender.cpp -o $@

$(SRCDIR)/MovieSystem.o: $(SRCDIR)/MovieSystem.cpp $(SRCDIR)/MovieSystem.h $(SRCDIR)/MovieManager.h $(SRCDIR)/RatingManager.h $(SRCDIR)/UserManager.h $(SRCDIR)/Recommender.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/MovieSystem.cpp -o $@

.PHONY: clean run

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)