class Grammar:
    @staticmethod
    def parseLine(line):
        equalPos = line.index('=')
        rhs = line[equalPos + 1:].strip('\n').strip(' ')[1:-1]
        return [symbol.strip() for symbol in rhs.split(',')]

    @staticmethod
    def fromFile(fileName):
        with open(fileName) as file:
            N = Grammar.parseLine(file.readline())
            E = Grammar.parseLine(file.readline())
            S = file.readline().split('=')[1].strip()
            P = Grammar.parseRules([line.strip('\n').strip(' ').strip(',') for line in file][1:-1])

            return Grammar(N, E, P, S)

    @staticmethod
    def parseRules(rules):
        result = []

        for rule in rules:
            lhs, rhs = rule.split('->')
            lhs = lhs.strip()
            rhs = [value.strip() for value in rhs.split('|')]

            for value in rhs:
                result.append((lhs, value.split()))

        return result

    def __init__(self, N, E, P, S):
        self.N = N
        self.E = E
        self.P = P
        self.S = S

    def isNonTerminal(self, value):
        return value in self.N

    def isTerminal(self, value):
        return value in self.E

    def isRegular(self):
        usedInRhs = dict()
        notAllowedInRhs = list()

        for rule in self.P:
            lhs, rhs = rule
            hasTerminal = False
            hasNonTerminal = False
            for char in rhs:
                if self.isNonTerminal(char):
                    usedInRhs[char] = True
                    hasNonTerminal = True
                elif self.isTerminal(char):
                    if hasNonTerminal:
                        return False
                    hasTerminal = True
                if char == 'E':
                    notAllowedInRhs.append(lhs)

            if hasNonTerminal and not hasTerminal:
                return False

        for char in notAllowedInRhs:
            if char in usedInRhs:
                return False

        return True

    def getProductionsFor(self, nonTerminal):
        if not self.isNonTerminal(nonTerminal):
            raise Exception('Can only show productions for non-terminals')

        return [prod for prod in self.P if prod[0] == nonTerminal]

    def showProductionsFor(self, nonTerminal):
        productions = self.getProductionsFor(nonTerminal)

        print(', '.join([' -> '.join(prod) for prod in productions]))

    def __str__(self):
        return 'N = { ' + ', '.join(self.N) + ' }\n' \
               + 'E = { ' + ', '.join(self.E) + ' }\n' \
               + 'P = { ' + ', '.join([' -> '.join([prod[0], ' '.join(prod[1])]) for prod in self.P]) + ' }\n' \
               + 'S = ' + str(self.S) + '\n'