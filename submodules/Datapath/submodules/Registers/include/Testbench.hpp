#ifndef TESTBENCH_HPP
#define TESTBENCH_HPP


#include "VRegisters.h"
#include "verilated.h"
#include <verilated_vcd_c.h>
#include "port.hpp"
#include <iostream>
#include <string>


class Testbench {
public:
    unsigned long   m_tickcount;
    VRegisters  *m_core;
    OUTPUT_PORT *testPort;
    VerilatedVcdC   *m_trace;
    std::string version = "v1.0";
    std::string error_msg = "";
    bool trace_on;

    Testbench(bool trace_state = false);

    virtual ~Testbench(void);

    void reset(void);

    // Open/create a trace file
    void opentrace(const char *vcdname);

    void close(void);

    void tick(void);

    void eval(void);

    bool run_tests(std::string, int);

    bool done(void);

    virtual void set_input();

    // virtual void set_register_addresses(int, int, int);
};


#endif //TESTBENCH_HPP