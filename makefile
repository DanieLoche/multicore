CXX = g++
RM = rm -f
CFLAGS = -Wall -std=c++11 -Iinclude
EXEC_NAME = SchedulerSimulator
# INCLUDES = to include other makefiles
# LIBS = ""
HEADER_FILES = $(shell find ./include -maxdepth 1 -name "*.h")
SRC_FILES = $(shell find ./src -maxdepth 1 -name "*.cpp")
OBJ_FILES = $(patsubst %.cpp, %.o, $(SRC_FILES))
INSTALL_DIR = ./bin

all : $(EXEC_NAME)

clean :
	$(RM) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.cc
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

install :
	cp $(EXEC_NAME) $(INSTALL_DIR)
