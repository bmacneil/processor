class CustomPrinter(object):
    def __init__(self, val):
        self.val = val

    def to_string(self):
        res = "{"
        for m in xrange(64):
            res += hex(int(self.val[m]))
            if m != 63:
                res += ", "
        res += " }"
        return res


def lookup_type(val):
    if str(val.type) == 'unsigned char [64]':
        return CustomPrinter(val)
    return None


gdb.pretty_printers.append(lookup_type)
