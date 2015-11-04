 # Description: Makefile
 #
 # This program is free software: you can redistribute it and/or modify it under the terms of the
 # GNU General Public License as published by the Free Software Foundation, either version 3 of the
 # License, or any later version.
 #
 # This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 # even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 # General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License along with this program. If
 # not, see <http://www.gnu.org/licenses/>.

CC=/usr/bin/g++
CFLAGS=-c -Wall -O3

UNAME := $(shell uname)

#LINUX:
ifeq ($(UNAME), Linux)
LDFLAGS=-rdynamic -Lhazelcast/lib -lHazelcastClient3.7-SNAPSHOT_64-linux64 -lpthread  -lrt
endif

#MAC OSX:
ifeq ($(UNAME), Darwin)
LDFLAGS=-Lhazelcast/lib -lHazelcastClient3.7-SNAPSHOT_64-mac -lpthread
endif

INC=-Ihazelcast/include
SOURCES = $(wildcard *.cpp)


OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=simplemin

all: 	$(SOURCES) $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(INC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(INC) $(CFLAGS)  $< -o $@

clean:
	rm *.o $(EXECUTABLE)
