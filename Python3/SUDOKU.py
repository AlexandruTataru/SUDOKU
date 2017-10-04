import ctypes
lib = ctypes.WinDLL('CppBinding.dll')

func = lib[0]
func.restype = ctypes.c_char_p
value = func()
