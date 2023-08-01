#pragma once
#include <assert.h>
#include <list>
#include <map>
#include <algorithm>
#include <string>

#pragma warning(push)
#pragma warning(disable : 4201 4996) // nonstandard extension used : nameless struct/union // The POSIX name for this item is deprecated.


#include "chunk_defs.h"
#include "chunk_fmt.h"


namespace chunk
{
  struct Variant;
  class FileName;
  class Librarium;
  class Chunk;
  class ChunkItem;
  class ChunkNode;
  class ChunkUser;
}


namespace chunk_io
{
  class Stream;
  void Serialize( chunk_io::Stream& a, chunk::Variant& v);
}

namespace chunk
{

  class Exception : public std::exception
  {
  public:
    Exception() {}
    virtual ~Exception() {}
    virtual const char* what() const { return "unknown"; }
  };

  template< typename T > 
  inline T Max( T Value0, T Value1 ){
    return ( Value0 > Value1 )? Value0 : Value1;
  }
  template< typename T >
  inline T Min( T Value0, T Value1 ){
    return ( Value0 < Value1 )? Value0 : Value1;
  }  



  typedef std::list<ChunkUser*> ChunkUsersList;
  typedef std::map<void*, ChunkUsersList> ChunkUsersMap;

  // ��������� �������� ���������� ������������
  struct BrowsComment
  {
    void Set(const BrowsComment& src);
    //// �������� ����
    //inline bool writeTo(chunk_io::Stream& out, bool inScript) const;
    // ��������� ����
    inline bool loadFrom(chunk_io::Stream& in, bool inScript);
    // ����� ������
    bool isEmpty() const;
    std::string m_displayName;
    std::string m_displayComment;
    // �������� ����������
    void clear();
  };


  const char PATH_DELIM = '/';

  // ���� ������, �������� �����
  enum ChunkItemType 
  {
    chByte = 0,
    chInt32,
    chInt64,
    chFloat,
    chString,
    // ��������� ������ ����
    chLast,
    chInternal = 50
  };

  // ������� ������� � ����� Chunk'� ��� ����������
  enum ChunkBrowsAccess 
  {
    baHidden = 0,     // �� ���������� � ��������
    baConst,          // ���������� ������ ��� ������
    baPublic,         // ������ ������ � ��������
    baLikeParent,     // ��� � ��������
    // ��������� ������ ����
    baLast
  };

  struct Variant    //�| ���������� ��� �������� ���������� �����
  {
  public:
    // ��������� ���, ��������� ����� ��������
    const ChunkItemType& GetType() const
    {
      return m_type;
    }
    // polymorphic variants
    // used by:
    // 1) ChunkItem::InitDefaults()
    // 2) ox_gentle_import.cpp
    // 3) TMIDEGameRegistry
    void SetType(ChunkItemType type)
    {
      m_type=type;
    }

    // ������������
    inline void Set(unsigned char value);
    inline unsigned char GetByte() const;

    inline void  Set(int32 value);
    inline int32 GetInt32() const;

    inline void  Set(__int64 value);
    inline __int64 GetInt64() const;

    inline void  Set(float value);
    inline float GetFloat() const;

    inline void Set(std::string const &str);
    inline std::string const GetString() const;
    inline const char* GetStringSZ() const;

    void Set(const Variant& value)
    {
      *this=value;
    }
    //const Variant& Get() const{
    //  return(*this);
    //};

    // Constructors
    Variant()
    {}
    Variant(unsigned char value)
      : m_type(chByte)
    {
      m_chByte = value;
    }
    Variant(int32 value)
      : m_type(chInt32)
    {
      m_chInt32 = value;
    }
    Variant(int64 value)
      : m_type(chInt64)
    {
      m_chInt64 = value;
    }
    Variant(float value)
      : m_type(chFloat)
    {
      m_chFloat = value;
    }
    Variant(std::string const &str)
      : m_type(chString)
    {
      m_chString = str;
    }

    Variant &operator=(const Variant &src)
    {
      memcpy(&m_chAlign,&src.m_chAlign,sizeof(m_chAlign));
      m_chString=src.m_chString;
      m_type=src.m_type;
      return *this;
    }
    bool operator == (const Variant& val) const
    {
      if (val.m_type != m_type)
        return false;

      switch (m_type)
      {
      case chByte:   return m_chByte   == val.m_chByte;
      case chInt32:  return m_chInt32  == val.m_chInt32;
      case chInt64:  return m_chInt64  == val.m_chInt64;
      case chFloat:  return m_chFloat  == val.m_chFloat;
      case chString: return m_chString == val.m_chString;
      default: assert(!"Unknown Variant type!!!"); return false;
      }
    }
    bool operator != (const Variant& val) const
    {
      return !( *this == val);
    }

