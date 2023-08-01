#pragma once
#include <assert.h>
#include <cstdarg>
#include <ctype.h>
#include "chunk_defs.h"

namespace chunk_fmt
{
  const char* va(const char *szFormat, ...);
  std::string vas(const char *szFormat, ...);
  std::string fmt( const char *szFormat, ...);
  inline std::string IntToStr(int value)          { return vas("%d",value); }
  inline std::string UintToStr(int value)         { return vas("%u",value); }
  inline std::string Int32ToStr(int32 value)      { return vas("%d", value); }
  inline std::string Int64ToStr(__int64 value)      { return vas("%I64d", value); }
  inline std::string FloatToStr(float value)      { return vas("%g", value); }
  inline std::string DoubleToStr(double value)    { return vas("%g", value); }

  template<class T> std::string    ToString(T const& val, uint uiPrecision = 1);

  inline   std::string             ToString                 (const char* val,         uint uiPrecision);
  template<> inline   std::string  ToString<std::string>       (std::string const& val,       uint uiPrecision);
  template<> inline   std::string  ToString<bool>           (bool const& val,           uint uiPrecision);
  template<> inline   std::string  ToString<char>           (char const& val,           uint uiPrecision);
  template<> inline   std::string  ToString<signed char>    (signed char const& val,    uint uiPrecision);
  template<> inline   std::string  ToString<unsigned char>  (unsigned char const& val,  uint uiPrecision);
  template<> inline   std::string  ToString<short>          (short const& val,          uint uiPrecision);
  template<> inline   std::string  ToString<unsigned short> (unsigned short const& val, uint uiPrecision);
  template<> inline   std::string  ToString<int>            (int const& val,            uint uiPrecision);
  template<> inline   std::string  ToString<unsigned int>   (unsigned int const& val,   uint uiPrecision);
  template<> inline   std::string  ToString<int64>          (int64 const& dest,         uint uiPrecision);
  template<> inline   std::string  ToString<uint64>         (uint64 const& dest,        uint uiPrecision);
  template<> inline   std::string  ToString<float>          (float const& val,          uint uiPrecision);
  template<> inline   std::string  ToString<double>         (double const& val,         uint uiPrecision);

  inline int    StrToInt(const char *szValue)         
  { 
    return std::atoi(szValue); 
  }

  inline __int64  StrToInt64(const char *szValue)       
  { 
    return ::_atoi64(szValue); 
  }

  inline uint32 StrToUint32(const char *szValue)      
  { 
    return static_cast<uint32>(std::atoi(szValue)); 
  }

  inline int32  StrToInt32(const char *szValue)       
  {
    return std::atoi(szValue); 
  }

  inline float  StrToFloat(const char *szValue)   
  { 
    return static_cast<float>(std::strtod(szValue, NULL)); 
  }

  inline int reverse_stricmp(const char* ps1, const char* ps2, size_t len)
  {
    if(ps1 == ps2) return 0;
    char c1, c2;
    for(int i = (int)len - 1; i >= 0; --i)
    {
      c1 = tolower(ps1[i]);
      c2 = tolower(ps2[i]);
      if(c1 != c2) return -1;
    }
    return 0;
  }

  inline int reverse_stricmp(std::string const& str1, std::string const& str2) {
    size_t s1 = str1.size();
    if(s1 != str2.size()) return -1;
    return reverse_stricmp(str1.c_str(), str2.c_str(), s1);
  }
  inline int reverse_stricmp(std::string const& str1, const char* szStr2) {
    size_t s1 = str1.size();
    if(s1 != strlen(szStr2)) return -1;
    return reverse_stricmp(str1.c_str(), szStr2, s1);
  }

  inline int vsprintf( char* szDest, unsigned int uiDestSize, const char *szFormat, va_list argptr)
  {
    if (!uiDestSize) return 0;

    int ret = ::_vsnprintf(szDest, uiDestSize - 1, szFormat, argptr);
    szDest[uiDestSize - 1] = 0;
    return ret;
  }

  inline int sprintf( char* szDest, unsigned int uiDestSize, const char *szFormat, ...)
  {
    assert(uiDestSize);

    if( !uiDestSize )
      return 0;

    va_list argptr;
    va_start(argptr, szFormat);
    int ret = _vsnprintf(szDest, uiDestSize - 1, szFormat, argptr);
    va_end(argptr);

    szDest[uiDestSize - 1] = 0;
    return ret;
  }

  inline void strcat(char *szDest, unsigned int uiDestSize, const char *szSrc) 
  {
    assert(uiDestSize);
    size_t uiLen = strlen(szDest);
    strcpy(szDest + uiLen, szSrc);
  }

  inline std::string vfmt( const char *szFormat, va_list pArg)
  {
    static char szBuffer[128*1024]; // not thread safe !!! but fast
    vsprintf(szBuffer,rgsizeof(szBuffer), szFormat, pArg);
    return std::string(szBuffer);
  }

