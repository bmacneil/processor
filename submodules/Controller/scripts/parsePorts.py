import re
from collections import namedtuple
from bdp import *
from math import ceil
import subprocess as sp


Port = namedtuple('Port', ('name', 'size', 'pDir'))


class Ports(object):
    def __init__(self):
        self.ports = []

    def append(self, port):
        self.ports.append(port)

    def __len__(self):
        return len(self.ports)

    def __iter__(self):
        return self.ports.__iter__()

    @property
    def names(self):
        return [port.name for port in self.ports]

    @property
    def sizes(self):
        return [port.size for port in self.ports]

    @property
    def pDirs(self):
        return [port.pDir for port in self.ports]


inPattern = re.compile(r"\W*((input)\slogic)\s*", re.IGNORECASE)
outPattern = re.compile(r"\W*((output)\slogic)\s*", re.IGNORECASE)


def trimPorts(pattern, ports, pDir):
    port = Ports()
    for p in ports:
        size = re.findall(r'\d+', p)
        size = [int(s) for s in size]
        name = re.sub('[0-9,):\[\];\s]', '', re.sub(pattern, '', p))
        port.append(Port(name, size, pDir))
    return port


def match(pattern, string):
    # print(string)
    if re.match(pattern, string):
        return True
    else:
        return False


inPorts = []
outPorts = []
verilogFile = 'Controller.sv'
with open(verilogFile, 'r') as file:
    for line in file.readlines():
        if match(inPattern, line):
            inPorts.append(line)
        elif match(outPattern, line):
            outPorts.append(line)

inPorts = trimPorts(inPattern, inPorts, 'in')
outPorts = trimPorts(outPattern, outPorts, 'out')

for port in inPorts.names:
    print(port)
for port in outPorts.names:
    print(port)

# First session info
# Com[pleted: formatted single bit port for C++, output bit length of in and out ports
# Write a in and out port in C++, test for ease of use

totalBits = 0
for s in inPorts.sizes:
    totalBits += 1
    if s != []:
        totalBits += max(s[0], s[1])
print('In Bits: ', totalBits)

totalBits = 0
for s in outPorts.sizes:
    totalBits += 1
    if s != []:
        totalBits += max(s[0], s[1])
print('In Bits: ', totalBits)

# for port in inPorts:
#     if port.size == []:
#         print('uint32_t ', port.name, ' : ', 1, '; // ', port.pDir)
#     elif port.size != []:
#         # Need to determine directionality here, max won't always work
#         bits = 1 + max(port.size[0], port.size[1])
#         print('uint32_t ', port.name, ' : ', str(bits), '; //', port.pDir, ' : MSBF')
# for port in outPorts:
#     if port.size == []:
#         print('uint32_t ', port.name, ' : ', 1, '; // ', port.pDir)
#     elif port.size != []:
#         bits = 1 + max(port.size[0], port.size[1])
#         print('uint32_t ', port.name, ' : ', str(bits), '; //', port.pDir, ' : MSBF')

header = '''#ifndef PORTS_H
#define PORTS_H

#include "VController.h"
#include "verilated.h"
#include <verilated_vcd_c.h>
#include <iostream>
#include <string>
#include <bitset>

'''
footer = '''
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
'''
bitset_template = 'bitset<{size}>  {name};  // {bit_direction}\n'
reset_bit_template = '{name}.reset();\n'
print_template = 'std::cout << "{name_string}" << {name} << std::endl;\n'
test_def_template = '''void OUTPUT_PORT::{name}_test() {{
if (!bitTest({name}, m_core->{name}))
std::cout << "{name}_test FAILED" << std::endl;
}}
'''
test_call_template = '{name}_test();\n'

outPorts = sorted(outPorts, key=lambda x: (x.size, x.name))

with open('include/port.hpp', 'w') as file:
    file.write(header)
    file.write('struct OUTPUT_PORT {VController *m_core;\n')
    for port in outPorts:
        try:
            file.write(bitset_template.format(
                size=1 + max(port.size[0], port.size[1]),
                name=port.name, bit_direction='MSBF'))
        except IndexError:
            file.write(bitset_template.format(
                size=1, name=port.name, bit_direction='MSBF'))
    file.write('\nvoid reset();\n')
    file.write('\nvoid state();\n')
    file.write('\nvoid run_all_tests();\n')
    for port in outPorts:
        file.write("\nvoid " + test_call_template.format(name=port.name))
    file.write('\ntemplate < size_t N > bool bitTest (bitset < N > testBits, int moduleOutput);\n')
    file.write('};\n')
    file.write('#endif //PORTS_H\n')

with open('src/port.cpp', 'w') as file:
    file.write('#include "../include/port.hpp"\n')

    file.write('\nvoid OUTPUT_PORT::reset() {\n')
    for port in outPorts:
        file.write(reset_bit_template.format(name=port.name))
    file.write('}\n')
    file.write('\nvoid OUTPUT_PORT::state() {\n')
    for port in outPorts:
        file.write(print_template.format(
            name_string=port.name.ljust(15), name=port.name))
    file.write('}\n')
    file.write('\n')
    for port in outPorts:
        file.write(test_def_template.format(name=port.name))
    file.write('\nvoid OUTPUT_PORT::run_all_tests() {\n')
    for port in outPorts:
        file.write(test_call_template.format(name=port.name))
    file.write('}\n')
    file.write(footer)

cmd = 'indent include/port.hpp -o include/port.hpp'
flags = ' -nip -npsl -br -bls -brf -ip4 -npcs -nce -sbi2 -ts1 -bad -bap -nsob'
sp.call(cmd + flags, shell=True)

cmd = 'indent src/port.cpp -o src/port.cpp'
sp.call(cmd + flags, shell=True)

'''
def gridOn(fig, X, Y):
    # t = block(size=(8, 8))
    for x in range(-X, X):
        line = path((x, -X), (x, X))
        line.line_width = 0.0001
        line.color = 'black!30!white'
        fig << line
    for y in range(-Y, Y):
        line = path((-Y, y), (Y, y))
        line.line_width = 0.0001
        line.color = 'black!30!white'
        fig << line
    # fig << t

# gridOn(fig, 8, 8)
maxPort = max(len(inPorts), len(outPorts))
print(maxPort)
block.nodesep = (3, 3)
block = block(r"Controller", alignment='nw')
height = ceil(maxPort)
width = ceil(block.size[0])
width = len(max(inPorts.names, key=len)) + len(max(outPorts.names, key=len)) // 2
print(width)
block.size = (width, height)
block.p = (-block.size[0] / 2, -block.size[1] / 2)
print('Block P: ', block.n(-block.size[0], -block.size[1]))
print('Block Size: ', block.size)

fig << block

pos = 0.1
for name in inPorts.names:
    pos += 0.06
    fig << path(block.w(pos), poffx(-1.5), style=('', ''))
    fig << text(name.replace('_', r'\_'), style=r'{text=black, font=\fontsize{7}{10}\selectfont}').align(
        fig[-1].pos(0.0), prev().w(0.5, -0.0))
pos = 0.1
for name in outPorts.names:
    pos += 0.06
    fig << path(block.e(pos), poffx(1.5), style=('', ''))
    fig << text(name.replace('_', r'\_'), style=r"{text=black, font=\fontsize{7}{10}\selectfont}").align(
        fig[-1].pos(0.0), prev().e(0.5, 0.0))
'''
