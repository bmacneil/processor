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


inPattern = re.compile(r"\W*((input)\s*logic)\s*", re.IGNORECASE)
outPattern = re.compile(r"\W*((output)\s*logic)\s*", re.IGNORECASE)


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


def get_ports(moduleFile):
    inPorts = []
    outPorts = []
    # verilogFile = 'Controller.sv'
    with open(moduleFile, 'r') as file:
        for line in file.readlines():
            if match(inPattern, line):
                inPorts.append(line)
            elif match(outPattern, line):
                outPorts.append(line)

    inPorts = trimPorts(inPattern, inPorts, 'in')
    outPorts = trimPorts(outPattern, outPorts, 'out')

    # for port in inPorts.names:
    #     print(port)
    # for port in outPorts.names:
    #     print(port)
    return inPorts, outPorts


port_template = '\t.{name}' + '( CONNECT_IN_TOPLEVEL ),  // Size {size}'

root, dirs, files = os.walk("submodules").__next__()
for d in dirs:
    moduleFile = '{0}/{1}/{1}.sv'.format(root, d)
    print('******************************')
    inPorts, outPorts = get_ports(moduleFile)
    print('Instance_Name ' + d + '(')
    for port in inPorts:
        print(port_template.format(name=port.name.ljust(15), size=port.size))
    for port in outPorts:
        print(port_template.format(name=port.name.ljust(15), size=port.size))

    print(');\n')
