#pragma once 

// stolen from Vis600 rtl_bstream.h


#include <map>
#include <set>

namespace chunk_io
{
  //////////////////////////////////////////////////////////////////////////


  class FileException 
    : public chunk::Exception
  {
  public:
    explicit FileException( std::string const& cause )
    {
      m_msg = cause;
    }
    FileException( std::string const& cause, std::string const& name )
    {
      std::string result = cause;
      result.append(" '");
      result.append(name);
      result.append("'");
      m_msg = result;
    }
    virtual const char* what() const
    {
      return m_msg.c_str();
    }

  protected:
    std::string m_msg;
  }; // class FileException 

#define ERR_TYPE(X, Y)                              \
  class X : public FileException                    \
  {                                                   \
  public:                                             \
  X()                                               \
  : FileException(Y)                              \
  {}                                                \
  explicit X(std::string const& name)                  \
  : FileException(Y, name)                        \
  {}                                                \
  inline static ttchar const* GetErrorDescription() \
  {                                                 \
  return Y;                                       \
  }                                                 \
  };


  ERR_TYPE(none,                 "Unknown error");
  ERR_TYPE(generic,              "Generic error");
  ERR_TYPE(fileNotFound,         "File not found");
  ERR_TYPE(badPath,              "Bad path");
  ERR_TYPE(tooManyOpenFiles,     "Too many opened files");
  ERR_TYPE(accessDenied,         "Access denied");
  ERR_TYPE(invalidFile,          "Invalid file");
  ERR_TYPE(removeCurrentDir,     "Remove current directory");
  ERR_TYPE(directoryFull,        "Directory is full");
  ERR_TYPE(badSeek,              "Bad seek");
  ERR_TYPE(hardIO,               "Hard IO error");
  ERR_TYPE(sharingViolation,     "Sharing violation");
  ERR_TYPE(lockViolation,        "Lock violation");
  ERR_TYPE(diskFull,             "Disk is full");
  ERR_TYPE(endOfFile,            "End of file");
  ERR_TYPE(fileOpenError,        "File open error");
  ERR_TYPE(fileCloseError,       "File close error");
  ERR_TYPE(readError,            "Read error");
  ERR_TYPE(writeError,           "Write error");
  ERR_TYPE(putCharBackError,     "Put char back error");
  ERR_TYPE(badFileName,          "Bad file name");
  ERR_TYPE(badFileHandle,        "Bad file handle");
  ERR_TYPE(writeProtectError,    "Write protect error");
  ERR_TYPE(wrongAccessType,      "Wring access type");
  ERR_TYPE(fileAlreadyExist,     "File already exist");
  ERR_TYPE(notEnoughMemoryError, "Not enough memory");
  ERR_TYPE(deviceNotReady,       "Device is not ready");
  ERR_TYPE(wrongDrive,           "Wrong device");
  ERR_TYPE(wrongDisk,            "Wrong disk");
  ERR_TYPE(lockedDrive,          "Drive is locked");
  ERR_TYPE(wrongFileFormat,      "Wrong file format");

#undef ERR_TYPE
  //--------------------------------------------------------------------------
  // base stream class
  //--------------------------------------------------------------------------

  enum
  {
    SM_READ     = 1 << 0,                         ///< open file for reading
    SM_WRITE    = 1 << 1,                         ///< open file for writing (will erase existing file)
    SM_APPEND   = 1 << 2,                         ///< open file for writing (will append data when file exists)
    SM_TEXT     = 1 << 3,                         ///< file uses MS-DOS text format on disk; have meaning for FileStream only
    SM_NOEXCEPT = 1 << 4                          ///< do not generate exceptions; can be used instead of SetUseExceptions(false)
  };


  class Stream
  {
  public:
    void           SetUseExceptions(bool b);      ///< enables / disables exception throwing when an error occurs (enabled by default)
    bool           IsUseExceptions() const;       ///< determines whether exceptions are thrown when an error occurs
    bool           IsOpen() const;                ///< determines whether the stream is open
    bool           IsBad() const;                 ///< determines the open stream is goods
    bool           Failed() const;                ///< determines whether the last IO operation failed
    bool           IsStoring() const;
    bool           IsLoading() const;
    unsigned int           Size() const;          ///< returns size of the stream
    unsigned int           GetFilePosition() const;          ///< current file position
    unsigned int SetPos(unsigned int pos);        ///< sets new reading position, can be very slow for some file streams (e.g. zipped or enscripted files)
    unsigned int SeekForward(unsigned int byteCount);
    unsigned int RawRead(void* pdst, unsigned int sz);
    //unsigned int RawWrite(const void* psrc, unsigned int sz);

