import ctypes
lib = ctypes.WinDLL('CppBinding_x64.dll')

readBoard_CBinding = lib[1]
solveBoard_CBinding = lib[2]
retrieveSolvedBoard_CBinding = lib[3]
retrieveSolvedBoard_CBinding.restype = None

board = (ctypes.c_uint8 * 81)()
for i in range(0,81):
    board[i] = 3

readBoard_CBinding()
solveBoard_CBinding()
solvedBoard = (ctypes.c_uint8 * 81)()
retrieveSolvedBoard_CBinding(solvedBoard)
print(list(solvedBoard))
