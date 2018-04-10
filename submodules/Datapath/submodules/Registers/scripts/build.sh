FILENAME="${1%.*}"
VERILOGFILE=$FILENAME.sv
MAKEFILE=V$FILENAME.mk
OBJECTFILE=V$FILENAME
TESTBENCH=$2

verilator -Wall --cc --trace $VERILOGFILE --exe $TESTBENCH
cd obj_dir/
pwd
make -f $MAKEFILE $OBJECTFILE
cd ..
pwd
# obj_dir/$OBJECTFILE

# # cleanup
# rm -rf obj_dir
# rm -f  counter.vcd


# # run Verilator to translate Verilog into C++, include C++ testbench
# verilator -Wall --cc --trace counter.v --exe counter_tb.cpp
# # build C++ project
# make -j -C obj_dir/ -f Vcounter.mk Vcounter
# # run executable simulation
# obj_dir/Vcounter


# # view waveforms
# gtkwave counter.vcd counter.sav &
