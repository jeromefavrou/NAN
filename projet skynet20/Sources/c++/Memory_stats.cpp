#include "header/Memory_stats.hpp"

Memory_stat::Memory_stat(void)
{
    this->MemTotal=0;
    this->MemFree=0;
    this->MemAvailable=0;
    this->Buffers=0;
    this->Cached=0;
    this->SwapCached=0;
    this->SwapTotal=0;
    this->SwapFree=0;
    this->Mapped=0;
    this->KernelStack=0;
    this->WritebackTmp=0;
}

Memory_stat::~Memory_stat(void)
{
}

/////////////////////////////////////////////////
///updating of memory info
/////////////////////////////////////////////////
void Memory_stat::update_info(void)
{
    #ifdef WIN32
    MEMORYSTATUS stat;
    GlobalMemoryStatus (&stat);

    this->MemFree=stat.dwAvailVirtual;
    this->MemTotal=stat.dwTotalVirtual;
    this->MemAvailable=-INFINITY;
    this->Buffers=-INFINITY;
    this->Cached=-INFINITY;
    this->SwapCached=-INFINITY;
    this->SwapTotal=-INFINITY;
    this->SwapFree=-INFINITY;
    this->Mapped=-INFINITY;
    this->KernelStack=-INFINITY;
    this->WritebackTmp=-INFINITY;
    #endif

    #ifndef WIN32
    std::ifstream If("/proc/meminfo");

    while(If)
        this->attribute(If);

    #endif // linux
}


/////////////////////////////////////////////////
///attribute attributes for linux os
/////////////////////////////////////////////////
bool Memory_stat::attribute(std::ifstream & If)
{
    std::string jmp("");

    If >> jmp;

    if(jmp=="MemFree:")
    {
        If >> this->MemFree;
        return true;
    }
    else if(jmp=="MemTotal:")
    {
        If >> this->MemTotal;
        return true;
    }
    else if(jmp=="MemAvailable:")
    {
        If >> this->MemAvailable;
        return true;
    }
    else if(jmp=="Buffers:")
    {
        If >> this->Buffers;
        return true;
    }
    else if(jmp=="Cached:")
    {
        If >> this->Cached;
        return true;
    }
    else if(jmp=="SwapCached:")
    {
        If >> this->SwapCached;
        return true;
    }
    else if(jmp=="SwapTotal:")
    {
        If >> this->SwapTotal;
        return true;
    }
    else if(jmp=="SwapFree:")
    {
        If >> this->SwapFree;
        return true;
    }
    else if(jmp=="Mapped:")
    {
        If >> this->Mapped;
        return true;
    }
    else if(jmp=="KernelStack:")
    {
        If >> this->KernelStack;
        return true;
    }
    else if(jmp=="WritebackTmp:")
    {
        If >> this->WritebackTmp;
        return true;
    }
    else
        return false;
}
