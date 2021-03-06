// ***************************
// Date:
// Author:
// Module Name: ALUDec
// Description:
// ***************************
#include "verilated.h"
#include <verilated_vcd_c.h>
// Included with project
#include "include/Testbench.hpp"
//Generated by verilator
#include "VALUDec.h"
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

enum functcode {e_ADD = 0b100000,
                e_SUB = 0b100010,
                e_AND = 0b100100,
                e_OR  = 0b100101,
                e_SLT = 0b101010};



std::string get_functcode(functcode funct) {
    switch(funct) {
        case e_ADD:
            return "ADD";
        case e_SUB:
            return "SUB";
        case e_AND:
            return "AND";
        case e_OR:
            return "OR";
        case e_SLT:
            return "SLT";
    }
}

enum opcode {e_BRNCH = 0b01,
             e_MEMOP = 0b00,
             e_FUNCT = 0b11};

std::string get_opcode(opcode op) {
    switch(op) {
        case e_BRNCH:
            return "BRNCH";
        case e_MEMOP:
            return "MEMOP";
        case e_FUNCT:
            return "FUNCT";
    }
}
void set_input(VALUDec *port, opcode op, functcode funct) {
    port->i_funct = funct;
    port->i_aluop = op;
}

void set_input(VALUDec *port, opcode op) {
    port->i_funct = 0;
    port->i_aluop = op;
}

template <size_t N>
void set_expected_output(bitset<N> &expt_output, int expt_value) {
    expt_output = expt_value;
}

void decode_operation(opcode op, int expected, Testbench *top) {
    print(get_opcode(op), bitset<2>(op));
    set_input(top->m_core, op);
    set_expected_output(top->testPort->o_alucontrol, expected);
    top->tick();
    top->runTests();
}

void decode_function(opcode op, functcode funct, int expected, Testbench *top) {
    print(get_functcode(funct), bitset<6>(funct));
    set_input(top->m_core, op, funct);
    set_expected_output(top->testPort->o_alucontrol, expected);
    top->tick();
    top->runTests();
}

int main(int argc, char **argv, char **env) {
    Verilated::commandArgs(argc, argv);
    Testbench *top = new Testbench();
    // Open the trace file for waveform vcd
    top->opentrace("trace/trace.vcd");

    top->tick();

    decode_operation(e_MEMOP, 0b010, top);
    decode_operation(e_BRNCH, 0b110, top);
    decode_operation(e_FUNCT, 0b010, top);
    decode_function(e_FUNCT, e_ADD, 0b010, top);
    decode_function(e_FUNCT, e_SUB, 0b110, top);
    decode_function(e_FUNCT, e_OR, 0b000, top);
    decode_function(e_FUNCT, e_AND, 0b001, top);
    decode_function(e_FUNCT, e_SLT, 0b111, top);

    delete top;
    exit(0);
}
