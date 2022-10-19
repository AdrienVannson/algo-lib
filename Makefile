.PHONY: docs format clean docs

all: docs

docs:
		doxygen docs/Doxyfile
		cd build/latex && make

clean:
		rm -r build

format:
		find src/ -regex ".*\.\(cpp\|hpp\)" -exec clang-format -i --style=file {} \;
		find tests/ -regex ".*\.\(cpp\|hpp\)" -exec clang-format -i --style=file {} \;
