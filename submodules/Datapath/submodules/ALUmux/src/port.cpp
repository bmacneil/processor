#include "../include/port.hpp"
#include <sstream>
std::stringstream oss;

void OUTPUT_PORT::reset() {
  o_AluA.reset();
  o_AluB.reset();
}

void OUTPUT_PORT::state() {
  std::cout << "o_AluA         " << o_AluA << std::endl;
  std::cout << "o_AluB         " << o_AluB << std::endl;
}

bool OUTPUT_PORT::o_AluA_test(std::string & msg) {
  bool pass = true;

  if (!bitTest(o_AluA, m_core->o_AluA, msg)) {
    oss << "\n    o_AluA_test FAILED: Expected: " << o_AluA.
      to_string() << " Output: " << int (m_core->o_AluA);
    msg = oss.str();
    pass = false;
  }
  return pass;
}
bool OUTPUT_PORT::o_AluB_test(std::string & msg) {
  bool pass = true;

  if (!bitTest(o_AluB, m_core->o_AluB, msg)) {
    oss << "\n    o_AluB_test FAILED: Expected: " << o_AluB.
      to_string() << " Output: " << int (m_core->o_AluB);
    msg = oss.str();
    pass = false;
  }
  return pass;
}

bool OUTPUT_PORT::run_all_tests(std::string & msg) {
  bool pass = true;

  if (!o_AluA_test(msg))
    pass = false;
  if (!o_AluB_test(msg))
    pass = false;
  return pass;
}

template < size_t N >
  bool OUTPUT_PORT::bitTest(bitset < N > testBits, int moduleOutput,
                            std::string & msg) {
  bool pass = true;

  bitset < N > moduleBits;
  moduleBits = bitset < N > (moduleOutput);

  for (int i = 0; i < N; ++i) {
    if (testBits.test(i) != moduleBits.test(i)) {
      oss << "\n    ERROR: Bit " << i << " EXPECTED: " << testBits.test(i);
      pass = false;
    }
  }
  return pass;
}