    void clearVariant()
    {
      m_chString.clear();
    }

    friend void chunk_io::Serialize(chunk_io::Stream& a, Variant& v);

  private:
    //Contents
    union
    {
      unsigned char            m_chByte;
      int32           m_chInt32;
      int64           m_chInt64;
      float           m_chFloat;
      unsigned char            m_chAlign[8];  // ��� �����������
    };
    std::string          m_chString;

    //Type of contents
    ChunkItemType   m_type;
  };


  // ���� ��� �����
  class ChunkNode
  {
    friend Chunk;
    friend ChunkItem;

  public:
    // �������� ��� ����
    inline  std::string    const & GetName() const { return m_name; }
    ChunkNode       * SetName(std::string const& sNewName, bool bNotifyUser=false);

    // �������� ����� ���� � ��������� ��� � ����
    ChunkItem       * Add(const char* name, unsigned char     value, bool bNotifyParent = false);
    ChunkItem       * Add(const char* name, int32             value, bool bNotifyParent = false);
    ChunkItem       * Add(const char* name, int64             value, bool bNotifyParent = false);
    ChunkItem       * Add(const char* name, float             value, bool bNotifyParent = false);
    ChunkItem       * Add(const char* name, const std::string&  value, bool bNotifyParent = false);
    ChunkItem       * Add(const char* name, const std::wstring&  value, bool bNotifyParent = false);
    ChunkItem       * Add(const char* name, const Variant& value, bool bNotifyParent = false);
    ChunkNode       * AddNode(const std::string& name, bool bNotifyUser = false);
    ChunkNode       * AddNode(const char* NameBegin, const char* NameEnd, bool bNotifyUser = false);
    ChunkNode       * DangerousAddNode(std::string const& name, bool bNotifyUser = false);

    // ���������� �����
    int                 GetNodeCount() const;
    int                 GetItemCount() const;

    // ���������
    // ���������� ��������
    ChunkNode       * GetParent();
    ChunkNode const * GetParent() const;
    // ���������� ���������� ������
    inline ChunkNode       * GetNextBrother()                           { return m_next;                     }
    inline ChunkNode const * GetNextBrother() const                     { return m_next;                     }
    // ���������� ����������� ������
    inline ChunkNode       * GetPrevBrother()                           { return m_prev;                     }
    inline ChunkNode const * GetPrevBrother() const                     { return m_prev;                     }
    // ���������� �������/���������� Node-�������
    inline ChunkNode       * GetFirstChildNode()                        { return m_first_child_node;         }
    inline ChunkNode const * GetFirstChildNode() const                  { return m_first_child_node;         }
    inline ChunkNode       * GetLastChildNode()                         { return m_last_child_node;          }
    inline ChunkNode const * GetLastChildNode() const                   { return m_last_child_node;          }
    // ���������� �������/���������� Item-�������
    inline ChunkItem       * GetFirstChildItem()                        { return m_first_child_item;         }
    inline ChunkItem const * GetFirstChildItem() const                  { return m_first_child_item;         }
    inline ChunkItem       * GetLastChildItem()                         { return m_last_child_item;          }
    inline ChunkItem const * GetLastChildItem() const                   { return m_last_child_item;          }
    // ���������� Node �� �����
    inline ChunkNode*       GetNode(std::string const& nodeName)           { return findNode(nodeName.c_str()); }
    inline ChunkNode const* GetNode(std::string const& nodeName) const     { return findNode(nodeName.c_str()); }
    inline ChunkNode*       GetNode(const char* nodeName)             { return findNode(nodeName);         }
    inline ChunkNode*       GetNode(const char* nodeName) const       { return findNode(nodeName);         }
    ChunkNode       * GetNodeByPath(const char* path);
    inline  ChunkNode const * GetNodeByPath(const char* path) const
    {
      return const_cast<ChunkNode*>(this)->GetNodeByPath(path);
    }
    inline  ChunkNode       * GetNodeByPath(const std::string& path)       { return GetNodeByPath(path.c_str()); }
    inline  ChunkNode const * GetNodeByPath(const std::string& path) const { return GetNodeByPath(path.c_str()); }

