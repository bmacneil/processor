#ifndef PORTS_H
#define PORTS_H

#include "VInstrDecoder.h"
#include "verilated.h"
#include <verilated_vcd_c.h>
#include <iostream>
#include <string>
#include <bitset>

  struct OUTPUT_PORT {
    VInstrDecoder *m_core;
      std::string version = "v1.0";
      bitset < 5 > o_RegA_addr; // MSBF
      bitset < 5 > o_RegB_addr; // MSBF
      bitset < 5 > o_RegD_addr; // MSBF
      bitset < 6 > o_funct;     // MSBF
      bitset < 6 > o_op;        // MSBF
      bitset < 8 > o_Imm;       // MSBF

    void reset();

    void state();

    bool run_all_tests(std::string & msg);

    bool o_RegA_addr_test(std::string & msg);

    bool o_RegB_addr_test(std::string & msg);

    bool o_RegD_addr_test(std::string & msg);

    bool o_funct_test(std::string & msg);

    bool o_op_test(std::string & msg);

    bool o_Imm_test(std::string & msg);

      template < size_t N > bool bitTest(bitset < N > testBits,
                                         int moduleOutput, std::string & msg);
  };
#endif //PORTS_H
