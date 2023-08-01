#ifndef _CHUNK_INL_
#define _CHUNK_INL_
#define E_FAIL  0x80004005
//#typedef uint8_t byte
#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)
#include <assert.h>
namespace chunk
{
  inline bool Chunk::isBadNode(const ChunkNode* node) const {
    return (node == getBadNode());
  }
  inline bool Chunk::isBadItem(const ChunkItem* item) const{
    return (item == getBadItem());
  }
  inline bool ChunkNode::isBad() const{
    return m_next == this;
  }
  inline bool ChunkNode::isGood() const{
    return m_next != this;
  }
  inline bool ChunkItem::isBad() const{
    return m_next == this;
  }
  inline bool ChunkItem::isGood() const{
    return m_next != this;
  }
  inline bool ChunkNode::isEmpty() const{
    return GetFirstChildNode()->isBad() && GetFirstChildItem()->isBad();
  }
  inline bool ChunkNode::IsUserEditable() const{
    return m_browsAccess != baConst && m_browsAccess != baHidden;
  }
  inline bool ChunkNode::isBrowsList() const{
    return m_browsList;
  }
  inline ChunkNode* ChunkNode::SetBrowsList(bool isList){
    m_browsList = isList;
    return this;
  }
  inline bool ChunkItem::IsUserEditable() const{
    return m_browsAccess != baConst && m_browsAccess != baHidden;
  }
  ///////////////////////////////////////////////////////////////////////////////
  inline void Variant::Set(unsigned char value)
  {
    switch (GetType())
    {
    case chByte:
      m_chByte = value;
      break;
    case chInt32:
      m_chInt32 = value;
      break;
    case chInt64:
      m_chInt64 = value;
      break;
    case chFloat:
      m_chFloat = value;
      break;
    case chString:
      m_chString = chunk_fmt::IntToStr(value);
      break;
    }
  }
  inline unsigned char Variant::GetByte() const
  {
    switch (GetType())
    {
    case chByte:
      return m_chByte;
    case chInt32:
      return (unsigned char)m_chInt32;
    case chInt64:
      return (unsigned char)m_chInt64;
    case chFloat:
      return (unsigned char)m_chFloat;
    case chString:
      return (unsigned char)chunk_fmt::StrToInt(m_chString.c_str());
    }
    return 0;
  }
  inline void Variant::Set(int32 value)
  {
    switch (GetType())
    {
    case chByte:
      m_chByte = (unsigned char)value;
      break;
    case chInt32:
      m_chInt32 = value;
      break;
    case chInt64:
      m_chInt64 = (int64)value;
      break;
    case chFloat:
      m_chFloat = (float)value;
      break;
    case chString:
      m_chString = chunk_fmt::Int32ToStr(value);
      break;
    }
  }
  inline int32 Variant::GetInt32(void) const
  {
    switch (GetType())
    {
    case chByte:
      return (int32)m_chByte;
    case chInt32:
      return (int32)m_chInt32;
    case chInt64:
      return (int32)m_chInt64;
    case chFloat:
      return (int32)m_chFloat;
    case chString:
      return chunk_fmt::StrToInt32(m_chString.c_str());
    }
    return 0;
  }
  inline void Variant::Set(int64 value)
  {
    switch (GetType())
    {
    case chByte:
      m_chByte = (unsigned char)value;
      break;
    case chInt32:
      m_chInt32 = (int32)value;
      break;
    case chInt64:
      m_chInt64 = value;
      break;
    case chFloat:
      m_chFloat = (float)value;
      break;
    case chString:
      m_chString = chunk_fmt::Int64ToStr(value);
      break;
    }
  }
  inline int64 Variant::GetInt64(void) const
  {
    switch (GetType())
    {
    case chByte:
      return (int64)m_chByte;
    case chInt32:
      return (int64)m_chInt32;
    case chInt64:
      return m_chInt64;
    case chFloat:
      return (int64)m_chFloat;
    }
    return 0;
  }
  inline void Variant::Set(float value)
  {
    switch (GetType())
    {
    case chByte:
      m_chByte = (unsigned char)value;
      break;
    case chInt32:
      m_chInt32 = (int32)value;
      break;
    case chInt64:
      m_chInt64 = (int64)value;
      break;
    case chFloat:
      m_chFloat = value;
      break;
    case chString:
      m_chString = chunk_fmt::FloatToStr(value);
      break;
    }
  }
  inline float Variant::GetFloat(void) const
  {
    switch (GetType())
    {
    case chByte:
      return (float)m_chByte;
    case chInt32:
      return (float)m_chInt32;
    case chInt64:
      return (float)m_chInt64;
    case chFloat:
      return m_chFloat;
    case chString:
      return chunk_fmt::StrToFloat(m_chString.c_str());
    }
    return 0;
  }
  inline void Variant::Set(const std::string &str)
  {
    switch (GetType())
    {
    case chByte:
      m_chByte = (unsigned char)chunk_fmt::StrToInt(str.c_str());
      break;
    case chInt32:
      m_chInt32 = chunk_fmt::StrToInt32(str.c_str());
      break;
    case chFloat:
      m_chFloat = chunk_fmt::StrToFloat(str.c_str());
      break;
    case chString:
      m_chString = str;
      break;
    }
  }
  inline const std::string Variant::GetString(void) const
  {
    switch (GetType())
    {
    case chByte:
      return chunk_fmt::IntToStr(m_chByte);
    case chInt32:
      return chunk_fmt::Int32ToStr(m_chInt32);
    case chInt64:
      return chunk_fmt::Int64ToStr(m_chInt64);
    case chFloat:
      return chunk_fmt::FloatToStr(m_chFloat);
    case chString:
      return m_chString;
    }
    return "";
  }
  inline const char* Variant::GetStringSZ(void) const
  {
    return m_chString.c_str();
  }


}

#define MAX_NODE_NAME       512
#define MAX_ITEM_NAME       512
#define MAX_BROWSE_TYPE     256
#define MAX_BROWSE_COMMENT  512
#define MAX_TYPE_NAME       16      // max of typeNames[]
#define MAX_ACCESS_NAME     16      // max of accessNames[]
#define MAX_VALUE_LEN       64      // numeric value
#define MAX_STR_VALUE_LEN   65536   // string value

#define BEGIN_BLOCK         do{
#define END_BLOCK           }while(0);

//--------------------------------------------------------------------------

#define CHECK_STREAM(S)     \
{                           \
  if((S).Failed())          \
  return false;           \
}    

#define CHECK_STREAM_EX(S)  \
{                           \
  if((S).Failed())          \
  return rr_IOFailed;     \
}

namespace chunk
{

  inline const char* itemTypeToString( ChunkItemType t )
  {
    // corresponds to ChunkItemType
    static const char* typeNames[]   = { "uchar", "int32", "int64", "float", "string" };
    assert(chLast == rgsizeof(typeNames));
    assert( (size_t)t < rgsizeof(typeNames));
    return typeNames[ t ];
  }

  // corresponds to ChunkBrowsAccess
  inline const char* accessTypeToString( ChunkBrowsAccess t )
  {
    // corresponds to ChunkItemType
    static const char* accessNames[] = { "hidden", "const", "public", "likeParent"   };
    assert(baLast == rgsizeof(accessNames));
    assert( (size_t)t < rgsizeof(accessNames));
    return accessNames[ t ];
  }

  // найти сточку в массиве и вернуть ее номер
  inline int findNameInArray(const char** arr, int arrSize, const char* str)
  {
    for (int i = 0; i < arrSize; i++)
      if (!stricmp(arr[i], str))
        return i;
    return arrSize;
  }

  inline ChunkItemType stringToItemType( const char * str )
  {
    // corresponds to ChunkItemType
    static const char* typeNames[]   = { "uchar", "int32", "int64", "float", "string" };
    return ChunkItemType( findNameInArray(typeNames, chLast, str) );
  }

  inline ChunkBrowsAccess stringToAccessType( const char* str )
  {
    // corresponds to ChunkItemType
    static const char* accessNames[] = { "hidden", "const", "public", "likeParent"   };
    return ChunkBrowsAccess( findNameInArray(accessNames, baLast, str) );
  }

  inline const char* NameDelims( )
  {
    static const char NAME_DELIMS[] = "= \t\r\n#[(<{";
    return NAME_DELIMS;
  }

  inline void StepBack(chunk_io::Stream& in, unsigned int count = 1) //?? integrate functionality to chunk_io::Stream ??
  {
    in.SetPos(in.GetFilePosition() - count);
  }



  class ChunkException : public Exception
  {
  public:
    ChunkException(const std::string& what)
      : Exception()
      , m_what(what)
    {} // Пусто...
    virtual const char* what(void) const{
      return m_what.c_str();
    }
  private:
    std::string m_what;
  };


  inline void Chunk::ReportError(const char* fmt, ...) const
  {

    char buffer[1024];
    va_list	argptr;
    va_start(argptr, fmt);
    chunk_fmt::vsprintf(ARRAY_ARG(buffer), fmt, argptr);
    va_end(argptr);

    //  g_wrn.Printf("Chunk: (%08X), top: \"%s\": %s\n", *(reinterpret_cast<const uint_ptr*>(this)), GetTopNode()->GetName().c_str(), buffer);
  }

  inline void Chunk::ReportBadType(const ChunkItem* where) const
  {
    ReportError("illegal Item access.\nNode: %s\nItem: (%s)%s",
    where->m_parent->GetFullPath().c_str(),itemTypeToString(where->GetType()),where->GetName().c_str());
  }

  // плохой формат файла
  inline void Chunk::ReportBadFileFormat(chunk_io::Stream& in, int line) const
  {
    ReportError("syntax error in %s%s",in.GetName(),(line >= 0) ? chunk_fmt::va("(%d)", line) : "");
  }


  static void ReadString(chunk_io::Stream& in, char* buffer, unsigned int bufSize, const char *pszDelimiters)
  {
    unsigned int i = 0;
    buffer[0] = 0;

    while (true)
    {
      char c;
      if (in.RawRead(&c, sizeof(char)) == 0)
      {
        // should not happen, but if so - prevent infinite loop
        buffer[0] = 0;
        return;
      }
      if (c == '\r')
        continue;           // ignore '\r'
      if (strchr(pszDelimiters, c))  // is it delimiter ?
      {
        StepBack(in);
        c = 0;
      }
      // put character
      if (i < bufSize)
        buffer[i] = c;      // put char
      i++;
      if (c == 0)           // end of string
        return;
    }
    if (i >= bufSize)
    {
      buffer[bufSize-1] = 0;
    }
  }


  inline std::string WiseAllocateString(const char *str)
  {
    // check for digit and delimiter chars
    for (const char *s = str; *s; s++)
    {
      if ((*s >= '0' && *s <= '9') || *s == '/' || *s == '\\')
      {
        if (s[1] == 0) continue;  // allow 1 digit at string end
        return std::string(str);  // compound string
      }
    }
    // simple string, allocate in pool
    return std::string(str);
  }


  ///////////////////////////////////////////////////////////////////////////////
  //  ChunkItem Area                                                 =BEGIN= //
  //                                                                           //

  const int32  MIN_STRING = 0;
  const int32  MAX_STRING = 1024;

  inline ChunkItem::ChunkItem(const char* name, ChunkItemType type, ChunkNode* parent)
    : m_name(name)
    , m_parent(parent)
  {
    InitDefaults(type);
  }

  inline void ChunkItem::ReInit(const char* name, ChunkItemType type, ChunkNode* parent)
  {
    m_name   = name;
    m_parent = parent;
    InitDefaults(type);
  }

  inline ChunkItem* ChunkItem::SetBrowsType(const char* typeName)
  {
    m_browsType = typeName;
    return this;
  }

  inline void ChunkItem::InitDefaults(ChunkItemType type)
  {
    SetType(type);

    // Устанавливаем батин уровень доступа
    m_browsAccess = baLikeParent;
    m_prev = m_next = m_parent->m_owner->getBadItem();

    // Заполняем дефолтовый диапозон
    if(type==chInt32 ) {
      m_minInt32 = MIN_INT32;
      m_maxInt32 = MAX_INT32;
      m_stepInt32=0;
    } else if(type==chFloat ) {
      m_minFloat = MIN_FLOAT;
      m_maxFloat = MAX_FLOAT;
      m_stepFloat=0;
    } else if(type==chString ) {
      m_minInt32 = MIN_STRING;
      m_maxInt32 = MAX_STRING;
    } else if(type==chByte ) {
      m_minByte = MIN_BYTE;
      m_maxByte = MAX_BYTE;
      m_stepByte=0;
    } else if(type==chInt64 ) {
      m_minInt64 = MIN_INT64;
      m_maxInt64 = MAX_INT64;
      m_stepInt64=0;
    }
  }

  inline std::string ChunkItem::GetFullPath() const
  {
    std::string res = GetFullPath();
    res.append("/");
    res.append(GetName());
    return res;
  }

  inline bool ChunkItem::AddUser(ChunkUser* pUser )
  {
    return GetParent()->GetOwner()->AddUser( pUser, this );
  }

  inline bool ChunkItem::RemoveUser(ChunkUser* pUser )
  {
    return GetParent()->GetOwner()->RemoveUser( pUser, this );
  }

  inline bool ChunkItem::Set(unsigned char value, bool notifyUser)
  {
    if (isBad())
      return false;
    if( notifyUser && !GetParent()->GetOwner()->NotifyItemChanging( this, value) )
      return false;//Changing is cancelled by one of users

    Variant vOld=Get();
    __super::Set(value);

    if( notifyUser )
    {
      ////Notify user of chunk
      //if ((m_parent->m_owner->m_user))
      //  if(FAILED(m_parent->m_owner->m_user->OnItemChange(this, ChunkUser::acChange, vOld)))
      //  {
      //    __super::Set(vOld);
      //    return false;//Обломались
      //  }
      //Notify users of nodes/items
      GetParent()->GetOwner()->NotifyItemChanged( this, vOld );
    }

    return true;
  }

  inline unsigned char ChunkItem::GetByte() const
  {
    if (GetType() != chByte)
      m_parent->m_owner->ReportBadType(this);

    return __super::GetByte();
  }

  inline bool ChunkItem::Set(int32 value, bool notifyUser)
  {
    if (isBad())
      return false;
    if( notifyUser && !GetParent()->GetOwner()->NotifyItemChanging( this, value))
      return false;//Cahnging is cancelled by one of users

    Variant vOld=Get();
    __super::Set(value);

    if( notifyUser )
    {
      ////Notify user of chunk
      //if ((m_parent->m_owner->m_user))
      //  if(FAILED(m_parent->m_owner->m_user->OnItemChange(this, ChunkUser::acChange, vOld)))
      //  {
      //    __super::Set(vOld);
      //    return false;//Обломались
      //  }
      //Notify users of nodes/items
      GetParent()->GetOwner()->NotifyItemChanged( this, vOld );
    }

    return true;
  }

  inline int32 ChunkItem::GetInt32() const
  {
    if (GetType() != chInt32)
      m_parent->m_owner->ReportBadType(this);

    return __super::GetInt32();
  }

  inline bool ChunkItem::Set(int64 value, bool notifyUser)
  {
    if (isBad())
      return false;
    if( notifyUser && !GetParent()->GetOwner()->NotifyItemChanging( this, value))
      return false;//Cahnging is cancelled by one of users

    Variant vOld=Get();
    __super::Set(value);

    if( notifyUser )
    {
      ////Notify user of chunk
      //if ((m_parent->m_owner->m_user))
      //  if(FAILED(m_parent->m_owner->m_user->OnItemChange(this, ChunkUser::acChange, vOld)))
      //  {
      //    __super::Set(vOld);
      //    return false;//Обломались
      //  }
      //Notify users of nodes/items
      GetParent()->GetOwner()->NotifyItemChanged( this, vOld );
    }

    return true;
  }

  inline int64 ChunkItem::GetInt64(void) const
  {
    if (GetType() != chInt64)
      m_parent->m_owner->ReportBadType(this);

    return __super::GetInt64();
  }

  inline bool ChunkItem::Set(float value, bool notifyUser)
  {
    if (isBad())
      return false;
    if( notifyUser && !GetParent()->GetOwner()->NotifyItemChanging( this, value))
      return false;//Cahnging is cancelled by one of users

    Variant vOld=Get();
    __super::Set(value);

    if( notifyUser )
    {
      ////Notify user of chunk
      //if ((m_parent->m_owner->m_user))
      //if(FAILED(m_parent->m_owner->m_user->OnItemChange(this, ChunkUser::acChange, vOld)))
      //{
      //  __super::Set(vOld);
      //  return false;//Обломались
      //}
      //Notify users of nodes/items
      GetParent()->GetOwner()->NotifyItemChanged( this, vOld );
    }

    return true;
  }

