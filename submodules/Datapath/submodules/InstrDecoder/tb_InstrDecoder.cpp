// ***************************
// Date:
// Author:
// Module Name: InstrDecoder
// Description:
// ***************************
#include "verilated.h"
#include <verilated_vcd_c.h>
// Included with project
#include "include/Testbench.hpp"
//Generated by verilator
#include "VInstrDecoder.h"
// Generated by python script
#include "include/port.hpp"
// Std library
#include <iostream>
#include <string>


template<typename T, typename U>
void print(T val1, U val2) {
    std::cout << val1 << " : " << val2 << std::endl;
}

template<typename T, typename U, typename V>
void print(T val1, U val2, V val3) {
    std::cout << val1 << " : " << val2 << " : " << val3 << std::endl;
}

int assert_output(Testbench *top) {
    static int count = 0;
    top->testPort->o_RegA_addr = 0b00000;
    top->testPort->o_RegB_addr = 0b11111;
    if(int(top->m_core->i_regdst))
        top->testPort->o_RegD_addr = 0b00000;
    else
        top->testPort->o_RegD_addr = 0b11111;
    top->testPort->o_op = 0x3F;
    top->testPort->o_funct = 0x00;
    top->testPort->o_Imm = 0xC0 ;
    return count++;
}

int assert_output_inverted(Testbench *top) {
    static int count = 0;
    top->testPort->o_RegA_addr = 0b11111;
    top->testPort->o_RegB_addr = 0b00000;
    if(int(top->m_core->i_regdst))
        top->testPort->o_RegD_addr = 0b11111;
    else
        top->testPort->o_RegD_addr = 0b00000;
    top->testPort->o_op = 0x00;
    top->testPort->o_funct = 0x3F;
    top->testPort->o_Imm = 0x3F ;
    return count++;
}

void set_input(VInstrDecoder * core, int regdst, int instrwrite) {
    core->i_regdst = regdst;
    core->i_instrwrite = instrwrite;
}


int main(int argc, char **argv, char **env) {
    Verilated::commandArgs(argc, argv);
    Testbench *top = new Testbench(true);
    // Open the trace file for waveform vcd
    top->opentrace("trace/trace.vcd");
    int regdst;
    int instrwrite;

    print("Testbench Version", top->version);
    print("Port Version", top->testPort->version);
    print("\nModule", "InstrDecoder", "Running Tests");
    top->reset();
    top->m_core->i_Memdata = 0xFC1F07C0;
    regdst = 0b1;
    instrwrite = 0b1;
    set_input(top->m_core, regdst, instrwrite);
    top->tick();
    top->run_tests("Instruction Test (0xFC1F07C0)", assert_output(top));
    top->m_core->i_Memdata = uint32_t(~0xFC1F07C0);
    regdst = 0b1;
    instrwrite = 0b1;
    set_input(top->m_core, regdst, instrwrite);
    top->tick();
    top->run_tests("Instruction Test Inverted(~0xFC1F07C0)", assert_output_inverted(top));
    top->m_core->i_Memdata = uint32_t(0xFC1F07C0);
    regdst = 0b1;
    instrwrite = 0b0;
    set_input(top->m_core, regdst, instrwrite);
    top->tick();
    top->run_tests("Instruction Test Inverted(~0xFC1F07C0)", assert_output_inverted(top));
    top->m_core->i_Memdata = uint32_t(0xFC1F07C0);
    regdst = 0b0;
    instrwrite = 0b0;
    set_input(top->m_core, regdst, instrwrite);
    top->tick();
    top->run_tests("Instruction Test Inverted (~0xFC1F07C0)", assert_output_inverted(top));
    top->m_core->i_Memdata = uint32_t(0xFC1F07C0);
    regdst = 0b0;
    instrwrite = 0b1;
    set_input(top->m_core, regdst, instrwrite);
    top->tick();
    top->run_tests("Instruction Test (0xFC1F07C0)", assert_output(top));
    delete top;
    exit(0);
}