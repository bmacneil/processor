#include "../include/Testbench.hpp"

Testbench::Testbench(void) {
    m_core = new VALUmux;
    testPort = new OUTPUT_PORT;
    testPort->m_core = m_core;
    m_tickcount = 0l;
    // According to the Verilator spec, you *must* call
    // traceEverOn before calling any of the tracing functions
    // within Verilator.
    Verilated::traceEverOn(true);
}


Testbench::~Testbench(void) {
    delete m_core;
    m_core = NULL;

}

// Open/create a trace file
void Testbench::opentrace(const char *vcdname) {
    if (!m_trace) {
        m_trace = new VerilatedVcdC;
        m_core->trace(m_trace, 99);
        m_trace->open(vcdname);
    }
}

void Testbench::close(void) {
    if (m_trace) {
        m_trace->close();
        m_trace = NULL;
    }
}


void Testbench::eval(void) {
    // Increment our own internal time reference
    m_tickcount++;
    trace = true;

    m_core->eval();

    if (m_trace) {
        // This portion, though, is a touch different.
        // After dumping our values as they exist on the
        // negative clock edge ...
        m_trace->dump(10*m_tickcount+5);
        //
        // We'll also need to make sure we flush any I/O to
        // the trace file, so that we can use the assert()
        // function between now and the next tick if we want to.
        m_trace->flush();
    }

}

bool Testbench::run_tests(std::string test_name) {
    bool pass = true;
    if(!testPort->run_all_tests(error_msg)) {
        std::cout << "ALUmux : FAILED :\n" << error_msg << std::endl;
        pass = false;
    }
    else {std::cout << test_name << " : PASSED" << std::endl;}

    testPort->reset();
    return pass;
}


bool Testbench::done(void) { return (Verilated::gotFinish()); }

