#pragma once
#include "chunk_defs.h"
#include "chunk.h"

namespace chunk
{
  static const char* CI_VALS  =  "values";

  // reads
  template <typename A, typename B>
  bool Read(const ChunkNode *pNode, const char* sName, A &object, const B &defaultObject)
  {
    if (pNode->isBad() || !Read(pNode, sName, object))
    {
      object = defaultObject;
      return false;
    }
    return true;
  }

  bool Read(const ChunkNode *pNode, const char* sItemName, std::string &object);
  bool Read(const ChunkNode *pNode, const char* sItemName, bool &object);
  bool Read(const ChunkNode *pNode, const char* sItemName, int8 &object);
  bool Read(const ChunkNode *pNode, const char* sItemName, uint8 &object);
  bool Read(const ChunkNode *pNode, const char* sItemName, int16 &object);
  bool Read(const ChunkNode *pNode, const char* sItemName, uint16 &object);
  bool Read(const ChunkNode *pNode, const char* sItemName, int32 &object);
  bool Read(const ChunkNode *pNode, const char* sItemName, uint32 &object);
  bool Read(const ChunkNode *pNode, const char* sItemName, float &object);
  bool Read(const ChunkNode *pNode, const char* sItemName, double &object);
  bool Read(const ChunkNode *pNode, const char* sNodeName, Color4f &object);      // r, g, b, a  or  red, green, blue, alpha
  //   bool Read(const ChunkNode *pNode, const char* sNodeName, math::Vector2f &object);     // x, y
  //   bool Read(const ChunkNode *pNode, const char* sNodeName, math::Vector3f &object);     // x, y, z
  //   bool Read(const ChunkNode *pNode, const char* sNodeName, math::Vector4f &object);     // x, y, z, w
  //   bool Read(const ChunkNode *pNode, const char* sNodeName, math::Quaternion &object);     // x, y, z, w
  //   bool Read(const ChunkNode *pNode, const char* sNodeName, math::Angles &object);      // yaw, pitch, roll
  //   bool Read(const ChunkNode *pNode, const char* sNodeName, math::Matrix4x4f &object);

  //  bool Write(ChunkNode *pNode, const char* sItemName, std::string object);
  //  bool Write(ChunkNode *pNode, const char* sItemName, bool object);
  //  bool Write(ChunkNode *pNode, const char* sItemName, int8 object);
  //  bool Write(ChunkNode *pNode, const char* sItemName, uint8 object);
  //  bool Write(ChunkNode *pNode, const char* sItemName, int16 object);
  //  bool Write(ChunkNode *pNode, const char* sItemName, uint16 object);
  //  bool Write(ChunkNode *pNode, const char* sItemName, int32 object);
  //  bool Write(ChunkNode *pNode, const char* sItemName, uint32 object);
  //  bool Write(ChunkNode *pNode, const char* sItemName, float object);
  //  bool Write(ChunkNode *pNode, const char* sItemName, double object);
  //   bool Write(ChunkNode *pNode, const char* sNodeName, const math::Color4f &object);
  //   bool Write(ChunkNode *pNode, const char* sNodeName, const math::Vector2f &object);
  //   bool Write(ChunkNode *pNode, const char* sNodeName, const math::Vector3f &object);
  //   bool Write(ChunkNode *pNode, const char* sNodeName, const math::Vector4f &object);
  //   bool Write(ChunkNode *pNode, const char* sNodeName, const math::Quaternion &object);
  //   bool Write(ChunkNode *pNode, const char* sNodeName, const math::Angles &object);
  //   bool Write(ChunkNode *pNode, const char* sNodeName, const math::Matrix4x4f &object);


  inline bool Read(const ChunkNode *pNode, const char* sItemName, long &object)
  {
    return Read(pNode, sItemName, (int&) object);
  }

  inline bool Read(const ChunkNode *pNode, const char* sItemName, unsigned long &object)
  {
    return Read(pNode, sItemName, (unsigned int&) object);
  }

