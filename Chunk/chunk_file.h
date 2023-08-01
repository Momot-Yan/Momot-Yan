#pragma once
#include "chunk_fileio.h"

//#include <thread>

namespace chunk_io
{

  class PlaneFile 
    : public File
  {
  public:
    virtual ~PlaneFile();
    virtual unsigned int Read(unsigned char* pBuffer, unsigned int size);
    //virtual unsigned int Write(void* pBuffer, unsigned int size);
    virtual unsigned int Seek(int offset, OriginTypes sm);
    virtual unsigned int GetFilePosition();
    virtual unsigned int Size();
    virtual bool IsEof();
    virtual bool IsOpen() { return m_hfile.is_open(); }

    // own
    PlaneFile();
    PlaneFile(const char* filename);

  private:

    bool Initialize(const char* filename);
    void Close();

    //HANDLE CreateHandle(const char* filename, unsigned int mode);


    std::ifstream   m_hfile;
    std::string m_name;
    unsigned int   m_size;
    unsigned int   m_pos;
  }; // class PlaneFile 

} // namespace chunk_io
