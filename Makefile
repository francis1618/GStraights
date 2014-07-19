CXX= g++
CXXFLAGS = -Wall -O -g -MMD `pkg-config gtkmm-2.4 --cflags --libs`
OBJS = Subject.o Model.o View.o Controller.o CardButton.o CardImage.o Card.o Deck.o Misc.o StraightStrategy.o HumanStrategy.o ComputerStrategy.o Player.o main.o
DEPENDS = ${OBJS:.o=.d}
EXEC = hello

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(EXEC)


clean:
	rm -rf ${OBJS} ${EXEC} ${DEPENDS}

-include ${DEPENDS}