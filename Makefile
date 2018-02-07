CXX := g++
CXXFLAGS := 
TARGET := mfc

SRC_FILE := $(shell find . -name "*.cpp")
INC_FILE := $(shell find . -name "*.h")

$(TARGET) : $(SRC_FILE) $(INC_FILE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_FILE)

clean:
	-rm -f $(TARGET)
