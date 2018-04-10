#ifndef PORTS_H
#define PORTS_H

#include "VProcessor.h"
#include "verilated.h"
#include <verilated_vcd_c.h>
#include <iostream>
#include <string>
#include <bitset>

  struct OUTPUT_PORT {
    VProcessor *m_core;
      std::string version = "v1.0";
      bitset < 1 > o_memwrite;  // MSBF
      bitset < 32 > o_Address;  // MSBF
      bitset < 32 > o_WriteData; // MSBF

    void reset();

    void state();

    bool run_all_tests(std::string & msg);

    bool o_memwrite_test(std::string & msg);

    bool o_Address_test(std::string & msg);

    bool o_WriteData_test(std::string & msg);

      template < size_t N > bool bitTest(bitset < N > testBits,
                                         int moduleOutput, std::string & msg);
  };
#endif //PORTS_H
