#ifndef PORTS_H
#define PORTS_H

#include "VRegisters.h"
#include "verilated.h"
#include <verilated_vcd_c.h>
#include <iostream>
#include <string>
#include <bitset>

  struct OUTPUT_PORT {
    VRegisters *m_core;
      std::string version = "v1.0";
      bitset < 32 > o_RegA;     // MSBF
      bitset < 32 > o_RegB;     // MSBF

    void reset();

    void state();

    bool run_all_tests(std::string & msg);

    bool o_RegA_test(std::string & msg);

    bool o_RegB_test(std::string & msg);

      template < size_t N > bool bitTest(bitset < N > testBits,
                                         int moduleOutput, std::string & msg);
  };
#endif //PORTS_H