  inline float ChunkItem::GetFloat(void) const
  {
    if (GetType() != chFloat)
      m_parent->m_owner->ReportBadType(this);

    return __super::GetFloat();
  }

  inline bool ChunkItem::Set(const std::string &str, bool notifyUser)
  {
    if (isBad())
      return false;
    if( notifyUser && !GetParent()->GetOwner()->NotifyItemChanging( this, str))
      return false;//Cahnging is cancelled by one of users

    Variant vOld=Get();
    __super::Set(str);

    if( notifyUser )
    {
      ////Notify user of chunk
      //if ((m_parent->m_owner->m_user))
      //  if(FAILED(m_parent->m_owner->m_user->OnItemChange(this, ChunkUser::acChange, vOld)))
      //  {
      //    __super::Set(vOld);
      //    return false;//Обломались
      //  }
      //Notify users of nodes/items
      GetParent()->GetOwner()->NotifyItemChanged( this, vOld );
    }

    return true;
  }

  inline bool ChunkItem::Set(const std::wstring &str, bool notifyUser)
  {
    return Set( str, notifyUser );
  }

  inline const char* ChunkItem::GetString() const
  {
    if (GetType() != chString)
      m_parent->m_owner->ReportBadType(this);

    return __super::GetStringSZ();
  }

  inline bool ChunkItem::Set(const Variant& value, bool bNotifyUser)
  {
    if (isBad())
      return false;
    if( bNotifyUser && !GetParent()->GetOwner()->NotifyItemChanging( this, value))
      return false;//Cahnging is cancelled by one of users

    Variant vOld=Get();
    __super::Set(value);

    if( bNotifyUser )
    {
      ////Notify user of chunk
      //if ((m_parent->m_owner->m_user))
      //  if(FAILED(m_parent->m_owner->m_user->OnItemChange(this, ChunkUser::acChange, vOld)))
      //  {
      //    __super::Set(vOld);
      //    return false;//Обломались
      //  }
      //Notify users of nodes/items
      GetParent()->GetOwner()->NotifyItemChanged( this, vOld );
    }
    return true;
  };

  inline Variant ChunkItem::Get() const{
    if(isBad())
      m_parent->m_owner->ReportBadType(this);

    return *this;
  }


  inline void ChunkItem::unregMeNow()
  {
    ChunkItem* bad_item = m_parent->m_owner->getBadItem();

    //left
    if(m_prev == bad_item)
      m_parent->m_first_child_item = m_next;
    else
      m_prev->m_next = m_next;
    //right
    if(m_next == bad_item)
      m_parent->m_last_child_item = m_prev;
    else
      m_next->m_prev = m_prev;
  }

  inline void ChunkItem::regMeNow(ChunkNode* parent)
  {
    ChunkItem* bad_item = parent->m_owner->getBadItem();
    if(parent->m_first_child_item == bad_item){
      parent->m_first_child_item = this;
      parent->m_last_child_item = this;
      m_prev = m_next = bad_item;
    }else{
      m_prev = parent->m_last_child_item;
      m_next = parent->m_last_child_item->m_next;
      parent->m_last_child_item->m_next = this;
      parent->m_last_child_item = this;
    }
  }

  //////////////////////////////
  // Инфа для браузера пропертей

  inline void ChunkItem::GetByteRange(unsigned char& min, unsigned char& max) const
  {
    if (GetType() != chByte)
      m_parent->m_owner->ReportBadType(this);
    min = m_minByte;
    max = m_maxByte;
  }

  inline ChunkItem* ChunkItem::SetByteRange(unsigned char min, unsigned char max)
  {
    if (GetType() != chByte)
      m_parent->m_owner->ReportBadType(this);
    m_minByte = min;
    m_maxByte = max;
    return this;
  }

  inline void ChunkItem::GetInt32Range(int32& min, int32& max) const
  {
    if (GetType() != chInt32)
      m_parent->m_owner->ReportBadType(this);
    min = m_minInt32;
    max = m_maxInt32;
  }

  inline ChunkItem* ChunkItem::SetInt32Range(int32 min, int32 max)
  {
    if (GetType() != chInt32)
      m_parent->m_owner->ReportBadType(this);
    m_minInt32 = min;
    m_maxInt32 = max;
    return this;
  }

  inline void ChunkItem::GetInt64Range(int64& min, int64& max) const
  {
    if (GetType() != chInt64)
      m_parent->m_owner->ReportBadType(this);
    min = m_minInt64;
    max = m_maxInt64;
  }

  inline ChunkItem* ChunkItem::SetInt64Range(int64 min, int64 max)
  {
    if (GetType() != chInt64)
      m_parent->m_owner->ReportBadType(this);
    m_minInt64 = min;
    m_maxInt64 = max;
    return this;
  }

  inline void ChunkItem::GetFloatRange(float& min, float& max) const
  {
    if (GetType() != chFloat)
      m_parent->m_owner->ReportBadType(this);
    min = m_minFloat;
    max = m_maxFloat;
  }

  inline ChunkItem* ChunkItem::SetFloatRange(float min, float max)
  {
    if (GetType() != chFloat)
      m_parent->m_owner->ReportBadType(this);
    m_minFloat = min;
    m_maxFloat = max;
    return this;
  }

  inline void ChunkItem::GetStringRange(int32& min, int32& max) const
  {
    if (GetType() != chString)
      m_parent->m_owner->ReportBadType(this);
    min = m_minString;
    max = m_maxString;
  }

  inline ChunkItem* ChunkItem::SetStringRange(int32 min, int32 max)
  {
    if (GetType() != chString)
      m_parent->m_owner->ReportBadType(this);
    m_minString = min;
    m_maxString = max;
    return this;
  }
  //C| - by Centurn
  inline void ChunkItem::GetByteStep(unsigned char& step) const
  {
    if (GetType() != chByte)
      m_parent->m_owner->ReportBadType(this);
    step = m_stepByte;
  }

  inline ChunkItem* ChunkItem::SetByteStep(unsigned char step)
  {
    if (GetType() != chByte)
      m_parent->m_owner->ReportBadType(this);
    m_stepByte=step;
    return this;
  }

  inline void ChunkItem::GetInt32Step(int32& step) const
  {
    if (GetType() != chInt32)
      m_parent->m_owner->ReportBadType(this);
    step = m_stepInt32;
  }

  inline ChunkItem* ChunkItem::SetInt32Step(int32 step)
  {
    if (GetType() != chInt32)
      m_parent->m_owner->ReportBadType(this);
    m_stepInt32 = step;
    return this;
  }

  inline void ChunkItem::GetInt64Step(int64& step) const
  {
    if (GetType() != chInt64)
      m_parent->m_owner->ReportBadType(this);
    step = m_stepInt64;
  }

  inline ChunkItem* ChunkItem::SetInt64Step(int64 step)
  {
    if (GetType() != chInt64)
      m_parent->m_owner->ReportBadType(this);
    m_stepInt64 = step;
    return this;
  }

  inline void ChunkItem::GetFloatStep(float& step) const
  {
    if (GetType() != chFloat)
      m_parent->m_owner->ReportBadType(this);
    step = m_stepFloat;
  }

  inline ChunkItem* ChunkItem::SetFloatStep(float step)
  {
    if (GetType() != chFloat)
      m_parent->m_owner->ReportBadType(this);
    m_stepFloat = step;
    return this;
  }
  //|C

  inline std::string ChunkItem::GetBrowsName() const
  {
    if (!m_browsComment.m_displayName.empty())
      return GetBrowsComment().m_displayName;
    return GetName();
  }

  // Инфа для браузера пропертей
  //////////////////////////////

  //                                                                           //
  //  ChunkItem Area                                                   =END= //
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  //  ChunkNode Area                                                 =BEGIN= //
  //                                                                           //
  inline ChunkNode::ChunkNode(const std::string& name, ChunkNode* parent, Chunk* owner)
    : m_name(name)
    , m_parent(parent)
    , m_owner(owner)
  {
    InitDefaults();
  }

  inline void ChunkNode::ReInit(const std::string& name, ChunkNode* parent, Chunk* owner)
  {
    m_name   = name;
    m_parent = parent;
    m_owner  = owner;
    InitDefaults();
  }

  inline ChunkNode* ChunkNode::SetBrowsType(const char* typeName)
  {
    m_browsType = std::string(typeName);
    return this;
  }

  inline void ChunkNode::InitDefaults()
  {
    m_browsAccess = baLikeParent;
    m_browsList   = false;

    if (m_owner)
    {
      m_prev = m_next = m_first_child_node = m_last_child_node = m_owner->getBadNode();
      m_first_child_item = m_last_child_item = m_owner->getBadItem();
    }
    else
    {
      m_prev = m_next = m_first_child_node = m_last_child_node = NULL;
      m_first_child_item = m_last_child_item = NULL;
    }
  }


  inline ChunkNode* ChunkNode::SetName(const std::string& sNewName, bool bNotifyUser)
  {
    if (bNotifyUser)
    {
      const std::string sOldName(m_name);
      m_name = sNewName;

      //if (m_parent && m_parent->m_owner->m_user)
      //  if (FAILED(m_parent->m_owner->m_user->OnNodeChange(this, ChunkUser::acRename, sOldName)))
      //    m_name = sOldName; //Changing is canceled by one of users
    }
    else
      m_name = sNewName;

    return this;
  }

  inline ChunkNode* ChunkNode::GetParent()
  {
    return (!m_parent) ? m_owner->getBadNode() : m_parent;
  }

  inline const ChunkNode* ChunkNode::GetParent() const
  {
    return (!m_parent) ? m_owner->getBadNode() : m_parent;
  }

  inline ChunkNode* ChunkNode::GetNodeByPath(const char* path)
  {
    ChunkNode* node = this;
    if (path[0] == 0)
      return node;

    const char* B = path;    // Begin
    while (true)
    {
      const char* C = strchr(B, PATH_DELIM);
      if (C)
      {
        node = node->findNode(B, C);
        if (node->isBad())
          break;
        B = C + 1;
      }
      else
      {
        node = node->findNode(B);
        break;
      }
    }

    return node ? node : GetOwner()->getBadNode();
  }

  inline std::string ChunkNode::GetFullPath() const
  {
    if (!GetParent()->isBad()){
      std::string sTemp=GetParent()->GetFullPath();
      if(sTemp.compare(""))
        return GetName();
      else
        return chunk_fmt::fmt("%s/%s", sTemp.c_str(), GetName().c_str());
    }
    else
      return "";
  }



  inline ChunkItem* ChunkNode::Add(const char* name, unsigned char value, bool bNotifyParent)
  {
    if (isBad())
      return m_owner->getBadItem();

    ChunkItem* newItem = findItem(name);
    if (newItem->isGood())
    {
      if (newItem->GetType() != chByte)
      {
        m_owner->ReportBadType(newItem);
        return m_owner->getBadItem();
      }
    }
    else
    {
      newItem = m_owner->allocItem(name, chByte, this);
      newItem->regMeNow(this);
    }
    newItem->Set(value, bNotifyParent);
    return newItem;
  }

  inline ChunkItem* ChunkNode::Add(const char* name, int32 value, bool bNotifyParent)
  {
    if (isBad())
      return m_owner->getBadItem();

    ChunkItem* newItem = findItem(name);
    if (newItem->isGood())
    {
      if (newItem->GetType() != chInt32)
      {
        m_owner->ReportBadType(newItem);
        return m_owner->getBadItem();
      }
    }
    else
    {
      newItem = m_owner->allocItem(name, chInt32, this);
      newItem->regMeNow(this);
    }

    newItem->Set(value, bNotifyParent);
    return newItem;
  }

  inline ChunkItem* ChunkNode::Add(const char* name, int64 value, bool bNotifyParent)
  {
    if (isBad())
      return m_owner->getBadItem();

    ChunkItem* newItem = findItem(name);
    if (newItem->isGood())
    {
      if  (newItem->GetType() != chInt64)
      {
        m_owner->ReportBadType(newItem);
        return m_owner->getBadItem();
      }
    }
    else
    {
      newItem = m_owner->allocItem(name, chInt64, this);
      newItem->regMeNow(this);
    }
    newItem->Set(value, bNotifyParent);
    return newItem;
  }

  inline ChunkItem* ChunkNode::Add(const char* name, float value, bool bNotifyParent)
  {
    if (isBad())
      return m_owner->getBadItem();

    ChunkItem* newItem = findItem(name);
    if (newItem->isGood())
    {
      if (newItem->GetType() != chFloat)
      {
        m_owner->ReportBadType(newItem);
        return m_owner->getBadItem();
      }
    }
    else
    {
      newItem = m_owner->allocItem(name, chFloat, this);
      newItem->regMeNow(this);
    }

    newItem->Set(value, bNotifyParent);
    return newItem;
  }

  inline ChunkItem* ChunkNode::Add(const char* name, const std::string& value, bool bNotifyParent)
  {
    if (isBad())
      return m_owner->getBadItem();

    ChunkItem* newItem = findItem(name);
    if (newItem->isGood())
    {
      if  (newItem->GetType() != chString)
      {
        m_owner->ReportBadType(newItem);
        return m_owner->getBadItem();
      }
    }
    else
    {
      newItem = m_owner->allocItem(name, chString, this);
      newItem->regMeNow(this);
    }
    newItem->Set(value, bNotifyParent);
    return newItem;
  }

  inline ChunkItem* ChunkNode::Add(const char* name, const std::wstring& value, bool bNotifyParent)
  {
    return Add( name, value, bNotifyParent );
  }

  inline ChunkItem* ChunkNode::Add(const char* name, const Variant& value, bool bNotifyParent)
  {
    if (isBad())
      return m_owner->getBadItem();

    ChunkItem* newItem = findItem(name);
    if (newItem->isBad())
    {
      newItem = m_owner->allocItem(name, value.GetType(), this);
      newItem->regMeNow(this);
    }
    newItem->Set(value, bNotifyParent);
    return newItem;
  }



  inline ChunkNode* ChunkNode::AddNode(const std::string& name, bool bNotifyUser)
  {
    if (isBad())
      return this;

    ChunkNode* newNode = findNode(name);
    if (newNode->isGood())
      return newNode;

    newNode = m_owner->allocNode(name, this);
    newNode->regMeNow(this);

    // Notify user of chunk
    if( bNotifyUser && m_parent && m_parent->m_owner->m_user )
      m_parent->m_owner->m_user->OnNodeChange(newNode, ChunkUser::acAdd);

    return newNode;
  }

  inline ChunkNode* ChunkNode::AddNode( const char* NameBegin, const char* NameEnd, bool bNotifyUser)
  {
    if (isBad())
      return this;

    ChunkNode* newNode = findNode(NameBegin, NameEnd);
    if (newNode->isGood())
      return newNode;

    newNode = m_owner->allocNode(std::string(NameBegin, NameEnd), this);
    newNode->regMeNow(this);

    // Notify user of chunk
    if( bNotifyUser && m_parent && m_parent->m_owner->m_user )
      m_parent->m_owner->m_user->OnNodeChange(newNode, ChunkUser::acAdd);

    return newNode;
  }

  inline ChunkNode* ChunkNode::DangerousAddNode(const std::string& name, bool bNotifyUser)
  {
    ChunkNode* newNode = m_owner->allocNode(name, this);
    newNode->regMeNow(this);

    // Notify user of chunk
    if( bNotifyUser && m_parent && m_parent->m_owner->m_user )
      m_parent->m_owner->m_user->OnNodeChange(newNode, ChunkUser::acAdd);

    return newNode;
  }

  inline int ChunkNode::GetNodeCount(void) const
  {
    // Maybe need value to be stored...
    int count = 0;
    const ChunkNode* end = m_owner->getBadNode();
    for(const ChunkNode* cur = m_first_child_node; cur !=  end; cur = cur->m_next)
      ++count;
    return count;
    //  return (isBad()) ? 0 : m_nodes.size();
  }

  inline int ChunkNode::GetItemCount(void) const
  {
    // Maybe need value to be stored...
    int count = 0;
    const ChunkItem* end = m_owner->getBadItem();
    for(const ChunkItem* cur = m_first_child_item; cur !=  end; cur = cur->m_next)
      ++count;
    return count;
    //  return (isBad()) ? 0 : m_items.size();
  }

  inline ChunkNode* ChunkNode::findNode(const char* szName)
  {
    ChunkNode* cur = m_first_child_node;
    ChunkNode* end = cur->m_prev;
    assert(end->isBad());
    for(; cur != end; cur = cur->m_next)
    {
      if(!chunk_fmt::reverse_stricmp(cur->GetName(), szName))
        return cur;
    }
    return cur;
  }

  inline ChunkNode* ChunkNode::findNode(const char* NameBegin, const char* NameEnd)
  {
    char findName[MAX_NODE_NAME];
    ptrdiff_t len = NameEnd - NameBegin;
    assert(len > 0);
    if (len > MAX_NODE_NAME)
      len = MAX_NODE_NAME;
    strncpy(findName, NameBegin, len);
    findName[len] = 0;
    return findNode(findName);
  }

