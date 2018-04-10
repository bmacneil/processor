#include "../include/Testbench.hpp"

Testbench::Testbench(void) {
    m_core = new VALU;
    testPort = new OUTPUT_PORT;
    testPort->m_core = m_core;
    m_tickcount = 0l;
    // m_core->i_reset = 1;
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

void Testbench::runTests(void) {
    testPort->run_all_tests();
    testPort->reset();
}


bool Testbench::done(void) { return (Verilated::gotFinish()); }