    virtual const char* GetName() const = 0;

    // error generating functions
    void ReadError();
    void SeekError();
    void SizeError(const char* errMessage = NULL);
    void FormatError(const char* errMessage = NULL);

    void Printf(const char* format, ...);

    virtual ~Stream();
    //virtual void Flush();

    ////No function call was found
    virtual bool eof() const = 0;

  protected:
    Stream();

    // virtuals

    virtual unsigned int OnUnderflow(unsigned char* dst, unsigned int size) = 0; ///< SM_READ:  will read buffer from disk

    virtual void   OnOverflow() = 0;      ///< SM_WRITE: will flush buffer to disk

    //virtual unsigned int DoSetPos(unsigned int pos) = 0;
    // buffer interaction functions
    // gets pointer to application-level data and its size
    // returns number of processed application data bytes
    // can modify `size' when cannot process all data( not enough availBuf)
    unsigned int PutDataToBuffer(const unsigned char* src, unsigned int& size, unsigned int availBuf);
    unsigned int GetDataFromBuffer(unsigned char* dst, unsigned int& size, unsigned int availBuf);

    // stream state flags
    enum
    {
      SF_IS_OPEN                = 1 << 0,         /// Binary 1 
      SF_IS_BAD                 = 1 << 1,         /// Binary 10 
      SF_FAIL_BIT               = 1 << 2,         /// Binary 100 
      SF_DONT_USE_EXCEPTIONS    = 1 << 3,         /// Binary 1000   ///< do not throw exceptions on errors
      SF_MODE_WRITE             = 1 << 4,         /// Binary 10000 
      SF_MODE_TEXT              = 1 << 5          /// Binary 100000   ///< text stream, used for FileStream only

    };

    // stream data
    unsigned int        m_flags;          ///< set of stream state flags
    unsigned int      m_beginPos;         ///< offset of m_pbegin from the beginning of the file
    unsigned int      m_writenBytes;      ///< number of bytes writen to buffer (may be < m_size when seeking in-buffer)
    unsigned char*       m_pbegin;        ///< buffer begin
    unsigned char*       m_pend;          ///< buffer end
    unsigned char*       m_ppos;          ///< current reading / writing position
    unsigned int      m_size;             ///< stream size
    std::string    m_name;                ///< stream name

    inline void Clear();
    template<class T> void SetFailed(const char* errMessage, unsigned int k = SF_FAIL_BIT);

  private:
    Stream(Stream const&);
    Stream& operator=(Stream const&);
  };


  //--------------------------------------------------------------------------
  // buffered file stream class
  //--------------------------------------------------------------------------

  class File;

  class FileStream : public Stream
  {
  public:
    FileStream()
      : m_planeFile(NULL)
    {}
    virtual ~FileStream()
    {
      Close();
    }
    //virtual void Flush();

    FileStream(const char* filename, unsigned int mode, unsigned int unused = 0)
      : m_planeFile(NULL)
    {
      Open(filename, mode);
    }

    // Open() functions returns 'true' when successed, and 'false' when failed and exceptions
    // are disabled or throw exception (fileNotFound)
    inline bool Open(const char* filename, unsigned int mode, unsigned int unused = 0);
    inline bool Open(const std::string& filename, unsigned int mode, unsigned int unused = 0)
    {
      return Open(filename.c_str(), mode);
    }

    void Close();
    virtual bool eof() const;

    virtual const char* GetName() const;

  protected:
    // Stream overrides
    virtual unsigned int OnUnderflow(unsigned char* dst, unsigned int size);
    virtual void   OnOverflow();
    //virtual unsigned int DoSetPos(unsigned int pos);

    //void   WriteBuffer();
    //unsigned int Seek(unsigned int a, bool seekForward);

    static const unsigned int BUFFER_SIZE = 32768;
    File*       m_planeFile;                ///< the file
    unsigned char        m_buff[BUFFER_SIZE];    ///< data buffer
  };


  //--------------------------------------------------------------------------



  //--------------------------------------------------------------------------
  // memory stream class
  //--------------------------------------------------------------------------

  class MemStream : public Stream
  {
  public:
    ////No function call was found
    //MemStream();

    ////No function call was found
    //MemStream(void* pdst,       unsigned int sz, unsigned int mode);    ///< uses user buffer, any mode

