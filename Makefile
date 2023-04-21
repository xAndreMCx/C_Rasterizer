TARGET = $(BIN_DIR)/rasterizer.exe

INCLUDE_DIR = ./include
LIB_DIR = ./lib
BIN_DIR = ./bin
SRC_DIR = ./src
OBJ_DIR = $(BUILD_DIR)/obj

CC = gcc
WARNFLAGS = -Wall -Wextra
DEFINES =
CCFLAGS = -g $(WARNFLAGS) -I$(INCLUDE_DIR) $(DEFINES)
LDFLAGS = -L$(LIB_DIR)
LDLIBS = -leasyppm

CFILES = $(SRC_DIR)/main.c

OBJECTS = $(subst $(SRC_DIR), $(OBJ_DIR), $(CFILES:%.c=%.o))

.PHONY: all clean run

all: $(TARGET)

run: $(TARGET)
	@$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	$(RM) -rf $(TARGET) $(OBJECTS)
