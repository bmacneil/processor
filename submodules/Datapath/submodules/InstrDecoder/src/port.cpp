#include "../include/port.hpp"
#include <sstream>
std::stringstream oss;

void OUTPUT_PORT::reset() {
  o_RegA_addr.reset();
  o_RegB_addr.reset();
  o_RegD_addr.reset();
  o_funct.reset();
  o_op.reset();
  o_Imm.reset();
}

void OUTPUT_PORT::state() {
  std::cout << "o_RegA_addr    " << o_RegA_addr << std::endl;
  std::cout << "o_RegB_addr    " << o_RegB_addr << std::endl;
  std::cout << "o_RegD_addr    " << o_RegD_addr << std::endl;
  std::cout << "o_funct        " << o_funct << std::endl;
  std::cout << "o_op           " << o_op << std::endl;
  std::cout << "o_Imm          " << o_Imm << std::endl;
}


bool OUTPUT_PORT::o_RegA_addr_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_RegA_addr, m_core->o_RegA_addr, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_RegA_addr_test FAILED: Expected: " << hex <<
      o_RegA_addr.to_ulong() << " Output: " << hex << int (m_core->
                                                           o_RegA_addr);
    pass = false;
  }
  msg += oss.str() + bit_error_msg;
  return pass;
}

bool OUTPUT_PORT::o_RegB_addr_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_RegB_addr, m_core->o_RegB_addr, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_RegB_addr_test FAILED: Expected: " << hex <<
      o_RegB_addr.to_ulong() << " Output: " << hex << int (m_core->
                                                           o_RegB_addr);
    pass = false;
  }
  msg += oss.str() + bit_error_msg;
  return pass;
}

bool OUTPUT_PORT::o_RegD_addr_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_RegD_addr, m_core->o_RegD_addr, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_RegD_addr_test FAILED: Expected: " << hex <<
      o_RegD_addr.to_ulong() << " Output: " << hex << int (m_core->
                                                           o_RegD_addr);
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

bool OUTPUT_PORT::o_Imm_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_Imm, m_core->o_Imm, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_Imm_test FAILED: Expected: " << hex << o_Imm.
      to_ulong() << " Output: " << hex << int (m_core->o_Imm);
    pass = false;
  }
  msg += oss.str() + bit_error_msg;
  return pass;
}

bool OUTPUT_PORT::run_all_tests(std::string & msg) {
  bool pass = true;

  if (!o_RegA_addr_test(msg))
    pass = false;
  if (!o_RegB_addr_test(msg))
    pass = false;
  if (!o_RegD_addr_test(msg))
    pass = false;
  if (!o_funct_test(msg))
    pass = false;
  if (!o_op_test(msg))
    pass = false;
  if (!o_Imm_test(msg))
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