  //inline bool Write(ChunkNode *pNode, const char* sItemName, long object)
  //{
  //  return Write(pNode, sItemName, (int&) object);
  //}

  //inline bool Write(ChunkNode *pNode, const char* sItemName, unsigned long object)
  //{
  //  return Write(pNode, sItemName, (unsigned int&) object);
  //}


  bool PropsEqual(const ChunkNode* pDest, const ChunkNode* pSource, std::string &DstProp, std::string &SrcProp);
  // Поиск аналогичного узла
  const ChunkNode* FindSameNode(const ChunkNode* pNodeWhere, const ChunkNode* pNodeWhat, bool bIgnoreNodeNames = false);
  // Сравнить два узла
  bool CompareNodes(const ChunkNode* pNode1, const ChunkNode* pNode2, bool bIgnoreNodeNames = false);

  template<class T> void Read(ChunkItem const* pItem, T& obj);
  template<> inline void Read<std::string>(ChunkItem const* pItem, std::string& obj)  { obj = pItem->GetString(); }
  template<> inline void Read<bool    >(ChunkItem const* pItem, bool& obj)      { obj = pItem->GetInt32() != 0; }
  template<> inline void Read<char    >(ChunkItem const* pItem, char& obj)      { obj = static_cast<char  >( pItem->GetByte() ); }
  template<> inline void Read<uint8   >(ChunkItem const* pItem, uint8& obj)     { obj = static_cast<uint8 >( pItem->GetByte() ); }
  template<> inline void Read<int16   >(ChunkItem const* pItem, int16& obj)     { obj = static_cast<int16 >( pItem->GetInt32() ); }
  template<> inline void Read<uint16  >(ChunkItem const* pItem, uint16& obj)    { obj = static_cast<uint16>( pItem->GetInt32() ); }
  template<> inline void Read<int32   >(ChunkItem const* pItem, int32& obj)     { obj = pItem->GetInt32(); }
  template<> inline void Read<uint32  >(ChunkItem const* pItem, uint32& obj)    { obj = static_cast<uint32>( pItem->GetInt32() ); }
  template<> inline void Read<int64   >(ChunkItem const* pItem, int64& obj)     { obj = pItem->GetInt64(); }
  template<> inline void Read<float   >(ChunkItem const* pItem, float& obj)     { obj = pItem->GetFloat(); }
  template<> inline void Read<double  >(ChunkItem const* pItem, double& obj)    { obj = static_cast<double>( pItem->GetFloat() ); }
  template<> inline void Read<Variant> (ChunkItem const* pItem, Variant& obj)    { obj = *pItem; }


  // Reads a chunk item and throws SerializeException if
  // reading failed and default value was not specified
  template<class T>
  inline   void ReadChunk(ChunkNode const* pNode, const char* itemName, T& val )
  {
    ChunkItem const* pItem = pNode->GetItem(itemName);
    if(pItem->isBad())
    {
      return;
    }
    else
      Read<T>(pItem, val);
  }

  template<class T>
  inline   void ReadChunk(ChunkNode const* pNode, const char* itemName, T& val, T const* defValPtr )
  {
    ChunkItem const* pItem = pNode->GetItem(itemName);
    if(pItem->isBad())
    {
      if(defValPtr)
        val = *defValPtr;
      else
        throw SerializeException(pNode, itemName, SerializeException::Item, false);
    }
    else
      Read<T>(pItem, val);
  }

  template<>  void ReadChunk<chunk::Color4f>    (ChunkNode const*, const char* name, chunk::Color4f& val,   chunk::Color4f const* defValPtr);
  template<>  void ReadChunk<chunk::Color4b>    (ChunkNode const*, const char* name, chunk::Color4b& val,   chunk::Color4b const* defValPtr);
  template<>  void ReadChunk<chunk::Vector2f>   (ChunkNode const*, const char* name, chunk::Vector2f& val,  chunk::Vector2f const* defValPtr);
  template<>  void ReadChunk<chunk::Vector3f>   (ChunkNode const*, const char* name, chunk::Vector3f& val,  chunk::Vector3f const* defValPtr);
  template<>  void ReadChunk<chunk::Vector3d>   (ChunkNode const*, const char* name, chunk::Vector3d& val,  chunk::Vector3d const* defValPtr);
  template<>  void ReadChunk<chunk::Vector4f>   (ChunkNode const*, const char* name, chunk::Vector4f& val,  chunk::Vector4f const* defValPtr);
  template<>  void ReadChunk<chunk::Angles>     (ChunkNode const*, const char* name, chunk::Angles & val,   chunk::Angles  const* defValPtr);