  inline ChunkItem* ChunkNode::findItem(const char* szName)
  {
    ChunkItem* cur = m_first_child_item;
    ChunkItem* end = cur->m_prev;
    assert(end->isBad());

    const size_t nameSize = strlen(szName);

    for(; cur != end; cur = cur->m_next)
    {
      if(cur->GetName().size() == nameSize && !stricmp(cur->GetName().c_str(), szName))
        return cur;
    }
    return cur;
  }

  inline const ChunkItem* ChunkNode::findItem(const char* szName) const
  {
    const ChunkItem* cur = m_first_child_item;
    const ChunkItem* end = cur->m_prev;
    assert(end->isBad());

    const size_t nameSize = strlen(szName);

    for(; cur != end; cur = cur->m_next)
    {
      if(cur->GetName().size() == nameSize && !stricmp(cur->GetName().c_str(), szName))
        return cur;
    }

    return cur;
  }

  inline void ChunkNode::unregMeNow()
  {
    ChunkNode* bad_node = m_owner->getBadNode();

    //left
    if(m_prev == bad_node)
      m_parent->m_first_child_node = m_next;
    else
      m_prev->m_next = m_next;
    //right
    if(m_next == bad_node)
      m_parent->m_last_child_node = m_prev;
    else
      m_next->m_prev = m_prev;
  }

  inline void ChunkNode::regMeNow(ChunkNode* parent)
  {
    //  m_parent = parent;
    //  m_parent->m_nodes.push_back(this);
    ChunkNode* bad_node = m_owner->getBadNode();
    if(parent->m_first_child_node == bad_node){
      parent->m_first_child_node = this;
      parent->m_last_child_node = this;
      m_prev = m_next = bad_node;
    }else{
      m_prev = parent->m_last_child_node;
      m_next = parent->m_last_child_node->m_next;
      parent->m_last_child_node->m_next = this;
      parent->m_last_child_node = this;
    }
  }

  inline bool ChunkNode::AddUser(ChunkUser* pUser )
  {
    return GetOwner()->AddUser( pUser, this );
  }

  inline bool ChunkNode::RemoveUser(ChunkUser* pUser )
  {
    return GetOwner()->RemoveUser( pUser, this );
  }

  inline ChunkNode const * ChunkNode::GetBrother(std::string const& brotherName) const{
    // Try to find from this node to the end
    const ChunkNode* cur = m_next;
    for(const ChunkNode* next = cur->m_next; cur != next; cur = next, next = next->m_next)
      if(!chunk_fmt::reverse_stricmp(cur->GetName(), brotherName))
        return cur;
    // Not found. try to search from me to the begin of the list
    cur = this;
    for(const ChunkNode* prev = cur->m_prev;prev != cur; cur = prev, prev = prev->m_prev)
      if(!chunk_fmt::reverse_stricmp(cur->GetName(), brotherName))
        return cur;
    return cur;
  }

  inline ChunkNode* ChunkNode::GetBrother(std::string const& brotherName){
    // Try to find from this node to the end
    ChunkNode* cur = m_next;
    for(ChunkNode* next = cur->m_next; cur != next; cur = next, next = next->m_next)
      if(!chunk_fmt::reverse_stricmp(cur->GetName(), brotherName))
        return cur;
    // Not found. try to search from me to the begin of the list
    cur = this;
    for(ChunkNode* prev = cur->m_prev;prev != cur; cur = prev, prev = prev->m_prev)
      if(!chunk_fmt::reverse_stricmp(cur->GetName(), brotherName))
        return cur; 
    return cur;
  }

  inline ChunkItem* ChunkNode::GetItemByPath(std::string const& path){
    std::string::size_type nDelimPos = path.find_last_of('/');
    if(nDelimPos == std::string::npos)
      return GetItem(path);
    ChunkNode* pNode = GetNodeByPath(path.substr(0,nDelimPos));
    if(pNode->isGood())
      return pNode->GetItem(path.substr(nDelimPos+1));
    return GetOwner()->getBadItem();;
  }

  inline ChunkItem const * ChunkNode::GetItemByPath(std::string const& path) const{
    return const_cast<ChunkNode*>(this)->GetItemByPath(path);
  }

  inline ChunkItem* ChunkItem::GetBrother(const std::string& brotherName){
    // Try to find from this node to the end
    ChunkItem* cur = m_next;
    for(ChunkItem* next = cur->m_next; cur != next; cur = next, next = next->m_next)
      if(!chunk_fmt::reverse_stricmp(cur->GetName(), brotherName))
        return cur;
    // Not found. try to search from me to the begin of the list
    cur = this;
    for(ChunkItem* prev = cur->m_prev;prev != cur; cur = prev, prev = prev->m_prev)
      if(!chunk_fmt::reverse_stricmp(cur->GetName(), brotherName))
        return cur;
    return cur;
  }

  inline const ChunkItem* ChunkItem::GetBrother(const std::string& brotherName) const{
    // Try to find from this node to the end
    const ChunkItem* cur = m_next;
    for(const ChunkItem* next = cur->m_next; cur != next; cur = next, next = next->m_next)
      if(!chunk_fmt::reverse_stricmp(cur->GetName(), brotherName))
        return cur;
    // Not found. try to search from me to the begin of the list
    cur = this;
    for(const ChunkItem* prev = cur->m_prev;prev != cur; cur = prev, prev = prev->m_prev)
      if(!chunk_fmt::reverse_stricmp(cur->GetName(), brotherName))
        return cur;
    return cur;
  }

  inline bool ChunkNode::DeleteNode(const std::string& nodeName, bool bUserNotify)
  {
    ChunkNode* pNode = GetNode(nodeName);
    if (pNode->isBad())
      return false;
    return DeleteNode(pNode, bUserNotify);
  }

  inline bool ChunkNode::DeleteNode(ChunkNode* pChildNode, bool bUserNotify)
  {
    if (pChildNode->isBad())
      return false;
    //if( bUserNotify && isBrowsList() )
    //{
    //  if( m_owner->m_user )
    //  {
    //    if(FAILED( m_owner->m_user->OnNodeChange(pChildNode, ChunkUser::acRemove) ))
    //      return false;
    //  }
    //}

    bool rv = m_owner->delNode(pChildNode);

    if( bUserNotify && isBrowsList() )
    {
      if( m_owner->m_user )
        m_owner->m_user->OnNodeChange(this, ChunkUser::acRemoved); // Для родительской ноды, т.к. настоящую уже удалили
    }

    return rv;
  }

  inline bool ChunkNode::DeleteItem(const std::string& itemName, bool bUserNotify)
  {
    ChunkItem* item = GetItem(itemName);
    if (item->isBad())
      return false;
    return m_owner->delItem(item);
  }

  inline bool ChunkNode::DeleteAllChild( bool bUserNotify )
  {
    // Kill all child...(KKND)

    if (isBad())
      return false;

    ChunkItem* bad_item = m_owner->getBadItem();
    if( m_first_child_item != bad_item )
    {
      for(ChunkItem* cur = m_first_child_item; cur != bad_item; )
      {
        ChunkItem* tmp = cur;
        cur = cur->m_next;
        // Notify user
        if( bUserNotify && m_owner->m_user && cur->GetParent()->isBrowsList() )
          m_owner->m_user->OnItemChange(cur, ChunkUser::acRemove, cur->Get());

        // Delete item
        m_owner->freeItem(tmp);
      }
      m_first_child_item = bad_item;
      m_last_child_item = bad_item;
    }

    ChunkNode* bad_node = m_owner->getBadNode();
    if( m_first_child_node != bad_node )
    {
      for(ChunkNode* cur = m_first_child_node; cur != bad_node; )
      {
        //      ChunkNode* pNode = *iNode;
        ChunkNode* tmp = cur;
        cur = cur->m_next;
        // Notify user
        if( bUserNotify && cur->GetParent()->isBrowsList() )
        {

          if( m_owner->m_user )
            m_owner->m_user->OnNodeChange(cur, ChunkUser::acRemove);
          GetOwner()->NotifyNodeChanging( this, cur->GetName(), cur, true );
        }

        // Delete node
        cur->DeleteAllChild(bUserNotify);
        m_owner->freeNode(tmp);
      }
      m_first_child_node = bad_node;
      m_last_child_node = bad_node;

      //C-
      if( bUserNotify && isBrowsList() )
      {
        if( m_owner->m_user )
          m_owner->m_user->OnNodeChange(this, ChunkUser::acRemoved);
        GetOwner()->NotifyNodeChanged( this, "", NULL, true );
      }
    }
    return S_OK;
  }

  inline std::string ChunkNode::GetBrowsName() const
  {
    if (!m_browsComment.m_displayName.empty())
      return GetBrowsComment().m_displayName;
    return GetName();
  }

#define INIT_CHUNK                                \
  : m_topNode("Top", NULL, NULL)     \
  , m_badNode("BadNode", NULL, NULL) \
  , m_badItem("BadItem", chByte, &m_badNode)        \
  , m_bGoodLooking(true)                            \
  , m_user(NULL)                                    \
  , m_freeNodes(NULL)                               \
  , m_freeItems(NULL)                               \
  , m_indent(0)

#if MEM_DEBUG
#define MEM(x)  x
#else
#define MEM(x)
#endif

#define INIT_CHUNK2               \
  m_badNode.m_owner = this;       \
  m_topNode.m_owner = this;       \
  m_badItem.m_prev = m_badItem.m_next  = &m_badItem; \
  m_topNode.InitDefaults();       \
  m_badNode.InitDefaults();       \
  m_badItem.regMeNow(&m_badNode);



  inline Chunk::Chunk()
    INIT_CHUNK
  {
    INIT_CHUNK2
      m_topNode.SetBrowsAccess(baPublic);
  }

  inline Chunk::Chunk(const Chunk& chunk)
    INIT_CHUNK
  {
    INIT_CHUNK2
      assert(&chunk);
    copyFrom(chunk.GetTopNode());
  }

  inline Chunk::Chunk(const ChunkNode* node)
    INIT_CHUNK
  {
    INIT_CHUNK2
      assert(&node);
    copyFrom(node);
  }

#undef INIT_CHUNK
#undef INIT_CHUNK2

  inline Chunk::~Chunk()
  {
    if (m_user)
      m_user->m_chunk = NULL;
    m_topNode.DeleteAllChild();

    m_badNode.PreDestroy();
    m_topNode.PreDestroy();

    // destruct m_freeNodes, m_freeItems
    for (ChunkNode* node = m_freeNodes; node; node = node->m_next)
      node->~ChunkNode();
    for (ChunkItem* item = m_freeItems; item; item = item->m_next)
      item->~ChunkItem();
  }

  inline void Chunk::copyFrom(const ChunkNode* source)
  {
    assert(source);
    ChunkNode* dest = GetTopNode();
    dest->m_name = source->GetName();

    dest->m_browsType    = source->m_browsType;
    dest->m_browsComment = source->m_browsComment;
    dest->m_browsAccess  = baPublic;
    dest->m_browsList    = source->m_browsList;

    // Клонируем поля
    const ChunkItem* next_item = source->GetFirstChildItem();
    while (!next_item->isBad())
    {
      next_item->CloneMe(dest, next_item->GetName());
      next_item = next_item->GetNextBrother();
    }
    // Клонируем ветки
    const ChunkNode* next_node = source->GetFirstChildNode();
    while (!next_node->isBad())
    {
      next_node->CloneMe(dest, next_node->GetName());
      next_node = next_node->GetNextBrother();
    }
  }

  inline void Chunk::operator=(const Chunk& chunk)
  {
    Clear();
    copyFrom(chunk.GetTopNode());
  }
  inline ChunkItem* Chunk::GetItem(const std::string& path, const std::string& item)
  {
    return GetNode(path)->GetItem(item);
  }
  inline const ChunkItem* Chunk::GetItem(const std::string& path, const std::string& item) const
  {
    return GetNode(path)->GetItem(item);
  }
  inline ChunkItem* Chunk::GetItem(const std::string& FullPath)
  {
    std::string::size_type nDelimPos = FullPath.find_last_of('/');
    return nDelimPos == std::string::npos? GetTopNode()->GetItem(FullPath) :GetNode(FullPath.substr(0,nDelimPos))->GetItem(FullPath.substr(nDelimPos+1));
  }

  inline const ChunkItem* Chunk::GetItem(const std::string& FullPath) const
  {
    std::string::size_type nDelimPos = FullPath.find_last_of('/');
    return nDelimPos == std::string::npos? GetTopNode()->GetItem(FullPath) :GetNode(FullPath.substr(0,nDelimPos))->GetItem(FullPath.substr(nDelimPos+1));
  }
  inline ChunkNode* Chunk::CreatePath(const std::string& path, bool bNotifyUser)
  {
    ChunkNode* node = GetTopNode();
    if (path.empty()) return node;

    std::string::const_iterator B = path.begin();    // Begin
    std::string::const_iterator C = path.begin();    // Cursor
    std::string::const_iterator E = path.end();      // End
    // Отключаем   conditional expression is constant
    for(;;)
    {
      C = std::find(B, E, PATH_DELIM);
      //    std::string name(B, C);
      ////    ChunkNode* res = node->GetNode(name);
      node = /*(!res->isBad()) ? res :*/ node->AddNode(&(*B), &(*C), bNotifyUser);
      if (C == E)  break;
      B = C + 1;
    }
    return node;
  }

  inline ChunkNode* Chunk::GetNode(const char* path){
    return GetTopNode()->GetNodeByPath(path);
  }
  inline const ChunkNode* Chunk::GetNode(const char* path) const{
    return GetTopNode()->GetNodeByPath(path);
  }
  inline ChunkNode* Chunk::GetTopNode(){
    return &m_topNode;
  }
  inline const ChunkNode* Chunk::GetTopNode() const{
    return &m_topNode;
  }
  inline bool Chunk::delItem(ChunkItem* item)
  {
    assert(item);

    if (item->isBad())
    {
      ReportError("deleting bad item");
      return false;
    }

    item->unregMeNow();
    freeItem(item);
    return true;
  }

  inline bool Chunk::delNode(ChunkNode* node)
  {
    assert(node);
    node->unregMeNow();
    freeNode(node);
    return true;
  }

  inline bool Chunk::DeleteItem(const std::string& path, const std::string& itemName)
  {
    return delItem(GetItem(path, itemName));
  }
  inline bool Chunk::DeleteNode(const std::string& path)
  {
    return delNode(GetNode(path));
  }
  inline void Chunk::Clear()
  {
    GetTopNode()->DeleteAllChild();
  }
  inline bool Chunk::SetUser(ChunkUser* user)
  {
    assert(user);
    if (m_user)
    {
      ReportError("cannot set user");
      return false;
    }
    m_user = user;
    user->m_chunk = this;
    return true;
  }

  inline bool Chunk::AddUser(ChunkUser* pUser, void* pContext )
  {
    assert(pContext);
    if(!pContext)
      return false;

    ChunkUsersList& Users = m_UsersMap[pContext];
    ChunkUsersList::iterator FindIt = std::find( Users.begin(), Users.end(), pUser );
    if( FindIt != Users.end() )
    {
      //    g_wrn << _T("Tried to add already registered ChunkUser") << endl;
      return false;
    }
    Users.push_back( pUser );
    return true;
  }

  inline bool Chunk::RemoveUser(ChunkUser* pUser, void* pContext )
  {
    //Find list for corresponding context
    ChunkUsersMap::iterator FindIt = m_UsersMap.begin();
    for( ; FindIt != m_UsersMap.end(); ++FindIt )
    {
      if( FindIt->first == pContext )
        break;
    }
    if( FindIt == m_UsersMap.end() )
    {
      //    g_err << _T("Tried to remove ChunkUser for context that is not known") << endl;
      return false;
    }

    //Try to find user fo that context
    ChunkUsersList::iterator ListIt = std::find(FindIt->second.begin(), FindIt->second.end(), pUser );
    if(ListIt == FindIt->second.end() )
    {
      //    g_err << _T("Tried to remove ChunkUser that is not registered") << endl;
      return false;
    }
    FindIt->second.erase( ListIt );
    //Kill entry if list of users becomes empty
    if(FindIt->second.empty())
      m_UsersMap.erase(FindIt);
    return true;
  }
  inline const ChunkUsersList* Chunk::GetUsersList( void* pContext )const
  {
    //Find list for corresponding context
    ChunkUsersMap::const_iterator FindIt = m_UsersMap.begin();
    for( ; FindIt != m_UsersMap.end(); ++FindIt )
    {
      if( FindIt->first == pContext )
        break;
    }
    if( FindIt == m_UsersMap.end() )
      return NULL;
    return &(FindIt->second);
  }

