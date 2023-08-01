#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include <fstream>  
#include <filesystem>
#include <cstdio>
#include "chunk_file.h"
#include "chunk_bstream.h"
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>
#include <thread>


/*#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2*/    //commented by me
//typedef _Longlong streamsize;

namespace chunk_io
{
  inline void PlatformFileName( char* szFileName )
  {
    while(*szFileName)
    {
      if('/' == *szFileName)
        *szFileName = '\\';
      else
        *szFileName = tolower(*szFileName);
      ++szFileName;
    }
  }

  inline void PlatformFileName( std::string& sFileName )
  {
    const size_t len = sFileName.size();
    for(size_t i(0); len != i; ++i)
    {
      if('/' == sFileName[i])
        sFileName[i] = '\\';
      else
        sFileName[i] = tolower(sFileName[i]);
    }
  }

  inline PlaneFile::PlaneFile()//: m_hfile( INVALID_HANDLE_VALUE )
  {
  }

  inline PlaneFile::PlaneFile(const char* filename)
  {
    Initialize(filename);
  }


  inline PlaneFile::~PlaneFile()
  {
    Close();
  }

  inline unsigned int PlaneFile::Read(unsigned char* pBuffer, unsigned int size)
  {
    if (!size)
      return 0;

    unsigned long readBytes = 0;
    //::ReadFile(m_hfile, pBuffer, static_cast<unsigned long>(size), &readBytes, 0);
    //streamsize pBufferLen = ((char*)(pBuffer)).length();
    //readBytes = m_hfile.readsome ((char*) pBuffer, size);
    try {
        m_hfile.read((char*)pBuffer, size);
    }
    catch(...){}
    readBytes = m_hfile.gcount();
    m_pos += readBytes;
    if (m_pos > m_size){          // this can happen if the file has been modified after openings
      //  m_size = ::GetFileSize(m_hfile, NULL);
      //m_hfile.seekg(0, std::ios_base::end);
      m_size = m_hfile.tellg();
      //m_hfile.seekg(0, std::ios_base::beg);
    }
    return readBytes;
  }

  //inline unsigned int PlaneFile::Write( void* pBuffer, unsigned int size )
  //{

  //  unsigned long writtenBytes = 0;
  //  //::WriteFile(m_hfile, pBuffer, static_cast<unsigned long >(size), &writtenBytes, 0);
  //  m_size += writtenBytes;
  //  m_pos  += writtenBytes;
  //  return writtenBytes;
  //}

  inline unsigned int PlaneFile::Seek( int offset, OriginTypes sm )
  {
    /*unsigned long wsm;
    switch(sm)
    {
    case SeekSet: wsm = FILE_BEGIN;   break;
    case SeekCur: wsm = FILE_CURRENT; break;
    case SeekEnd: wsm = FILE_END;     break;
    default: return bad_pos;
    };*/    //commented by me

    // Move cursor to position offset (in bytes) forward from beginning of the stream

    m_hfile.seekg(offset, std::ios::beg);
    m_pos = m_hfile.tellg();
    //m_pos = ::SetFilePointer( m_hfile, offset, 0, wsm );

    if(m_hfile.bad())
    {
      assert(false);
      m_pos = File::bad_pos;
    }
    return m_pos;
  }

  inline unsigned int PlaneFile::GetFilePosition()
  {
    return m_pos;
  }

  inline unsigned int PlaneFile::Size()
  {
    return m_size;
  }

  //inline HANDLE PlaneFile::CreateHandle(const char* filename, unsigned int mode)
  //{
  //  // set access and sharing modes
  //  unsigned long access(0);
  //  if( mode & ( SM_WRITE | SM_APPEND ) )
  //    access |= GENERIC_WRITE;
  //  if(mode & SM_READ )
  //    access |= GENERIC_READ;

  //  // select creation disposition
  //  unsigned long disp = 0;
  //  if( mode & SM_READ && !(mode & SM_WRITE) )
  //    disp = OPEN_EXISTING;
  //  else if (mode & SM_WRITE)
  //    disp = CREATE_ALWAYS;
  //  else if (mode & SM_APPEND)
  //    disp = OPEN_ALWAYS;

  //  HANDLE h = ::CreateFileA(filename, access, FILE_SHARE_READ, NULL, disp, 0, 0);

  //  return h;
  //}

  inline bool PlaneFile::Initialize(const char* filename)
  {
    std::ios_base::openmode mode = std::ios_base::in;

    //TCHAR buffer[MAX_PATH] = { 0 };
    //GetModuleFileName( NULL, buffer, MAX_PATH );

    //m_hfile.open(filename, mode);
    //m_hfile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    /*try {
      m_hfile.open (filename);
      m_hfile.close();
    }
    catch (std::ifstream::failure e) {
      std::cout << "Caught an ios_base::failure.\n" << "Explanatory string: " << e.what() << '\n' << "Error code: " << e.code() << '\n';// std::cout << e.code << " ";
      std::string text = e.what();
      //e.code().


      std::cerr << "Exception opening/reading/closing file\n";
    }*/
    m_hfile.open (filename);
    if (!m_hfile.is_open() || !m_hfile) {
      return false;
    }
    // setup file size and position
    m_hfile.seekg(0, std::ios_base::end);
    m_size = m_hfile.tellg();
    m_hfile.seekg(0, std::ios_base::beg);
    m_pos  = 0;

    return true;

    /*
    //m_hfile = CreateHandle( filename, mode );
    m_pos   = 0;
    if( m_hfile == INVALID_HANDLE_VALUE )
  ////////////////////  {
    return false;
    }
    //// setup file size and pointer
    //if( mode & SM_APPEND )
    //  m_size = m_pos = ::SetFilePointer(m_hfile, 0, 0, FILE_END);
    else if( mode & SM_READ )
    {
    //m_size = ::GetFileSize(m_hfile, NULL);
    m_pos  = 0;
    }
    else // SM_WRITE
    m_size = m_pos = 0;

    return true;*/
  }

  inline void PlaneFile::Close()
  {
    if (m_hfile.is_open() && m_hfile) {
      m_hfile.close();
    }


    if( m_hfile.is_open() )
    {
      //::CloseHandle(m_hfile);
      m_hfile.close();
    }
    //m_hfile = INVALID_HANDLE_VALUE;
  }

  inline bool PlaneFile::IsEof()
  {
    return ( m_pos >= m_size );
  }

} // namespace io
