#include "../include/port.hpp"
#include <sstream>
std::stringstream oss;

void OUTPUT_PORT::reset() {
  o_ALUout.reset();
  o_Address.reset();
  o_PC.reset();
}

void OUTPUT_PORT::state() {
  std::cout << "o_ALUout       " << o_ALUout << std::endl;
  std::cout << "o_Address      " << o_Address << std::endl;
  std::cout << "o_PC           " << o_PC << std::endl;
}


bool OUTPUT_PORT::o_ALUout_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_ALUout, m_core->o_ALUout, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_ALUout_test FAILED: Expected: " << hex << o_ALUout.
      to_ulong() << " Output: " << hex << int (m_core->o_ALUout);
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

bool OUTPUT_PORT::o_PC_test(std::string & msg) {
  bool pass = true;

  std::string bit_error_msg = "";

  if (!bitTest(o_PC, m_core->o_PC, bit_error_msg)) {
    oss.str("");
    oss << "\n\n    o_PC_test FAILED: Expected: " << hex << o_PC.
      to_ulong() << " Output: " << hex << int (m_core->o_PC);
    pass = false;
  }
  msg += oss.str() + bit_error_msg;
  return pass;
}

bool OUTPUT_PORT::run_all_tests(std::string & msg) {
  bool pass = true;

  if (!o_ALUout_test(msg))
    pass = false;
  if (!o_Address_test(msg))
    pass = false;
  if (!o_PC_test(msg))
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
