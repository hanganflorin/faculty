from grammer import Grammar
from Lr0Parser import Lr0Parser
from gcc import Scanner


def readPif():
    input = []
    f = open("output/pif.txt", "r")
    for line in f.read().split('\n'):
        if line:
            input.append(line.split(' ')[0])
    return input


# if __name__ == '__main__':
#     g = Grammar.fromFile("files/grammer.txt")
#     g.P = [('S1', ['.', g.S])] + g.P
#     g.N += ['S1']
#     lr0 = Lr0Parser(g)
#
#     print(lr0.parse('abbc'))


if __name__ == '__main__':
    filename = "files/program.cpp"
    s = Scanner(filename)
    s.tokenize()

    g = Grammar.fromFile("files/my_grammer.txt")
    g.P = [('S1', ['.', g.S])] + g.P
    g.N += ['S1']
    lr0 = Lr0Parser(g)

    input = readPif()

    print(lr0.parse(input))