    // Get broter by name
    ChunkNode       * GetBrother(std::string const& brotherName);
    ChunkNode const * GetBrother(std::string const& brotherName) const;

    // Get item by its name
    ChunkItem       * GetItem(const char* szItemName)                 { return findItem(szItemName);       }
    ChunkItem const * GetItem(const char* szItemName) const           { return findItem(szItemName);       }
    ChunkItem       * GetItem(std::string const& itemName)                 { return findItem(itemName.c_str()); }
    ChunkItem const * GetItem(std::string const& itemName) const           { return findItem(itemName.c_str()); }

    ChunkItem       * GetItemByPath(std::string const& path);
    ChunkItem const * GetItemByPath(std::string const& path) const;
    // � ������ ����� �� ������������
    inline  Chunk           * GetOwner()                                { return m_owner; }
    inline  Chunk     const * GetOwner() const                          { return m_owner; }


    // ���� ����?
    inline bool isEmpty() const;

    // ������� �������
    bool DeleteNode(std::string const& nodeName, bool bUserNotify=false);
    bool DeleteNode( ChunkNode* pNode, bool bUserNotify=false);
    bool DeleteItem(std::string const& itemName, bool bUserNotify=false);
    // ������� ��� �����
    bool DeleteAllChild( bool bUserNotify=false );

    // ������� ����� ����� � ����� ������(�� ������ �� ���������)
    ChunkNode* CloneMe(ChunkNode* cloneParent, std::string const& cloneName = EMPTY_STRING) const;
    // If You know that this node does not already exists...
    ChunkNode* DangerousCloneMe(ChunkNode* cloneParent, std::string const& cloneName = EMPTY_STRING) const;

    // �������� �� ����������
    inline bool isBad () const;
    inline bool isGood() const;

    // ������ ���� � ����
    std::string GetFullPath() const;

    bool AddUser   (ChunkUser* pUser );
    bool RemoveUser(ChunkUser* pUser );

  private:
    // ����� ���� �� �����
    ChunkNode* findNode(const char* NameBegin, const char* NameEnd);
    inline  ChunkNode* findNode(const char* NameBegin, const char* NameEnd) const
    {
      return const_cast<ChunkNode*>(this)->findNode(NameBegin, NameEnd);
    }
    ChunkNode* findNode(const char* szName);
    inline  ChunkNode* findNode(const char* szName) const
    {
      return const_cast<ChunkNode*>(this)->findNode(szName);
    }
    inline  ChunkNode* findNode(const std::string& name)
    {
      return findNode(name.c_str());
    }
    inline  ChunkNode* findNode(const std::string& name) const
    {
      return findNode(name.c_str());
    }

    // ����� ���� �� �����
    ChunkItem       * findItem(const char* szName);
    ChunkItem const * findItem(const char* szName)const;

    // �������� ���� �� ��������
    void unregMeNow();
    // ��������� ���� � �������
    void regMeNow(ChunkNode* parent);

    // ������������ & �����������
    ChunkNode(const std::string& name, ChunkNode* parent, Chunk* owner);
    void ReInit(const std::string& name, ChunkNode* parent, Chunk* owner);
    void InitDefaults();
    // ����������� �������� ����
    ~ChunkNode()
    {}
    void PreDestroy();

    std::string           m_name;

    Chunk*           m_owner;
    ChunkNode*       m_parent;

    ChunkItem*       m_first_child_item;
    ChunkItem*       m_last_child_item;

    ChunkNode*       m_prev;
    ChunkNode*       m_next;
    ChunkNode*       m_first_child_node;
    ChunkNode*       m_last_child_node;


    //////////////////////////////
    // ���� ��� �������� ���������
  public:

    //  ��������� ����������� ��������
    bool Merge(ChunkNode const* source, std::list<ChunkItem*>* whiteList = NULL, const Librarium* pLibrarium = NULL, bool bMergeConst = true);

    // ������ ��������� ���������� �����
    inline const std::string& GetBrowsType() const
    {
      return m_browsType;
    }
    ChunkNode* SetBrowsType(const char*   typeName);
    inline  ChunkNode* SetBrowsType(const std::string& typeName)
    {
      return SetBrowsType(typeName.c_str());
    }

