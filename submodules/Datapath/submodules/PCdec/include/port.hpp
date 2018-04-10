#ifndef PORTS_H
#define PORTS_H

#include "VPCdec.h"
#include "verilated.h"
#include <verilated_vcd_c.h>
#include <iostream>
#include <string>
#include <bitset>

  struct OUTPUT_PORT {
    VPCdec *m_core;
      std::string version = "v1.0";
      bitset < 32 > o_ALUout;   // MSBF
      bitset < 32 > o_Address;  // MSBF
      bitset < 32 > o_PC;       // MSBF

    void reset();

    void state();

    bool run_all_tests(std::string & msg);

    bool o_ALUout_test(std::string & msg);

    bool o_Address_test(std::string & msg);

    bool o_PC_test(std::string & msg);

      template < size_t N > bool bitTest(bitset < N > testBits,
                                         int moduleOutput, std::string & msg);
  };
#endif //PORTS_H
