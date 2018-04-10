#ifndef PORTS_H
#define PORTS_H

#include "VDatapath.h"
#include "verilated.h"
#include <verilated_vcd_c.h>
#include <iostream>
#include <string>
#include <bitset>

  struct OUTPUT_PORT {
    VDatapath *m_core;
      std::string version = "v1.0";
      bitset < 1 > o_zero;      // MSBF
      bitset < 6 > o_funct;     // MSBF
      bitset < 6 > o_op;        // MSBF
      bitset < 32 > o_Address;  // MSBF

    void reset();

    void state();

    bool run_all_tests(std::string & msg);

    bool o_zero_test(std::string & msg);

    bool o_funct_test(std::string & msg);

    bool o_op_test(std::string & msg);

    bool o_Address_test(std::string & msg);

      template < size_t N > bool bitTest(bitset < N > testBits,
                                         int moduleOutput, std::string & msg);
  };
#endif //PORTS_H
