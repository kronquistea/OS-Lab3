memsim: main.cpp memsim.cpp
	@echo "Compiling main.cpp and memsim.cpp"
	g++ -o memsim main.cpp memsim.cpp

clean:
	rm memsim