  template<class T>
  inline ChunkNode const* OpenNodeRead(ChunkNode const* pNode, const char* sub, T& val, T const* defValPtr)
  {
    ChunkNode const* pSubNode = pNode->GetNode(sub);
    if(pSubNode->isBad())
    {
      if(defValPtr)
      {
        val = *defValPtr;
        return 0;
      }
      else
        throw SerializeException(pNode, sub, SerializeException::Node, false);
    }
    return pSubNode;
  }

  inline ChunkNode const* GetSubNode(ChunkNode const* pNode, const char* sub )
  {
    ChunkNode const* pSubNode = pNode->GetNode(sub);
    return pSubNode->isGood() ? pSubNode : NULL;
  }


  template<class T>
  inline void ReadChunkDirect(ChunkItem const* pItem, T& val)
  {
    ChunkUtils::Read<T>(pItem, val);
  }

  template<class T>
  inline void ReadChunkDirect(ChunkNode const* pNode, T& val)
  {
    // need to be defined for structure
    int a[-1];
  }



  typedef std::vector<std::string> TStringVector;

  inline void split_string( const char* str, const char* delims, TStringVector& terms )
  {
    size_t sz = strlen( str );
    ttchar* buff = new ttchar[ sz + 1 ];
    strcpy_s( buff, sz + 1, str );
    ttchar* nextToken;
    ttchar* token  = strtok_s( buff,  delims, &nextToken );
    while( token != NULL )
    {
      terms.push_back( token );
      token = strtok_s( NULL, delims, &nextToken );
    }
    delete buff;
  }

  inline bool ReadStringVectorFromChunkDirect( ChunkNode const * pNode, TStringVector& terms )
  {
    if ( pNode == NULL )
      return false;

    std::string str;
    ReadChunk(pNode, CI_VALS, str);
    split_string( str.c_str(), " ", terms );
    return !terms.empty();
  }

  inline bool ReadStringVectorFromChunk( ChunkNode const * pNode, const char* name, TStringVector& terms )
  {
    return ReadStringVectorFromChunkDirect( GetSubNode( pNode, name ), terms );
  }


  template<> inline void ReadChunkDirect<TIndexArray>(ChunkNode const * pNode, TIndexArray& val )
  {
    TStringVector terms;
    if ( !ReadStringVectorFromChunkDirect( pNode, terms ) )
      return;
    val.resize( terms.size() );
    for ( size_t i = 0; i < val.size(); ++ i )
    {
      val[ i ] = atoi( terms[ i ].c_str() );
    }
  };

  template<> inline void ReadChunk<TIndexArray>(ChunkNode const * pNode, const char* name, TIndexArray& val )
  {
    ReadChunkDirect( GetSubNode( pNode, name ), val );
  };

  template<> inline void ReadChunkDirect<TFloatArray>(ChunkNode const * pNode, TFloatArray& val )
  {
    TStringVector terms;
    if ( !ReadStringVectorFromChunkDirect( pNode, terms ) )
      return;
    val.resize( terms.size() );
    for ( size_t i = 0; i < val.size(); ++ i )
    {
      val[ i ] = (float)atof( terms[ i ].c_str() );
    }
  };

  template<> inline void ReadChunk<TFloatArray>(ChunkNode const * pNode, const char* name, TFloatArray& val )
  {
    ReadChunkDirect( GetSubNode( pNode, name ), val );
  };


