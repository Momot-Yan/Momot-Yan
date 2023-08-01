#pragma once
#include <assert.h>
#include "chunk_defs.h"
// stolen from Vis600 rtl_bstream.inl, rtl_bstream.cpp


namespace chunk_io
{

  //--------------------------------------------------------
  // Stream implementation
  //--------------------------------------------------------

  inline Stream::Stream()
    : m_flags(0)
  {
    Clear();
  }


  inline Stream::~Stream()
  {
    Clear();
  }


  inline void Stream::Clear()
  {
    m_flags &= SF_DONT_USE_EXCEPTIONS;
    m_pbegin      = NULL;
    m_pend        = NULL;
    m_ppos        = NULL;
    m_size        = 0;
    m_beginPos    = 0;
    m_writenBytes = 0;
    m_name.clear();
  }


  inline void Stream::SetUseExceptions(bool b)
  {
    if(!b)
    {
      m_flags |= SF_DONT_USE_EXCEPTIONS;
    }
    else
    {
      m_flags &= ~SF_DONT_USE_EXCEPTIONS;
    }
  }


  inline bool Stream::IsUseExceptions() const
  {
    return (m_flags & SF_DONT_USE_EXCEPTIONS) == 0;
  }


  inline bool Stream::IsOpen() const
  {
    return (m_flags & SF_IS_OPEN) != 0;
  }


  inline bool Stream::IsBad() const
  {
    return (m_flags & SF_IS_BAD) != 0;
  }


  inline bool Stream::Failed() const
  {
    return (m_flags & SF_FAIL_BIT) != 0;
  }


  inline bool Stream::IsStoring() const
  {
    assert(IsOpen());
    return (m_flags & SF_MODE_WRITE) != 0;
  }


  inline bool Stream::IsLoading() const
  {
    return !IsStoring();
  }


  inline unsigned int Stream::Size() const
  {
    assert(IsOpen());
    return m_size;
  }


  inline unsigned int Stream::GetFilePosition() const
  {
    assert(IsOpen());
    return (unsigned int)(m_beginPos + (m_ppos - m_pbegin));
  }


  inline unsigned int Stream::SeekForward(unsigned int byteCount)
  {
    return SetPos(GetFilePosition() + byteCount);
  }


  //--------------------------------------------------------
  // MemStream
  //--------------------------------------------------------

  ////No function call was found
  //inline MemStream::MemStream()
  //{
  //  DoClear();
  //}


  //inline MemStream::MemStream(void* pdst, unsigned int sz, unsigned int mode)
  //{
  //  DoClear();
  //  Create(pdst, sz, mode);
  //}


  inline MemStream::MemStream(void const* pdst,  unsigned int sz, unsigned int mode)
  {
    DoClear();
    Create(pdst, sz, mode);
  }


  inline MemStream::MemStream(unsigned int mode, unsigned int initSize)
  {
    DoClear();
    Create(mode, initSize);
  }


  //inline MemStream::MemStream(unsigned int mode, Stream& src)
  //{
  //  DoClear();
  //  Create(mode, src);
  //}


  ////No function call was found
  //inline MemStream::~MemStream()
  //{
  //  Destroy();
  //}


  ////No function call was found
  //inline void MemStream::Reset()
  //{
  //  m_ppos = m_pbegin;
  //}


  inline void MemStream::DoClear()
  {
    Stream::Clear();

    m_size     = 0;
    m_bCapture = true;
  }


  inline void MemStream::Destroy()
  {
    if (m_bCapture)
      delete[] m_pbegin;
    Clear();
  }


  inline unsigned int MemStream::Capacity() const
  {
    assert(IsOpen());
    return (unsigned int)(m_pend - m_pbegin);
  }

  inline void MemStream::Resize(unsigned int sz)
  {
    assert(m_bCapture);
    if (!m_bCapture)
      return;

    unsigned int cap = Capacity();
    if (sz > cap)
      Realloc(sz);

    if (IsLoading())
    {
      m_pend = m_pbegin + sz;
      if (m_ppos > m_pend)
        m_ppos = m_pend;
    }

    m_size = GetFilePosition();
    if ( m_size < sz )
      m_size = sz;
  }


