.PHONY: format

format:
		find src/ -regex ".*\.\(cpp\|hpp\)" -exec clang-format -i --style=file {} \;
		find tests/ -regex ".*\.\(cpp\|hpp\)" -exec clang-format -i --style=file {} \;