    MemStream(void const* pdst, unsigned int sz, unsigned int mode);    ///< uses user buffer, mode must be SM_READ

    MemStream(unsigned int mode, unsigned int initSize = 0);    ///< allocates own buffer, any mode; 'initSize' for writing means initial capacity

    ////No function call was found
    //MemStream(unsigned int mode, Stream& src);                    ///< allocates own buffer and copies whole Stream to it; any mode

    ////No function call was found
    //~MemStream();

    void  Create(void* pdst, unsigned int sz, unsigned int mode);
    void  Create(void const* pdst, unsigned int sz, unsigned int mode);
    void  Create(unsigned int mode, unsigned int initSize = 0);
    void  Create(unsigned int mode, Stream& src);

    ////No function call was found
    //void          Reset();

    void          Destroy();

    unsigned int        Capacity() const;

    void          Resize(unsigned int sz);           ///< does nothing for non-captured buffers; sets capacity for writing buffer

    ////No function call was found
    //unsigned char*         UnattachBuffer();            ///< gives us ownership of the buffer, user must delete it himself

    ////No function call was found
    //void          ChangeMode(unsigned int mode);

    ////No function call was found
    //const unsigned char*   Data() const;
    unsigned char*         Data();

    virtual bool eof() const;

    virtual const char* GetName() const;

  //protected:

    virtual unsigned int OnUnderflow(unsigned char* dst, unsigned int size);

    virtual void   OnOverflow();
    //virtual unsigned int DoSetPos(unsigned int pos);

    void  Realloc(unsigned int sz);
    void  DoClear();
    bool m_bCapture;      ///< buffer is freed by Destroy and can grow
  };


  //--------------------------------------------------------------------------
  // read / write functions
  //--------------------------------------------------------------------------

#define DEFINE_RW_METHODS_RAW(classname) \
  inline void Read (Stream& a, classname& out)      { a.RawRead (&out, sizeof(classname)); } \
  //inline void Write(Stream& a, const classname& in) { a.RawWrite(&in,  sizeof(classname)); }

  DEFINE_RW_METHODS_RAW(bool);
  DEFINE_RW_METHODS_RAW(char);
  DEFINE_RW_METHODS_RAW(unsigned char);
  DEFINE_RW_METHODS_RAW(short);
  DEFINE_RW_METHODS_RAW(unsigned short);
  DEFINE_RW_METHODS_RAW(int);
  DEFINE_RW_METHODS_RAW(unsigned int);
  //DEFINE_RW_METHODS_RAW(int64);
  //DEFINE_RW_METHODS_RAW(uint64);
  DEFINE_RW_METHODS_RAW(float);
  DEFINE_RW_METHODS_RAW(time_t);
  DEFINE_RW_METHODS_RAW(double);

  // undefined template class used
  // to generate compile-time error
  // for types that does not support reading / writing
  template<class T> class UnsupportedTypeError;

  ////No function call was found
  //// disable pointer serialization: when trying to Write() pointer,
  //// compiler will perform Write(Stream, bool) ...
  //template<class T> inline void Read (Stream& a, T* t)       { UnsupportedTypeError<T*> error; }
  //template<class T> inline void Write(Stream& a, const T* t) { UnsupportedTypeError<T*> error; }


  /// Copy (append) contents of whole 'src' to 'dst' stream
  /// Initial position of source stream does not matters.
  /// After function, source stream will be set to the end-of-file position.
  //void Write(Stream& dst, Stream& src);

  Stream& getline(Stream& a, std::string& out, char delim = '\n');
  Stream& getline(Stream& a, char* pOut, unsigned int MaxSize, char delim = '\n');


  ////No function call was found
  //inline void ReadStreamDataToString(Stream& a, std::string& out)
  //{
  //  unsigned int count = a.Size() - a.GetFilePosition();
  //  out.resize(count);
  //  a.RawRead(const_cast<char*>(out.data()), count);
  //}
  
  ////No function call was found
  //inline void ReadStreamDataToStringArray(Stream& a, unsigned char** out, unsigned int* puiSize = 0 )
  //{
  //  unsigned int count = a.Size() - a.GetFilePosition();
  //  *out = new unsigned char[count+1];
  //  a.RawRead(*out, count);
  //  if( puiSize )
  //    *puiSize = count;
  //  (*out)[count] = '\0';
  //}

  //--------------------------------------------------------------------------
  // array reading function
  //--------------------------------------------------------------------------