  ////No function call was found
  //inline unsigned char* MemStream::UnattachBuffer()
  //{
  //  assert(IsOpen());
  //  m_bCapture = false;
  //  return m_pbegin;
  //}


  inline unsigned char* MemStream::Data()
  {
    assert(IsOpen());
    return m_pbegin;
  }


  ////No function call was found
  //inline unsigned char const* MemStream::Data() const
  //{
  //  assert(IsOpen());
  //  return m_pbegin;
  //}


  ////No function call was found
  //inline void MemStream::ChangeMode(unsigned int mode)
  //{
  //  assert(IsOpen());
  //  assert(mode == SM_WRITE || mode == SM_READ);
  //  assert(m_bCapture);

  //  if (mode & SM_WRITE)
  //    m_flags |= SF_MODE_WRITE;
  //  else
  //    m_flags &= ~SF_MODE_WRITE;
  //}


  //--------------------------------------------------------------------------
  // Stream
  //--------------------------------------------------------------------------

  //inline void Stream::Flush()
  //{
  //   // empty for generic stream
  //}


  inline void Stream::Printf(const char* format, ...)
  {
    // speedup: do not format string when no '%' characters
    if (!strchr(format, '%'))
    {
      //RawWrite(format, (unsigned int)(strlen(format) * sizeof(char)));
      return;
    }

    va_list pArg;
    va_start(pArg, format);
    char buffer[32768];
    const int len = chunk_fmt::vsprintf(buffer,rgsizeof(buffer), format, pArg);
    va_end(pArg);

    if (len < 0 || len >= sizeof(buffer) - 1) return;   //?? may be, write anyway

    //RawWrite(buffer, len);
  }


  inline unsigned int Stream::SetPos(unsigned int pos)
  {
    assert(IsOpen());
    unsigned int offset = pos - m_beginPos;
    bool allowInbufferSeek;
    // read mode: allow any in-buffer seeks
    allowInbufferSeek = (offset < static_cast<unsigned int>(m_pend - m_pbegin) );

    //if (m_flags & SF_MODE_WRITE)
    //{
    //  // write mode: allow to seek backward only, otherwise should invalidate buffer
    //  allowInbufferSeek = (offset <= (int)m_writenBytes);
    //}
    //else
    //{
    //  // read mode: allow any in-buffer seeks
    //  allowInbufferSeek = (offset < static_cast<unsigned int>(m_pend - m_pbegin) );
    //}

    if (allowInbufferSeek)
    {
      // new offset is inside current buffer contents
      m_ppos = m_pbegin + offset;
    }
    else
    {
      //// new offset requires buffer change
      //pos = DoSetPos(pos);
    }

    if (pos > m_size)
    {
      //assert(m_flags & SF_MODE_WRITE);  // should happen only in write mode
      m_size = pos;                         // advance file size
    }
    return pos;
  }

  inline unsigned int Stream::RawRead(void* pdst, unsigned int sz)
  {
    assert(IsLoading());

    if (!sz)
      return 0;

    unsigned int rest      = sz;
    unsigned int bytesRead = 0;
    unsigned char*  pByteDst  = (unsigned char*)pdst;

    for(;;)
    {
      unsigned int avail = (unsigned int)(m_pend - m_ppos);

      // copy buffer to pdst
      unsigned int toRead = rest;
      unsigned int read   = GetDataFromBuffer(pByteDst, toRead, avail);
      // NOTE: real `read' may be smaller, than `toRead' (when SM_TEXT)

      // advance pointers
      m_ppos    += toRead;
      pByteDst  += read;
      rest      -= read;
      bytesRead += read;

      if (rest && m_ppos == m_pend)      // no more data in buffer
      {
        // fill buffer with next data
        // stream may decide to put data directly to "pdst"
        read = OnUnderflow(pByteDst, rest);
        pByteDst  += read;
        rest      -= read;
        bytesRead += read;
        // check for availability of new data in buffer
        avail = (unsigned int)(m_pend - m_ppos);
        if (!avail)
          break;                         // end of file reached
      }
      else
      {
        break;
      }
    }

    if (!bytesRead)                      // we're trying to read from file beyond its end
      SetFailed<endOfFile>(NULL);

    return bytesRead;
  }


