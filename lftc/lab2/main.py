from grammer import Grammar
from finite_automata import FiniteAutomata

# if __name__ == "__main__":
#     grammar = Grammar.fromFile('files/rg.txt')
#     print(grammar)
#
#     if grammar.isRegular():
#         finiteAutomata = FiniteAutomata.fromRegularGrammar(grammar)
#         print(finiteAutomata)


if __name__ == "__main__":
    finiteAutomata = FiniteAutomata.fromFile('files/fa.txt')
    print(finiteAutomata)

    grammar = Grammar.fromFiniteAutomata(finiteAutomata)
    print(grammar)


# if __name__ == "__main__":
#     grammar = Grammar.fromConsole()
#     print(grammar)

# if __name__ == "__main__":
#     fa = FiniteAutomata.fromConsole()
#     print(fa)
