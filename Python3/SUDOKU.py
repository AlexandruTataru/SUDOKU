import ctypes
import datetime
import sys
lib = ctypes.WinDLL('CppBinding_x64.dll')

def testDLL():
    loadBoard_CBinding = lib['loadBoard']
    loadBoard_CBinding.argtypes = [ctypes.POINTER(ctypes.c_uint8)]
    loadBoard_CBinding.restype = ctypes.c_bool

    board = (ctypes.c_uint8 * 81)()
    
    #easy board
    #values = [2, 6, 7, 1, 6, 8, 7, 9, 1, 9, 4, 5, 8, 2, 1, 4, 4, 6, 2, 9, 5, 3, 2, 8, 9, 3, 7, 4, 4, 5, 3, 6, 7, 3, 1, 8]
    #positions = [3, 4, 6, 8, 9, 10, 13, 16, 18, 19, 23, 24, 27, 28, 30, 34, 38, 39, 41, 42, 46, 50, 52, 53, 56, 57, 61, 62, 64, 67, 70, 71, 72, 74, 76, 77]

    #medium board
    values = [6, 1, 2, 7, 9, 1, 5, 6, 4, 8, 2, 6, 7, 5, 9, 4, 5, 9, 3, 8, 3, 6, 1, 7]
    positions = [0, 2, 5, 7, 10, 12, 15, 23, 26, 28, 34, 38, 42, 46, 52, 54, 57, 65, 68, 70, 73, 75, 78, 80]
    
    #very hard board
    #values = [3, 8, 5, 1, 2, 5, 7, 4, 1, 9, 5, 7, 3, 2, 1, 4, 9]
    #positions = [14, 16, 17, 20, 22, 30, 32, 38, 42, 46, 54, 61, 62, 65, 67, 76, 80]
    
    for i in range(0, len(positions)):
        board[positions[i]] = values[i]
    start = datetime.datetime.now()
    loadBoard_CBinding(board)

    solveBoard_CBinding = lib['solveBoard']
    solveBoard_CBinding.restype = ctypes.c_bool
    isBoardSolved = solveBoard_CBinding()

    print('Is board solved? ' + str(isBoardSolved))

    if isBoardSolved:
        retrieveSolvedBoard_CBinding = lib['retrieveSolvedBoard']
        retrieveSolvedBoard_CBinding.argtypes = [ctypes.POINTER(ctypes.c_uint8)]
        retrieveSolvedBoard_CBinding.restype = ctypes.c_bool

        solvedBoard = (ctypes.c_uint8 * 81)()
        returnValue = retrieveSolvedBoard_CBinding(solvedBoard)

        print('Is solved board retrieved? ' + str(returnValue))

        solutionVerified = verifySolution(solvedBoard)
        print('Is solved board verified and correct? ' + str(solutionVerified))

        if solutionVerified:
            printBoard(solvedBoard)

        if returnValue:
            end = datetime.datetime.now()
            print(end - start)

def verifySolution(board):
    Matrix = [[0 for x in range(9)] for y in range(9)]
    k = 0
    for i in range(9):
        for j in range(9):
            Matrix[i][j] = board[k]
            k += 1
    
    for i in range(9):
        s = {1, 2, 3, 4, 5, 6, 7, 8, 9}
        for j in range(9):
            if Matrix[i][j] in s:
                s.discard(Matrix[i][j])
            else:
                return False
            
        if len(s) != 0:
            return False

    for i in range(9):
        s = {1, 2, 3, 4, 5, 6, 7, 8, 9}
        for j in range(9):
            if Matrix[j][i] in s:
                s.discard(Matrix[j][i])
            else:
                return False
            
        if len(s) != 0:
            return False

    offsetI = 0
    offsetJ = 0
    for k in range (9):
        if k in (1, 2, 4, 5, 7, 8):
            offsetJ += 3
        if k in (3, 6):
            offsetI += 3
            offsetJ = 0
        s = {1, 2, 3, 4, 5, 6, 7, 8, 9}
        for i in range (3):
            for j in range (3):
                if Matrix[offsetI + i][offsetJ + j] in s:
                    s.discard(Matrix[offsetI + i][offsetJ + j])
                else:
                    return False
                
        if len(s) != 0:
            return False

    return True

def printBoard(board):
    k = 0
    for i in range(9):
        for j in range(9):
            sys.stdout.write(str(board[k]) + ' ')
            k += 1
        sys.stdout.write('\n')

testDLL()
