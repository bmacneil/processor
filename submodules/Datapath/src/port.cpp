#include "../include/port.hpp"
#include <sstream>
std::stringstream oss;

void OUTPUT_PORT::reset() {
  o_zero.reset();
  o_funct.reset();
  o_op.reset();
  o_Address.reset();
}

void OUTPUT_PORT::state() {
  std::cout << "o_zero         " << o_zero << std::endl;
  std::cout << "o_funct        " << o_funct << std::endl;
  std::cout << "o_op           " << o_op << std::endl;
  std::cout << "o_Address      " << o_Address << std::endl;
}


bool OUTPUT_PORT::o_zero_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_zero, m_core->o_zero, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_zero_test FAILED: Expected: " << hex << o_zero.
      to_ulong() << " Output: " << hex << int (m_core->o_zero);
    pass = false;
  }
  msg += oss.str() + bit_error_msg;
  return pass;
}

bool OUTPUT_PORT::o_funct_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_funct, m_core->o_funct, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_funct_test FAILED: Expected: " << hex << o_funct.
      to_ulong() << " Output: " << hex << int (m_core->o_funct);
    pass = false;
  }
  msg += oss.str() + bit_error_msg;
  return pass;
}

bool OUTPUT_PORT::o_op_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_op, m_core->o_op, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_op_test FAILED: Expected: " << hex << o_op.
      to_ulong() << " Output: " << hex << int (m_core->o_op);
    pass = false;
  }
  msg += oss.str() + bit_error_msg;
  return pass;
}

bool OUTPUT_PORT::o_Address_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_Address, m_core->o_Address, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_Address_test FAILED: Expected: " << hex << o_Address.
      to_ulong() << " Output: " << hex << int (m_core->o_Address);
    pass = false;
  }
  msg += oss.str() + bit_error_msg;
  return pass;
}

bool OUTPUT_PORT::run_all_tests(std::string & msg) {
  bool pass = true;

  if (!o_zero_test(msg))
    pass = false;
  if (!o_funct_test(msg))
    pass = false;
  if (!o_op_test(msg))
    pass = false;
  if (!o_Address_test(msg))
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
