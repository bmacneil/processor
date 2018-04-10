#include "../include/port.hpp"

void OUTPUT_PORT::reset() {
  o_zero.reset();
  o_result.reset();
}

void OUTPUT_PORT::state() {
  std::cout << "o_zero         " << o_zero << std::endl;
  std::cout << "o_result " << o_result << std::endl;
}

void OUTPUT_PORT::o_zero_test() {
  if (!bitTest(o_zero, m_core->o_zero))
    std::cout << "o_zero_test FAILED" << std::endl;
}
void OUTPUT_PORT::o_result_test() {
  if (!bitTest(o_result, m_core->o_result))
    std::cout << "o_result_test FAILED" << std::endl;
}

void OUTPUT_PORT::run_all_tests() {
  o_zero_test();
  o_result_test();
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
