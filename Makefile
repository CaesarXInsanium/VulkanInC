BUILD_DIR=build
BIN=$(BUILD_DIR)/vkvk

all: $(BUILD_DIR)
	./compile_shaders
	meson compile -C $(BUILD_DIR)

$(BUILD_DIR):
	meson setup $(BUILD_DIR)

run: all
	./$(BIN)	

debug: all
	gdb $(BIN)

clean:
	rm -rf $(BUILD_DIR)