  inline void  Chunk::RemoveAllUsers( const void* pContext )
  {
    //Find list for corresponding context
    ChunkUsersMap::iterator FindIt = m_UsersMap.begin();
    for( ; FindIt != m_UsersMap.end(); ++FindIt )
    {
      if( FindIt->first == pContext )
        break;
    }
    if( FindIt == m_UsersMap.end() )
      return;
    m_UsersMap.erase(FindIt);
  }

  inline bool Chunk::NotifyItemChanging( ChunkItem* sender, const Variant& vNewValue )const
  {
    //Notify users of item itself
    const ChunkUsersList* Users =  GetUsersList( sender );
    if(Users)
    {
      ChunkUsersList::const_iterator UpdateIt = Users->begin();
      for( ; UpdateIt != Users->end(); ++UpdateIt )
        if( !(*UpdateIt)->OnItemChanging( sender, vNewValue) )
          return false;//One of users refuses to accept changes.
    }
    //Notify users of parent node
    Users =  GetUsersList( sender->GetParent() );
    if(Users)
    {
      ChunkUsersList::const_iterator UpdateIt = Users->begin();
      for( ; UpdateIt != Users->end(); ++UpdateIt )
        if( !(*UpdateIt)->OnItemChanging( sender, vNewValue) )
          return false;//One of users refuses to accept changes.
    }
    return true;
  }

  inline void Chunk::NotifyItemChanged( ChunkItem* sender, const Variant& vOldValue )const
  {
    //Notify users of item itself
    const ChunkUsersList* Users =  GetUsersList( sender );
    if(Users)
    {
      ChunkUsersList::const_iterator UpdateIt = Users->begin();
      for( ; UpdateIt != Users->end(); ++UpdateIt )
        (*UpdateIt)->OnItemChanged( sender, vOldValue);
    }
    //Notify users of parent node
    Users =  GetUsersList( sender->GetParent() );
    if(Users)
    {
      ChunkUsersList::const_iterator UpdateIt = Users->begin();
      for( ; UpdateIt != Users->end(); ++UpdateIt )
        (*UpdateIt)->OnItemChanged( sender, vOldValue);
    }
  }

  inline bool Chunk::NotifyNodeChanging(ChunkNode* pParent, const std::string& sNodeName, ChunkNode* pSender, bool bIsRemoving)const
  {
    assert( bIsRemoving == !!pSender );
    const ChunkUsersList* pUsers;
    if(pSender)
    {
      //Notify users of sender itself
      pUsers =  GetUsersList( pSender );
      if( pUsers )
      {
        ChunkUsersList::const_iterator UpdateIt = pUsers->begin();
        for( ; UpdateIt != pUsers->end(); ++UpdateIt )
          if( !(*UpdateIt)->OnNodeChanging( pParent, sNodeName, pSender, bIsRemoving) )
            return false;//One of users refuses to accept changes.
      }
    }
    //Parent users is notified in any case
    pUsers =  GetUsersList( pParent->GetParent() );
    if(pUsers)
    {
      ChunkUsersList::const_iterator UpdateIt = pUsers->begin();
      for( ; UpdateIt != pUsers->end(); ++UpdateIt )
        if( !(*UpdateIt)->OnNodeChanging( pParent, sNodeName, pSender, bIsRemoving) )
          return false;//One of users refuses to accept changes.
    }
    return true;
  }

  inline void Chunk::NotifyNodeChanged(ChunkNode* pParent, const std::string& sNodeName, ChunkNode* pSender, bool bIsRemoved)
  {//There we have only users of parent. To sender they are not attached yet
    assert( bIsRemoved == !pSender );
    const ChunkUsersList* pUsers =  GetUsersList( pParent->GetParent() );
    if(pUsers)
    {
      ChunkUsersList::const_iterator UpdateIt = pUsers->begin();
      for( ; UpdateIt != pUsers->end(); ++UpdateIt )
        (*UpdateIt)->OnNodeChanging( pParent, sNodeName, pSender, bIsRemoved);
    }
  }

  inline void ChunkNode::PreDestroy()
  {
    ChunkItem* bad_item = m_first_child_item->m_prev;
    for(ChunkItem* cur = m_first_child_item; cur != bad_item; ){
      ChunkItem* tmp =  cur;
      cur = cur->m_next;
      m_owner->freeItem(tmp);
    }
    //  m_first_child_item = m_last_child_item = NULL;

    ChunkNode* bad_node = m_first_child_node->m_prev;
    for(ChunkNode* cur = m_first_child_node; cur != bad_node; ){
      ChunkNode* tmp =  cur;
      cur = cur->m_next;
      m_owner->freeNode(tmp);
    }
    //  m_first_child_node = m_last_child_node = NULL;
  }

  inline ChunkNode* Chunk::allocNode(const std::string& name, ChunkNode* parent)
  {
    if (m_freeNodes)
    {
      // get node from m_freeNodes list
      ChunkNode* node = m_freeNodes;
      m_freeNodes = node->m_next;
      node->ReInit(name, parent, this);
      return node;
    }
    return new ChunkNode(name, parent, this);
  }

  inline ChunkItem* Chunk::allocItem(const char* name, ChunkItemType type, ChunkNode* parent)
  {
    if (m_freeItems)
    {
      // get item from m_freeItems list
      ChunkItem* item = m_freeItems;
      m_freeItems = item->m_next;
      item->ReInit(name, type, parent);
      return item;
    }
    return new ChunkItem(name, type, parent);
  }

  inline void Chunk::freeNode(ChunkNode* node)
  {
    RemoveAllUsers(node);
    if ((node == &m_topNode) || (node == &m_badNode))
      return;
    node->PreDestroy();
    delete node;
    return;
  }

  inline void Chunk::freeItem(ChunkItem* item)
  {
    RemoveAllUsers(item);
    delete item;
  }
  const unsigned char SIGN       = '$';
  const unsigned char chTabIn    = chInternal + 1;
  const unsigned char chTabOut   = chInternal + 2;
  const unsigned char chNode     = chInternal + 3;
  const unsigned char chBType    = chInternal + 4;
  const unsigned char chValue    = chInternal + 5;
  const unsigned char chBRange   = chInternal + 6;
  const unsigned char chBComment = chInternal + 7;
  const unsigned char chBAccess  = chInternal + 8;
  const unsigned char chBDesign  = chInternal + 9;
  const unsigned char chBList    = chInternal + 10;
  const unsigned char chBStep    = chInternal + 11;

  const int  TAB_SIZE = 2;
  const char COMMENT  = '#';
  const char DESIGN   = '@';
  const char DELIM    = ';';
  const char LP       = '{';
  const char RP       = '}';
  const char CLONE    = '%';

  const unsigned char CHUNK_VERSION = 1;

  //// заголовок для чанка...
  //inline bool Chunk::writeHeader(chunk_io::Stream& out, bool inScript) const
  //{
  //  if (!inScript)
  //  {
  //    out << SIGN << CHUNK_VERSION;
  //  }
  //  else
  //  {
  //    m_indent = 0;
  //  }
  //  return (false == out.Failed());
  //}

  inline bool Chunk::readBrowseTime(chunk_io::Stream& in, bool inScript)
  {
    char c;
    in >> c;
    if ((!inScript && c != chBDesign) ||
      (inScript && c != DESIGN))
    {
      StepBack(in);
      return false;
    }

    //  g_err.Printf("Chunk: %s (%d): BrowsTime used (obsolete)\n", in.GetName(), m_curLine);
    return true;
  }

  //// новая строка
  //inline void writeNewLine(chunk_io::Stream& out)
  //{
  //  out.Printf("\n");
  //}

  inline void Chunk::skipWhiteSpace(chunk_io::Stream& in)
  {
    char c;
    while (true)
    {
      if (in.eof())
        return;
      in >> c;
      if (c == '\n')
      {
        ++m_curLine;
        continue;
      }
      if (c > 0 && c <= ' ')  // ignore special syms (c < 0 means russian symbols)
        continue;

      if (c == '#')
      {
        while (c != '\n')
          in >> c;
        ++m_curLine;
        continue;
      }

      if ( c == '/' )
      {
        // C/C++-style comments
        in >> c;
        if (c == '*')
        {
          //multiline C-style comments
          while (true)
          {
            in >> c;
loop:
            if (c == '\n')
            {
              ++m_curLine;
              continue;
            }
            if (c != '*')
              continue;
            in >> c;
            if (c == '/')
              break;
            goto loop;   // avoid seek back 1 char
          }
        }
        else if (c == '/')
        {
          // C++-style line comments
          while (c != '\n')
            in >> c;
          ++m_curLine;
        }
        else
        {
          StepBack(in, 2);
          break;
        }
        continue;
      }

      StepBack(in);
      break;
    }
  }

  //inline void Chunk::writeBrowseType(chunk_io::Stream& out, bool inScript, const std::string& browsType) const
  //{
  //  if (!inScript)
  //  {
  //    out << chBType;
  //    WriteSZ(out, browsType);
  //  }
  //  else
  //  {
  //    out.Printf(" (%s)", browsType.c_str());
  //  }
  //}

  inline Chunk::readResult Chunk::readBrowseType(chunk_io::Stream& in, char* buffer, unsigned int bufSize, bool inScript)
  {
    buffer[0] = 0;
    char c;
    in >> c;
    if (!inScript)
    {
      if (c == chBType)
      {
        ReadSZ(in, buffer, bufSize);
      }
      else
        StepBack(in);
      if(in.Failed())
        return rr_IOFailed;
    }
    else
    {
      if (c != '(')
      {
        StepBack(in);
        return rr_OK;
      }
      skipWhiteSpace(in);
      ReadString(in, buffer, bufSize, ")");

      if(in.Failed())
        return rr_IOFailed;

      skipWhiteSpace(in);
      in >> c;
      if (c != ')')
      {
        ReportBadFileFormat(in, m_curLine);
        return rr_BadFormat;
      }
      skipWhiteSpace(in);
      if(in.Failed())
        return rr_IOFailed;
    }
    return rr_OK;
  }

  //inline void Chunk::writeBrowseAccess(chunk_io::Stream& out, bool inScript, ChunkBrowsAccess access) const
  //{
  //  if (!inScript)
  //  {
  //    out << chBAccess << char(access);
  //  }
  //  else
  //  {
  //    out.Printf(" <%s>", accessTypeToString( access ));
  //  }
  //}

  inline Chunk::readResult Chunk::readBrowseAccess(chunk_io::Stream& in, ChunkBrowsAccess& access, bool inScript)
  {
    ChunkBrowsAccess res = baLikeParent;

    unsigned char c;
    in >> c;

    if(inScript)
    {
      if (c != '<')
      {
        StepBack(in);
        CHECK_STREAM_EX(in);

        access = res;
        return rr_OK;
      }

      skipWhiteSpace(in);
      char sAccess[MAX_ACCESS_NAME];
      ReadString(in, ARRAY_ARG(sAccess), " \r\n\t#>");
      CHECK_STREAM_EX(in);

      res = stringToAccessType( sAccess );
      if(res == baLast)
        return rr_BadFormat;

      skipWhiteSpace(in);
      in >> c;
      CHECK_STREAM_EX(in);

      if (c != '>')
        return rr_BadFormat;
      skipWhiteSpace(in);
      CHECK_STREAM_EX(in);
    }
    else
    {
      if (c == chBAccess)
      {
        in >> c;
        res = ChunkBrowsAccess(c);
      }
      else
      {
        StepBack(in);
      }
      CHECK_STREAM_EX(in);
    }

    access = res;
    return rr_OK;
  }

  inline void set_string_char( std::string& str, unsigned int pos, char c )
  {
    if ( str.size() <= pos )
      str.resize( pos + 1 );
    str[ pos ] = c;
  }

  // read quoted string till '"'; assumed, that last read char was opening quote
  // after reading, stream will point to next char after closing '"'
  static void readString(chunk_io::Stream& in, std::string& str )
  {
    unsigned int pos = 0;
    while (true)
    {
      char c;
      in >> c;
      if (c == '\"')          // closing quote - end of string
      {
        set_string_char( str, pos, 0 );    // make null-terminated
        break;
      }
      if (c == '\\')          // escape-sequence: read next char
      {
        in >> c;
        if (c != '\"' && c != '\\')
        {
          // sigh ... this code was marked as "remove it", but still used (used strings
          // like "path\filename" instead of "path\\filename")
          // we will act like non-escape string
          set_string_char( str, pos, '\\' );
          pos++;
        }
      }
      // append char
      set_string_char( str, pos, c );
      pos++;
      // NOTE: even when buffer size is not enough, will read until string end
    }
  }


  // read quoted string till '"'; assumed, that last read char was opening quote
  // after reading, stream will point to next char after closing '"'
  static void readString(chunk_io::Stream& in, char* buffer, unsigned int bufSize)
  {
    unsigned int pos = 0;
    while (true)
    {
      char c;
      in >> c;
      if (c == '\"')          // closing quote - end of string
      {
        if (pos < bufSize)
          buffer[pos] = 0;    // make null-terminated
        break;
      }
      if (c == '\\')          // escape-sequence: read next char
      {
        in >> c;
        if (c != '\"' && c != '\\')
        {
          // sigh ... this code was marked as "remove it", but still used (used strings
          // like "path\filename" instead of "path\\filename")
          // we will act like non-escape string
          if (pos < bufSize)
            buffer[pos] = '\\';
          pos++;
        }
      }
      // append char
      if (pos < bufSize)
        buffer[pos] = c;
      pos++;
      // NOTE: even when buffer size is not enough, will read until string end
    }
    // check for overflow
    if (pos > bufSize-1)
    {
      buffer[bufSize-1] = 0;
    }
  }

  //static void writeScriptName(chunk_io::Stream& out, const char* str)
  //{
  //  // check for quote requirement
  //  for (const char* s = str; *s; s++)
  //    if (strchr(NameDelims(), *s))
  //    {
  //      // delimiter found - write quoted string
  //      WriteQuotedString(out, str);
  //      return;
  //    }
  //    out.RawWrite(str, (unsigned int)strlen(str));
  //}

  static void readScriptName(chunk_io::Stream& in, char* buffer, unsigned int bufSize)
  {
    char c;
    in >> c;
    if (c == '"')
    {
      readString(in, buffer, bufSize);
    }
    else
    {
      StepBack(in);
      // читаем строку до пробела
      ReadString(in, buffer, bufSize, NameDelims());
    }
  }

  //--------------------------------------------------------------------------
  // Main chunk file saving code
  //--------------------------------------------------------------------------
  inline bool Chunk::SaveTo(chunk_io::Stream& out, bool bAsBinary, bool bGoodLooking) const
  {
#define HANDLE_ERROR(ER)                                                                                 \
    {                                                                                                        \
    m_bGoodLooking = true;                                                                                 \
    return false;                                                                                          \
  }
    m_bGoodLooking = bGoodLooking;
    bool inScript  = !bAsBinary;

    //if(false == writeHeader(out, inScript))
    //  HANDLE_ERROR("IO operation failure!");

    if(inScript)
    {
      // query current locale
      char oldLocale[64];
      strcpy(oldLocale, setlocale(LC_NUMERIC, NULL));
      // set POSIX locale
      setlocale(LC_NUMERIC, "C");
      //// write chunk to text stream
      //if(false == writeScriptNode(out, GetTopNode()))
      //  HANDLE_ERROR("IO operation failure!");
      // restore previous locale
      setlocale(LC_NUMERIC, oldLocale);
    }
    else
    {
      /*if(false == writeBinaryNode(out, GetTopNode()))
      HANDLE_ERROR("IO operation failure!");*/
    }

    m_bGoodLooking = true;
    return true;

#undef HANDLE_ERROR
  }


  //--------------------------------------------------------------------------
  // Chunk saving wrappers
  //--------------------------------------------------------------------------

  inline bool Chunk::SaveTo(std::string& str, bool isBinary, bool bGoodLooking) const
  {
    chunk_io::MemStream mem(chunk_io::SM_WRITE | chunk_io::SM_NOEXCEPT, 16384);
    if (SaveTo(mem, isBinary, bGoodLooking))
    {
      str.assign((const char*)mem.Data(), mem.Size());
      return true;
    }
    return false;
  }

  inline bool Chunk::SaveTo( const char* szFileName ) const
  {  
    chunk_io::FileStream file;
    if (!file.Open(szFileName, chunk_io::SM_WRITE | chunk_io::SM_NOEXCEPT))
      return false;

    bool res = SaveTo( file, false, true );
    file.Close();

    return res;
  }



  //--------------------------------------------------------------------------
  // Main chunk file loading code
  //--------------------------------------------------------------------------