  //inline unsigned int Stream::RawWrite(const void* psrc, unsigned int sz)
  //{
  //   assert(IsStoring());
  //
  //   if (!sz)
  //      return 0;
  //
  //   unsigned int rest          = sz;
  //   unsigned int bytesWriten   = 0;
  //   const unsigned char* pByteSrc = (const unsigned char*)psrc;
  //
  //   while (rest)
  //   {
  //      unsigned int avail = (unsigned int)(m_pend - m_ppos);
  //      if (!avail)
  //      {
  //         OnOverflow();                        // flush buffer
  //         avail = (unsigned int)(m_pend - m_ppos);             // and recompute free space
  //      }
  //      assert(avail);
  //
  //      // copy psrc to buffer
  //      unsigned int toWrite = rest;
  //      unsigned int writen  = PutDataToBuffer(pByteSrc, toWrite, avail);
  //      // NOTE: real `writen' may be larger, than `toWrite' (when SM_TEXT)
  //      // in that case, toWrite will be set to real used buffer
  //
  //      if (!writen)                           // possibly, no space for "\n" in text mode (have space for 1 char, requires 2)
  //      {
  //         OnOverflow();
  //         continue;
  //      }
  //
  //      // advance pointers
  //      m_ppos      += toWrite;
  //      pByteSrc    += writen;
  //      rest        -= writen;
  //      bytesWriten += writen;
  //
  //      // update count of bytes, writen to a buffer
  //      unsigned int bufOffset = (unsigned int)(m_ppos - m_pbegin);
  //      if (bufOffset > m_writenBytes)         // else - writing to middle of buffer (not appending data)
  //         m_writenBytes = bufOffset;
  //   }
  //
  //   if (bytesWriten != sz)
  //      SetFailed<writeError>(NULL);
  //
  //   // update stream size
  //   m_size = m_size > GetFilePosition() ? m_size : GetFilePosition();
  //   return bytesWriten;
  //}


  inline unsigned int Stream::PutDataToBuffer(const unsigned char* src, unsigned int& size, unsigned int availBuf)
  {
    if (m_flags & SF_MODE_TEXT)
    {
      // text mode: should insert '\r' chars before '\n'
      unsigned int put = 0, get = 0;
      unsigned char*  dst = m_ppos;
      while (put < availBuf && get < size)
      {
        unsigned char c = *src++;
        get++;
        if (c == '\n')              // special: requires space for 2 bytes
        {
          if (put + 2 > availBuf)   // not enough space for "\r\n"
          {
            get--;                  // return char back
            break;                  // and break the loop with smaller number of taken bytes
          }
          *dst++ = '\r';
          put++;
        }
        *dst++ = c;
        put++;
      }
      size = put;
      return get;
    }

    // binary stream
    if (size > availBuf)
      size = availBuf;
    memcpy(m_ppos, src, size);
    return size;
  }
  inline unsigned int Stream::GetDataFromBuffer(unsigned char* dst, unsigned int& size, unsigned int availBuf)
  {
    if (m_flags & SF_MODE_TEXT)
    {
      // text mode: should remove all '\n' chars
      unsigned int put = 0, get = 0;
      unsigned char*  src = m_ppos;
      while (put < size && get < availBuf)
      {
        unsigned char c = *src++;
        get++;
        if (c == '\r')
          continue;
        *dst++ = c;
        put++;
      }
      size = get;
      return put;
    }

    // binary stream
    if (size > availBuf)
      size = availBuf;
    memcpy(dst, m_ppos, size);
    return size;
  }
  inline void Stream::ReadError()
  {
    SetFailed<readError>(NULL);
  }

