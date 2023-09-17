CPPFLAGS = -Wall -std=c++17 -fPIC
INCLUDE_PATH="/home/gw_mc/miniconda3/include/python3.11/"
PYBIND11_INCLDUES = "./lib/pybind11/include"
# PYBIND11_LIB = "./lib/pybind11/include/pybind11/"

SHARED_LIB_NAME=libpycall

SRC_PATH=./src
LOCAL_TEST_PATH=./_test
OUTPUT_PATH=./lib
LOCAL_TEST_OUTPUT_PATH=./_test

# src of all cpp in src folder
SRC=$(wildcard $(SRC_PATH)/*.cpp)
SRC_WITH_PYBIND=$(SRC)
SRC_WITHOUT_PYBIND=$(filter-out $(SRC_PATH)/_Python_lib.cpp, $(SRC_WITH_PYBIND))
LOCAL_TEST_PATH_SRC=$(wildcard $(LOCAL_TEST_PATH)/handler/*.cpp)

# src of all cpp in src folder
OBJ=$(SRC:.cpp=.o)
OBJ_WITHOUT_PYBIND=$(SRC_WITHOUT_PYBIND:.cpp=.o)
TEST_OBJ=$(LOCAL_TEST_PATH_SRC:.cpp=.o)

all: $(OUTPUT_PATH)/libpycall.so 

test: $(LOCAL_TEST_PATH)/main.exe

$(OUTPUT_PATH)/libpycall.so: $(OBJ)
	@echo compiling shared library
	g++ -shared -o $@ $^ $(CPPFLAGS) -I$(INCLUDE_PATH) -I$(PYBIND11_INCLDUES)

%.o: %.cpp
	@echo compiling object: $@
	g++ -c -o $@ $< $(CPPFLAGS) -I$(INCLUDE_PATH) -I$(PYBIND11_INCLDUES)

$(LOCAL_TEST_PATH)/main.o: $(LOCAL_TEST_PATH)/main.cpp
	@echo compiling main.o
	@g++ -c -o $@ $< $(CPPFLAGS) -I$(INCLUDE_PATH) -I$(PYBIND11_INCLDUES)

$(LOCAL_TEST_PATH)/main.exe: $(OBJ_WITHOUT_PYBIND) $(TEST_OBJ) $(LOCAL_TEST_PATH)/main.o 
	@echo compiling main.exe for local _test
	@g++ -o $@ $^ $(CPPFLAGS) 

cleanTest:
ifeq ($(OS), Windows_NT)
	del $(LOCAL_TEST_PATH)/*.o 
	del $(LOCAL_TEST_PATH)/**/*.o 
	del $(LOCAL_TEST_PATH)/main.exe 
else
	rm -f $(LOCAL_TEST_PATH)/*.o 
	rm -f $(LOCAL_TEST_PATH)/**/*.o 
	rm -f $(LOCAL_TEST_PATH)/main.exe
endif

cleanAll:
ifeq ($(OS), Windows_NT)
	del $(OBJ) $(OUTPUT_PATH)/$(SHARED_LIB_NAME).so
	del $(LOCAL_TEST_PATH)/*.o
	del $(LOCAL_TEST_PATH)/**/*.o
	del $(LOCAL_TEST_PATH)/main.exe
else
	rm -f $(OBJ) $(OUTPUT_PATH)/$(SHARED_LIB_NAME).so 
	rm -f $(LOCAL_TEST_PATH)/*.o 
	rm -f $(LOCAL_TEST_PATH)/**/*.o 
	rm -f $(LOCAL_TEST_PATH)/main.exe 
endif

