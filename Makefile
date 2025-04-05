CC = gcc
CFLAGS = -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
TARGET = pizza_analyzer
SOURCES = src/pizza_analysis.c main.c
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean run

all: $(BUILD_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/pizza_analysis.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@
	@echo "Compilación exitosa. Ejecutable creado en $(BUILD_DIR)/$(TARGET)"

run: $(BUILD_DIR)/$(TARGET)
	@echo "Ejecutando el analizador de pizzas..."
	@$(BUILD_DIR)/$(TARGET) $(csv_file) $(metrics)

clean:
	@echo "Limpiando archivos..."
	@rm -rf $(OBJ_DIR) $(BUILD_DIR)