  inline void Stream::SeekError()
  {
    SetFailed<badSeek>("unable to seek");
  }

  inline void Stream::SizeError(const char* errMessage)
  {
    SetFailed<endOfFile>(errMessage);
  }

  inline void Stream::FormatError(const char* errMessage)
  {
    SetFailed<wrongFileFormat>(errMessage);
  }

  template<class T>
  void Stream::SetFailed(const char* errMessage, unsigned int k)
  {
    m_flags |= k;

    std::string msg = GetName();
    if (errMessage)
    {
      msg.append(" - ");
      msg.append((std::string)(errMessage));
    }

    if (IsOpen())
    {
      unsigned int pos = GetFilePosition();
      char buff[128];
      chunk_fmt::sprintf(buff, sizeof(buff), " (current position = 0x%x)", pos);
      msg += buff;
    }

    if (IsUseExceptions())
      throw T(msg); // remove, after all clients will not use exceptions

    //   g_err << T::GetErrorDescription() << " \'" << msg << "\'" << endl;
  }



  //--------------------------------------------------------------------------
  // FileStream
  //--------------------------------------------------------------------------

  inline bool FileStream::Open(const char* filename, unsigned int mode, unsigned int unused)
  {
    assert(filename);

    Close();

    //unsigned int mode2 = mode & (SM_READ|SM_WRITE|SM_APPEND);
    //assert( ( mode2 == SM_READ || mode2 == SM_WRITE || mode2 == SM_APPEND ) && "Incorrect FileStream open mode");

    m_name = filename;
    m_flags |= SF_DONT_USE_EXCEPTIONS;

    // create a buffered file
    m_planeFile  = new PlaneFile(filename);
    if( NULL != m_planeFile && m_planeFile->IsOpen() )
    {
      m_flags |= SF_IS_OPEN;
      m_size   = m_planeFile->Size();
      m_pbegin = &m_buff[0];

      //if (mode & SM_TEXT)
      //  m_flags |= SF_MODE_TEXT;

      //if (mode2 == SM_WRITE || mode2 == SM_APPEND)
      //{
      //  m_flags |= SF_MODE_WRITE;
      //  m_ppos   = m_pbegin;
      //  m_pend   = m_pbegin + BUFFER_SIZE;
      //}
      //else
      //{
      //  m_pend = m_ppos = m_pbegin;
      //}
    }
    else
    {
      m_flags |= SF_FAIL_BIT | SF_IS_BAD;
      if (IsUseExceptions())
        throw fileNotFound(filename);
      return false;
    }
    return true;
  }


  inline void FileStream::Close()
  {
    if (m_planeFile)
    {
      /*if (IsStoring())
      WriteBuffer();*/
      SAFE_DELETE(m_planeFile);
    }

    m_name.clear();
    Stream::Clear();
  }


  //inline void FileStream::Flush()
  //{
  //   WriteBuffer();
  //}


  inline bool FileStream::eof() const
  {
    return m_planeFile
      ? m_ppos == m_pend && m_planeFile->IsEof()
      : false;
  }


  inline unsigned int FileStream::OnUnderflow(unsigned char* dst, unsigned int size)
  {
    assert(m_ppos == m_pend);
    assert(IsLoading());

    if (size >= BUFFER_SIZE &&     // reading large block
      !(m_flags & SF_MODE_TEXT))   // text files requires buffering and GetDataFromBuffer() calls
    {
      unsigned int read = m_planeFile->Read(dst, size);
      m_beginPos = m_planeFile->GetFilePosition();
      m_ppos = m_pend = m_pbegin;
      return read;
    }

    m_beginPos = m_planeFile->GetFilePosition();
    unsigned long read = m_planeFile->Read(m_pbegin, BUFFER_SIZE);
    m_ppos = m_pbegin;
    m_pend = m_pbegin + read;
    return 0;
  }


  inline void FileStream::OnOverflow()
  {
     //assert(IsStoring());
     //WriteBuffer();
  }

