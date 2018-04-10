import re
from collections import namedtuple
import os


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


parameterPattern = re.compile(r"\#\s*\(\s*(parameter).*\s*\)")
inPattern = re.compile(r"\W*((input)\s*logic)\s*", re.IGNORECASE)
outPattern = re.compile(r"\W*((output)\s*logic)\s*", re.IGNORECASE)

def findParameters(string, para):
    for k, v in para.items():
        string = re.sub(k, str(v), string)
    return string


def getSize(string):
    sizePattern = r"(.*\[)|(\].*\s)$"
    sizes = []
    if re.search(sizePattern, string):
        sizes = re.split(':', re.sub(sizePattern, '', string))
        try:
            sizes = [int(s) for s in sizes]
        except ValueError:
            sizes = [eval(s) for s in sizes]
    return sizes


def trimPorts(pattern, ports, pDir, parameter):
    port = Ports()
    for p in ports:
        new_p = findParameters(p, parameter)
        size = getSize(new_p)
        # size = re.findall(r'\d+', new_p)
        # size = [int(s) for s in size]
        name = re.sub('[0-9,)-:\[\];\s]', '', re.sub(pattern, '', new_p))

        port.append(Port(name, size, pDir))
    return port


def trimParameter(string):
    startPattern = re.compile(r".*\#\((parameter)|(\).*)$")
    string = re.search(parameterPattern, string).string
    string = re.sub(startPattern, '', re.sub(r"\s*", '', string))
    parameters = re.split(r",", string)
    return {re.split(r"=", p)[0]: int(re.split(r"=", p)[1]) for p in parameters}


# for port in inPorts:
#     print(port.name, ' : ', port.size)
# for port in outPorts:
#     print(port.name, ' : ', port.size)


def get_ports(moduleFile):
    inPorts = []
    outPorts = []
    # verilogFile = 'Datapath.sv'
    with open(moduleFile, 'r') as file:
        for line in file.readlines():
            if re.search(parameterPattern, line):
                para_dict = trimParameter(line)
            if re.match(inPattern, line):
                inPorts.append(line)
            elif re.match(outPattern, line):
                outPorts.append(line)

    try:
        repr(para_dict)
    except NameError:
        para_dict = {"EMPTY": 1}
    inPorts = trimPorts(inPattern, inPorts, 'in', para_dict)
    outPorts = trimPorts(outPattern, outPorts, 'out', para_dict)

    # for port in inPorts.names:
    #     print(port)
    # for port in outPorts.names:
    #     print(port)
    return inPorts, outPorts


# First session info
# Com[pleted: formatted single bit port for C++, output bit length of in and out ports
# Write a in and out port in C++, test for ease of use

# totalBits = 0
# for s in inPorts.sizes:
#     totalBits += 1
#     if s != []:
#         totalBits += max(s[0], s[1])
# print('In Bits: ', totalBits)

# totalBits = 0
# for s in outPorts.sizes:
#     totalBits += 1
#     if s != []:
#         totalBits += max(s[0], s[1])

# print('In Bits: ', totalBits)

port_template = '\t.{name}' + '( CONNECT_IN_TOPLEVEL ),  // Size {size}'

root, dirs, files = os.walk("submodules").__next__()
for d in dirs:
    moduleFile = '{0}/{1}/{1}.sv'.format(root, d)
    print('// ******************************')
    print('`include "' + moduleFile + '"')
    inPorts, outPorts = get_ports(moduleFile)
    print(d + 'Instance_Name ' + '(')
    for port in inPorts:
        print(port_template.format(name=port.name.ljust(15), size=port.size))
    for port in outPorts:
        print(port_template.format(name=port.name.ljust(15), size=port.size))

    print(');\n')
