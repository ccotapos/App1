CC = gcc
CFLAGS = -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
TARGET = app1
SOURCES = src/pizza_analysis.c main.c
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean run

all: $(BUILD_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/pizza_analysis.h
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@
	@echo "Compilación exitosa. Ejecutable creado en $(BUILD_DIR)/$(TARGET)"

run: $(BUILD_DIR)/$(TARGET)
	@echo "Ejecutando el analizador de pizzas..."
	@$(BUILD_DIR)/$(TARGET) $(csv_file) $(metrics)

clean:
	@echo "Limpiando archivos..."
	@if exist $(OBJ_DIR) rd /s /q $(OBJ_DIR)
	@if exist $(BUILD_DIR) rd /s /q $(BUILD_DIR)
