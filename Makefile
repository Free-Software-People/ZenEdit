CXX = g++
CXXFLAGS = -std=c++17 $(shell pkg-config --cflags Qt5Widgets)
LDFLAGS = $(shell pkg-config --libs Qt5Widgets)

TARGET = ZenEdit
SRC_DIR = src
BUILD_DIR = build

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/zenedit.cpp
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/zenedit.o
MOC_FILE = $(SRC_DIR)/zenedit.h
MOC_SRC = $(BUILD_DIR)/moc_zenedit.cpp
MOC_OBJ = $(BUILD_DIR)/moc_zenedit.o

.PHONY: all build run test clean

all: build

build: $(TARGET)

$(TARGET): $(OBJS) $(MOC_OBJ)
	$(CXX) $(OBJS) $(MOC_OBJ) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/zenedit.o: $(SRC_DIR)/zenedit.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MOC_SRC): $(MOC_FILE)
	@mkdir -p $(BUILD_DIR)
	moc $(MOC_FILE) -o $(MOC_SRC)

$(MOC_OBJ): $(MOC_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: build
	./$(TARGET)

test:
	@echo "No tests defined. Skipping tests."

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
