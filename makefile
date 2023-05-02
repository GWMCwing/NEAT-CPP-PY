CPPFLAGS = -Wall -std=c++17 -O3
INCLUDE_PATH="/usr/include/python3.9"

SHARED_LIB_NAME=libpycall

SRC_PATH=./src
OUTPUT_PATH=./lib

# src of all cpp in src folder
SRC=$(wildcard $(SRC_PATH)/*.cpp)

# src of all cpp in src folder
OBJ=$(SRC:.cpp=.o)

all: $(OUTPUT_PATH)/libpycall.so

$(OUTPUT_PATH)/libpycall.so: $(OBJ)
	@echo compiling shared library
	g++ -shared -o $@ $^ $(CPPFLAGS) -I$(INCLUDE_PATH)

%.o: %.cpp
	@echo compiling object: $@
	g++ -c -fPIC -o $@ $< $(CPPFLAGS) -I$(INCLUDE_PATH)

clean:
ifeq ($(OS), Windows_NT)
	del $(OBJ) $(OUTPUT_PATH)/$(SHARED_LIB_NAME).so
else
	rm -f $(OBJ) $(OUTPUT_PATH)/$(SHARED_LIB_NAME).so
endif

