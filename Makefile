.PHONY: test test-coverage docs format clean

test:
	cd tests && algocompile && ./prog

test-coverage:
	cd tests && algocompile
	rm tests/prog
	mkdir -p build/temp
	mv tests/output.cpp build/temp/output.cpp
	cd build/temp && \
		g++ -coverage -O0 output.cpp -o prog && \
		./prog && \
		gcov prog-output --relative-only && \
		lcov --capture --directory . --output-file coverage.info && \
		genhtml coverage.info --demangle-cpp --title Algolib -o ../coverage
	rm -r build/temp

docs:
	doxygen docs/Doxyfile
	sphinx-build -b html -Dbreathe_projects.algolib=../build/xml docs build/docs

clean:
	rm -r build

format:
	find src/ -regex ".*\.\(cpp\|hpp\)" -exec clang-format -i --style=file {} \;
	find tests/ -regex ".*\.\(cpp\|hpp\)" -exec clang-format -i --style=file {} \;
