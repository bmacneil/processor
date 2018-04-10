#ifndef PORTS_H
#define PORTS_H

#include "VALUDec.h"
#include "verilated.h"
#include <verilated_vcd_c.h>
#include <iostream>
#include <string>
#include <bitset>

  struct OUTPUT_PORT {
    VALUDec *m_core;
      bitset < 3 > o_alucontrol; // MSBF

    void reset();

    void state();

    void run_all_tests();

    void o_alucontrol_test();

      template < size_t N > bool bitTest(bitset < N > testBits,
                                         int moduleOutput);
  };
#endif //PORTS_H