  inline bool Chunk::LoadFrom(chunk_io::Stream& in)
  {
#define CHECK_RESULT        \
    {                         \
    if(rr_OK != result)     \
    break;                \
  }

#define CHECK_STREAM_EX2(S) \
    {                           \
    if((S).Failed())          \
    {                         \
    result = rr_IOFailed;   \
    break;                  \
  }                         \
  }

    readResult result = rr_OK;
    BEGIN_BLOCK
    // determine file format
    unsigned char c;
    chunk_io::Read(in, c);
    CHECK_STREAM_EX(in);
    StepBack(in);
    CHECK_STREAM_EX(in);
    Clear();

    ChunkNode* pNode = GetTopNode();

    bool bScriptMode = (SIGN != c);
    if(bScriptMode)
    {
      m_curLine = 1;
      // [Header]
      skipWhiteSpace(in);
      CHECK_STREAM_EX(in);

      // just for compatibility
      readBrowseTime(in, bScriptMode);
      CHECK_STREAM_EX2(in);

      char name[MAX_NODE_NAME];
      readScriptName(in, ARRAY_ARG(name));
      CHECK_STREAM_EX2(in);

      skipWhiteSpace(in);
      CHECK_STREAM_EX2(in);

      pNode->m_name = std::string(name);
    }
    else
    {
      // [SIGN]
      in >> c;
      CHECK_STREAM_EX2(in);
      // [VER]
      in >> c;
      CHECK_STREAM_EX2(in);

      if(CHUNK_VERSION != c)
      {
        result = rr_BadFormat;
        break;
      }

      // [chNode]
      in >> c;
      CHECK_STREAM_EX2(in);
      if(chNode != c)
      {
        result = rr_BadFormat;
        break;
      }

      // [NAME]
      std::string str;
      ReadSZ(in, str);
      CHECK_STREAM_EX2(in);
      pNode->m_name = str;

      // just for compatibility
      readBrowseTime(in, bScriptMode); // return value is used 
      CHECK_STREAM_EX2(in); 
    }

    // [BTYPE]
    char browseType[MAX_BROWSE_TYPE];
    result = readBrowseType(in, ARRAY_ARG(browseType), bScriptMode);
    CHECK_RESULT;
    pNode->SetBrowsType(browseType);

    // [ACCESS]
    ChunkBrowsAccess access;
    result = readBrowseAccess(in, access, bScriptMode);
    CHECK_RESULT;
    if(access == baLikeParent)
      access = baPublic;
    pNode->SetBrowsAccess(access);

    // [COMMENT]
    pNode->m_browsComment.loadFrom(in, bScriptMode);
    CHECK_STREAM_EX2(in);

    if(bScriptMode)
    {
      skipWhiteSpace(in);
      CHECK_STREAM_EX2(in);
    }

    result = bScriptMode ? readScriptNode(in, pNode) : readBinaryNode(in, pNode);
    END_BLOCK

      if(rr_OK == result)
        return true;

    std::string sError = "";
    switch(result)
    {
    case rr_IOFailed:
      sError = "IO operation failure!";
      break;
    case rr_BadFormat:
      ReportBadFileFormat(in, m_curLine);
      sError = "file format mismatch";
      break;
    default:
      assert(!"unknown error!");
      sError = "unknown error!";
      break;
    }

    //  g_err.Printf("Failed to load chunk from stream <%s> due to error: <%s>\n", in.GetName(), sError.c_str()); 
    m_bGoodLooking = true;
    Clear();

    return false;

#undef CHECK_RESULT
#undef CHECK_STREAM_EX2
  }



  inline bool Chunk::LoadFrom( const char* szFileName )
  {  
    chunk_io::FileStream file;
    if (!file.Open(szFileName, chunk_io::SM_READ | chunk_io::SM_NOEXCEPT))
      return false;

    if( !LoadFrom(file) )
      return false;

    file.Close();
    return true;
  }

  inline bool Chunk::LoadFrom(std::string const& str)
  {
    chunk_io::MemStream mem(str.data(), static_cast<unsigned int>(str.size()), chunk_io::SM_READ | chunk_io::SM_NOEXCEPT);
    return LoadFrom(mem);
  }


  //--------------------------------------------------------------------------

  //// отступ
  //inline void Chunk::writeIndent(chunk_io::Stream& out) const
  //{
  //  unsigned const indent = m_bGoodLooking ? m_indent * TAB_SIZE : m_indent;
  //  for(unsigned i = 0; i < indent; ++i)
  //    out.Printf(" ");
  //}

  //// разделитель
  //inline void Chunk::writeDelim(chunk_io::Stream& out) const
  //{
  //  out << DELIM;
  //  writeNewLine(out);
  //}

  //inline void Chunk::writeTabIn(chunk_io::Stream& out, bool inScript) const
  //{
  //  if (!inScript)
  //  {
  //    out << chTabIn;
  //  }
  //  else
  //  {
  //    writeIndent(out);
  //    out << LP;
  //    ++m_indent;
  //  }
  //}

  inline Chunk::readResult Chunk::readTabIn(chunk_io::Stream& in, bool inScript)
  {
    unsigned char c;
    in >> c;
    if (!inScript)
    {
      if (c != chTabIn)
        return rr_BadFormat;
    }
    else
    {
      if (c != LP)
        return rr_BadFormat;
      skipWhiteSpace(in);
    }
    return in.Failed() ? rr_IOFailed : rr_OK;
  }


  //inline void Chunk::writeTabOut(chunk_io::Stream& out, bool inScript) const
  //{
  //  if (!inScript)
  //  {
  //    out << chTabOut;
  //  }
  //  else
  //  {
  //    //if (m_bGoodLooking)
  //      writeNewLine(out);
  //    m_indent--;
  //    writeIndent(out);
  //    out << RP;
  //  }
  //}

  inline void Chunk::readTabOut(chunk_io::Stream& in, bool inScript)
  {
    char c;
    in >> c;
    if (!inScript)
    {
      if (c != chTabOut)
        ReportBadFileFormat(in);
    }
    else
    {
      if (c != RP)
        ReportBadFileFormat(in, m_curLine);
      skipWhiteSpace(in);
    }
  }

  //inline void Chunk::writeBrowsList(chunk_io::Stream& out, bool inScript) const
  //{
  //  if (!inScript)
  //  {
  //    out << chBList;
  //  }
  //  else
  //  {
  //    out << CLONE;
  //  }
  //}

  inline bool Chunk::readBrowsList(chunk_io::Stream& in, bool inScript)
  {
    char c;
    in >> c;
    if ((!inScript && c != chBList) ||
      (inScript && c != CLONE))
    {
      StepBack(in);
      return false;
    }
    return true;
  }

  //inline bool Chunk::writeBinaryNode(chunk_io::Stream& out, const ChunkNode* node) const
  //{
  //  // Сохраним заголовок
  //  out << chNode;
  //  WriteSZ(out, node->GetName());
  //  CHECK_STREAM(out);
  //
  //  // сохраним броузерную информацию
  //  if (m_bGoodLooking)
  //  {
  //    // [%]
  //    if ((node->isBrowsList()) && (node != GetTopNode()))
  //    {
  //      writeBrowsList(out, false);
  //      CHECK_STREAM(out);
  //    }
  //  }
  //  // [chBType]
  //  if (!node->GetBrowsType().empty())
  //  {
  //    writeBrowseType(out, false, node->GetBrowsType());
  //    CHECK_STREAM(out);
  //  }
  //
  //  if (m_bGoodLooking)
  //  {
  //    // [chBAccess]
  //    if (node == GetTopNode())
  //    {
  //      if (node->GetBrowsAccess() != baPublic)
  //        writeBrowseAccess(out, false, node->GetBrowsAccess());
  //    }
  //    else
  //    {
  //      if (node->GetBrowsAccess() != baLikeParent)
  //        writeBrowseAccess(out, false, node->GetBrowsAccess());
  //    }
  //    CHECK_STREAM(out);
  //
  //    // [chBComment]
  //    node->m_browsComment.writeTo(out, false);
  //    CHECK_STREAM(out);
  //  }
  //
  //  writeTabIn(out, false);
  //  CHECK_STREAM(out);
  //
  //  // Пишем внутренние поля
  //  const ChunkItem* ownItem = node->GetFirstChildItem();
  //  while (!ownItem->isBad())
  //  {
  //    if(false == writeBinaryItem(out, ownItem))
  //      return false;
  //    ownItem = ownItem->GetNextBrother();
  //  }
  //
  //  // Пишем внутренние ветки(узлы)
  //  const ChunkNode* ownNode = node->GetFirstChildNode();
  //  while (!ownNode->isBad())
  //  {
  //    if(false == writeBinaryNode(out, ownNode))
  //      return false;
  //    ownNode = ownNode->GetNextBrother();
  //  }
  //
  //  writeTabOut(out, false);
  //  CHECK_STREAM(out);
  //
  //  return true;
  //}

  inline Chunk::readResult Chunk::readBinaryNode(chunk_io::Stream& in, ChunkNode* pParent)
  {
#define CHECK_RESULT(expr)    \
    {                             \
    readResult result = (expr); \
    if(rr_OK != result)         \
    return result;            \
  }

    // [chTabIn]
    CHECK_RESULT(readTabIn(in, false));

    unsigned char c;
    while (true)
    {
      in >> c;
      switch (c)
      {
      case chNode:
        {
          // [NAME]
          char str[MAX_NODE_NAME];
          ReadSZ(in, ARRAY_ARG(str));
          CHECK_STREAM_EX(in);

          ChunkNode* pNode = NULL;
          // [@] TEMP for compatibility, Remove it nafig later!
          readBrowseTime(in, false);
          CHECK_STREAM_EX(in);

          // [%]
          bool isList = readBrowsList(in, false);
          CHECK_STREAM_EX(in);
          if(pParent)
          {
            pNode = allocNode(WiseAllocateString(str), pParent);
            pNode->regMeNow(pParent);

            // Notify user of chunk
            if(m_user)
              m_user->OnNodeChange(pNode, ChunkUser::acAdd);
          }
          pNode->SetBrowsList(isList);

          //[chBType]
          char browseType[MAX_BROWSE_TYPE];
          CHECK_RESULT(readBrowseType(in, ARRAY_ARG(browseType), false));
          pNode->SetBrowsType(browseType);

          // [chBAccess]
          ChunkBrowsAccess access;
          CHECK_RESULT(readBrowseAccess(in, access, false));
          pNode->SetBrowsAccess(access);

          // [chBComment]
          pNode->m_browsComment.loadFrom(in, false);
          CHECK_STREAM_EX(in);
          CHECK_RESULT(readBinaryNode(in, pNode));
        }
        break;
      case chTabOut:
        return rr_OK;
      default:
        StepBack(in);
        CHECK_STREAM_EX(in);
        CHECK_RESULT(readBinaryItem(in, pParent));
      }
    }

#undef CHECK_RESULT
  }

  //inline void Chunk::writeType(chunk_io::Stream& out, bool inScript, ChunkItemType type) const
  //{
  //  if (!inScript)
  //  {
  //    out << char(type);
  //  }
  //  else
  //  {
  //    out.Printf("%s ", itemTypeToString(type));
  //  }
  //}

  inline Chunk::readResult Chunk::readType(chunk_io::Stream& in , ChunkItemType& type, bool inScript)
  {
    ChunkItemType res = chLast;
    if (!inScript)
    {
      unsigned char c;
      in >> c;
      res = ChunkItemType(c);
      if (res < 0 || res >= chLast)
        return rr_BadFormat;
    }
    else
    {
      char sType[MAX_TYPE_NAME];
      ReadSZ(in, ARRAY_ARG(sType));
      if(in.Failed())
        return rr_IOFailed;
      res = stringToItemType( sType );
      if (res < 0 || res >= chLast)
        return rr_BadFormat;
    }
    type = res;
    return rr_OK;
  }

  //inline void Chunk::writeBrowsRange(chunk_io::Stream& out, bool inScript, const ChunkItem* item) const
  //{
  //  bool haveRange = false;  // "range specified"; for scripts
  //
  //  char sMin[MAX_VALUE_LEN], sMax[MAX_VALUE_LEN], sStep[MAX_VALUE_LEN];
  //#define INT2STR(v,s)    chunk_fmt::sprintf(ARRAY_ARG(s), "%d",    v)
  //#define FLOAT2STR(v,s)  chunk_fmt::sprintf(ARRAY_ARG(s), "%g",    v)
  //#define INT642STR(v,s)  chunk_fmt::sprintf(ARRAY_ARG(s), "%I64d", v)
  //
  //  switch (item->GetType())
  //  {
  //  case chByte:
  //    {
  //      unsigned char minByte, maxByte, stepByte;
  //      item->GetByteRange(minByte, maxByte);
  //      if ((minByte != MIN_BYTE) || (maxByte != MAX_BYTE))
  //      {
  //        haveRange = true;
  //        if (!inScript)
  //        {
  //          out << chBRange << minByte << maxByte;
  //        }
  //        else
  //        {
  //          INT2STR(minByte, sMin);
  //          INT2STR(maxByte, sMax);
  //        }
  //      }
  //      item->GetByteStep(stepByte);
  //      if (!inScript && stepByte != 0)
  //      {
  //        out << chBStep << stepByte;
  //      }
  //      else
  //      {
  //        INT2STR(stepByte, sStep);
  //      }
  //    }
  //    break;
  //  case chInt32:
  //    {
  //      int32 minInt32, maxInt32, stepInt32;
  //      item->GetInt32Range(minInt32, maxInt32);
  //      if ((minInt32 != MIN_INT32) || (maxInt32 != MAX_INT32))
  //      {
  //        haveRange = true;
  //        if (!inScript)
  //        {
  //          out << chBRange << minInt32 << maxInt32;
  //        }
  //        else
  //        {
  //          INT2STR(minInt32, sMin);
  //          INT2STR(maxInt32, sMax);
  //        }
  //      }
  //      item->GetInt32Step(stepInt32);
  //      if (!inScript && stepInt32 != 0)
  //      {
  //        out << chBStep << stepInt32;
  //      }
  //      else
  //      {
  //        INT2STR(stepInt32, sStep);
  //      }
  //    }
  //    break;
  // /* case chInt64:
  //    {
  //      int64 minInt64, maxInt64, stepInt64;
  //      item->GetInt64Range(minInt64, maxInt64);
  //      if ((minInt64 != MIN_INT64) || (maxInt64 != MAX_INT64))
  //      {
  //        haveRange = true;
  //        if (!inScript)
  //        {
  //          out << chBRange << minInt64 << maxInt64;
  //        }
  //        else
  //        {
  //          INT642STR(minInt64, sMin);
  //          INT642STR(maxInt64, sMax);
  //        }
  //      }
  //      item->GetInt64Step(stepInt64);
  //      if (!inScript && stepInt64 != 0)
  //      {
  //        out << chBStep << stepInt64;
  //      }
  //      else
  //      {
  //        INT642STR(stepInt64, sStep);
  //      }
  //    }
  //    break;*/
  //  case chFloat:
  //    {
  //      float minFloat, maxFloat, stepFloat;
  //      item->GetFloatRange(minFloat, maxFloat);
  //      if ((minFloat != MIN_FLOAT) || (maxFloat != MAX_FLOAT))
  //      {
  //        haveRange = true;
  //        if (!inScript)
  //        {
  //          out << chBRange << minFloat << maxFloat;
  //        }
  //        else
  //        {
  //          FLOAT2STR(minFloat, sMin);
  //          FLOAT2STR(maxFloat, sMax);
  //        }
  //      }
  //      item->GetFloatStep(stepFloat);
  //      if (!inScript && stepFloat != 0)
  //      {
  //        out << chBStep << stepFloat;
  //      }
  //      else
  //      {
  //        FLOAT2STR(stepFloat, sStep);
  //      }
  //    }
  //    break;
  //  case chString:
  //    {
  //      int32 minString, maxString;
  //      item->GetStringRange(minString, maxString);
  //      if ((minString != MIN_STRING) || (maxString != MAX_STRING))
  //      {
  //        haveRange = true;
  //        if (!inScript)
  //        {
  //          out << chBRange << minString << maxString;
  //        }
  //        else
  //        {
  //          INT2STR(minString, sMin);
  //          INT2STR(maxString, sMax);
  //        }
  //      }
  //    }
  //    break;
  //  }
  //
  //  if (inScript)
  //  {
  //    bool haveStep = item->GetType() != chString && strcmp(sStep, "0") != 0;
  //    if (haveRange && haveStep)
  //      out.Printf(" (%s, %s, %s)", sMin, sMax, sStep);
  //    else if (haveRange && !haveStep)
  //      out.Printf(" (%s, %s)", sMin, sMax);
  //    else if (/*HERE: !specRange &&*/ haveStep)
  //      out.Printf(" (%s)", sStep);
  //  }
  //}

