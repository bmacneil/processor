VC=verilator
VFLAGS=-Wall --cc --trace
CC=g++
CFLAGS='-std=c++14 -W -Wall -pedantic'


FILE=Controller

verilator:
	$(VC) $(VFLAGS) -CFLAGS $(CFLAGS) $(FILE).sv --exe tb_$(FILE).cpp src/*.cpp

port:
	python scripts/parsePorts.py

testbench:
	make -j -C obj_dir/ -f V$(FILE).mk V$(FILE)

build: | verilator port testbench
	obj_dir/V$(FILE)

run-tb: testbench
	obj_dir/V$(FILE)

run: | verilator testbench
	obj_dir/V$(FILE)

wave:
	gtkwave trace/trace.vcd trace/trace.sav &

all: | verilator port testbench run wave

clean:
	rm -rf obj_dir
	rm -f trace.vcd