    // ������ ��������� ����������� ����������
    inline const BrowsComment& GetBrowsComment() const
    {
      return m_browsComment;
    }
    inline ChunkNode* SetBrowsComment(BrowsComment const& comment)
    {
      m_browsComment.Set(comment);
      return this;
    }
    // ��� ���������� ����������
    std::string GetBrowsName() const;

    // ������ ��������� ������������� ������� � ������
    inline ChunkBrowsAccess GetBrowsAccess() const
    {
      return m_browsAccess;
    }
    inline ChunkNode* SetBrowsAccess(ChunkBrowsAccess access)
    {
      m_browsAccess = access;
      return this;
    }
    inline bool IsUserEditable() const;

    // ������ ��������� �������
    inline bool isBrowsList() const;
    inline ChunkNode* SetBrowsList(bool isList);

  private:
    // ����������� ������ ������ ���� �� ������ � ����������� ������������ (�����������)
    bool mergeNode(ChunkNode* dest, const ChunkNode* source, std::list<ChunkItem*>* whiteList, bool inList = false, const Librarium* pLibrarium = NULL, bool bMergeConst = true);
    // ����������� ������ ������ ���� �� ������ � ����������� ������������
    bool mergeItem(ChunkItem* dest, const ChunkItem* source, std::list<ChunkItem*>* whiteList, const Librarium* pLibrarium = NULL, bool bMergeConst = true);

    std::string           m_browsType;
    BrowsComment     m_browsComment;
    ChunkBrowsAccess m_browsAccess;
    bool               m_browsList;
    // ���� ��� �������� ���������
    //////////////////////////////
  };

  // ���� �����
  class ChunkItem : public Variant
  {
    friend Chunk;
    friend ChunkNode;

  public:
    // ��������� ��� ����
    inline std::string const& GetName() const
    {
      return m_name;
    }
    ChunkItem* SetName(std::string const& sNewName, bool bNotifyUser=false)
    {
      //std::string const sOldName( bNotifyUser ?m_name :EMPTY_STRING );
      m_name = sNewName;
      //if( bNotifyUser && m_parent->m_owner->m_user )
      //  if(FAILED(m_parent->m_owner->m_user->OnItemChange(this, ChunkUser::acRename, sOldName)))
      //    m_name = sOldName; //Cahnging is cancelled by one of users
      return this;
    }

    // ������������(� ������������ ������������)
    bool Set(unsigned char value, bool notifyUser = false);
    unsigned char GetByte() const;

    bool Set(int32 value, bool notifyUser = false);
    int32 GetInt32() const;

    bool Set(int64 value, bool notifyUser = false);
    int64 GetInt64() const;

    bool Set(float value, bool notifyUser = false);
    float GetFloat() const;

    bool Set(std::string const &str, bool notifyUser = false);
    bool Set(std::wstring const &str, bool notifyUser = false);
    const char* GetString() const;

    bool  Set(const Variant &value, bool bNotifyUser=false);
    Variant Get() const;
    // ���������
    // ���������� ��������
    inline ChunkNode*       GetParent()            { return m_parent;             }
    inline const ChunkNode* GetParent() const      { return m_parent;             }
    // ���������� ���������� ������
    inline ChunkItem*       GetNextBrother()       { return m_next;               }
    inline const ChunkItem* GetNextBrother() const { return m_next;               }
    // ���������� ����������� ������
    inline ChunkItem*       GetPrevBrother()       { return m_prev;               }
    inline const ChunkItem* GetPrevBrother() const { return m_prev;               }

    // Get brother by name
    ChunkItem*      GetBrother(const std::string& brotherName);
    const ChunkItem*GetBrother(const std::string& brotherName) const;

    // � ������ ����� �� ������������
    inline Chunk* GetOwner()                       { return m_parent->GetOwner(); }
    inline const Chunk* GetOwner() const           { return m_parent->GetOwner(); }

    // ������� ����� ���� � ����� ������(�� ������ �� ���������)
    ChunkItem* CloneMe(ChunkNode* cloneParent, std::string const& cloneName = EMPTY_STRING) const;

    // �������� �� ����������
    inline bool isBad() const;
    inline bool isGood() const;
    // ������ ���� � ����
    std::string GetFullPath() const;

    bool AddUser(ChunkUser* pUser );
    bool RemoveUser(ChunkUser* pUser );

