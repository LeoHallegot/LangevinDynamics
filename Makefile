CPPC = g++
CFLAGS = -W -Wall -Wshadow -pedantic -std=c++17
RM = rm -f
rep = src/

OBJS = $(SRCS:.cpp=.o)

a.out : $(rep)langevin_dynamics.o $(rep)constants.o $(rep)potentials.o
	$(CPPC) $(rep)langevin_dynamics.cpp $(rep)constants.cpp $(rep)potentials.cpp


langevin_dynamics.o : $(rep)langevin_dynamics.cpp $(rep)langevin_dynamics.h $(rep)constants.h $(rep)potentials.h
	$(CPPC) -c $(CFLAGS) $(rep)langevin_dynamics.cpp

constants.o : $(rep)constants.cpp $(rep)constants.h
	$(CPPC) -c $(CFLAGS) $(rep)constants.cpp


potentials.o : $(rep)potentials.cpp $(rep)potentials.h $(rep)constants.h
	$(CPPC) -c $(CFLAGS) $(rep)potentials.cpp

#tools.o : $(rep)tools.cpp $(rep)tools.h $(rep)potentials.h $(rep)constants.h $(rep)langevin_dynamics.h
#	$(CPPC) -c $(CFLAGS) $(rep)tools.cpp

#Removing .o files
.PHONY: clean
clean:
	/bin/rm -f src/ *.o
