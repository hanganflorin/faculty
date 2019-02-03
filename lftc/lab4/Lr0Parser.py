class Lr0Parser:

    def __init__(self, grammar):
        self.__grammar = grammar
        self.__workingStack = []
        self.__inputStack = []
        self.__output = []

    def closure(self, productions):

        if productions == []:
            return None
        C = productions
        finished = False

        while not finished:
            finished = True
            for dottedProd in C:
                dotIndex = dottedProd[1].index('.')
                alpha = dottedProd[1][:dotIndex]
                Bbeta = dottedProd[1][dotIndex + 1:]

                if len(Bbeta) == 0:
                    continue

                B = Bbeta[0]
                if self.__grammar.isTerminal(B):
                    continue

                for prod in self.__grammar.getProductionsFor(B):
                    dottedProd = (prod[0], ['.'] + prod[1])
                    if dottedProd not in C:
                        C += [dottedProd]
                        finished = False
        return C

    def goTo(self, state, symbol):
        C = []

        for dottedProd in state:
            dotIndex = dottedProd[1].index('.')
            alpha = dottedProd[1][:dotIndex]
            Xbeta = dottedProd[1][dotIndex + 1:]

            if len(Xbeta) == 0:
                continue

            X, beta = Xbeta[0], Xbeta[1:]

            if X == symbol:
                resultProd = (dottedProd[0], alpha + [X] + ['.'] + beta)
                C = C + [resultProd]

        return self.closure(C)

    def getCannonicalCollection(self):
        C = [self.closure([('S1', ['.', self.__grammar.S])])]

        finished = False

        while not finished:
            finished = True

            for state in C:
                for symbol in self.__grammar.N + self.__grammar.E:
                    nextState = self.goTo(state, symbol)
                    if nextState is not None and nextState not in C:
                        C = C + [nextState]
                        finished = False

        return C

    def getTable(self):
        states = self.getCannonicalCollection()
        table = [{} for _ in range(len(states))]

        for index, state in enumerate(states):
            meetsFirstRule = 0
            meetsSecondRule = 0
            meetsThirdRule = 0

            for prod in state:
                dotIndex = prod[1].index('.')
                alpha = prod[1][:dotIndex]
                beta = prod[1][dotIndex + 1:]
                if len(beta) != 0:
                    meetsFirstRule += 1
                else:
                    if prod[0] != 'S1':
                        meetsSecondRule += 1
                        productionIndex = self.__grammar.P.index((prod[0], alpha))
                    elif alpha == [self.__grammar.S]:
                        meetsThirdRule += 1

            if meetsFirstRule == len(state):
                table[index]['action'] = 'shift'

            elif meetsSecondRule == len(state):
                table[index]['action'] = 'reduce ' + str(productionIndex)

            elif meetsThirdRule == len(state):
                table[index]['action'] = 'acc'

            else:
                raise (Exception('No action detected for state ' + str(index) + ' ' + str(state)))

            for symbol in self.__grammar.N + self.__grammar.E:
                nextState = self.goTo(state, symbol)
                if nextState in states:
                    table[index][symbol] = states.index(nextState)

        return table

    def parse(self, inputSequence):
        table = self.getTable()

        self.__workingStack = ['0']
        self.__inputStack = [symbol for symbol in inputSequence]
        self.__output = []

        while len(self.__workingStack) != 0:
            state = int(self.__workingStack[-1])
            if len(self.__inputStack) > 0:
                symbol = self.__inputStack.pop(0)
            else:
                symbol = None

            if table[state]['action'] == 'shift':
                if symbol not in table[state]:
                    print('workstack', self.__workingStack)
                    print('inputstack', self.__inputStack)
                    print('state', state)
                    print('symbol', symbol)

                    raise (Exception('Cannot parse shift'))
                self.__workingStack.append(symbol)
                self.__workingStack.append(table[state][symbol])

            elif table[state]['action'] == 'acc':
                if len(self.__inputStack) != 0:
                    raise (Exception('Cannot Parse acc'))

                self.__workingStack.clear()

            else:
                reducedState = int(table[state]['action'].split(' ')[1])
                reducedProduction = self.__grammar.P[reducedState]

                toRemoveFromWorkingStack = [symbol for symbol in reducedProduction[1]]

                while len(toRemoveFromWorkingStack) > 0 and len(self.__workingStack) > 0:
                    if self.__workingStack[-1] == toRemoveFromWorkingStack[-1]:
                        toRemoveFromWorkingStack.pop()
                    self.__workingStack.pop()

                if len(toRemoveFromWorkingStack) != 0:
                    raise (Exception('Cannot Parse reduce'))

                self.__inputStack.insert(0, reducedProduction[0])
                self.__output.insert(0, str(reducedState))

        return self.__output