  template<class T>
  inline void ReadArray(Stream& a, T* ptr, unsigned int count, bool sizeCheck = true)
  {
    if(sizeCheck)
    {
      unsigned int scnt;
      Read(a, scnt);
      if(scnt != count)
      {
        a.SizeError();
        return;
      }
    }
    for(unsigned int i = 0; i < count; ++i)
      Read(a, ptr[i]);
    //a.RawRead(ptr, sizeof(T) * count);
  }


  ////No function call was found
  //template<class Key, class Type, class Traits, class Alloc>
  //inline void Read(Stream& a, std::map<Key, Type, Traits, Alloc>& t)
  //{
  //  t.clear();
  //  unsigned int sz;
  //  Read(a, sz);

  //  for(unsigned int i = 0; i < sz; ++i)
  //  {
  //    std::pair<std::map<Key, Type, Traits, Alloc>::key_type, std::map<Key, Type, Traits, Alloc>::mapped_type> obj;
  //    Read(a, obj);
  //    t.insert(obj);
  //  }
  //}

  ////No function call was found
  //template<class T>
  //inline void Read(Stream& a, std::set<T>& t )
  //{
  //  t.clear();
  //  unsigned int sz;
  //  Read(a, sz, pl);

  //  for(unsigned int i=0; i < sz; ++i)
  //  {
  //    T v;
  //    Read(a, v, pl);
  //    t.insert(v);
  //  }
  //}


  ////No function call was found
  //// same as Read(..., platform), but can use T without correct serializer
  //template<class T>
  //inline void Read(Stream& a, std::vector<T>& t)
  //{
  //  unsigned int s;
  //  Read(a, s);

  //  if (s > t.max_size())
  //  {
  //    a.ReadError();
  //    return;
  //  }

  //  t.resize(s);
  //  for (std::vector<T>::iterator iter = t.begin(); iter != t.end(); ++iter)
  //    Read(a, *iter);
  //}

  ////No function call was found
  // template<class Key, class Type, class Traits, class Alloc, class Base>
  // inline void Read(Stream& a, rtl::vmap<Key, Type, Traits, Alloc, Base>& t )
  // {
  //   t.clear();
  //   unsigned int sz;
  //   Read(a, sz);
  // 
  //   for(unsigned int i = 0; i < sz; ++i)
  //   {
  //     rtl::vmap<Key, Type, Traits, Alloc, Base>::value_type obj;
  //     Read(a, obj);
  //     t.insert(obj);
  //   }
  // }

  ////No function call was found
  // template<class Key,class Traits, class Alloc, class Base>
  // inline void Read(Stream& a, rtl::vset<Key, Traits, Alloc, Base>& t )
  // {
  //   t.clear();
  //   unsigned int sz;
  //   Read(a, sz);
  // 
  //   for(unsigned int i = 0; i < sz; ++i)
  //   {
  //     typename rtl::vset<Key, Traits, Alloc, Base>::value_type obj;
  //     Read(a, obj);
  //     t.insert(obj);
  //   }
  // }

  inline void ReadSZ(Stream& a, char* buf, unsigned int bufSize)
  {
    getline(a, buf, bufSize, 0);
  }

  inline void ReadSZ(Stream& a, std::string& s)
  {
    getline(a, s, 0);
  }

  ////No function call was found
  //template<class T1, class T2>
  //inline void Read(Stream& a, std::pair<T1, T2>& t)
  //{
  //  Read(a, t.first);
  //  Read(a, t.second);
  //}

  //--------------------------------------------------------------------------
  // std::stream-like I/O operators
  //--------------------------------------------------------------------------

  //template<class T> inline Stream& operator << (Stream& out, const T& t)
  //{
  //  Write(out, t);
  //  return out;
  //}

  template<class T> inline Stream& operator >> (Stream& in, T& t)
  {
    Read(in, t);
    return in;
  }


  //--------------------------------------------------------------------------
  // serialize functions
  //--------------------------------------------------------------------------

  template<class T>
  inline void Serialize(Stream& a, T& t)
  {
    if(a.IsStoring())
    {
      //Write(a, t);
    }
    else
    {
      Read(a, t);
    }
  }
  template<class T>
  inline void SerializeArray(Stream& a, T* ptr, unsigned int count, bool sizeCheck = true)
  {
    if(a.IsStoring())
    {
      //WriteArray(a, ptr, count, sizeCheck);
    }
    else
    {
      ReadArray(a, ptr, count, sizeCheck);
    }
  }


