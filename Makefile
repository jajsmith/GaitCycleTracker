# Makefile

Q1FLAG = -DLISTTYPE
CC = g++
CXXFLAGS = -Wall -g -MMD

OBJS = sensorpoint.o
DEPENDS = $(OBJS:.o=.d)

EXEC = gait

$(EXEC) : $(OBJS)
	$(CC) $(CXXFLAGS) $(Q1FLAG) $(OBJS) gait.cpp -o $(EXEC)

#get all *.d depends files
-include ${DEPENDS}

.PHONY: clean
clean:
	\rm *.o gait