  inline std::string fmt( const char *szFormat, ...)
  {
    va_list pArg;
    va_start(pArg, szFormat);
    std::string const sResult(vfmt(szFormat, pArg));
    va_end(pArg);
    return sResult;
  }



#define VA_GOODSIZE  512
#define VA_BUFSIZE  2048

  inline const char* va(const char *format, ...)
  {
    static char buf[VA_BUFSIZE];
    static int bufPos = 0;
    // wrap buffer
    if (bufPos >= VA_BUFSIZE - VA_GOODSIZE)
      bufPos = 0;

    va_list argptr;
    va_start(argptr, format);

    // print
    char *str = buf + bufPos;
    int len = vsprintf(str, VA_BUFSIZE - bufPos, format, argptr);
    if (len < 0 && bufPos > 0)
    {
      // buffer overflow - try again with printing to buffer start
      bufPos = 0;
      str = buf;
      len = vsprintf(buf, VA_BUFSIZE, format, argptr);
    }

    va_end (argptr);

    if (len < 0)                                    // not enough buffer space
    {
      const char suffix[] = " ... (overflow)";    // it is better, than return empty string
      memcpy(buf + VA_BUFSIZE - sizeof(suffix), suffix, rgsizeof(suffix));
      return str;
    }

    bufPos += len + 1;
    return str;
  }

  inline std::string vas(const char *format, ...)
  {
    static char buf[VA_BUFSIZE];
    static int bufPos = 0;
    // wrap buffer
    if (bufPos >= VA_BUFSIZE - VA_GOODSIZE)
      bufPos = 0;

    va_list argptr;
    va_start(argptr, format);

    // print
    char *str = buf + bufPos;
    int len = vsprintf(str, VA_BUFSIZE - bufPos, format, argptr);
    if (len < 0 && bufPos > 0)
    {
      // buffer overflow - try again with printing to buffer start
      bufPos = 0;
      str = buf;
      len = vsprintf(buf, VA_BUFSIZE, format, argptr);
    }

    va_end (argptr);

    if (len < 0)                                    // not enough buffer space
    {
      const char suffix[] = " ... (overflow)";    // it is better, than return empty string
      memcpy(buf + VA_BUFSIZE - sizeof(suffix), suffix, rgsizeof(suffix));
      return std::string( str );
    }

    bufPos += len + 1;
    return std::string( str );
  }


  //////////////////////////////////////////////////////////////////////////
  inline std::string ToString(const char* val, uint uiPrecision)
  {
    return std::string( val );
  }

  template<> inline std::string ToString<std::string>(std::string const& val, uint uiPrecision)
  {
    return val;
  }

  template<> inline std::string ToString<bool>(bool const& val, uint uiPrecision)
  {
    return Int32ToStr(val);
  }

  template<> inline std::string ToString<char>(char const& val, uint uiPrecision)
  {
    return std::string(1, val);
  }

  template<> inline std::string ToString<signed char>(signed char const& val, uint uiPrecision)
  {
    return std::string(1, val);
  }

  template<> inline std::string ToString<unsigned char>(unsigned char const& val, uint uiPrecision)
  {
    return std::string(1, val);
  }

  template<> inline std::string ToString<short>(short const& val, uint uiPrecision)
  {
    return va("%d", val);
  }

  template<> inline std::string ToString<unsigned short>(unsigned short const& val, uint uiPrecision)
  {
    return va("%u", val);
  }

  template<> inline std::string ToString<int>(int const& val, uint uiPrecision)
  {
    return va("%d", val);
  }

  template<> inline std::string ToString<unsigned int>(unsigned int const& val, uint uiPrecision)
  {
    return va("%u", val);
  }

  template<> inline std::string ToString<int64>(int64 const& val, uint uiPrecision)
  {
    return va("%I64d", val);
  }

  template<> inline std::string ToString<uint64>(uint64 const& val, uint uiPrecision)
  {
    return va("%I64u", val);
  }

  template<> inline std::string ToString<float>(float const& val, uint uiPrecision)
  {
    char fmt[32], buf[1024];
    sprintf(fmt, sizeof(fmt)/sizeof(fmt[0]), "%%.%if", uiPrecision);
    sprintf(buf, sizeof(buf)/sizeof(buf[0]), fmt, val);
    return std::string(buf);
  }

  template<> inline std::string ToString<double>(double const& val, uint uiPrecision)
  {
    char fmt[32], buf[1024];
    sprintf(fmt, sizeof(fmt)/sizeof(fmt[0]), "%%.%if", uiPrecision);
    sprintf(buf, sizeof(buf)/sizeof(buf[0]), fmt, val);
    return std::string(buf);
  }


} // namespace chunk_fmt