  //--------------------------------------------------------------------------
  // set / read checkpoint
  // when reading, if read checkpoint value isn't equal
  // to the specified, fail bit is set and 'ArchiveFormatError' exception
  // raised (if exception are enabled)
  //--------------------------------------------------------------------------

  //template<class T>
  //inline void CheckPoint(Stream& a, T const& val, const char* errMessage = NULL)
  //{
  //  if(a.IsStoring())
  //  {
  //    //Write(a, val);
  //  }
  //  else
  //  {
  //    T k;
  //    Read(a, k);
  //    if(k != val)
  //    {
  //      if(errMessage)
  //      {
  //        a.FormatError(errMessage);
  //      }
  //      else
  //      {
  //        const std::string v = rtl::ToString<T>(val);
  //        const std::string msg = rtl::fmt("check point failed: %s expected",v.c_str());
  //        a.FormatError(msg.c_str());
  //      }
  //    }
  //  }
  //}


  template<class T>
  inline void CheckPoint(Stream& a, T t[], const char* errMessage = NULL)
  {
    UnsupportedTypeError<T*> error;
  }

#ifndef SERIALIZE_ARRAY_SIZE
#define SERIALIZE_ARRAY_SIZE(STREAM, SIZE)                  \
  {                                                           \
  unsigned int s;                                                 \
  io::Serialize(STREAM, s);                                 \
  assert(s == SIZE);                                    \
  }
#endif

#define CHECKED_SERIALIZE(stream, arg)                       \
  {                                                            \
  io::Serialize((stream), (arg));                            \
  if((stream).Failed())                                      \
  {                                                          \
  g_err << "Error while serializing occurred!" << endl;    \
  return false;                                            \
  }                                                          \
  }

#ifndef CHECKED_SERIALIZE_ARRAY
#define CHECKED_SERIALIZE_ARRAY(stream, arg1, arg2)          \
  {                                                            \
  io::SerializeArray((stream), (arg1), (arg2));              \
  if((stream).Failed())                                      \
  {                                                          \
  g_err << "Error while serializing occurred!" << endl;    \
  return false;                                            \
  }                                                          \
  }
#endif

#define CHECKED_SERIALIZE_ARRAY_EX(stream, arg1, arg2, arg3) \
  {                                                            \
  io::SerializeArray((stream), (arg1), (arg2), (arg3));      \
  if((stream).Failed())                                      \
  {                                                          \
  g_err << "Error while serializing occurred!" << endl;    \
  return false;                                            \
  }                                                          \
  }

#ifndef CHECKED_SERIALIZE_ARRAY_SIZE
#define CHECKED_SERIALIZE_ARRAY_SIZE(STREAM, SIZE)           \
  {                                                            \
  unsigned int s;                                                  \
  io::Serialize(STREAM, s);                                  \
  if(STREAM.Failed())                                        \
  {                                                          \
  g_err << "Error while serializing occurred!" << endl;    \
  return false;                                            \
  }                                                          \
  assert(s == SIZE);                                     \
  }
#endif


  //--------------------------------------------------------------------------
  // endian staff - need refactoring

  // std::string is stored in the array format, with preceding size, and without terminating NULL character
  //void Write(Stream& a, std::string const& s );
  void Read(Stream& a, std::string& s );
  /*
  // serializer for scalar type
  #define PLATFORM_SERIALIZER(type)                                   \
  inline void Write(Stream& a, const type& s )  \
  {                                                                   \
  a.RawWrite(&s, sizeof(type));                                  \
  }                                                                   \
  inline void Read(Stream& a, type& s)         \
  {                                                                   \
  a.RawRead(&s, sizeof(type));                                   \
  }
  */
  // serializer for types, compound of few floats
#ifndef HACKY_SERIALIZER
#define HACKY_SERIALIZER(type)                                      \
  /*inline void Write(Stream& a, const type& s)  \
  {                                                                   \
  unsigned int* data = (unsigned int*)&s;                                       \
  for (unsigned int i = 0; i < sizeof(type) / sizeof(unsigned int); i++, data++)  \
  Write(a, *data);                                             \
  }  */                                                                 \
  inline void Read(Stream& a, type& s)         \
  {                                                                   \
  unsigned int* data = (unsigned int*)&s;                                       \
  for (unsigned int i = 0; i < sizeof(type) / sizeof(unsigned int); i++, data++)  \
  Read(a, *data);                                              \
  }
#endif

} // namespace chunk_io

#include "chunk_bstream.inl"
