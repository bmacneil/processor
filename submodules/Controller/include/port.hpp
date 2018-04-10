#ifndef PORTS_H
#define PORTS_H

#include "VController.h"
#include "verilated.h"
#include <verilated_vcd_c.h>
#include <iostream>
#include <string>
#include <bitset>

  struct OUTPUT_PORT {
    VController *m_core;
      bitset < 1 > o_alusrca;   // MSBF
      bitset < 1 > o_iord;      // MSBF
      bitset < 1 > o_memread;   // MSBF
      bitset < 1 > o_memtoreg;  // MSBF
      bitset < 1 > o_memwrite;  // MSBF
      bitset < 1 > o_pcen;      // MSBF
      bitset < 1 > o_regdst;    // MSBF
      bitset < 1 > o_regwrite;  // MSBF
      bitset < 2 > o_alusrcb;   // MSBF
      bitset < 2 > o_pcsrc;     // MSBF
      bitset < 3 > o_alucontrol; // MSBF

    void reset();

    void state();

    void run_all_tests();

    void o_alusrca_test();

    void o_iord_test();

    void o_memread_test();

    void o_memtoreg_test();

    void o_memwrite_test();

    void o_pcen_test();

    void o_regdst_test();

    void o_regwrite_test();

    void o_alusrcb_test();

    void o_pcsrc_test();

    void o_alucontrol_test();

      template < size_t N > bool bitTest(bitset < N > testBits,
                                         int moduleOutput);
  };
#endif //PORTS_H