  private:
    // ������������ � �����������...
    ChunkItem(const char* name, ChunkItemType type, ChunkNode* parent);
    void ReInit(const char* name, ChunkItemType type, ChunkNode* parent);
    void InitDefaults(ChunkItemType type);
    ~ChunkItem()
    {}

    // �������� ���� �� ��������
    void unregMeNow();
    // ��������� ���� � ��������
    void regMeNow(ChunkNode* parent);

    std::string          m_name;
    ChunkNode*      m_parent;

    ChunkItem*      m_prev;
    ChunkItem*      m_next;

    //////////////////////////////
    // ���� ��� �������� ���������
  public:
    // ������ ��������� ��������� �����
    inline const std::string& GetBrowsType() const
    {
      return m_browsType;
    }
    ChunkItem* SetBrowsType(const char*   typeName);
    inline  ChunkItem* SetBrowsType(const std::string& typeName)
    {
      return SetBrowsType(typeName.c_str());
    }

    // ������ ��������� ����������� ����������
    inline const BrowsComment& GetBrowsComment() const
    {
      return m_browsComment;
    }
    inline ChunkItem* SetBrowsComment(const BrowsComment& comment)
    {
      m_browsComment.Set(comment);
      return this;
    }
    // ��� ���������� ����������
    std::string GetBrowsName() const;

    // ������ ��������� ������������� ������� � ������
    inline ChunkBrowsAccess GetBrowsAccess() const
    {
      return m_browsAccess;
    }
    inline ChunkItem* SetBrowsAccess(ChunkBrowsAccess access)
    {
      m_browsAccess = access;
      return this;
    }
    inline bool IsUserEditable() const;

    // ������ ��������� ���������� ��������
    void GetByteRange(unsigned char& min, unsigned char& max) const;
    ChunkItem* SetByteRange(unsigned char min, unsigned char max);
    void GetInt32Range(int32& min, int32& max) const;
    ChunkItem* SetInt32Range(int32 min, int32 max);
    void GetInt64Range(int64& min, int64& max) const;
    ChunkItem* SetInt64Range(int64 min, int64 max);
    void GetFloatRange(float& min, float& max) const;
    ChunkItem* SetFloatRange(float min, float max);
    void GetStringRange(int32& min, int32& max) const;
    ChunkItem* SetStringRange(int32 min, int32 max);

    void GetByteStep(unsigned char& step) const; //C|	 by Centurn
    ChunkItem* SetByteStep(unsigned char step);
    void GetInt32Step(int32& step) const;
    ChunkItem* SetInt32Step(int32 step);
    void GetInt64Step(int64& step) const;
    ChunkItem* SetInt64Step(int64 step);
    void GetFloatStep(float& step) const;
    ChunkItem* SetFloatStep(float step);

  private:
    std::string           m_browsType;    // ���������� ���
    BrowsComment     m_browsComment; // ���������� �����������
    ChunkBrowsAccess m_browsAccess;  // ������� �������

    // ��������� �������� ���������
    union
    {
      struct
      {
        unsigned char m_maxByte;
        unsigned char m_minByte;
        unsigned char m_stepByte;
      };
      struct
      {
        int32 m_maxInt32;
        int32 m_minInt32;
        int32 m_stepInt32;
      };
      struct
      {
        int64 m_maxInt64;
        int64 m_minInt64;
        int64 m_stepInt64;
      };
      struct
      {
        float m_maxFloat;
        float m_minFloat;
        float m_stepFloat;
      };
      struct
      {
        int32 m_maxString;
        int32 m_minString;
      };
    };

    // ���� ��� �������� ���������
    //////////////////////////////
  };

  // ����
  class Chunk
  {
    friend ChunkNode;
    friend ChunkItem;
    friend ChunkUser;

  public:
    // ������������ & �����������...
    Chunk();
    Chunk(const Chunk& chunk);
    Chunk(const ChunkNode* node);
    ~Chunk();

    // �������� ����������
    void operator=(const Chunk& chunk);

