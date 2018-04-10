// ***************************
// Date:
// Author:
// Module Name: ALU
// Description:
// ***************************
#include "verilated.h"
#include <verilated_vcd_c.h>
// Included with project
#include "include/Testbench.hpp"
//Generated by verilator
#include "VALU.h"
// Generated by python script
#include "include/port.hpp"
// Std library
#include <iostream>
#include <string>

int test_count = 1;

template<typename T, typename U>
void print(T val1, U val2) {
    std::cout << val1 << " : " << val2 << std::endl;
}

template<typename T, typename U, typename V>
void print(T val1, U val2, V val3) {
    std::cout << val1 << " : " << val2 << " : " << val3 << std::endl;
}

enum aluctrl {
    ADD = 0b010,
    SUB = 0b110,
    AND = 0b000,
    OR  = 0b001,
    SLT = 0b111
};



void test_operation(aluctrl op, int a, int b, int expected, int exp_zero, Testbench *top) {
    print("Test", test_count);
    top->m_core->i_a = a;
    top->m_core->i_b = b;
    top->m_core->i_alucontrol = op;
    top->testPort->o_result = expected;
    top->testPort->o_zero = exp_zero;
    top->eval();
    top->runTests();
    test_count++;
}


int main(int argc, char **argv, char **env) {
    Verilated::commandArgs(argc, argv);
    Testbench *top = new Testbench();
    // Open the trace file for waveform vcd
    top->opentrace("trace/trace.vcd");
    print("\nRunning Tests", "");

    // Test Addition
    test_operation(ADD, 1, 1, 2, 0, top);
    test_operation(ADD, 1, 0, 1, 0, top);
    test_operation(ADD, 0, 1, 1, 0, top);

    // Test Subtraction
    test_operation(SUB, 1, 0, 1, 0, top);
    test_operation(SUB, 5, 0, 5, 0, top);
    test_operation(SUB, 5, 2, 3, 0, top);
    test_operation(SUB, 0, 1, ~0, 0, top);

    // Test less than
    test_operation(SLT, 1, 1, 0, 1, top);
    test_operation(SLT, 1, 0, 0, 1, top);
    test_operation(SLT, 1, 2, 1, 0, top);

    //Test AND
    test_operation(AND, 0b00110, 0b10100, 0b0100, 0, top);

    // Test Or
    test_operation(OR, 0b1010, 0b0101, 0b1111, 0, top);

    delete top;
    exit(0);
}