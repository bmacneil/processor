#include "../include/port.hpp"

void OUTPUT_PORT::reset() {
  o_alusrca.reset();
  o_iord.reset();
  o_memread.reset();
  o_memtoreg.reset();
  o_memwrite.reset();
  o_pcen.reset();
  o_regdst.reset();
  o_regwrite.reset();
  o_alusrcb.reset();
  o_pcsrc.reset();
  o_alucontrol.reset();
}

void OUTPUT_PORT::state() {
  std::cout << "o_alusrca      " << o_alusrca << std::endl;
  std::cout << "o_iord         " << o_iord << std::endl;
  std::cout << "o_memread      " << o_memread << std::endl;
  std::cout << "o_memtoreg     " << o_memtoreg << std::endl;
  std::cout << "o_memwrite     " << o_memwrite << std::endl;
  std::cout << "o_pcen         " << o_pcen << std::endl;
  std::cout << "o_regdst       " << o_regdst << std::endl;
  std::cout << "o_regwrite     " << o_regwrite << std::endl;
  std::cout << "o_alusrcb      " << o_alusrcb << std::endl;
  std::cout << "o_pcsrc        " << o_pcsrc << std::endl;
  std::cout << "o_alucontrol   " << o_alucontrol << std::endl;
}

void OUTPUT_PORT::o_alusrca_test() {
  if (!bitTest(o_alusrca, m_core->o_alusrca))
    std::cout << "o_alusrca_test FAILED" << std::endl;
}
void OUTPUT_PORT::o_iord_test() {
  if (!bitTest(o_iord, m_core->o_iord))
    std::cout << "o_iord_test FAILED" << std::endl;
}
void OUTPUT_PORT::o_memread_test() {
  if (!bitTest(o_memread, m_core->o_memread))
    std::cout << "o_memread_test FAILED" << std::endl;
}
void OUTPUT_PORT::o_memtoreg_test() {
  if (!bitTest(o_memtoreg, m_core->o_memtoreg))
    std::cout << "o_memtoreg_test FAILED" << std::endl;
}
void OUTPUT_PORT::o_memwrite_test() {
  if (!bitTest(o_memwrite, m_core->o_memwrite))
    std::cout << "o_memwrite_test FAILED" << std::endl;
}
void OUTPUT_PORT::o_pcen_test() {
  if (!bitTest(o_pcen, m_core->o_pcen))
    std::cout << "o_pcen_test FAILED" << std::endl;
}
void OUTPUT_PORT::o_regdst_test() {
  if (!bitTest(o_regdst, m_core->o_regdst))
    std::cout << "o_regdst_test FAILED" << std::endl;
}
void OUTPUT_PORT::o_regwrite_test() {
  if (!bitTest(o_regwrite, m_core->o_regwrite))
    std::cout << "o_regwrite_test FAILED" << std::endl;
}
void OUTPUT_PORT::o_alusrcb_test() {
  if (!bitTest(o_alusrcb, m_core->o_alusrcb))
    std::cout << "o_alusrcb_test FAILED" << std::endl;
}
void OUTPUT_PORT::o_pcsrc_test() {
  if (!bitTest(o_pcsrc, m_core->o_pcsrc))
    std::cout << "o_pcsrc_test FAILED" << std::endl;
}
void OUTPUT_PORT::o_alucontrol_test() {
  if (!bitTest(o_alucontrol, m_core->o_alucontrol))
    std::cout << "o_alucontrol_test FAILED" << std::endl;
}

void OUTPUT_PORT::run_all_tests() {
  o_alusrca_test();
  o_iord_test();
  o_memread_test();
  o_memtoreg_test();
  o_memwrite_test();
  o_pcen_test();
  o_regdst_test();
  o_regwrite_test();
  o_alusrcb_test();
  o_pcsrc_test();
  o_alucontrol_test();
}

template < size_t N >
  bool OUTPUT_PORT::bitTest(bitset < N > testBits, int moduleOutput) {
  bool pass = true;

  bitset < N > moduleBits;
  moduleBits = bitset < N > (moduleOutput);

  for (int i = 0; i < N; ++i) {
    if (testBits.test(i) != moduleBits.test(i)) {
      std::cout << "        ERROR: Bit " << i <<
        " EXPECTED: " << testBits.test(i) << std::endl;
      pass = false;
    }
  }
  return pass;
}
