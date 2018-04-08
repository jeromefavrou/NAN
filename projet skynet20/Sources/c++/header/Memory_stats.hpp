#ifndef MEMORY_STATS_HPP_INCLUDED
#define MEMORY_STATS_HPP_INCLUDED

#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>

#include <cstdlib>

#ifdef WIN32
    #include <windows.h>
#endif


class Memory_stat
{
public:
    Memory_stat(void);

    ~Memory_stat(void);

    /////////////////////////////////////////////////
    ///updating of memory info
    /////////////////////////////////////////////////
    void update_info(void);

    size_t MemTotal;
    size_t MemFree;
    size_t MemAvailable;
    size_t Buffers;
    size_t Cached;
    size_t SwapCached;
    size_t SwapTotal;
    size_t SwapFree;
    size_t Mapped;
    size_t KernelStack;
    size_t WritebackTmp;

private:
    /////////////////////////////////////////////////
    ///attribute attributes for linux os
    /////////////////////////////////////////////////
    bool attribute(std::ifstream &);
};

#endif // MEMORY_STATS_HPP_INCLUDED