  inline Chunk::readResult Chunk::readBrowseRange(chunk_io::Stream& in, bool inScript, ChunkItem* item, ChunkItemType type)
  {
    unsigned char c;
    if (!inScript)
    {
      in >> c;
      if (c != chBRange)
      {
        // range not specified
        StepBack(in);
        return rr_OK;
      }

      switch (type)
      {
      case chByte:
        {
          unsigned char min, max;
          in >> min >> max;
          item->SetByteRange(min, max);
        }
        break;
      case chInt32:
        {
          int32 min, max;
          in >> min >> max;
          item->SetInt32Range(min, max);
        }
        break;
        /* case chInt64:
        {
        int64 min, max;
        in >> min >> max;
        item->SetInt64Range(min, max);
        }
        break;*/
      case chFloat:
        {
          float min, max;
          in >> min >> max;
          item->SetFloatRange(min, max);
        }
        break;
      case chString:
        {
          int32 min, max;
          in >> min >> max;
          item->SetStringRange(min, max);
        }
        break;
      }
      return in.Failed() ? rr_IOFailed : rr_OK;
    }

    // script range
    in >> c;
    if (c != '(')
    {
      // range not specified
      StepBack(in);
      return in.Failed() ? rr_IOFailed : rr_OK;
    }
    skipWhiteSpace(in);
    CHECK_STREAM_EX(in);

    char min[MAX_VALUE_LEN], max[MAX_VALUE_LEN], step[MAX_VALUE_LEN];
    ReadString(in, ARRAY_ARG(min), " \r\n\t,)#");
    CHECK_STREAM_EX(in);
    skipWhiteSpace(in);
    CHECK_STREAM_EX(in);
    in >> c;
    CHECK_STREAM_EX(in);
    if (c==')')
    {							 //C| В скобках задано 1 число - min трактуем как step
      switch (type)
      {
      case chByte:
        item->SetByteStep((unsigned char)(chunk_fmt::StrToInt(min)));
        break;
      case chInt32:
        item->SetInt32Step(chunk_fmt::StrToInt32(min));
        break;
      case chFloat:
        item->SetFloatStep(chunk_fmt::StrToFloat(min));
        break;
      case chString: //C-Если у строки в скобках одно число - это максимум. Минимум-0.
        item->SetStringRange(0, chunk_fmt::StrToInt32(min));
        break;
      }
      skipWhiteSpace(in);
      CHECK_STREAM_EX(in);
    }
    else  //С-После одного числа задано еще что-то - значит, должно быть задано еще как минимум одно число
    {
      if (c != ',')                 //|C
        return rr_BadFormat;
      skipWhiteSpace(in);
      CHECK_STREAM_EX(in);
      ReadString(in, ARRAY_ARG(max), " \r\t\n,)#");
      CHECK_STREAM_EX(in);
      skipWhiteSpace(in);
      CHECK_STREAM_EX(in);

      in >> c;
      if (c==',')
      {			   //C| Еще одна запятая - ожидаем, что задан еще и шаг.
        if (type==chString)
          return rr_BadFormat;
        skipWhiteSpace(in);
        CHECK_STREAM_EX(in);
        ReadString(in, ARRAY_ARG(step), " \t\r\n,)#");
        CHECK_STREAM_EX(in);
        skipWhiteSpace(in);
        CHECK_STREAM_EX(in);
        in >> c;
        CHECK_STREAM_EX(in);
      };
      if (c != ')')
        return rr_OK;
      switch (type)
      {
      case chByte:
        item->SetByteRange(static_cast<unsigned char>(chunk_fmt::StrToInt(min)), static_cast<unsigned char>(chunk_fmt::StrToInt(max)));
        item->SetByteStep(static_cast<unsigned char>(chunk_fmt::StrToInt(step)));	//C-
        break;
      case chInt32:
        item->SetInt32Range(chunk_fmt::StrToInt32(min), chunk_fmt::StrToInt32(max));
        item->SetInt32Step(chunk_fmt::StrToInt32(step));//C-
        break;
      case chFloat:
        item->SetFloatRange(chunk_fmt::StrToFloat(min), chunk_fmt::StrToFloat(max));
        item->SetFloatStep(chunk_fmt::StrToFloat(step)); //C-
        break;
      case chString:
        item->SetStringRange(chunk_fmt::StrToInt32(min), chunk_fmt::StrToInt32(max));
        break;
      }
    };
    skipWhiteSpace(in);
    return in.Failed() ? rr_IOFailed : rr_OK;
  }

  inline void Chunk::readBinaryStep(chunk_io::Stream& in, ChunkItem* item, ChunkItemType type)//C|Читает шаг из бинарника
  {
    char c;
    in >> c;
    if (c != chBStep)
    {
      // range not specified
      StepBack(in);
      return;
    };

    switch (type)
    {
    case chByte:
      {
        unsigned char step;
        in >> step;
        item->SetByteStep(step);
      }
      break;
    case chInt32:
      {
        int32 step;
        in >> step;
        item->SetInt32Step(step);
      }
      break;
      /* case chInt64:
      {
      int64 step;
      in >> step;
      item->SetInt64Step(step);
      }
      break;*/
    case chFloat:
      {
        float step;
        in >> step;
        item->SetFloatStep(step);
      }
      break;
    }
  } //|C

  //inline bool Chunk::writeBinaryItem(chunk_io::Stream& out, const ChunkItem* item) const
  //{
  //  ChunkItemType itemType = item->GetType();
  //  // [chByte, chFloat ...]
  //  writeType(out, false, itemType);
  //  CHECK_STREAM(out);
  //  // [NAME]
  //  WriteSZ(out, item->GetName());
  //  CHECK_STREAM(out);
  //
  //  // [chBType]
  //  if (!item->GetBrowsType().empty())
  //  {
  //    writeBrowseType(out, false, item->GetBrowsType());
  //    CHECK_STREAM(out);
  //  }
  //
  //  // [chValue]
  //  out << chValue;
  //
  //  switch (itemType)
  //  {
  //  case chByte:
  //    {
  //      unsigned char v = item->GetByte();
  //      out << v;
  //    }
  //    break;
  //  case chInt32:
  //    {
  //      int32 v = item->GetInt32();
  //      out << v;
  //    }
  //    break;
  //  /*case chInt64:
  //    {
  //      int64 v = item->GetInt64();
  //      out << v;
  //    }
  //    break;*/
  //  case chFloat:
  //    {
  //      float v = item->GetFloat();
  //      out << v;
  //    }
  //    break;
  //  case chString:
  //    WriteSZ(out, item->GetString());
  //    break;
  //  default:
  //    ReportBadType(item);
  ////    Sys_DebugBreak();
  //  }
  //  CHECK_STREAM(out);
  //
  //  if (m_bGoodLooking)
  //  {
  //    // [chBRange]
  //    writeBrowsRange(out, false, item);
  //    CHECK_STREAM(out);
  //    // [chBAccess]
  //    if (item->GetBrowsAccess() != baLikeParent)
  //    {
  //      writeBrowseAccess(out, false, item->GetBrowsAccess());
  //      CHECK_STREAM(out);
  //    }
  //    // [chBComment]
  //    item->GetBrowsComment().writeTo(out, false);
  //    CHECK_STREAM(out);
  //  }
  //  
  //  return true;
  //}

  inline Chunk::readResult Chunk::readBinaryItem(chunk_io::Stream& in, ChunkNode* parent)
  {
#define CHECK_RESULT(expr)    \
    {                             \
    readResult result = (expr); \
    if(rr_OK != result)         \
    return result;            \
  }

    // [chByte, chFloat...]
    ChunkItemType type;
    CHECK_RESULT(readType(in, type, false));

    // [NAME]
    char name[MAX_ITEM_NAME];
    ReadSZ(in, ARRAY_ARG(name));
    CHECK_STREAM_EX(in);

    // [@] TEMP For compatibility. Remove it nafig later!
    readBrowseTime(in, false);
    CHECK_STREAM_EX(in);

    // [chBType]
    char browseType[MAX_BROWSE_TYPE];
    CHECK_RESULT(readBrowseType(in, ARRAY_ARG(browseType), false));

    ChunkItem* item = NULL;

    // [chValue]
    unsigned char c;
    in >> c;
    if (chValue != c)
      return rr_BadFormat;

    switch(type)
    {
    case chByte:
      {
        unsigned char val;
        in >> val;
        item = parent->Add(name, val);
      }
      break;
    case chInt32:
      {
        int32 val;
        in >> val;
        item = parent->Add(name, val);
      }
      break;
      /* case chInt64:
      {
      int64 val;
      in >> val;
      item = parent->Add(name, val);
      }
      break;*/
    case chFloat:
      {
        float val;
        in >> val;
        item = parent->Add(name, val);
      }
      break;
    case chString:
      {
        char sValue[MAX_STR_VALUE_LEN];
        ReadSZ(in, ARRAY_ARG(sValue));
        item = parent->Add(name, WiseAllocateString(sValue));
      }
      break;
    }
    CHECK_STREAM_EX(in);
    item->SetBrowsType(browseType);

    // [chBRange]
    CHECK_RESULT(readBrowseRange(in, false, item, type));
    // [chBStep]
    readBinaryStep(in, item, type);
    CHECK_STREAM_EX(in);

    // [chBAccess]
    ChunkBrowsAccess access;
    CHECK_RESULT(readBrowseAccess(in, access, false));
    item->SetBrowsAccess(access);
    // [chBComment]

    item->m_browsComment.loadFrom(in, false);

    return in.Failed() ? rr_IOFailed : rr_OK;
  }


  //inline bool Chunk::writeScriptNode(chunk_io::Stream& out, const ChunkNode* node) const
  //{
  //  writeNewLine(out);
  //  CHECK_STREAM(out);
  //  writeIndent(out);
  //  CHECK_STREAM(out);
  //  //[%]
  //  if (node->isBrowsList())
  //  {
  //    writeBrowsList(out, true);
  //    CHECK_STREAM(out);
  //  }
  //  // [NAME]
  //  writeScriptName(out, node->GetName().c_str());
  //  CHECK_STREAM(out);
  //
  //  // [chBType]
  //  if (!node->GetBrowsType().empty())
  //  {
  //    writeBrowseType(out, true, node->GetBrowsType());
  //    CHECK_STREAM(out);
  //  }
  //  if (m_bGoodLooking)
  //  {
  //    // [chBAcceess]
  //    if (node == GetTopNode())
  //    {
  //      if (node->GetBrowsAccess() != baPublic)
  //        writeBrowseAccess(out, true, node->GetBrowsAccess());
  //    }
  //    else
  //    {
  //      if (node->GetBrowsAccess() != baLikeParent)
  //        writeBrowseAccess(out, true, node->GetBrowsAccess());
  //    }
  //    CHECK_STREAM(out);
  //    //[chBComment]
  //    node->GetBrowsComment().writeTo(out, true);
  //    CHECK_STREAM(out);
  //  }
  //
  //
  //  writeNewLine(out);
  //  CHECK_STREAM(out);
  //
  //  // [chTabIn]
  //  writeTabIn(out, true);
  //  CHECK_STREAM(out);
  //
  //  // Пишем внутренние поля
  //  const ChunkItem* ownItem = node->GetFirstChildItem();
  //  while (!ownItem->isBad())
  //  {
  //    if(false == writeScriptItem(out, ownItem))
  //      return false;
  //    ownItem = ownItem->GetNextBrother();
  //  }
  //
  //  // Пишем внутренние ветки(узлы)
  //  const ChunkNode* ownNode = node->GetFirstChildNode();
  //  while (!ownNode->isBad())
  //  {
  //    if(false == writeScriptNode(out, ownNode))
  //      return false;
  //    ownNode = ownNode->GetNextBrother();
  //  }
  //
  //  // [chTabOut]
  //  writeTabOut(out, true);
  //  CHECK_STREAM(out);
  //
  //  return true;
  //}

  inline Chunk::readResult Chunk::readScriptNode(chunk_io::Stream& in, ChunkNode* parent)
  {
    // [TABIN]
    CHECK_RESULT(readTabIn(in, true));

    unsigned char c;
    while (true)
    {
      in >> c;
      if(c == RP)
        return rr_OK;

      StepBack(in);
      CHECK_STREAM_EX(in);

      // [@] TEMP For compatibility. Remove it nafig later!
      readBrowseTime(in, true);
      CHECK_STREAM_EX(in);

      bool isList = readBrowsList(in, true);
      CHECK_STREAM_EX(in);

      // [NAME]
      char str[MAX_NODE_NAME];
      readScriptName(in, ARRAY_ARG(str));
      skipWhiteSpace(in);
      CHECK_STREAM_EX(in);

      ChunkItemType type = stringToItemType(str);
      if (type < chLast)
      {
        // [ITEM]
        if(isList)
          return rr_BadFormat;
        CHECK_RESULT(readScriptItem(in, parent, type));
        continue;
      }
      // [NODE] 
      ChunkNode* node = NULL;
      if (parent){
        //node = parent->Add(str);

        node = allocNode(WiseAllocateString(str), parent);
        node->regMeNow(parent);

        // Notify user of chunk
        if( m_user )
          m_user->OnNodeChange(node, ChunkUser::acAdd);
      }

      // [BTYPE]
      char browseType[MAX_BROWSE_TYPE];
      CHECK_RESULT(readBrowseType(in, ARRAY_ARG(browseType), true));
      node->SetBrowsType(browseType);

      // [ACCESS]
      ChunkBrowsAccess access;
      CHECK_RESULT(readBrowseAccess(in, access, true));
      // [COMMENT]
      node->m_browsComment.loadFrom(in, true);
      CHECK_STREAM_EX(in);

      skipWhiteSpace(in);
      CHECK_STREAM_EX(in);

      node->SetBrowsList(isList);
      node->SetBrowsAccess(access);

      CHECK_RESULT(readScriptNode(in, node));
      skipWhiteSpace(in);
      CHECK_STREAM_EX(in);
    }
  }

  //inline bool Chunk::writeScriptItem(chunk_io::Stream& out, const ChunkItem* item) const
  //{
  //  writeNewLine(out);
  //  CHECK_STREAM(out);
  //  writeIndent(out);
  //  CHECK_STREAM(out);
  //
  //  ChunkItemType itemType = item->GetType();
  //  // [chByte, chFloat ...]
  //  writeType(out, true, itemType);
  //  CHECK_STREAM(out);
  //
  //  // [NAME]
  //  writeScriptName(out, item->GetName().c_str());
  //  CHECK_STREAM(out);
  //  out.Printf("%s=", m_bGoodLooking ? " " : "");
  //  CHECK_STREAM(out);
  //  // [chBType]
  //  if (!item->GetBrowsType().empty())
  //  {
  //    writeBrowseType(out, true, item->GetBrowsType());
  //    CHECK_STREAM(out);
  //  }
  //  // [chValue]
  //  if (m_bGoodLooking)
  //  {
  //    out << ' ';
  //    CHECK_STREAM(out);
  //  }
  //  switch (itemType)
  //  {
  //  case chByte:
  //    out.Printf("%d", item->GetByte());
  //    break;
  //  case chInt32:
  //    out.Printf("%d", item->GetInt32());
  //    break;
  //  case chInt64:
  //    out.Printf("%I64d", item->GetInt64());
  //    break;
  //  case chFloat:
  //    out.Printf("%f", item->GetFloat());
  //    break;
  //  case chString:
  //    WriteQuotedString(out, item->GetString());
  //    break;
  //  default:
  //    ReportBadType(item);
  ////    Sys_DebugBreak();
  //  }
  //  CHECK_STREAM(out);
  //
  //  if (m_bGoodLooking)
  //  {
  //    // [chBRange]
  //    writeBrowsRange(out, true, item);
  //    CHECK_STREAM(out);
  //    // [chBAccess]
  //    if (item->GetBrowsAccess() != baLikeParent)
  //    {
  //      writeBrowseAccess(out, true, item->GetBrowsAccess());
  //      CHECK_STREAM(out);
  //    }
  //    // [chBComment]
  //    item->GetBrowsComment().writeTo(out, true);
  //  }
  //  out << DELIM;
  //  CHECK_STREAM(out);
  //
  //  return true;
  //}

