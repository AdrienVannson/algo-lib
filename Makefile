.PHONY: format

format:
		find include/ -regex ".*\.\(cpp\|hpp\)" -exec clang-format -i --style=Webkit {} \;
		find tests/ -regex ".*\.\(cpp\|hpp\)" -exec clang-format -i --style=Webkit {} \;
