from os import sys, path
from random import randint
from sortedcontainers import SortedDict


class Scanner:
    def __init__(self, fileName):
        #.cpp filename
        self.fileName = fileName
        # file to store the program internal form
        self.pifFileName = "output/pif.txt"
        # clear file if already exist
        open(self.pifFileName, 'w').close()
        # file to store the identifiers table
        self.outputIdentifiersTable = "output/id_table.txt"
        # file to store the constants table
        self.outputConstantsTable = "output/const_table.txt"
        # dictionary for all the program symbols (if, for, while, else, int, float, etc)
        self.codificationTable = {}
        # dictionary for storing the identifiers, as a pair identifier -> integer id
        self.identifiersTable = SortedDict()
        # dictionary for storing the identifiers, as a pair constant -> integer id
        self.constantsTable = SortedDict()
        # load all the toy language symbols
        self.populateCodificationTable()
        self.inputText = self.getInputText()
        self.currentIndex = 0

    # method loads symbol table in memory from the disc
    def populateCodificationTable(self):
        try:
            # open the file
            f = open("files/codifications.dat")
            # iterate through its lines
            for line in f.readlines():
                # get the symbol and the symbol id
                (symbol, sid) = line.split()
                # add to the symbols table
                self.codificationTable[symbol] = sid
        except IOError:
            # In case there is no such file, fail fast!
            print("ERROR: Symbols file not found!")
            sys.exit()

    #get all text from filename
    def getInputText(self):
        try:
            # open the file for reading
            f = open(self.fileName, "r")
            return f.read() + "\n"
        # if file was not found, print error and fail fast
        except IOError:
            print("ERROR: Source file not found!")

    #get next character from input.txt. Throws error if no more characters
    def getNextCharacter(self):
        if self.currentIndex >= len(self.inputText):
            raise EOFError
        c = self.inputText[self.currentIndex]
        self.currentIndex += 1
        return c

    def pickNextCharacter(self):
        if self.currentIndex >= len(self.inputText):
            return ''
        return self.inputText[self.currentIndex]

    # method append buff to the file outputFileName
    def appendToPifFile(self, buff, token = ''):
        #for debugging
        #buff = buff.rstrip('\n') + " " + token + "\n"
        # open file
        with open(self.pifFileName, "a") as f:
            # write the string buff as a new line
            f.write(buff)

    # method write the identifier and constant tables
    def writeTables(self):
        # open file for identifiers table
        with open(self.outputIdentifiersTable, "w") as f:
            # iterate through the identifiers table
            for (key, val) in self.identifiersTable.items():
                # write the pair on a new line
                f.write("%s %s\n" % (key, val))
        # open file for constant table
        with open(self.outputConstantsTable, "w") as f:
            # iterate through the constants table
            for (key, val) in self.constantsTable.items():
                # write the pair on a new line
                f.write("%s %s\n" % (key, val))

    # method decides if _token is a symbol or an identifier
    def addToken(self, _token):
        # if the token is in the codification table, then it's a symbol
        if _token in self.codificationTable:
            self.appendToPifFile(str(self.codificationTable[_token]) + " -1\n", _token)
        # else, it must be an identifier
        else:
            self.addIdentifier(_token)

    def addSymbol(self, _symbol):
        # if the symbol is in the symbol table
        if _symbol in self.codificationTable:
            # print it
            self.appendToPifFile(str(self.codificationTable[_symbol]) + " -1\n", _symbol)
            return True
        else:
            # return false because _symbol is not a valid symbol
            return False

    # method prints identifier and it's id to the output file
    def addIdentifier(self, _id):
        if _id not in self.identifiersTable:
            self.identifiersTable[_id] = len(self.identifiersTable) + 1
        # print to program internal form output file
        self.appendToPifFile(
            self.codificationTable["identifier"] + " " + str(self.identifiersTable[_id]) + "\n", _id)

    # method adds a constant to the table and prints it to the output file
    def addConstant(self, _val):
        # assign a new, unsued integer id for the current identifier
        if _val not in self.constantsTable:
            self.constantsTable[_val] = len(self.constantsTable) + 1
        # print to the program internal form output file
        self.appendToPifFile(
            self.codificationTable["constant"] + " " + str(self.constantsTable[_val]) + "\n", _val)

    # method tokenize the source file
    def tokenize(self):
        try:
            ch = self.getNextCharacter()
            #iterate character by character
            while True:
                # in case we have an alphabet character (a, b, .. z, A, B, .. Z)
                if ch.isalpha():
                    # variable to store the current identifier
                    _id = ""
                    # we iterate while we have valid identifier characters
                    while ch.isalpha() or ch == '_':
                        # append the current character to _id
                        _id += ch
                        # get the next character
                        ch = self.getNextCharacter()
                    # at the end, if the lenght of the iterator is more than the max allowed lenght
                    # throw an error, and fail fast
                    if len(_id) > 250:
                        print("ERROR: Identifier has too many characters.")
                        sys.exit()
                    # add the token
                    self.addToken(_id)
                # in case we have a digit (0-9)
                elif ch.isdigit() or (ch in "+-" and self.pickNextCharacter().isdigit()):
                    # variable stores the current constant
                    _val = ch
                    ch = self.getNextCharacter()
                    # while there is a digit or if the current character is .
                    while ch.isdigit() or ch == '.':
                        # append the character to the constant
                        _val += ch
                        # get next character
                        ch = self.getNextCharacter()
                    # add the constant to the program internal form and to the internal hashmaps
                    self.addConstant(_val)
                # ignore whitespace characters
                elif ch.isspace():
                    # get the next character
                    ch = self.getNextCharacter()
                # else, we may have a symbol or an invalid identifier
                else:
                    # pick the next character
                    next = self.pickNextCharacter()
                    # if we are in one of the cases >=, <=, == or !=, we update the variable
                    if ch+next in ["<=", ">=", "!=", "=="]:
                        _id = _id + next
                    # if we couldn't add the symobl, we throw an error because it is an unexpected
                    # symbol identifier
                    if not self.addSymbol(ch):
                        print("ERROR: Unexpected token '%s'" % ch)
                        sys.exit()
                    ch = self.getNextCharacter()

        # in case we reached the end of the iteration
        except EOFError:
            self.writeTables()
            print("> finish")
            return

#
# # if name is main
# if __name__ == '__main__':
#     # filename = str(sys.argv[1])
#     filename = "input/circle.cpp"
#     # filename = "input/test.cpp"
#
#     print("> scanning " + filename + "...")
#     s = Scanner(filename)
#     s.tokenize()
