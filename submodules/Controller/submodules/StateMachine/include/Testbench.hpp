#ifndef TESTBENCH_HPP
#define TESTBENCH_HPP


#include "VStateMachine.h"
#include "verilated.h"
#include <verilated_vcd_c.h>
#include "port.hpp"
#include <iostream>
#include <string>


class Testbench {
public:
    unsigned long   m_tickcount;
    VStateMachine  *m_core;
    OUTPUT_PORT *testPort;
    VerilatedVcdC   *m_trace;
    bool trace;

    Testbench(void);

    ~Testbench(void);

    void reset(void);

    // Open/create a trace file
    void opentrace(const char *vcdname);

    void close(void);

    void tick(void);

    void runTests(void);

    bool done(void);
};


#endif //TESTBENCH_HPP