  template<> inline void ReadChunkDirect<TVertex3fArray>(ChunkNode const * pNode, TVertex3fArray& val )
  {
    TStringVector terms;
    if ( !ReadStringVectorFromChunkDirect( pNode, terms ) )
      return;
    val.resize( terms.size()/3 );
    for ( size_t i = 0; i < val.size(); ++ i )
    {
      val[ i ].x = (float)atof( terms[ i*3 + 0 ].c_str() );
      val[ i ].y = (float)atof( terms[ i*3 + 1 ].c_str() );
      val[ i ].z = (float)atof( terms[ i*3 + 2 ].c_str() );
    }
  };

  template<> inline void ReadChunk<TVertex3fArray>(ChunkNode const * pNode, const char* name, TVertex3fArray& val )
  {
    ReadChunkDirect( GetSubNode( pNode, name ), val );
  };

  template<> inline void ReadChunkDirect<TVertex2fArray>(ChunkNode const * pNode, TVertex2fArray& val )
  {
    TStringVector terms;
    if ( !ReadStringVectorFromChunkDirect( pNode, terms ) )
      return;
    val.resize( terms.size()/2 );
    for ( size_t i = 0; i < val.size(); ++ i )
    {
      val[ i ].x = (float)atof( terms[ i*2 + 0 ].c_str() );
      val[ i ].y = (float)atof( terms[ i*2 + 1 ].c_str() );
    }
  };

  template<> inline void ReadChunk<TVertex2fArray>(ChunkNode const * pNode, const char* name, TVertex2fArray& val )
  {
    ReadChunkDirect( GetSubNode( pNode, name ), val );
  };

  template<> inline void ReadChunkDirect<TColorArray>(ChunkNode const * pNode, TColorArray& val )
  {
    TStringVector terms;
    if ( !ReadStringVectorFromChunkDirect( pNode, terms ) )
      return;
    val.resize( terms.size()/4 );
    for ( size_t i = 0; i < val.size(); ++ i )
    {
      val[ i ].r = atoi( terms[ i*4 + 0 ].c_str() );
      val[ i ].g = atoi( terms[ i*4 + 1 ].c_str() );
      val[ i ].b = atoi( terms[ i*4 + 2 ].c_str() );
      val[ i ].a = atoi( terms[ i*4 + 3 ].c_str() );
    }
  };

  template<> inline void ReadChunk<TColorArray>(ChunkNode const * pNode, const char* name, TColorArray& val )
  {
    ReadChunkDirect( GetSubNode( pNode, name ), val );
  };


  template<class T> inline void ReadChunkVector(ChunkNode const* pNode, const char* itemName, std::vector<T> & val)
  {
    val.clear();
    ChunkNode const* pArrayNode = pNode->GetNode( itemName );
    if ( pArrayNode->isBad() )
      return;

    for ( ChunkNode const* pArrayItemNode = pArrayNode->GetFirstChildNode(); pArrayItemNode->isGood(); pArrayItemNode = pArrayItemNode->GetNextBrother() )
    {
      size_t index = static_cast<size_t>( atoi( pArrayItemNode->GetName().c_str() ) );
      if ( val.size() >= index )
        val.resize( index + 1 );
      ReadChunkDirect( pArrayItemNode, val[ index ] );
    }
  }


  template<class T> inline void ReadChunkItemVector(ChunkNode const* pNode, const char* itemName, std::vector<T> & val)
  {
    val.clear();
    ChunkNode const* pArrayNode = pNode->GetNode( itemName );
    if ( pArrayNode->isBad() )
      return;

    for ( ChunkItem const* pArrayItem = pArrayNode->GetFirstChildItem(); pArrayItem->isGood(); pArrayItem = pArrayItem->GetNextBrother() )
    {
      size_t index = static_cast<size_t>( atoi( pArrayItem->GetName().c_str() ) );
      if ( val.size() >= index )
        val.resize( index + 1 );
      ChunkUtils::Read( pArrayItem, val[ index ] );
    }
  }


