import copy

class Game:
    def __init__(self, filename):
        self.n = 0
        self.m = 0
        self.t = 0  # number of tiles
        self.map = []
        self.tiles = []
        self.filename = filename

    def readData(self):
        print("Reading file...")
        tokens = []
        f = open(self.filename, 'r')
        for line in f:
            for token in line.split():
                tokens.append(int(token))

        self.n = tokens.pop(0)
        self.m = tokens.pop(0)
        self.map = [[tokens.pop(0) for _ in range(self.m)] for _ in range(self.n)]

        self.t = tokens.pop(0)
        for _ in range(self.t):
            tile = {'n': tokens.pop(0), 'm': tokens.pop(0)}
            tile['map'] = [[tokens.pop(0) for _ in range(tile['m'])] for _ in range(tile['n'])]
            self.tiles.append(tile)

    def testInput(self):
        # check if number of spaces in map is equal with all the pieces from all tiles
        map_pieces = 0
        tiles_pieces = 0

        for i in range(self.n):
            for j in range(self.m):
                map_pieces += 0 if self.map[i][j] else 1

        for tile in self.tiles:
            for i in range(tile['n']):
                for j in range(tile['m']):
                    tiles_pieces += 1 if tile['map'][i][j] else 0

        if map_pieces == tiles_pieces:
            print("Input is valid")
        else:
            raise ValueError("Invalid Input: %d %d" % (map_pieces, tiles_pieces))

    def isSolution(self, configuration):
        for i in range(self.n):
            for j in range(self.m):
                if configuration[i][j] == 0:
                    return False
        return True

    def printSolution(self, configuration):
        for i in range(self.n):
            for j in range(self.m):
                print("%3d" % configuration[i][j], end="")
            print()

    def isInMap(self, i, j):
        return 0 <= i < self.n and 0 <= j < self.m

    def furtherCheck(self, configuration):
        """
        performs further checks if a configuration is valid
        :param configuration: current config
        :return: config if valid else None
        """

        di = [-1, 0, 1, 0]
        dj = [0, 1, 0, -1]

        # check if there are blocs of size 1x1 that are empty
        for i in range(self.n):
            for j in range(self.m):
                if self.map[i][j] == 0:
                    nrv = 0 # number of valid neighbours that are 0
                    for d in range(4):
                        iv = i + di[d]
                        jv = j + dj[d]
                        if self.isInMap(iv, jv) and self.map[iv][jv] == 0:
                            nrv += 1
                    if nrv == 0:
                        return None

        return configuration

    def nextConfiguration(self, configuration, i, j, current_tile):
        """
        :param configuration: current config
        :param i & j: position of where tile is inserted
        :return: new configuration or None if it is not valid
        """

        # check if tile in inside map
        tile_n = self.tiles[current_tile]['n']
        tile_m = self.tiles[current_tile]['m']
        tile_map = self.tiles[current_tile]['map']

        if self.n - tile_n - i < 0 or self.m - tile_m - j < 0:
            return None

        new_config = copy.deepcopy(configuration)
        for ti in range(tile_n):  # ti = title_i
            for tj in range(tile_m):  # tj = title_j
                if tile_map[ti][tj] != 0:
                    if new_config[i+ti][j+tj] != 0:
                        return None
                    new_config[i + ti][j + tj] = current_tile+1
        return new_config

    def backtracking(self, configuration, current_tile):
        print(current_tile)

        if current_tile == self.t:
            if self.isSolution(configuration):
                print("SOLUTION FOUND!")
                self.printSolution(configuration)
            return

        # try every position
        for i in range(self.n):
            for j in range(self.m):
                new_configuration = self.nextConfiguration(configuration, i, j, current_tile)
                if new_configuration is not None and self.furtherCheck(new_configuration) is not None:
                    self.backtracking(new_configuration, current_tile+1)

    def test(self):
        self.readData()
        if self.furtherCheck(self.map) is None:
            print("Fail")
        else:
            print("Success")

    def run(self):
        self.readData()
        self.testInput()
        print("Running backtracking...")
        self.backtracking(self.map, 0)
        print("END")


if __name__ == "__main__":
    g = Game("input.txt")
    g.run()
