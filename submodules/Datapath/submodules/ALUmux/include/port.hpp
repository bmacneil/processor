#ifndef PORTS_H
#define PORTS_H

#include "VALUmux.h"
#include "verilated.h"
#include <verilated_vcd_c.h>
#include <iostream>
#include <string>
#include <bitset>

  struct OUTPUT_PORT {
    VALUmux *m_core;
      bitset < 32 > o_AluA;     // MSBF
      bitset < 32 > o_AluB;     // MSBF

    void reset();

    void state();

    bool run_all_tests(std::string & msg);

    bool o_AluA_test(std::string & msg);

    bool o_AluB_test(std::string & msg);

      template < size_t N > bool bitTest(bitset < N > testBits,
                                         int moduleOutput, std::string & msg);
  };
#endif //PORTS_H