  class SerializeException : public Exception
  {
  public:
    explicit SerializeException(bool isStoring) {}
    enum ObjectType { Node, Item };
    SerializeException(ChunkNode const* pNode, const ttchar* name, ObjectType type, bool isStoring) {};
    virtual const char* what() const
    {
      return m_message.c_str();
    }

  protected:
    std::string m_message;
  };

  /*template<class T>
  void WriteChunk(ChunkNode* pNode, const char* itemName, T const& val)
  {
  ChunkItem* pItem = pNode->GetItem(itemName);
  if(pItem->isBad())
  {
  ChunkItem* pItem = pNode->Add(itemName, val, true);
  if(pItem->isBad())
  throw SerializeException(pNode, itemName, SerializeException::Item, true);
  }
  else
  {
  if(FAILED(pItem->Set(val, true)))
  throw SerializeException(pNode, itemName, SerializeException::Item, true);
  }
  }*/

  /*template<>
  inline void WriteChunk<bool>(ChunkNode* pNode, const char* itemName, bool const& val)
  {
  WriteChunk<int32>(pNode, itemName, static_cast<int32>(val));
  }

  template<>
  inline void WriteChunk<int8>(ChunkNode* pNode, const char* itemName, int8 const& val)
  {
  WriteChunk<uint8>(pNode, itemName, static_cast<uint8>(val));
  }

  template<>
  inline void WriteChunk<uint32>(ChunkNode* pNode, const char* itemName, uint32 const& val)
  {
  WriteChunk<int32>(pNode, itemName, static_cast<int32>(val));
  }

  template<>
  inline void WriteChunk<double>(ChunkNode* pNode, const char* itemName, double const& val)
  {
  WriteChunk<float>(pNode, itemName, static_cast<float>(val));
  }


  template<> void WriteChunk<Color4f   >(ChunkNode* pNode, const char* itemName, Color4f  const& val);
  template<> void WriteChunk<Color4b   >(ChunkNode* pNode, const char* itemName, Color4b  const& val);
  template<> void WriteChunk<Vector2f  >(ChunkNode* pNode, const char* itemName, Vector2f const& val);
  template<> void WriteChunk<Vector3f  >(ChunkNode* pNode, const char* itemName, Vector3f const& val);
  template<> void WriteChunk<Vector3d  >(ChunkNode* pNode, const char* itemName, Vector3d const& val);
  template<> void WriteChunk<Vector4f  >(ChunkNode* pNode, const char* itemName, Vector4f const& val);
  template<> void WriteChunk<Vector2i  >(ChunkNode* pNode, const char* itemName, Vector2i const& val);
  template<> void WriteChunk<Angles    >(ChunkNode* pNode, const char* itemName, Angles  const& val);
  template<> void WriteChunk<TVertex3fArray>(ChunkNode* pNode, const char* itemName, TVertex3fArray const& val);
  template<> void WriteChunk<TVertex2fArray>(ChunkNode* pNode, const char* itemName, TVertex2fArray const& val);
  template<> void WriteChunk<TColorArray>(ChunkNode* pNode, const char* itemName, TColorArray const& val);
  template<> void WriteChunk<TIndexArray>(ChunkNode* pNode, const char* itemName, TIndexArray const& val);
  template<> void WriteChunk<TFloatArray>(ChunkNode* pNode, const char* itemName, TFloatArray const& val);
  template<> void WriteChunk<TDoubleArray>(ChunkNode* pNode, const char* itemName, TDoubleArray const& val);
  template<> void WriteChunk<TIntArray>(ChunkNode* pNode, const char* itemName, TIntArray const& val);
  template<> void WriteChunk<TAnglesArray>(ChunkNode* pNode, const char* itemName, TAnglesArray const& val);
  template<class T> void WriteChunkVector(ChunkNode* pNode, const char* itemName, std::vector<T> const& val);
  template<class T> void WriteChunkPoint(ChunkNode* pNode, const char* itemName, T& point);
  */


  //--------------------------------------------------------

}

#include "chunk_utils.inl"