#include "../include/Testbench.hpp"

Testbench::Testbench(bool trace_state) {
    m_core = new VPCdec;
    testPort = new OUTPUT_PORT;
    testPort->m_core = m_core;
    m_tickcount = 0l;
    trace_on = trace_state;
    // According to the Verilator spec, you *must* call
    // traceEverOn before calling any of the tracing functions
    // within Verilator.
    Verilated::traceEverOn(trace_on);
}


Testbench::~Testbench(void) {
    delete m_core;
    m_core = NULL;

}
void Testbench::reset(void) {
    m_core->i_reset = 1;
    // Make sure any inheritance gets applied
    this->tick();
    m_core->i_reset = 0;
}

// Open/create a trace file
void Testbench::opentrace(const char *vcdname) {
    if ((!m_trace) && trace_on) {
        m_trace = new VerilatedVcdC;
        m_core->trace(m_trace, 99);
        m_trace->open(vcdname);
    }
}

void Testbench::close(void) {
    if ((m_trace) && trace_on) {
        m_trace->close();
        m_trace = NULL;
    }
}

void Testbench::tick(void) {
    // Increment our own internal time reference
    m_tickcount++;

    // Make sure any combinatorial logic depending upon
    // inputs that may have changed before we called tick()
    // has settled before the rising edge of the clock.
    m_core->i_clk = 0;
    m_core->eval();

    //  Dump values to our trace file
    //
    if(trace_on) m_trace->dump(10*m_tickcount-2);

    // Toggle the clock

    // Rising edge
    m_core->i_clk = 1;
    m_core->eval();

    if(trace_on) m_trace->dump(10*m_tickcount);


    // this->print();

    // Falling edge
    m_core->i_clk = 0;
    m_core->eval();

    if ((m_trace) && trace_on) {
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

void Testbench::eval(void) {
    // Increment our own internal time reference
    m_tickcount++;

    m_core->eval();

    if (trace_on) {
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

bool Testbench::run_tests(std::string test_name, int test_num) {
    bool pass = true;
    if(!testPort->run_all_tests(error_msg)) {
        std::cout << test_name << " : "<< test_num << " : FAILED :" << error_msg << std::endl;
        error_msg = "";
        pass = false;
    }
    else {std::cout << test_name << " : "<< test_num << " : PASSED" << std::endl;}

    testPort->reset();
    return pass;
}


bool Testbench::done(void) { return (Verilated::gotFinish()); }

