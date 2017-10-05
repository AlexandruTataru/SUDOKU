import ctypes
lib = ctypes.WinDLL('CppBinding_x64.dll')

def testDLL():
    loadBoard_CBinding = lib['loadBoard']
    loadBoard_CBinding.argtypes = [ctypes.POINTER(ctypes.c_uint8)]
    loadBoard_CBinding.restype = ctypes.c_bool

    board = (ctypes.c_uint8 * 81)()
    values = [2, 6, 7, 1, 6, 8, 7, 9, 1, 9, 4, 5, 8, 2, 1, 4, 4, 6, 2, 9, 5, 3, 2, 8, 9, 3, 7, 4, 4, 5, 3, 6, 7, 3, 1, 8]
    positions = [3, 4, 6, 8, 9, 10, 13, 16, 18, 19, 23, 24, 27, 28, 30, 34, 38, 39, 41, 42, 46, 50, 52, 53, 56, 57, 61, 62, 64, 67, 70, 71, 72, 74, 76, 77]
    for i in range(0, len(positions)):
        board[positions[i]] = values[i]
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

        if returnValue:
            for i in range(0, 81):
                print(solvedBoard[i])

testDLL()
