#ifndef PORTS_H
#define PORTS_H

#include "VALU.h"
#include "verilated.h"
#include <verilated_vcd_c.h>
#include <iostream>
#include <string>
#include <bitset>

  struct OUTPUT_PORT {
    VALU *m_core;
      bitset < 1 > o_zero;      // MSBF
      bitset < 32 > o_result; // MSBF

    void reset();

    void state();

    void run_all_tests();

    void o_zero_test();

    void o_result_test();

      template < size_t N > bool bitTest(bitset < N > testBits,
                                         int moduleOutput);
  };
#endif //PORTS_H