  inline Chunk::readResult Chunk::readScriptItem(chunk_io::Stream& in, ChunkNode* parent, ChunkItemType type)
  {
    // [@] TEMP For compatibility. Remove it nafig later!
    readBrowseTime(in, true);
    CHECK_STREAM_EX(in);

    // [NAME]
    char name[MAX_ITEM_NAME];
    readScriptName(in, ARRAY_ARG(name));
    CHECK_STREAM_EX(in);
    skipWhiteSpace(in);
    // [ = ]
    char c;
    in >> c;
    CHECK_STREAM_EX(in);
    if (c != '=')
      return rr_BadFormat;

    skipWhiteSpace(in);
    CHECK_STREAM_EX(in);

    // [BROWS_TYPE]
    char browseType[MAX_BROWSE_TYPE];
    CHECK_RESULT(readBrowseType(in, ARRAY_ARG(browseType), true));

    // [VALUE]
    ChunkItem* item = NULL;
    char value[MAX_VALUE_LEN];
    switch(type)
    {
    case chByte:
      ReadString(in, ARRAY_ARG(value), " <[;(\t\r\n");
      item = parent->Add(name, (unsigned char)chunk_fmt::StrToInt(value));
      skipWhiteSpace(in);
      break;

    case chInt32:
      ReadString(in, ARRAY_ARG(value), " <[;(\t\r\n");
      item = parent->Add(name, chunk_fmt::StrToInt32(value));
      skipWhiteSpace(in);
      break;
    case chFloat:
      ReadString(in, ARRAY_ARG(value), " <[;(\t\r\n");
      item = parent->Add(name, chunk_fmt::StrToFloat(value));
      skipWhiteSpace(in);
      break;

    case chString:
      {
        in >> c;
        if (c != '\"')
          return rr_BadFormat;

        //char sValue[MAX_STR_VALUE_LEN];
        std::string sValue;
        readString(in, sValue);
        skipWhiteSpace(in);
        item = parent->Add(name, sValue);
      }
      break;
    }
    CHECK_STREAM_EX(in);

    // [chBRange]
    CHECK_RESULT(readBrowseRange(in, true, item, type));
    // [chBAccess]
    ChunkBrowsAccess access;
    CHECK_RESULT(readBrowseAccess(in, access, true));

    // [chBComment]
    item->m_browsComment.loadFrom(in, true);
    CHECK_STREAM_EX(in);

    skipWhiteSpace(in);
    CHECK_STREAM_EX(in);

    item->SetBrowsType(browseType);
    item->SetBrowsAccess(access);

    in >> c;
    if (c != DELIM)
      return rr_BadFormat;

    skipWhiteSpace(in);

    return in.Failed() ? rr_IOFailed : rr_OK;
  }
  //                                                                           //
  //  DataStore Area                                                    =END=  //
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  //  CLone labs                                                       =BEGIN= //
  //                                                                           //

  inline ChunkNode* ChunkNode::CloneMe(ChunkNode* cloneParent, const std::string& cloneName) const
  {
    ChunkNode* cloneNode = NULL;

    bool bUseDangerous = false;
    if (!cloneName.empty()){
      cloneNode = cloneParent->findNode(cloneName);
      if (cloneNode->isBad()){
        cloneNode = cloneParent->DangerousAddNode(cloneName);
        bUseDangerous = true;
      }
    }
    else
      cloneNode = cloneParent; 

    cloneNode->m_browsType    = m_browsType;
    cloneNode->m_browsComment = m_browsComment;
    cloneNode->m_browsAccess  = m_browsAccess;
    cloneNode->m_browsList    = m_browsList;

    // Клонируем поля
    const ChunkItem* item = GetFirstChildItem();
    while(!item->isBad())
    {
      item->CloneMe(cloneNode);
      item = item->GetNextBrother();
    }
    // Клонируем ветки
    const ChunkNode* node = GetFirstChildNode();
    while(!node->isBad())
    {
      if(bUseDangerous)
        node->DangerousCloneMe(cloneNode, node->GetName());
      else
        node->CloneMe(cloneNode, node->GetName());
      node = node->GetNextBrother();
    }
    return cloneNode;
  }

  inline ChunkNode* ChunkNode::DangerousCloneMe(ChunkNode* cloneParent, const std::string& cloneName) const
  {
    ChunkNode* cloneNode = NULL;

    if (!cloneName.empty())
      cloneNode = cloneParent->DangerousAddNode(cloneName);
    else
      cloneNode = cloneParent;

    cloneNode->m_browsType    = m_browsType;
    cloneNode->m_browsComment = m_browsComment;
    cloneNode->m_browsAccess  = m_browsAccess;
    cloneNode->m_browsList    = m_browsList;

    // Клонируем поля
    const ChunkItem* item = GetFirstChildItem();
    while(!item->isBad())
    {
      item->CloneMe(cloneNode);
      item = item->GetNextBrother();
    }
    // Клонируем ветки
    const ChunkNode* node = GetFirstChildNode();
    while(!node->isBad())
    {
      node->DangerousCloneMe(cloneNode, node->GetName());
      node = node->GetNextBrother();
    }
    return cloneNode;
  }

  inline ChunkItem* ChunkItem::CloneMe(ChunkNode* cloneParent, const std::string& cloneName) const
  {
    assert(cloneParent);

    const char* itemName = (cloneName.empty()) ? GetName().c_str() : cloneName.c_str();
    ChunkItem* res = NULL;

    switch (GetType())
    {
    case chByte:
      res = cloneParent->Add(itemName, GetByte());
      break;
    case chInt32:
      res = cloneParent->Add(itemName, GetInt32());
      break;
    case chInt64:
      res = cloneParent->Add(itemName, GetInt64());
      break;
    case chFloat:
      res = cloneParent->Add(itemName, GetFloat());
      break;
    case chString:
      res = cloneParent->Add(itemName, GetString());
      break;
    }
    res->m_browsType    = m_browsType;
    res->m_browsComment = m_browsComment;
    if( res->m_browsAccess == baLikeParent || res->m_browsAccess == baPublic )
      res->m_browsAccess  = m_browsAccess;
    switch (GetType())
    {
    case chByte:
      {
        if ( (m_minByte != MIN_BYTE) || (m_maxByte != MAX_BYTE))
        {
          res->m_minByte = m_minByte;
          res->m_maxByte = m_maxByte;
        }
        if( m_stepByte != 0)
          res->m_stepByte= m_stepByte;
      } break;
    case chInt32:
      {
        if ( (m_minInt32 != MIN_INT32) || (m_maxInt32 != MAX_INT32))
        {
          res->m_minInt32 = m_minInt32;
          res->m_maxInt32 = m_maxInt32;
        }
        if( m_stepInt32 != 0)
          res->m_stepInt32= m_stepInt32;
      } break;
    case chInt64:
      {
        if ( (m_minInt64 != MIN_INT64) || (m_maxInt64 != MAX_INT64))
        {
          res->m_minInt64 = m_minInt64;
          res->m_maxInt64 = m_maxInt64;
        }
        if( m_stepInt64 != 0)
          res->m_stepInt64= m_stepInt64;
      } break;
    case chFloat:
      {
        if ( (m_minFloat != MIN_FLOAT) || (m_maxFloat != MAX_FLOAT))
        {
          res->m_minFloat = m_minFloat;
          res->m_maxFloat = m_maxFloat;
        }
        if( m_stepFloat != 0)
          res->m_stepFloat= m_stepFloat;
      } break;
    case chString:
      {
        if ( (m_minString != MIN_STRING) || (m_maxString != MAX_STRING))
        {
          res->m_minString= m_minString;
          res->m_maxString= m_maxString;
        }
      } break;
    }
    return res;
  }
  inline bool ChunkNode::mergeItem(ChunkItem* dest, const ChunkItem* source, std::list<ChunkItem*>* useList, const Librarium* pLibrarium, bool bMergeConst )
  {
    // Syncronize item name
    if( !chunk_fmt::reverse_stricmp(dest->GetName(), source->GetName()) )
      dest->m_name = source->m_name;

    if (useList)
    {
      std::list<ChunkItem*>::iterator i = std::find(useList->begin(), useList->end(), source);
      if (i == useList->end())
        return true;
    }

    if (dest->GetType() != source->GetType())
      return false;

    if(!bMergeConst && dest->GetBrowsAccess() == baConst)
      return true;

    bool isChange = false;
    switch (dest->GetType())
    {
    case chByte:
      if (dest->GetByte() != source->GetByte())
        isChange = true;
      if( !dest->Set(source->GetByte(), true) )
        return false;
      break;
    case chInt32:
      if (dest->GetInt32() != source->GetInt32())
        isChange = true;
      if( !dest->Set(source->GetInt32(), true) )
        return false;
      break;
    case chInt64:
      if (dest->GetInt64() != source->GetInt64())
        isChange = true;
      if( !dest->Set(source->GetInt64(), true) )
        return false;
      break;
    case chFloat:
      if (dest->GetFloat() != source->GetFloat())
        isChange = true;
      if( !dest->Set(source->GetFloat(), true) )
        return false;
      break;
    case chString:
      if (dest->GetString() != source->GetString())
        isChange = true;
      if( !dest->Set(source->GetString(), true ) )
        return false;
      break;
    }
    return true;
  }

  inline bool ChunkNode::mergeNode(ChunkNode* dest, const ChunkNode* source, std::list<ChunkItem*>* useList, bool inList, const Librarium* pLibrarium, bool bMergeConst)
  {
    bool res = true;

    // Syncronize node name
    if( !chunk_fmt::reverse_stricmp(dest->GetName(), source->GetName()) )
      dest->m_name = source->m_name;

    if (source->isBrowsList())
      inList = true;


    // Скопировать в dest значение или добавить шаблонный item
    const ChunkItem* sourceItem = source->GetFirstChildItem();
    if(sourceItem->isGood()){
      ChunkItem* destItem =  dest->GetItem(sourceItem->GetName());
      ChunkItem* lastGoodItem = destItem->isBad()? dest->GetFirstChildItem(): destItem;
      if(lastGoodItem->isGood()){
        for(;;/*sourceItem->isGood()*/)
        {
          //        ChunkItem* destItem = dest->GetItem(sourceItem->GetName());
          if( destItem->isGood() )
          {
            lastGoodItem = destItem;
            bool tRes = mergeItem(destItem, sourceItem, useList, pLibrarium, bMergeConst);
            if( !tRes)
              res = tRes;
          } else 
          {
            res = false;
          }
          sourceItem = sourceItem->GetNextBrother();
          if(sourceItem->isGood())
            destItem = lastGoodItem->GetBrother(sourceItem->GetName());
          else
            break;
        }
      }else
        res = false;//There is no items in dest at all
    }

    // Удаление "лишних" node в dest
    if (inList)
    {
      ChunkNode* destNode = dest->GetFirstChildNode();
      if(destNode->isGood()){
        const ChunkNode* sourceNode = source->GetNode(destNode->GetName());
        const ChunkNode* lastGoodNode = sourceNode->isBad()? source->GetFirstChildNode(): sourceNode;
        for(;;)
        {
          if ( sourceNode->isBad() ){
            // пропустить не шаблонную node
            if( !destNode->GetBrowsType().empty() && dest->GetBrowsType().find(destNode->GetBrowsType())!=std::string::npos ){
              // сгенерировать событие
              if( !m_owner->m_user || SUCCEEDED(m_owner->m_user->OnNodeChange(destNode, ChunkUser::acRemove)) ){
                if( GetOwner()->NotifyNodeChanging( dest, destNode->GetName(), destNode, true ) ){
                  ChunkNode* pDelNode = destNode;
                  const std::string& name = pDelNode->GetName();
                  destNode = destNode->GetNextBrother();
                  m_owner->delNode(pDelNode);
                  //dest->DeleteNode(name);
                  //C-
                  if (m_owner->m_user)
                    m_owner->m_user->OnNodeChange(dest, ChunkUser::acRemoved);
                  GetOwner()->NotifyNodeChanged( dest, name, NULL, true );
                  if(destNode->isGood()){
                    sourceNode = lastGoodNode->GetBrother(destNode->GetName());
                    continue;
                  }else
                    break;
                }
              }
            }
          }else
            lastGoodNode = sourceNode;

          destNode = destNode->GetNextBrother();
          if(destNode->isGood())
            sourceNode = lastGoodNode->GetBrother(destNode->GetName());
          else
            break;
        }
      }
    }

    // Скопировать в dest значения или добавить шаблонную node
    const ChunkNode* sourceNode = source->GetFirstChildNode();
    if(sourceNode->isGood()){
      ChunkNode* destNode = dest->GetNode(sourceNode->GetName());
      ChunkNode* lastGoodNode = destNode->isBad()? dest->GetFirstChildNode(): destNode;
      for(;;)
      {
        if (destNode->isBad()){
          if ( inList ){
            // пропустить не шаблонную node
            if( !sourceNode->GetBrowsType().empty() && dest->GetBrowsType().find(sourceNode->GetBrowsType())!=std::string::npos ){
              GetOwner()->NotifyNodeChanging( dest, sourceNode->GetName(), NULL, false );
              ChunkNode* newNode = NULL;
              /*if( pLibrarium )
              {
              pLibrarium->CreateType( sourceNode->GetBrowsType(), dest, sourceNode->GetName() );
              newNode = dest->GetLastChildNode();
              newNode->Merge( sourceNode, useList, pLibrarium, bMergeConst );
              }else*/
              newNode = sourceNode->DangerousCloneMe(dest, sourceNode->GetName());
              if (m_owner->m_user)
                m_owner->m_user->OnNodeChange(newNode, ChunkUser::acAdd);
              GetOwner()->NotifyNodeChanged( dest, newNode->GetName(), newNode, false );
            }
          }else
            res = false;
        }else{
          lastGoodNode = destNode;
          bool tRes = mergeNode(destNode, sourceNode, useList, inList, pLibrarium, bMergeConst);
          if( !tRes )
            res = tRes; 
        }
        sourceNode = sourceNode->GetNextBrother();
        if(sourceNode->isBad())
          break;
        destNode = lastGoodNode->GetBrother(sourceNode->GetName());
      }
    }
    return res;
  }

  inline bool ChunkNode::Merge(const ChunkNode* source, std::list<ChunkItem*>* useList, const Librarium* pLibrarium, bool bMergeConst )
  {
    return mergeNode(this, source, useList, false, pLibrarium, bMergeConst);
  }

  //                                                                           //
  //  Merge Area                                                        =END=  //
  ///////////////////////////////////////////////////////////////////////////////


  ///////////////////////////////////////////////////////////////////////////////
  //  Intercect Area                                                   =BEGIN= //
  //                                                                           //

  inline const ChunkNode* GetFullPathSrcNode(  const ChunkNode* pSrcNode, const std::string& sFullPath ) { 
    return pSrcNode->GetOwner()->GetNode(sFullPath);
  }
  inline ChunkNode* GetFullPathDstNode( ChunkNode* pDstNode, const std::string& sFullPath ) { 
    std::string sDstPath = pDstNode->GetFullPath();
    if( sDstPath.length() )
    {
      if( (sDstPath[sDstPath.length()-1] != '/') && sFullPath.length() && (sFullPath[0] != '/') )
        sDstPath += '/';
    }
    std::string res = sDstPath;
    res.append(sFullPath);
    return pDstNode->GetOwner()->GetNode(res) ;
  }

  inline const ChunkItem* GetFullPathSrcItem( const ChunkNode* pSrcNode, const std::string& sFullPath ) { 
    return pSrcNode->GetOwner()->GetItem(sFullPath);
  }
  inline ChunkItem* GetFullPathDstItem( ChunkNode* pDstNode, const std::string& sFullPath ) { 
    std::string sDstPath = pDstNode->GetFullPath();
    if( sDstPath.length() )
    {
      if( (sDstPath[sDstPath.length()-1] != '/') && sFullPath.length() && (sFullPath[0] != '/') )
        sDstPath += '/';
    }
    std::string res = sDstPath;
    res.append(sFullPath);
    return pDstNode->GetOwner()->GetItem(res) ;
  }

  inline BrowsIntersect::ItemChange::ItemChange( ChunkItem* pItem, const Variant& oldVal )
    : m_sPath(pItem->GetFullPath())
    , m_oldVal(oldVal)
  {
  }

  inline HRESULT BrowsIntersect::ItemChange::Apply( ChunkNode* dst, const ChunkNode* src )
  {
    const ChunkItem* pItem = GetFullPathSrcItem(src, m_sPath);
    ChunkItem* pNewItem = GetFullPathDstItem(dst, m_sPath);
    assert(pItem->isGood() && pNewItem->isGood());

    return pNewItem->Set( pItem->Get(), true );
  }

  inline HRESULT BrowsIntersect::ItemChange::Rollback( ChunkNode* dst, const ChunkNode* src )
  {
    ChunkItem* pNewItem = GetFullPathDstItem(dst, m_sPath);
    if( pNewItem->isGood() )
      return pNewItem->Set( m_oldVal );

    return E_FAIL;
  }

  inline BrowsIntersect::NodeChange::NodeChange( ChunkNode* pNode, ChunkUser::Action action, const std::string& sOldName )
    : m_action(action)
    , m_sPath(pNode->GetFullPath())
    , m_sOldName(sOldName)
  {
  }