  //
  //inline void FileStream::WriteBuffer()
  //{
  //   if (!IsStoring())
  //      return;
  //
  //   if (!m_writenBytes)
  //      return;
  //
  //   unsigned int written = m_planeFile->Write(m_pbegin, m_writenBytes);
  //   if (m_writenBytes != written)
  //      SetFailed<writeError>(NULL);
  //   m_beginPos    = m_planeFile->GetFilePosition();
  //   m_ppos        = m_pbegin;
  //   m_writenBytes = 0;
  //}


  //inline unsigned int FileStream::DoSetPos(unsigned int pos)
  //{
  //   assert(IsOpen());
  //
  //   //WriteBuffer();                    // flush buffer
  //   //unsigned int sz = m_planeFile->Seek(static_cast<int>(pos), SeekSet);
  //   //if (sz == File::bad_pos)
  //   //   SeekError();
  //
  //   //m_beginPos = sz;
  //   if (IsStoring())
  //   {
  //      m_ppos = m_pbegin;
  //   }
  //   else
  //   {
  //      m_pend = m_ppos = m_pbegin;     // force filling buffer
  //   }
  //
  //   m_size = m_planeFile->Size();         // update file size
  //   return sz;
  //}


  inline const char* FileStream::GetName() const
  {
    return m_name.c_str();
  }


  //--------------------------------------------------------------------------
  // MemStream
  //--------------------------------------------------------------------------

  inline void MemStream::Create(void* pdst, unsigned int sz, unsigned int mode)
  {
     assert(mode);
     Destroy();
  
     if (mode & SM_WRITE)
     {
        m_flags |= SF_MODE_WRITE;
     }
     else
     {
        m_size = sz;
     }
  
     if (mode & SM_NOEXCEPT)
        m_flags |= SF_DONT_USE_EXCEPTIONS;
  
     m_flags    |= SF_IS_OPEN;
     m_bCapture = false;
     m_pbegin   = (unsigned char*)pdst;
     m_pend     = m_pbegin + sz;
     m_ppos     = m_pbegin;
  }


  inline void MemStream::Create(void const* pdst, unsigned int sz, unsigned int mode)
  {
     assert(mode);
     Destroy();
  
     assert(mode & SM_READ);
  
     m_flags    |= SF_IS_OPEN;
     m_bCapture = false;
     m_pbegin   = (unsigned char*)pdst;
     m_pend     = m_pbegin + sz;
     m_ppos     = m_pbegin;
  
     if (mode & SM_READ)
        m_size = sz;
     if (mode & SM_NOEXCEPT)
        m_flags |= SF_DONT_USE_EXCEPTIONS;
  }


  inline void MemStream::Create(unsigned int mode, unsigned int initSize)
  {
     assert(mode);
     Destroy();
  
     assert(mode & SM_WRITE || mode & SM_READ);
  
     if (mode & SM_WRITE)
     {
        assert(!(mode & SM_READ));
        m_flags |= SF_MODE_WRITE;
     }
     else
     {
        assert(!(mode & SM_WRITE));
        m_size = initSize;
     }
  
     m_flags    |= SF_IS_OPEN;
     m_bCapture = true;
  
     if (mode & SM_NOEXCEPT)
        m_flags |= SF_DONT_USE_EXCEPTIONS;
  
     if (initSize)
        Realloc(initSize);
  }


  inline void MemStream::Create(unsigned int mode, Stream& src)
  {
     unsigned int srcSize = src.Size();
     Create(mode, srcSize);
     src.SetPos(0);
     unsigned int read = src.RawRead(m_pbegin, srcSize);
     if (read != srcSize)  // this may happen when reading from SM_TEXT ...
        Resize(read);
  }


  inline bool MemStream::eof() const
  {
    return (!(m_flags & SF_MODE_WRITE) && m_ppos == m_pend);
  }

  inline unsigned int MemStream::OnUnderflow(unsigned char* dst, unsigned int size)
  {
    // does nothing
    return 0;
  }


  inline void MemStream::OnOverflow()
  {
    Realloc(m_pend == NULL ? 4096 : Capacity() * 2);
  }

