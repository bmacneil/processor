#include "../include/port.hpp"
#include <sstream>
std::stringstream oss;

void OUTPUT_PORT::reset() {
  o_memwrite.reset();
  o_Address.reset();
  o_WriteData.reset();
}

void OUTPUT_PORT::state() {
  std::cout << "o_memwrite     " << o_memwrite << std::endl;
  std::cout << "o_Address      " << o_Address << std::endl;
  std::cout << "o_WriteData    " << o_WriteData << std::endl;
}


bool OUTPUT_PORT::o_memwrite_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_memwrite, m_core->o_memwrite, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_memwrite_test FAILED: Expected: " << hex << o_memwrite.
      to_ulong() << " Output: " << hex << int (m_core->o_memwrite);
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

bool OUTPUT_PORT::o_WriteData_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_WriteData, m_core->o_WriteData, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_WriteData_test FAILED: Expected: " << hex <<
      o_WriteData.to_ulong() << " Output: " << hex << int (m_core->
                                                           o_WriteData);
    pass = false;
  }
  msg += oss.str() + bit_error_msg;
  return pass;
}

bool OUTPUT_PORT::run_all_tests(std::string & msg) {
  bool pass = true;

  if (!o_memwrite_test(msg))
    pass = false;
  if (!o_Address_test(msg))
    pass = false;
  if (!o_WriteData_test(msg))
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
