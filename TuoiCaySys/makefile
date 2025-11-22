CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pthread
SOURCES = main.c spwc_controller.c hal_sensors.c hal_actuators.c hal_buttons.c
OBJ = $(SOURCES:.c=.o)
TARGET = spws

all: $(TARGET)

$(TARGET): $(OBJ)
    $(CC) $(CFLAGS) -o $@ $^

clean:
    rm -f $(OBJ) $(TARGET)