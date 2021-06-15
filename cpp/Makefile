all: run 

clean:
	rm -rf build

build:
	@mkdir -p build
	@echo "> cmake .."
	@cd build && cmake .. 
	@echo "> make"
	@cd build && make
	
run:
	@echo "> ./build/Connect4Solver"
	./build/Connect4Solver

test: 
	@echo "> ./build/Connect4Tests"
	./build/Connect4Tests --log_level=unit_scope

.PHONY: build