from sys import argv
from collections import namedtuple

try:
    script, instr_arg = argv
except ValueError:
    instr_arg = None

# print(bin(instr))
Op = namedtuple('Op', ['LB', 'SB', 'RTYPE', 'BEQ', 'J', 'ADDI'])
Funct = namedtuple('Funct', ['ADD', 'SUB', 'AND', 'OR', 'SLT', 'NON'])


instr_list = ['0x80020011',
              '0x80070010',
              '0x80e30045',
              '0x00e22025',
              '0x00642824',
              '0x00a42820',
              '0x10a70008',
              '0x0064302a',
              '0x10c00001',
              '0x80050000',
              '0x00e2302a',
              '0x00c53820',
              '0x00e23822',
              '0x0800000f',
              '0x80070000',
              '0xa0470047',
              '0x00000003',
              '0x00000005',
              '0x0000000c']


def get_funct(instr):
    funct = int(instr[-6:], 2)
    for code in functcode._fields:
        if funct == getattr(functcode, code):
            return code
    return str(funct)


opcode = Op(0b100000, 0b101000, 0b000000, 0b000100, 0b000010, 0b001000)
functcode = Funct(0b100000, 0b100010, 0b100100, 0b100101, 0b101010, 0b000000)


def instr_decode(instr):
    instr.replace('0x', '')
    scale = 16
    num_of_bits = 32
    instr = bin(int(instr, scale))[2:].zfill(num_of_bits)
    assem = ''
    op = instr[0:6]
    ra = instr[6:11]
    rb = instr[11:16]
    rd = instr[16:21]
    imm = instr[-16:]
    dest = instr[-26:]

    if int(op, 2) == opcode.LB:
        # print('OP'.ljust(len(op) + 1, ' '), 'RA'.ljust(len(ra) + 1, ' '),
        #       'RB'.ljust(len(rb) + 1, ' '), 'Imm'.ljust(len(imm) + 1, ' '))
        # print(op, '', ra, '', rb, '', imm)
        assem += 'LB'.ljust(len(op) + 2, ' ')
        assem += hex(int(ra, 2)).ljust(len(ra) + 2, ' ')
        assem += hex(int(rb, 2)).ljust(len(rb) + 2, ' ')
        assem += hex(int(imm, 2)).ljust(len(imm) + 2, ' ')
    elif int(op, 2) == opcode.SB:
        # print(op, '', ra, '', rb, '', imm)
        assem += 'SB '.ljust(len(op) + 2, ' ')
        assem += hex(int(ra, 2)).ljust(len(ra) + 2, ' ')
        assem += hex(int(rb, 2)).ljust(len(rb) + 2, ' ')
        assem += hex(int(imm, 2)).ljust(len(imm) + 2, ' ')
    elif int(op, 2) == opcode.RTYPE:
        # print('OP'.ljust(len(op) + 1, ' '), 'RA'.ljust(len(ra) + 1, ' '),
        #       'RB'.ljust(len(rb) + 1, ' '), 'RD'.ljust(len(rd) + 1, ' '),
        #       '       FUNCT'.ljust(len(op) + 1, ' '))
        # print(op, '', ra, '', rb, '', rb, '', '00000', '', instr[-6:])
        assem += 'RTYPE'.ljust(len(op) + 2, ' ')
        assem += hex(int(ra, 2)).ljust(len(ra) + 2, ' ')
        assem += hex(int(rb, 2)).ljust(len(rb) + 2, ' ')
        assem += hex(int(rd, 2)).ljust(len(rd) + 2, ' ')
        assem += "       "
        assem += get_funct(instr)

    elif int(op, 2) == opcode.BEQ:
        assem += 'BEQ '.ljust(len(op) + 2, ' ')
        assem += hex(int(ra, 2)).ljust(len(ra) + 2, ' ')
        assem += hex(int(rb, 2)).ljust(len(rb) + 2, ' ')
        assem += hex(int(imm, 2)).ljust(len(imm) + 2, ' ')
    elif int(op, 2) == opcode.J:
        assem += 'J '.ljust(len(op) + 2, ' ')
        assem += hex(int(dest, 2))

    print(assem)


if(instr_arg):
    instr_decode(instr_arg)

else:
    for instr in instr_list:
        # if(instr):
        #     # print(instr)
        # else:
        #     print("None")
        instr_decode(instr)
