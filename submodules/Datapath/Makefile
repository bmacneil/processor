VC=verilator
VFLAGS=-Wall --cc --trace
CC=g++
DEBUG=-g
CFLAGS='-std=c++14 -W -Wall -pedantic $(DEBUG)'


FILE=Datapath

verilator:
	$(VC) $(VFLAGS) -CFLAGS $(CFLAGS) $(FILE).sv --exe tb_$(FILE).cpp src/*.cpp

port:
	python scripts/parsePorts.py

testbench:
	make -j -C obj_dir/ -f V$(FILE).mk V$(FILE)

build: | verilator port

run-tb: testbench
	obj_dir/V$(FILE)

run: | verilator testbench
	obj_dir/V$(FILE)

debug: | verilator testbench
	gdb obj_dir/V$(FILE)

wave:
	gtkwave trace/trace.vcd trace/trace.sav &

all: | verilator port testbench run wave

clean:
	rm -rf obj_dir
	rm -f trace/trace.vcd
	rm -f include/port.hpp src/port.cpp

update: clean
	cp /home/brad/Projects/verilog/PROJECT/src/Testbench.cpp src/
	cp /home/brad/Projects/verilog/PROJECT/include/Testbench.hpp include/
	cp /home/brad/Projects/verilog/PROJECT/scripts/parsePorts.py scripts/
	sed -i -- 's/MODULENAME/'"$(FILE)"'/g' include/Testbench.hpp src/Testbench.cpp scripts/parsePorts.py

