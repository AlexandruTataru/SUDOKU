import ctypes
lib = ctypes.WinDLL('CppBinding_x64.dll')

def testDLL():
    loadBoard_CBinding = lib['loadBoard']
    loadBoard_CBinding.argtypes = [ctypes.POINTER(ctypes.c_uint8)]
    loadBoard_CBinding.restype = ctypes.c_bool

    board = (ctypes.c_uint8 * 81)()
    values = [4, 2, 3, 3, 7, 2, 8, 2, 6, 1, 9, 2, 9, 6, 7, 3, 2, 4, 3, 9, 7, 5, 5, 6, 4, 9, 5, 7, 2, 4, 6, 3, 4, 2, 1, 7]
    positions = [3, 4, 6, 10, 13, 15, 17, 18, 19, 21, 25, 28, 29, 33, 37, 39, 41, 44, 47, 48, 51, 52, 57, 58, 60, 62, 64, 65, 66, 67, 70, 71, 73, 74, 78, 79]
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