  inline HRESULT BrowsIntersect::NodeChange::Apply( ChunkNode* dst, const ChunkNode* src )
  {
    switch( m_action ) {
    case ChunkUser::acAdd: {
      const ChunkNode* pNode = GetFullPathSrcNode(src, m_sPath);
      const std::string dstPath = dst->GetFullPath();

      std::string temp = dstPath;
      temp.append("/");
      std::string res = (dstPath.length() ?(temp) :"");
      res.append(m_sPath);
      ChunkNode* pNewNode = dst->GetOwner()->CreatePath(res);
      assert(pNode->isGood() && pNewNode->isGood());

      //if(FAILED( (pNode->CloneMe( pNewNode )->isBad() ?E_FAIL :S_OK) ) )
      //  return E_FAIL;
      //if( dst->GetOwner()->GetUser() ) {
      //  if(FAILED((const_cast<ChunkUser*>(dst->GetOwner()->GetUser())->OnNodeChange(pNewNode, ChunkUser::acAdd))))
      //    return E_FAIL;
      //  //if( FAILED(const_cast<ChunkUser*>(dst->GetOwner()->GetUser())->OnNodeChange(pNewNode, ChunkUser::acAdd)) )
      //  //  pNewNode->GetParent()->DeleteNode(pNewNode->GetName());
      //}
      return S_OK;
                           } break;
    case ChunkUser::acRemove: {
      ChunkNode* pNode = GetFullPathDstNode(dst, m_sPath);
      assert(pNode->isGood());

      if( pNode->isGood() )
        return pNode->GetParent()->DeleteNode( pNode->GetName(), true );
                              } break;
    case ChunkUser::acRename: {
      const ChunkNode* pNode = GetFullPathSrcNode(src, m_sPath);
      const std::string dstParentPath = pNode->GetParent()->GetFullPath();

      std::string temp = dstParentPath;
      temp.append("/");
      std::string res = (dstParentPath.length() ?(temp) :"");
      res.append(m_sOldName);
      ChunkNode* pNewNode = GetFullPathDstNode(dst, res);
      assert(pNode->isGood() && pNewNode->isGood());

      pNewNode->SetName( pNode->GetName(), true );
      return S_OK;
                              } break;
    }

    return E_FAIL;
  }

  inline HRESULT BrowsIntersect::NodeChange::Rollback( ChunkNode* dst, const ChunkNode* src )
  {
    switch( m_action ) {
    case ChunkUser::acAdd: {
      ChunkNode* pNode = GetFullPathDstNode(dst, m_sPath);
      if( pNode->isGood() )
        return pNode->GetParent()->DeleteNode( pNode->GetName() );
                           } break;
    case ChunkUser::acRename: {
      ChunkNode* pNode = const_cast<ChunkNode*>(GetFullPathSrcNode(src, m_sPath));
      const ChunkNode* pNewNode = GetFullPathDstNode(dst, m_sPath);
      pNode->SetName( pNewNode->GetName() );
                              } break;
    }

    return E_FAIL;
  }

  inline BrowsIntersect::BrowsIntersect(void)
  {
  }

  inline BrowsIntersect::~BrowsIntersect(void)
  {
  }

  inline HRESULT BrowsIntersect::OnItemChange(ChunkItem* sender, ChunkUser::Action action, const Variant& OldValue)
  {
    assert(sender);

    if (action != ChunkUser::acChange)
      return S_OK;

    std::list< ItemChange >::const_iterator I = std::find(m_itemChanges.begin(), m_itemChanges.end(), sender->GetFullPath());

    if( I != m_itemChanges.end() )
      return S_OK;

    m_itemChanges.push_front(ItemChange(sender, OldValue));
    return S_OK;
  }

  inline HRESULT BrowsIntersect::OnNodeChange(ChunkNode* sender, Action action, const std::string& sOldName)
  {
    std::list< NodeChange >::iterator I = std::find( m_nodeChanges.begin(), m_nodeChanges.end(), sender->GetFullPath() );

    switch( action ) 
    {
    case ChunkUser::acRename: {
      if( I == m_nodeChanges.end() )
        m_nodeChanges.push_back( NodeChange(sender, action, sOldName) );
                              } break;
    case ChunkUser::acAdd: {
      assert(I == m_nodeChanges.end());

      m_nodeChanges.push_back( NodeChange(sender, action) );
                           } break;
    case ChunkUser::acRemove: {
      if( I == m_nodeChanges.end() )
        m_nodeChanges.push_back( NodeChange(sender, action) );
      else if( I->m_action==ChunkUser::acAdd )
        m_nodeChanges.erase(I);
      else
        assert(!"remove only created before or own added!");
                              } break;
    }

    return S_OK;
  }

  inline HRESULT BrowsIntersect::AddChunk(ChunkNode* node)
  {
    assert(node);

    // Может узел уже в наличии
    std::list<ChunkNode*>::const_iterator i = std::find(m_nodes.begin(), m_nodes.end(), node);

    if (i != m_nodes.end())
    {
      //    g_wrn.Printf(_T("BrowsIntersect::AddCunk: Node(%s) is allready exist in selection.\n"), node->GetName().c_str());
      return S_OK;
    }

    m_nodes.push_front(node);

    return S_OK;
  }

  inline HRESULT BrowsIntersect::RemoveChunk(const ChunkNode* node)
  {
    assert(node);

    // Может этого узла и нет вовсе
    std::list<ChunkNode*>::iterator i = std::find(m_nodes.begin(), m_nodes.end(), node);

    if (i == m_nodes.end())
    {
      //    g_wrn.Printf(_T("BrowsIntersect::RemoveChunk: Can't find node(%s) in selection.\n"), node->GetName().c_str());
      return E_FAIL;
    }

    m_nodes.erase(i);

    return S_OK;
  }

  inline void BrowsIntersect::ClearSelection(void)
  {
    m_nodes.clear();
    m_whiteItems.clear();
    m_nodeChanges.clear();
    m_itemChanges.clear();
  }

  inline bool BrowsIntersect::isWhite(const ChunkItem* item)const
  {
    std::list<ChunkItem*>::const_iterator i = std::find(m_whiteItems.begin(), m_whiteItems.end(), item);
    return (i != m_whiteItems.end());
  }

  inline std::string b_typeIntersect(const std::string& bar, const std::string& foo)
  {
    return (!stricmp(bar.c_str(), foo.c_str()))? bar : EMPTY_STRING;
  }

  inline ChunkBrowsAccess b_accessIntersect(ChunkBrowsAccess foo, ChunkBrowsAccess bar)
  {
    return chunk::Min(foo, bar);
  }

  inline BrowsComment b_commentIntersect(const BrowsComment& bar, const BrowsComment& foo)
  {
    if (!bar.isEmpty()) return bar;
    if (!foo.isEmpty()) return foo;
    return bar;
  }

  inline void intersectItem(ChunkItem* result, const ChunkItem* source, std::list<ChunkItem*>* whiteList)
  {
    bool isWhite = false;
    switch(source->GetType())
    {
    case chByte:
      {
        if (result->GetByte() != source->GetByte())
          isWhite = true;
        unsigned char bmin, bmax, fmin, fmax;
        result->GetByteRange(bmin, bmax);
        source->GetByteRange(fmin, fmax);
        result->SetByteRange(chunk::Max(bmin, fmin), chunk::Min(bmax, fmax));
      }
      break;
    case chInt32:
      {
        if (result->GetInt32() != source->GetInt32())
          isWhite = true;
        int32 bmin, bmax, fmin, fmax;
        result->GetInt32Range(bmin, bmax);
        source->GetInt32Range(fmin, fmax);
        result->SetInt32Range(chunk::Max(bmin, fmin), chunk::Min(bmax, fmax));
      }
      break;
    case chInt64:
      {
        if (result->GetInt64() != source->GetInt64())
          isWhite = true;
        int64 bmin, bmax, fmin, fmax;
        result->GetInt64Range(bmin, bmax);
        source->GetInt64Range(fmin, fmax);
        result->SetInt64Range(chunk::Max(bmin, fmin), chunk::Min(bmax, fmax));
      }
      break;
    case chFloat:
      {
        if (result->GetFloat() != source->GetFloat())
          isWhite = true;
        float bmin, bmax, fmin, fmax;
        result->GetFloatRange(bmin, bmax);
        source->GetFloatRange(fmin, fmax);
        result->SetFloatRange(chunk::Max(bmin, fmin), chunk::Min(bmax, fmax));
      }
      break;
    case chString:
      {
        if (result->GetString() != source->GetString())
        {
          result->Set(std::string());
          isWhite = true;
        }
        int32 bmin, bmax, fmin, fmax;
        result->GetStringRange(bmin, bmax);
        source->GetStringRange(fmin, fmax);
        result->SetStringRange(chunk::Max(bmin, fmin), chunk::Min(bmax, fmax));
      }
      break;
    }

    if (isWhite)
      whiteList->push_back(result);

    result->SetBrowsType(b_typeIntersect(result->GetBrowsType(), source->GetBrowsType()));
    result->SetBrowsAccess(b_accessIntersect(result->GetBrowsAccess(), source->GetBrowsAccess()));
    result->SetBrowsComment(b_commentIntersect(result->GetBrowsComment(), source->GetBrowsComment()));
  }

  bool Intersect(ChunkNode* result, const ChunkNode* source, std::list<ChunkItem*>* whiteList);

  inline void intersectNode(ChunkNode* result, const ChunkNode* source, std::list<ChunkItem*>* whiteList)
  {
    Intersect(result, source, whiteList);

    result->SetBrowsList( result->isBrowsList() && source->isBrowsList() );
    result->SetBrowsComment(b_commentIntersect(result->GetBrowsComment(), source->GetBrowsComment()));
  }

  inline bool Intersect(ChunkNode* result, const ChunkNode* source, std::list<ChunkItem*>* whiteList)
  {
    ChunkItem* resItem = result->GetFirstChildItem();
    while(resItem->isGood())
    {
      const ChunkItem* sourceItem = source->GetItem(resItem->GetName());
      if ( (sourceItem->isBad()) || (sourceItem->GetType() != resItem->GetType()) )
      {
        // удалить результирующее поле пересечения(result)
        std::string name = resItem->GetName();
        resItem = resItem->GetNextBrother();
        result->DeleteItem(name);
        continue;
      }
      intersectItem(resItem, sourceItem, whiteList);
      resItem = resItem->GetNextBrother();
    }

    ChunkNode* resNode = result->GetFirstChildNode();
    while(resNode->isGood())
    {
      const ChunkNode* sourceNode = source->GetNode(resNode->GetName());
      if (sourceNode->isBad())
      {
        // удалить результирующее поле пересечения(result)
        std::string name = resNode->GetName();
        resNode = resNode->GetNextBrother();
        result->DeleteNode(name);
        continue;
      }
      intersectNode(resNode, sourceNode, whiteList);
      //    result->SetBrowsList( false );
      resNode = resNode->GetNextBrother();
    }

    result->SetBrowsAccess(b_accessIntersect(result->GetBrowsAccess(), source->GetBrowsAccess()));
    return !result->isEmpty();
  }

  inline void BrowsIntersect::GetIntersect(Chunk& chunk)
  {
    // приступим
    chunk.Clear();
    m_whiteItems.clear();
    m_nodeChanges.clear();
    m_itemChanges.clear();

    if (!m_nodes.size())
      return;

    ChunkNode* first = *(m_nodes.begin());
    first->CloneMe(chunk.GetTopNode());

    for(std::list<ChunkNode*>::iterator i = ++(m_nodes.begin());
      i != m_nodes.end(); ++i )
    {
      if (!Intersect(chunk.GetTopNode(), *i, &m_whiteItems))
        break;
    }
  }

  inline HRESULT BrowsIntersect::Apply(Chunk& chunk)
  {
    HRESULT rv = S_OK;

    std::list<NodeChange> m_nodeErrors;
    std::list<ItemChange> m_itemErrors;

    for(std::list<ChunkNode*>::iterator nodeIt = m_nodes.begin();
    nodeIt != m_nodes.end(); ++nodeIt)
    {

    // Apply node changes
    if( m_nodeChanges.size() )
      for( std::list< NodeChange >::iterator I=m_nodeChanges.begin(); I!=m_nodeChanges.end(); ++I ) {
        if( find(m_nodeErrors.begin(), m_nodeErrors.end(),*I) == m_nodeErrors.end() ) {
          if( !( I->Apply( *nodeIt, chunk.GetTopNode() ) ) )
            m_nodeErrors.push_back( *I );
        }
      }

    // Apply item changes
    if( m_itemChanges.size() )
      for( std::list< ItemChange >::iterator I=m_itemChanges.begin(); I!=m_itemChanges.end(); ++I ) {
        if( std::find(m_itemErrors.begin(), m_itemErrors.end(),*I) == m_itemErrors.end() ) {
          if( !( I->Apply( *nodeIt, chunk.GetTopNode() ) ) )
            m_itemErrors.push_back( *I );
        }
      }

    }

    // Rollback item changes
    if( m_itemErrors.size() ) {
      for( std::list< ItemChange >::iterator I=m_itemErrors.begin(); 
        I!=m_itemErrors.end(); ++I )
      {
        for(std::list<ChunkNode*>::iterator nodeIt = m_nodes.begin();
          nodeIt != m_nodes.end(); ++nodeIt)
        {
          I->Rollback( *nodeIt, chunk.GetTopNode() );
        }
      }
    }

    // Rollback node changes
    if( m_nodeErrors.size() ) {
      for( std::list< NodeChange >::iterator I=m_nodeErrors.begin(); 
        I!=m_nodeErrors.end(); ++I )
      {
        for(std::list<ChunkNode*>::iterator nodeIt = m_nodes.begin();
          nodeIt != m_nodes.end(); ++nodeIt)
        {
          I->Rollback( *nodeIt, chunk.GetTopNode() );
        }
      }
    }

    rv = (m_nodeErrors.size() || m_itemErrors.size()) ?E_FAIL :rv;
    if( m_nodeChanges.size() )
      m_nodeChanges.clear();
    if( m_itemChanges.size() )
      m_itemChanges.clear();

    return rv;
  }


  //                                                                           //
  //  Intercect Area                                                    =END=  //
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  //  BrowsComment Area                                               =END=  //
  //                                                                           //
  //inline bool BrowsComment::writeTo(chunk_io::Stream& out, bool inScript) const
  //{
  //  if (m_displayName.empty() && m_displayComment.empty())
  //    return false;
  //
  //  char buffer[512];
  //  buffer[0] = 0;
  //  if (!m_displayName.empty())
  //     chunk_fmt::sprintf(ARRAY_ARG(buffer), "(%s)", m_displayName.c_str());
  //  if (!m_displayComment.empty())
  //  {
  //    chunk_fmt::strcat(ARRAY_ARG(buffer), " ");
  //    chunk_fmt::strcat(ARRAY_ARG(buffer), m_displayComment.c_str());
  //  }
  //
  //  if (!inScript)
  //  {
  //    out << chBComment;
  //    WriteSZ(out, buffer);
  //  }
  //  else
  //  {
  //    out.Printf(" [%s]", buffer);
  //  }
  //  return true;
  //}

  inline char* skipWS(char* b, char* e = NULL)
  {
    for ( ; b[0] != 0 && b != e; b++)
    {
      if (b[0] == ' ' || b[0] == '\t') continue;
      break;
    }
    return b;
  }

  inline void BrowsComment::clear()
  {
    m_displayName.clear();
    m_displayComment.clear();
  }

  inline void BrowsComment::Set(const BrowsComment& src)
  {
    // reallocate strings from pool
    m_displayName    = src.m_displayName;
    m_displayComment = src.m_displayComment;
  }


  inline bool BrowsComment::loadFrom(chunk_io::Stream& in, bool inScript)
  {
    char c;
    in >> c;

    char comment[MAX_BROWSE_COMMENT];
    if (!inScript)
    {
      if (c != chBComment)
      {
        StepBack(in);
        return false;
      }
      ReadSZ(in, ARRAY_ARG(comment));
      if(in.Failed())
        return false;
    }
    else
    {
      if (c != '[')
      {
        StepBack(in);
        return false;
      }
      ReadString(in, ARRAY_ARG(comment), "]");
      in >> c;

      if(in.Failed())
        return false;
    }

    char* left = skipWS(comment);
    if (left[0] == 0)
      return true;

    if (left[0] == '(')
    {
      char* right = strchr(left, ')');
      if (!right)
      {
        // should not happen
        m_displayComment = comment;
        return true;
      }

      // B -> '(', E -> ')'
      right[0] = 0;  // cut ")..."
      m_displayName = left+1;
      right = skipWS(right+1);
      m_displayComment = right;
    }
    else
    {
      m_displayComment = left;
    }
    return true;
  }

  inline bool BrowsComment::isEmpty() const
  {
    return ((m_displayName.empty()) && (m_displayComment.empty()));
  }
} // namespace chunk


namespace chunk_io
{

  inline void Serialize(Stream& a, ::chunk::Variant& v)
  {
    chunk_io::SerializeArray(a, v.m_chAlign, rgsizeof(v.m_chAlign), false);
    chunk_io::Serialize(a, v.m_chString);
    chunk_io::Serialize(a, (int&)v.m_type);
  }

} // namespace io
#endif