    // ������� ����
    ChunkNode* CreatePath(std::string const& path, bool bNotifyUser = false);
    // ��������� ����...
    ChunkItem       * GetItem(std::string const& path, std::string const& item);
    ChunkItem const * GetItem(std::string const& path, std::string const& item) const;
    ChunkItem       * GetItem(std::string const& FullPath);
    ChunkItem const * GetItem(std::string const& FullPath) const;
    // ��������� ����
    ChunkNode       * GetNode(const char* path);
    ChunkNode const * GetNode(const char* path) const;
    inline  ChunkNode       * GetNode(const std::string& path)
    {
      return GetNode(path.c_str());
    }
    inline  ChunkNode const * GetNode(const std::string& path) const
    {
      return GetNode(path.c_str());
    }
    // ��������� Top-����
    ChunkNode       * GetTopNode();
    ChunkNode const * GetTopNode() const;
    // ������� ����
    bool DeleteItem(std::string const& path, std::string const& itemName);
    // ������� ����
    bool DeleteNode(std::string const& path);
    // ������� ���� (����� Top-����, ����������)
    void Clear();

    // ������������ (� ��������� ������ ����������� � ����������� ��������)
    bool     SaveTo(chunk_io::Stream& out, bool bAsBinary, bool bGoodLooking = true) const;
    bool     SaveTo(std::string& str, bool isBinary, bool bGoodLooking = true) const;
    bool     SaveTo( const char* szFileName ) const;
    bool     LoadFrom(chunk_io::Stream& in);
    bool     LoadFrom(std::string const& str);
    bool     LoadFrom(const char* szfileName );
    // ������� ������ ����
    inline ChunkNode* getBadNode()                { return &m_badNode; }
    inline const ChunkNode* getBadNode() const    { return &m_badNode; }

  private:
    // ������� �������
    bool delItem(ChunkItem* item);
    bool delNode(ChunkNode* node);

    // ���������� (�����������)
    void copyFrom(const ChunkNode* source);

    enum readResult 
    {
      rr_OK,
      rr_IOFailed,
      rr_BadFormat,
      rr_UnknownError,
    };

    //// ����������
    //bool writeBinaryNode(chunk_io::Stream& out, ChunkNode const* node) const;
    //bool writeBinaryItem(chunk_io::Stream& out, ChunkItem const* item) const;
    //bool writeScriptNode(chunk_io::Stream& out, ChunkNode const* node) const;
    //bool writeScriptItem(chunk_io::Stream& out, ChunkItem const* item) const;
    readResult readBinaryNode (chunk_io::Stream& in , ChunkNode* parent);
    readResult readBinaryItem (chunk_io::Stream& in , ChunkNode* parent);
    readResult readScriptNode (chunk_io::Stream& in , ChunkNode* parent);
    readResult readScriptItem (chunk_io::Stream& in , ChunkNode* parent, ChunkItemType type);

    inline bool readBrowseTime(chunk_io::Stream& in, bool inScript);
    ////bool writeHeader         (chunk_io::Stream& out, bool inScript) const;
    //bool readBrowseTime      (chunk_io::Stream& in , bool inScript);
    void skipWhiteSpace      (chunk_io::Stream& in);
    //void writeBrowseType     (chunk_io::Stream& out, bool inScript, std::string const& browsType) const;

    readResult readBrowseType         (chunk_io::Stream& in, char* buffer, unsigned int bufSize, bool inScript);
    //void writeBrowseAccess            (chunk_io::Stream& out, bool inScript, ChunkBrowsAccess access) const;
    readResult readBrowseAccess       (chunk_io::Stream& in , ChunkBrowsAccess& access, bool inScript);
    //void writeBrowsComment            (chunk_io::Stream& out, bool inScript, std::string const& browsComment) const;
    std::string const readBrowsComment   (chunk_io::Stream& in , bool inScript);
    //void writeIndent        (chunk_io::Stream& out) const;
    //void writeDelim         (chunk_io::Stream& out) const;
    //void writeTabIn         (chunk_io::Stream& out, bool inScript) const;
    readResult readTabIn    (chunk_io::Stream& in , bool inScript);
    //void writeTabOut        (chunk_io::Stream& out, bool inScript) const;
    void readTabOut         (chunk_io::Stream& in , bool inScript);
    //void writeBrowsList     (chunk_io::Stream& out, bool inScript) const;
    bool readBrowsList      (chunk_io::Stream& in , bool inScript);
    //void writeType          (chunk_io::Stream& out, bool inScript, ChunkItemType type) const;
    readResult readType     (chunk_io::Stream& in , ChunkItemType& type, bool inScript);
    //void writeBrowsRange    (chunk_io::Stream& out, bool inScript, ChunkItem const* item) const;
    readResult readBrowseRange     (chunk_io::Stream& in , bool inScript, ChunkItem      * item, ChunkItemType type);
    void readBinaryStep     (chunk_io::Stream& in , ChunkItem* item, ChunkItemType type);//C-������ ��� �� ���������

