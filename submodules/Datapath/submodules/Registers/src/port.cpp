#include "../include/port.hpp"
#include <sstream>
std::stringstream oss;

void OUTPUT_PORT::reset() {
  o_RegA.reset();
  o_RegB.reset();
}

void OUTPUT_PORT::state() {
  std::cout << "o_RegA         " << o_RegA << std::endl;
  std::cout << "o_RegB         " << o_RegB << std::endl;
}


bool OUTPUT_PORT::o_RegA_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_RegA, m_core->o_RegA, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_RegA_test FAILED: Expected: " << hex << o_RegA.
      to_ulong() << " Output: " << hex << int (m_core->o_RegA);
    pass = false;
  }
  msg += oss.str() + bit_error_msg;
  return pass;
}

bool OUTPUT_PORT::o_RegB_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_RegB, m_core->o_RegB, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_RegB_test FAILED: Expected: " << hex << o_RegB.
      to_ulong() << " Output: " << hex << int (m_core->o_RegB);
    pass = false;
  }
  msg += oss.str() + bit_error_msg;
  return pass;
}

bool OUTPUT_PORT::run_all_tests(std::string & msg) {
  bool pass = true;

  if (!o_RegA_test(msg))
    pass = false;
  if (!o_RegB_test(msg))
    pass = false;
  return pass;
}

template < size_t N >
  bool OUTPUT_PORT::bitTest(bitset < N > testBits, int moduleOutput,
                            std::string & msg) {
  bool pass = true;

  bitset < N > moduleBits;
  moduleBits = bitset < N > (moduleOutput);
  oss.str("");
  for (int i = 0; i < N; ++i) {
    if (testBits.test(i) != moduleBits.test(i)) {
      oss << "\n        ERROR: Bit " << dec << i << " EXPECTED: " << testBits.
        test(i);
      pass = false;
    }
  }
  msg += oss.str();
  return pass;
}
