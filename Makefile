C_FILES	:= $(wildcard *.cpp)
H_FILES	:= $(wildcard *.h)

out.exe: $(C_FILES) $(H_FILES)
	g++ $(C_FILES) --std=c++11 -o $@

clean:
	-rm out.exe

.PHONY: clean