    // ������� ������ ��������������
    void ReportError        (const char* fmt, ...) const;
    void ReportBadType      (const ChunkItem* where) const;
    void ReportBadFileFormat(chunk_io::Stream& in, int line = -1) const;

    // �������� �� ���������� ����
    inline bool isBadNode(const ChunkNode* node) const;
    // �������� �� ���������� ����
    inline bool isBadItem(const ChunkItem* item) const;
    // ������� ������ ����
    inline ChunkItem* getBadItem()              { return &m_badItem; }
    inline const ChunkItem* getBadItem() const  { return &m_badItem; }

    // ������������ ������ new � delete
    ChunkNode* allocNode(const std::string& name, ChunkNode* parent);
    ChunkItem* allocItem(const char* name, ChunkItemType type, ChunkNode* parent);
    void         freeNode(ChunkNode* node);
    void         freeItem(ChunkItem* node);


    ChunkNode       m_topNode;

    ChunkNode       m_badNode;
    ChunkItem       m_badItem;
    int             m_curLine;
    mutable bool    m_bGoodLooking;

    ChunkUser*      m_user;
    ChunkUsersMap   m_UsersMap;

    ChunkNode*      m_freeNodes;
    ChunkItem*      m_freeItems;

    mutable unsigned  m_indent;
  public:
    // ���������� ������������ �����������
    bool SetUser(ChunkUser* user);
    inline const ChunkUser* GetUser() const
    {
      return m_user;
    }
    inline ChunkUser* GetUser()
    {
      return m_user;
    }

    bool AddUser(ChunkUser* pUser, void* pContext );
    bool RemoveUser(ChunkUser* pUser, void* pContext );
    const ChunkUsersList* GetUsersList( void* pContext )const;
    void RemoveAllUsers( const void* pContext );

    //Notifies all users of corresponding ChunkItem about changes. If one of users don't want to change item, process will be cancelled
    bool NotifyItemChanging(ChunkItem* sender, const Variant& vNewValue) const;
    //Notifies users of item that it was changed
    void NotifyItemChanged(ChunkItem* sender, const Variant& vOldValue) const;

    bool NotifyNodeChanging(ChunkNode* pParent, std::string const& sNodeName, ChunkNode* pSender, bool bIsRemoving) const;
    void NotifyNodeChanged(ChunkNode* pParent, std::string const& sNodeName, ChunkNode* pSender, bool bIsRemoved);
  };

  // ������������ Chunk (���������� �����������)
  class ChunkUser
  {
    friend Chunk;
    friend ChunkNode;
    friend ChunkItem;

  public:
    // ���� �����������
    enum Action
    {
      acAdd,      // ��������
      acChange,   // ��������
      acRemove,   // �������
      acRemoved,
      acRename,   // �������������
    };

  public:
    // ����������� � ��������
    //For users of chunk
    virtual HRESULT OnNodeChange(ChunkNode* sender, Action action, std::string const& sOldName=EMPTY_STRING)
    { return S_OK; }
    virtual HRESULT OnItemChange(ChunkItem* sender, Action action, const Variant& OldValue)
    { return S_OK; }

    //For users of items/Nodes
    virtual bool OnItemChanging(ChunkItem* sender, const Variant& vNewValue)
    { return true; }
    virtual void OnItemChanged(ChunkItem* sender, const Variant& OldValue)
    {}
    virtual bool OnNodeChanging(ChunkNode* pParent, std::string const& sNewNodeName, ChunkNode* pSender, bool bIsRemoving )//If bIsRemoving, node is tried to remove, otherwise to add
    { return true; }
    virtual void OnNodeChanged(ChunkNode* pParent, std::string const& sNewNodeName, ChunkNode* pSender, bool bIsRemoved )//If bIsRemoving, node is tried to remove, otherwise to add
    {}

  protected:
    // ������������ & �����������
    ChunkUser() : m_chunk(NULL){};
    ~ChunkUser()
    {
      if (m_chunk)
        m_chunk->m_user = NULL;
    }
  private:
    Chunk* m_chunk;
  };

