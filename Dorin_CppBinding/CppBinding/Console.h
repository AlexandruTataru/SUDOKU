#pragma once

#if defined _DEBUG
    #include "Windows.h"
    #include <iostream>
#endif

class console
{
public:
    console()
    {
#if defined _DEBUG
        AllocConsole();
        AttachConsole(GetCurrentProcessId());
        freopen_s(&m_pCout, "CON", "w", stdout);
#endif
    }

    ~console()
    {
#if defined _DEBUG
        fclose(m_pCout);
#endif
    }

    template<typename T>
    console& operator << (const T & obj)
    {
#if defined _DEBUG
        std::cout << obj;
#endif
        return *this;
    }

private:
    FILE* m_pCout;
};