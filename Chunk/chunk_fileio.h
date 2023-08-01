#pragma once

namespace chunk_io
{
  enum OriginTypes
  {
    SeekSet,
    SeekCur,
    SeekEnd
  };
  typedef unsigned int Attribute;
  enum
  {
    normal =    0x00,
    readOnly =  0x01,
    hidden =    0x02,
    system =    0x04,
    volume =    0x08,
    directory = 0x10,
    archive =   0x20
  };
  class File
  {
  public:
    static const unsigned int bad_pos = 0xffffffffu;

    virtual ~File() {}
    virtual unsigned int Read(unsigned char* pBuffer, unsigned int size) = 0;
    //virtual unsigned int Write(void* pBuffer, unsigned int size) = 0;
    //virtual unsigned int Seek(int offset, OriginTypes sm) = 0;   // return bad_pos if failed
    virtual unsigned int GetFilePosition() = 0;
    virtual unsigned int Size() = 0;
    virtual bool   IsEof() = 0;
    virtual bool   IsOpen() = 0;
  };

  // class FileFinder

} // namespace chunk_io