  //inline unsigned int MemStream::DoSetPos(unsigned int pos)
  //{
  //   assert(IsStoring());  // should not get here when loading from MemStream
  //
  //   // perform seek beyond the buffer
  //   if (pos >= Capacity())
  //   {
  //      Realloc(pos * 2);
  //   }
  //   m_ppos = m_pbegin + pos;
  //   return pos;
  //}

  inline void MemStream::Realloc(unsigned int size)
  {
    assert(m_bCapture);
    assert(size > Capacity());

    unsigned int pos = (unsigned int)(m_ppos - m_pbegin);
    unsigned int end = (unsigned int)(m_pend - m_pbegin);

    unsigned char* pdata = new unsigned char[size];
    memcpy(pdata, m_pbegin, end);
    memset(pdata + end, 0, size - end);
    delete[] m_pbegin;
    m_pbegin = pdata;

    m_ppos = m_pbegin + pos;
    m_pend = m_pbegin + size;
  }


  inline const char* MemStream::GetName() const
  {
    static std::string name = "<memory stream>";
    return name.c_str();
  }


  //--------------------------------------------------------------------------
  // read / write function implementation
  //--------------------------------------------------------------------------

  //inline void Write(Stream& dst, Stream& src)
  //{
  //   src.SetPos(0);
  //   unsigned char buffer[4096];
  //   unsigned int size = src.Size();
  //   while (size > 0)
  //   {
  //      unsigned int toWrite = size < unsigned int(sizeof(buffer)) ? size : unsigned int(sizeof(buffer)) ;
  //      unsigned int taken = src.RawRead(buffer, toWrite);  // `taken' may be != `toWrite' when reading SM_TEXT-stream
  //      dst.RawWrite(buffer, taken);
  //      size -= toWrite;
  //   }
  //}

  //inline void WriteQuotedString(Stream& out, const char* str)
  //{
  //   out << '"';                  // opening quote
  //   for (const char* s = str; *s; s++)
  //   {
  //      if (*s == '"')             // '"' -> '\"'
  //         out.Printf("\\\"");
  //      else if (*s == '\\')       // '\' -> '\\'
  //         out.Printf("\\\\");
  //      else
  //         out << *s;
  //   }
  //   out << '"';                  // closing quote
  //}


  inline Stream& getline(Stream& a, std::string& out, char delim)
  {
    out.clear();

    char buf[512];
    int i = 0;
    while (!a.eof())
    {
      char c;
      a >> c;
      if (c == delim)
        break;

      buf[i++] = c;
      if (i >= rgsizeof(buf))  // buffer overflowed
      {
        out.append(buf, i);
        i = 0;
      }
    }

    if (i)
    {
      out.append(buf, i);
    }
    return a;
  }

  inline Stream& getline(Stream& a, char* pOut, unsigned int MaxSize, char delim)
  {
    assert(MaxSize > 0);
    unsigned int i = 0;
    while (!a.eof())
    {
      char c;
      a >> c;
      if (c == delim)
        break;

      if (i < MaxSize)   // do not break loop even when buffer overflowed: read string until the end
        pOut[i] = c;
      i++;
    }
    if (i >= MaxSize)
      i = MaxSize-1;
    pOut[i] = 0;

    return a;
  }


  //inline void Write(Stream& a, std::string const& s )
  //{
  //   Write(a, static_cast<unsigned int>(s.size()));
  //   WriteArray(a, s.data(), static_cast<unsigned int>(s.size()), false);
  //}

  inline void Read(Stream& a, std::string& s )
  {
    // based on Read(Stream&, string&) function
    unsigned int sz;
    Read(a, sz );
    if (!sz)
    {
      s = EMPTY_STRING;
      return;
    }

    if (sz > a.Size() - a.GetFilePosition())    // reading too much data
    {
      a.SizeError();
    }
    else
    {
      s.resize(sz);
      assert(sz == s.size());
      char* ptr = const_cast<char*>(s.data());
      a.RawRead(ptr, sz);
    }
  }

} // namespace chunk_io
