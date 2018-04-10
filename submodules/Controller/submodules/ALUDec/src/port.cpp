#include "../include/port.hpp"

void OUTPUT_PORT::reset() {
  o_alucontrol.reset();
}

void OUTPUT_PORT::state() {
  std::cout << "o_alucontrol   " << o_alucontrol << std::endl;
}

void OUTPUT_PORT::o_alucontrol_test() {
  if (!bitTest(o_alucontrol, m_core->o_alucontrol))
    std::cout << "o_alucontrol_test FAILED" << std::endl;
}

void OUTPUT_PORT::run_all_tests() {
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
