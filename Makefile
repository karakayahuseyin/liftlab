BUILD_DIR = build 
EXEC = LiftLab
TEST_EXEC = $(EXEC)_tests

.DEFAULT_GOAL := all

.PHONY: all build debug clean run test usage

all: build

build:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && make

debug:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug .. && make

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

run:
	@cd $(BUILD_DIR) && ./$(EXEC)

test:
	@cd $(BUILD_DIR) && ./$(TEST_EXEC)

usage:
	@echo "Usage:"
	@echo "  make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  all       - Build and run the project"
	@echo "  build     - Build the project. (Default target)"
	@echo "  debug     - Build the project with debug flags."
	@echo "  clean     - Clean the build directory"
	@echo "  run       - Run the project"
	@echo "  test      - Run the tests"
	@echo "  usage     - Show this usage message"