  // ����������� ������
  // ����� ��������������
  //    1. ��������� BrowsIntersect �� ������������ �������� �����.
  //    2. ��� ��������� �������� ����� ����������� ���������� ������������
  class BrowsIntersect : public ChunkUser
  {
  public:
    // �������� � ���������
    HRESULT AddChunk(ChunkNode* node);
    // ������ �� ���������
    HRESULT RemoveChunk(const ChunkNode* node);
    // �������� ���������
    void ClearSelection();
    // �������� ����������� ��� ���������
    void GetIntersect(Chunk& chunk);
    // ���������� �� �������� ��� ����
    bool isWhite(const ChunkItem* item)const;
    // ������� ���������
    HRESULT Apply(Chunk& chunk);
    bool isInIntersect( ChunkNode* pNode )
    { return std::find( m_nodes.begin(), m_nodes.end(), pNode ) != m_nodes.end(); }

    const std::list<ChunkNode*>& GetNodesList()const
    { return m_nodes; };

    // ������������ & �����������
    BrowsIntersect();
    ~BrowsIntersect();

  public:
    // from ChunkUser
    virtual HRESULT OnItemChange(ChunkItem* sender, Action action, const Variant& OldValue);
    virtual HRESULT OnNodeChange(ChunkNode* sender, Action action, std::string const& sOldName=EMPTY_STRING);

    Chunk m_result;
    std::list<ChunkNode*> m_nodes;
    std::list<ChunkItem*> m_whiteItems;

    struct ItemChange
    {
      ItemChange()
      {}
      ItemChange( ChunkItem* pItem, const Variant& oldVal );
      ItemChange( std::string const& sPath )
        : m_sPath(sPath)
      {}

      HRESULT  Apply   ( ChunkNode* dst, const ChunkNode* src );
      HRESULT  Rollback( ChunkNode* dst, const ChunkNode* src );

      bool operator == ( const ItemChange& ic ) {
        return m_sPath.compare(ic.m_sPath) == 0;
      }

      std::string  m_sPath;
      Variant m_oldVal;
    };
    struct NodeChange
    {
      NodeChange()
      {}
      NodeChange( ChunkNode* pNode, ChunkUser::Action action, std::string const& sOldName=EMPTY_STRING );
      NodeChange( std::string const& sPath )
        : m_sPath(sPath)
      {}

      HRESULT  Apply( ChunkNode* dst, const ChunkNode* src );
      HRESULT  Rollback( ChunkNode* dst, const ChunkNode* src );

      bool operator == ( const NodeChange& nc ) {
        return m_sPath.compare(nc.m_sPath) == 0;
      }

      ChunkUser::Action m_action;
      std::string            m_sPath;
      std::string            m_sOldName;
    };

    std::list<ItemChange> m_itemChanges;
    std::list<NodeChange> m_nodeChanges;
  };

  template<class oper>
  void ForEachChunkNode(const ChunkNode* pNode, oper Fn){
    Fn(pNode);
    for(const ChunkNode* pCurNode = pNode->GetFirstChildNode(); pCurNode->isGood(); pCurNode = pCurNode->GetNextBrother() )
      ForEachChunkNode<oper>(pCurNode, Fn);
  }

  template<class oper>
  void ForEachChunkItem(const ChunkNode* pNode, oper Fn){
    for(const ChunkItem* pCurItem = pNode->GetFirstChildItem(); pCurItem->isGood(); pCurItem = pCurItem->GetNextBrother() )
      Fn(pCurItem);
    for(const ChunkNode* pCurNode = pNode->GetFirstChildNode(); pCurNode->isGood(); pCurNode = pCurNode->GetNextBrother() )
      ForEachChunkItem<oper>(pCurNode, Fn);
  }

  // For nodes AND items
  template<class oper>
  void ForEachChunkPoint(const ChunkNode* pNode, oper Fn){
    Fn(pNode);
    for(const ChunkItem* pCurItem = pNode->GetFirstChildItem(); pCurItem->isGood(); pCurItem = pCurItem->GetNextBrother() )
      Fn(pCurItem);
    for(const ChunkNode* pCurNode = pNode->GetFirstChildNode(); pCurNode->isGood(); pCurNode = pCurNode->GetNextBrother() )
      ForEachChunkPoint<oper>(pCurNode, Fn);
  }
}
#include "chunk_file.inl"   
#include "chunk_bstream.inl"   
#include "chunk.inl"   
#pragma warning(pop)

