#pragma once
#include <iomanip>
#include <sstream>

#define NOTIFY_CHUNK_USER true

//--------------------------------------------------------------------------
// Reading of simple types
//--------------------------------------------------------------------------

#define CHECK_ERROR(val) \
  if (pItem->isBad()) \
  { \
  g_wrn.Printf("Read chunk: failed to read item \"%s\" from node \"%s\"\n", sItemName, pNode->GetName().c_str()); \
  object = val;  \
  return false; \
  }

namespace chunk
{
  inline bool Read(const ChunkNode *pNode, const char* sItemName, ttstring &object)
  {
    const ChunkItem *pItem = pNode->GetItem(sItemName);
    //CHECK_ERROR(EMPTY_STRING);
    object = pItem->GetString();
    return true;
  }

  inline bool Read(const ChunkNode *pNode, const char* sItemName, bool &object)
  {
    const ChunkItem *pItem = pNode->GetItem(sItemName);
    //CHECK_ERROR(false);
    object = (pItem->GetInt32() != 0);
    return true;
  }
  inline bool Read(const ChunkNode *pNode, const char* sItemName, int8 &object)
  {
    const ChunkItem *pItem = pNode->GetItem(sItemName);
    //CHECK_ERROR(0);
    object = (int8)pItem->GetByte();
    return true;
  }
  inline bool Read(const ChunkNode *pNode, const char* sItemName, uint8 &object)
  {
    const ChunkItem *pItem = pNode->GetItem(sItemName);
    //CHECK_ERROR(0);
    object = (uint8)pItem->GetByte();
    return true;
  }

  inline bool Read(const ChunkNode *pNode, const char* sItemName, int16 &object)
  {
    const ChunkItem *pItem = pNode->GetItem(sItemName);
    //CHECK_ERROR(0);
    object = (int16)pItem->GetInt32();
    return true;
  }
  inline bool Read(const ChunkNode *pNode, const char* sItemName, uint16 &object)
  {
    const ChunkItem *pItem = pNode->GetItem(sItemName);
    //CHECK_ERROR(0);
    object = (uint16)pItem->GetInt32();
    return true;
  }
  inline bool Read(const ChunkNode *pNode, const char* sItemName, int32 &object)
  {
    const ChunkItem *pItem = pNode->GetItem(sItemName);
    //CHECK_ERROR(0);
    object = pItem->GetInt32();
    return true;
  }
  inline bool Read(const ChunkNode *pNode, const char* sItemName, uint32 &object)
  {
    const ChunkItem *pItem = pNode->GetItem(sItemName);
    //CHECK_ERROR(0);
    object = (uint32)pItem->GetInt32();
    return true;
  }
  inline bool Read(const ChunkNode *pNode, const char* sItemName, float &object)
  {
    const ChunkItem *pItem = pNode->GetItem(sItemName);
    //CHECK_ERROR(0);
    object = pItem->GetFloat();
    return true;
  }
  inline bool Read(const ChunkNode *pNode, const char* sItemName, double &object)
  {
    const ChunkItem *pItem = pNode->GetItem(sItemName);
    //CHECK_ERROR(0);
    object = (double)pItem->GetFloat();
    return true;
  }
#undef CHECK_ERROR

#define CHECK_ERROR \
  if (pItem->isBad()) \
  { \
  g_wrn.Printf("Write chunk: failed to write item \"%s\" to node \"%s\"\n", sItemName, pNode->GetName().c_str()); \
  return false; \
  }

  //inline bool Write(ChunkNode *pNode, const char* sItemName, ttstring object)
  //{
  //  ChunkItem *pItem = pNode->Add(sItemName, object, NOTIFY_CHUNK_USER);
  // // CHECK_ERROR;
  //  return true;
  //}
  //inline bool Write(ChunkNode *pNode, const char* sItemName, bool object)
  //{
  //  ChunkItem *pItem = pNode->Add(sItemName, (int32)object, NOTIFY_CHUNK_USER);
  // // CHECK_ERROR;
  //  return true;
  //}
  //inline bool Write(ChunkNode *pNode, const char* sItemName, int8 object)
  //{
  //  ChunkItem *pItem = pNode->Add(sItemName, (unsigned char)object, NOTIFY_CHUNK_USER);
  // // CHECK_ERROR;
  //  return true;
  //}
  //inline bool Write(ChunkNode *pNode, const char* sItemName, uint8 object)
  //{
  //  ChunkItem *pItem = pNode->Add(sItemName, (unsigned char)object, NOTIFY_CHUNK_USER);
  // // CHECK_ERROR;
  //  return true;
  //}
  //inline bool Write(ChunkNode *pNode, const char* sItemName, int16 object)
  //{
  //  ChunkItem *pItem = pNode->Add(sItemName, (int32)object, NOTIFY_CHUNK_USER);
  // // CHECK_ERROR;
  //  return true;
  //}
  //inline bool Write(ChunkNode *pNode, const char* sItemName, uint16 object)
  //{
  //  ChunkItem *pItem = pNode->Add(sItemName, (int32)object, NOTIFY_CHUNK_USER);
  // // CHECK_ERROR;
  //  return true;
  //}
  //inline bool Write(ChunkNode *pNode, const char* sItemName, int32 object)
  //{
  //  ChunkItem *pItem = pNode->Add(sItemName, object, NOTIFY_CHUNK_USER);
  // // CHECK_ERROR;
  //  return true;
  //}
  //inline bool Write(ChunkNode *pNode, const char* sItemName, uint32 object)
  //{
  //  ChunkItem *pItem = pNode->Add(sItemName, (int32)object, NOTIFY_CHUNK_USER);
  ////  CHECK_ERROR;
  //  return true;
  //}
  //inline bool Write(ChunkNode *pNode, const char* sItemName, float object)
  //{
  //  ChunkItem *pItem = pNode->Add(sItemName, object, NOTIFY_CHUNK_USER);
  // // CHECK_ERROR;
  //  return true;
  //}
  //inline bool Write(ChunkNode *pNode, const char* sItemName, double object)
  //{
  //  const ChunkItem *pItem = pNode->Add(sItemName, (float)object, NOTIFY_CHUNK_USER);
  // // CHECK_ERROR;
  //  return true;
  //}
#undef CHECK_ERROR

  struct FieldInfo
  {
    const char* m_name;
    unsigned int          m_offset;
  };

  //field offset macros
  //get offset of the field in struc
#ifdef offsetof
#	define FIELD2OFS(struc, field)    (offsetof(struc, field))              // more compatible
#else
#	define FIELD2OFS(struc, field)    ((unsigned) &((struc *)NULL)->field)  // just in case
#endif

#define FIELD(x)        { #x,   FIELD2OFS(STRUC,x) }
#define FIELD2(x,name)  { name, FIELD2OFS(STRUC,x) }

    static bool ReadObject(const ChunkNode* pParentNode, const char* sNodeName,
    void* object, const FieldInfo* data, unsigned int count)
  {
    const ChunkNode *pNode = pParentNode->GetNode(sNodeName);
    if (pNode->isBad())
    {
      //g_wrn.Printf("Read chunk: failed to read node \"%s\"\n", sNodeName);
      return false;
    }
    for (unsigned int i = 0; i < count; i++, data++)
    {
      const ChunkItem* pItem = pNode->GetItem(data->m_name);
      if (pItem->isBad())
      {
        //g_wrn.Printf("Read chunk: failed to read item \"%s\" from node \"%s\"\n", data->m_name, sNodeName);
        return false;
      }
      float* dst = (float*) ((unsigned char*)object + data->m_offset);
      *dst = pItem->GetFloat();
    }
    return true;
  }

  //static bool WriteObject(ChunkNode* pParentNode, const char* sNodeName,
  //  const void* object, const FieldInfo* data, unsigned int count,
  //  const char* browsType = NULL)
  //{
  //  ChunkNode *pNode = pParentNode->AddNode(ttstring(sNodeName));
  //  if (pNode->isBad())
  //  {
  //    //  g_wrn.Printf("Write chunk: failed to write node \"%s\"\n", sNodeName);
  //    return false;
  //  }
  //  if (browsType)
  //    pNode->SetBrowsType(browsType);

  //  for (unsigned int i = 0; i < count; i++, data++)
  //  {
  //    const float* src = (float*) ((unsigned char*)object + data->m_offset);
  //    const ChunkItem* pItem = pNode->Add(data->m_name, *src, NOTIFY_CHUNK_USER);
  //    if (pItem->isBad())
  //    {
  //      //      g_wrn.Printf("Write chunk: failed to write item \"%s\" to node \"%s\"\n", data->m_name, sNodeName);
  //      return false;
  //    }
  //  }
  //  return true;
  //}
#define STRUC Color4f
  static const FieldInfo Color4_info[] = {
    FIELD(r), FIELD(g), FIELD(b),FIELD(a)
  };
#undef STRUC

  inline bool Read(const ChunkNode *pParentNode, const char* sNodeName, Color4f &object)
  {
    return ReadObject(pParentNode, sNodeName, &object, ARRAY_ARG(Color4_info));
  }

  //inline bool Write(ChunkNode *pParentNode, const char* sNodeName, Color4f& object)
  //{
  //  return WriteObject(pParentNode, sNodeName, &object, ARRAY_ARG(Color4_info), "COLOR_RGB");
  //}



#define STRUC Vector2f
  static const FieldInfo Vector2_info[] = {
    FIELD(x), FIELD(y)
  };
#undef STRUC

  inline bool Read(const ChunkNode *pParentNode, const char* sNodeName, Vector2f &object)
  {
    return ReadObject(pParentNode, sNodeName, &object, ARRAY_ARG(Vector2_info));
  }

  //inline bool Write(ChunkNode *pParentNode, const char* sNodeName, const Vector2f &object)
  //{
  //  return WriteObject(pParentNode, sNodeName, &object, ARRAY_ARG(Vector2_info));
  //}


#define STRUC Vector3f
  static const FieldInfo Vector3_info[] = {
    FIELD(x), FIELD(y), FIELD(z)
  };
#undef STRUC

  inline bool Read(const ChunkNode *pParentNode, const char* sNodeName, Vector3f &object)
  {
    return ReadObject(pParentNode, sNodeName, &object, ARRAY_ARG(Vector3_info));
  }

  //inline bool Write(ChunkNode *pParentNode, const char* sNodeName, const Vector3f &object)
  //{
  //  return WriteObject(pParentNode, sNodeName, &object, ARRAY_ARG(Vector3_info));
  //}


#define STRUC Vector4f
  static const FieldInfo Vector4_info[] = {
    FIELD(x), FIELD(y), FIELD(z), FIELD(w)
  };
#undef STRUC

  inline bool Read(const ChunkNode *pParentNode, const char* sNodeName, Vector4f &object)
  {
    return ReadObject(pParentNode, sNodeName, &object, ARRAY_ARG(Vector4_info));
  }

  //inline bool Write(ChunkNode *pParentNode, const char* sNodeName, const Vector4f &object)
  //{
  //  return WriteObject(pParentNode, sNodeName, &object, ARRAY_ARG(Vector4_info));
  //}



#define STRUC Angles
  static const FieldInfo Angles_info[] = {
    FIELD(yaw), FIELD(pitch), FIELD(roll)
  };
#undef STRUC

  inline bool Read(const ChunkNode *pParentNode, const char* sNodeName, Angles &object)
  {
    return ReadObject(pParentNode, sNodeName, &object, ARRAY_ARG(Angles_info));
  }

  //inline bool Write(ChunkNode *pParentNode, const char* sNodeName, const Angles &object)
  //{
  //  return WriteObject(pParentNode, sNodeName, &object, ARRAY_ARG(Angles_info));
  //}


  static const ChunkItem *SkipDeprecated(const ChunkItem *node)
  {
    while (node->isGood() && (node->GetName() == "PropVersion" || node->GetBrowsAccess() == baHidden))
      node  = node->GetNextBrother();

    return node;
  }

  static const ChunkNode *SkipDeprecated(const ChunkNode *node)
  {
    while (node->isGood() && node->GetBrowsAccess() == baHidden)
      node  = node->GetNextBrother();

    return node;
  }


  inline bool PropsEqual(const ChunkNode* pDest, const ChunkNode* pSource, ttstring &DstProp, ttstring &SrcProp)
  {
    for (const ChunkItem* sourceItem = SkipDeprecated(pSource->GetFirstChildItem()); sourceItem->isGood(); sourceItem = SkipDeprecated(sourceItem->GetNextBrother())) {
      const ChunkItem* destItem = SkipDeprecated(pDest->GetFirstChildItem());

      while (destItem->isGood() && destItem->GetName() != sourceItem->GetName())
        destItem  = SkipDeprecated(destItem->GetNextBrother());

      if (!destItem->isGood()) {
        DstProp = "<none>", SrcProp = sourceItem->GetName();
        return false;
      }

      if (destItem->GetType() != sourceItem->GetType() || destItem->GetBrowsAccess() != sourceItem->GetBrowsAccess()) {
        DstProp = destItem->GetName(), SrcProp = sourceItem->GetName();
        return false;
      }
    }

    for (const ChunkItem* destItem = SkipDeprecated(pDest->GetFirstChildItem()); destItem->isGood(); destItem = SkipDeprecated(destItem->GetNextBrother())) {
      const ChunkItem* sourceItem = SkipDeprecated(pSource->GetFirstChildItem());

      while (sourceItem->isGood() && sourceItem->GetName() != destItem->GetName())
        sourceItem  = SkipDeprecated(sourceItem->GetNextBrother());

      if (!sourceItem->isGood()) {
        DstProp = destItem->GetName(), SrcProp = "<none>";
        return false;
      }
    }

    for (const ChunkNode* sourceNode = SkipDeprecated(pSource->GetFirstChildNode()); sourceNode->isGood(); sourceNode = SkipDeprecated(sourceNode->GetNextBrother())) {
      const ChunkNode* destNode = SkipDeprecated(pDest->GetFirstChildNode());

      while (destNode->isGood() && destNode->GetName() != sourceNode->GetName())
        destNode  = SkipDeprecated(destNode->GetNextBrother());

      if (!destNode->isGood()) {
        DstProp = "<none>", SrcProp = sourceNode->GetName();
        return false;
      }

      if (destNode->GetBrowsType() != sourceNode->GetBrowsType() ||
        destNode->GetBrowsAccess() != sourceNode->GetBrowsAccess())
      {
        DstProp = destNode->GetName(), SrcProp = sourceNode->GetName();
        return false;
      }

      //skip lists content
        if(destNode->isBrowsList())
          continue;
      if(sourceNode->isBrowsList())
        continue;

      if (!PropsEqual(destNode, sourceNode, DstProp, SrcProp)) {
        return false;
      }
    }

    for (const ChunkNode* destNode = SkipDeprecated(pDest->GetFirstChildNode()); destNode->isGood(); destNode = SkipDeprecated(destNode->GetNextBrother())) {
      const ChunkNode* sourceNode = SkipDeprecated(pSource->GetFirstChildNode());

      while (sourceNode->isGood() && sourceNode->GetName() != destNode->GetName())
        sourceNode  = SkipDeprecated(sourceNode->GetNextBrother());

      if (!sourceNode->isGood()) {
        DstProp = destNode->GetName(), SrcProp = "<none>";
        return false;
      }
    }

    return true;
  }

  inline const ChunkNode * FindSameNode(const ChunkNode * pNodeWhere, const ChunkNode * pNodeWhat, bool bIgnoreNodeNames)
  {
    const ChunkNode * pCurNode = pNodeWhere->GetFirstChildNode();
    while (pCurNode->isGood())
    {
      if (CompareNodes(pCurNode, pNodeWhat, bIgnoreNodeNames))
        return pCurNode;
      pCurNode = pCurNode->GetNextBrother();
    }
    return pNodeWhere->GetOwner()->getBadNode();
  }

  inline bool CompareNodes(const ChunkNode * pNode1, const ChunkNode * pNode2, bool bIgnoreNodeNames)
  {
    if (pNode1->GetItemCount() != pNode2->GetItemCount())
      return false;
    if (pNode1->GetNodeCount() != pNode2->GetNodeCount())
      return false;

    const ChunkItem * pItem1 = pNode1->GetFirstChildItem();
    while (pItem1->isGood())
    {
      const ChunkItem * pItem2 = pNode2->GetItem(pItem1->GetName());
      if (pItem2->isBad())
        return false;
      if (!(*pItem1 == *pItem2))
        return false;
      pItem1 = pItem1->GetNextBrother();
    }

    const ChunkNode * pCurNode1 = pNode1->GetFirstChildNode();
    while (pCurNode1->isGood())
    {
      const ChunkNode * pCurNode2 = NULL;
      if (!bIgnoreNodeNames)
      {
        pCurNode2 = pNode2->GetNode(pCurNode1->GetName());
        if (pCurNode2->isBad())
          return false;
        if (!CompareNodes(pCurNode1, pCurNode2))
          return false;
      }
      else
      {
        pCurNode2 = FindSameNode(pNode2, pCurNode1, true);
        if (pCurNode2->isBad())
          return false;
      }
      pCurNode1 = pCurNode1->GetNextBrother();
    }
    return true;
  }

  //inline ChunkNode* OpenNodeWrite(ChunkNode* pNode, const char* sub)
  //{
  //  ChunkNode* pSub = pNode->DangerousAddNode(sub);
  //  if(pSub->isBad())
  //    throw SerializeException(pNode, sub, SerializeException::Node, true);
  //  return pSub;
  //}

  static const char* CI_R = "r";
  static const char* CI_G = "g";
  static const char* CI_B = "b";
  static const char* CI_A = "a";

  static const char* CI_X = "x";
  static const char* CI_Y = "y";
  static const char* CI_Z = "z";
  static const char* CI_W = "w";

  static const char* CI_XD = "x";
  static const char* CI_YD = "y";
  static const char* CI_ZD = "z";

  static const char* CI_YAW   = "yaw";
  static const char* CI_PITCH = "pitch";
  static const char* CI_ROLL  = "roll";

  static const char* CI_POINT  = "point";
  static const char* CI_DIR    = "dir";
  static const char* CI_NORMAL = "normal";
  static const char* CI_DIST   = "dist";

  static const char* CI_MIN_X = "minx";
  static const char* CI_MIN_Y = "miny";
  static const char* CI_MIN_Z = "minz";

  static const char* CI_MAX_X = "maxx";
  static const char* CI_MAX_Y = "maxy";
  static const char* CI_MAX_Z = "maxz";

  //template<class T> void WriteChunkPoint(ChunkNode* pNode, const char* itemName, T& point)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("VECTOR3");
  //    /*WriteChunk(pSubNode, CI_X, point.x);
  //    WriteChunk(pSubNode, CI_Y, point.y);
  //    WriteChunk(pSubNode, CI_Z, point.z);*/
  //  }
  //}

  //template<> inline void WriteChunk<Color4f >(ChunkNode* pNode, const char* itemName, Color4f const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("COLOR_ARGB");
  //    WriteChunk(pSubNode, CI_R, val.r);
  //    WriteChunk(pSubNode, CI_G, val.g);
  //    WriteChunk(pSubNode, CI_B, val.b);
  //    WriteChunk(pSubNode, CI_A, val.a);
  //  }
  //}

  //template<> inline void WriteChunk<Color4b >(ChunkNode* pNode, const char* itemName, Color4b const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("COLOR_ARGB");
  //    WriteChunk(pSubNode, CI_R, val.r);
  //    WriteChunk(pSubNode, CI_G, val.g);
  //    WriteChunk(pSubNode, CI_B, val.b);
  //    WriteChunk(pSubNode, CI_A, val.a);
  //  }
  //}


  template<>
  inline void ReadChunk<chunk::Color4f>(ChunkNode const* pNode, const ttchar* name, chunk::Color4f& val, chunk::Color4f const* ptr )
  {
    if(ChunkNode const* pSubNode = OpenNodeRead(pNode, name, val, ptr))
    {
      float f = 0.0f;
      ReadChunk(pSubNode, CI_R, val.r, &f);
      ReadChunk(pSubNode, CI_G, val.g, &f);
      ReadChunk(pSubNode, CI_B, val.b, &f);
      ReadChunk(pSubNode, CI_A, val.a, &f);
    }
  }

  template<>
  inline void ReadChunk<chunk::Color4b>(ChunkNode const* pNode, const ttchar* name, chunk::Color4b& val, chunk::Color4b const* ptr )
  {
    if(ChunkNode const* pSubNode = OpenNodeRead(pNode, name, val, ptr))
    {
      unsigned char f = 0;
      ReadChunk(pSubNode, CI_R, val.r, &f);
      ReadChunk(pSubNode, CI_G, val.g, &f);
      ReadChunk(pSubNode, CI_B, val.b, &f);
      ReadChunk(pSubNode, CI_A, val.a, &f);
    }
  }

  //template<> inline void WriteChunk<Vector2f>(ChunkNode* pNode, const char* itemName, Vector2f const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("VECTOR2");
  //    WriteChunk(pSubNode, CI_X, val.x);
  //    WriteChunk(pSubNode, CI_Y, val.y);
  //  }
  //}


  //template<> inline void WriteChunk<Vector3f>(ChunkNode* pNode, const char* itemName, Vector3f const& val)
  //{
  //  WriteChunkPoint( pNode, itemName, val );
  //}
  //template<> inline void WriteChunk<Vector3d>(ChunkNode* pNode, const char* itemName, Vector3d const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("VECTOR3D");
  //    WriteChunk(pSubNode, CI_XD, val.x);
  //    WriteChunk(pSubNode, CI_YD, val.y);
  //    WriteChunk(pSubNode, CI_ZD, val.z);
  //  }
  //}

  //template<> inline void WriteChunk<Vector4f>(ChunkNode* pNode, const char* itemName, Vector4f const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("VECTOR4");
  //    WriteChunk(pSubNode, CI_X, val.x);
  //    WriteChunk(pSubNode, CI_Y, val.y);
  //    WriteChunk(pSubNode, CI_Z, val.z);
  //    WriteChunk(pSubNode, CI_W, val.w);
  //  }
  //}

  //template<> inline void WriteChunk<Vector2i>(ChunkNode* pNode, const char* itemName, Vector2i const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("VECTOR2I");
  //    WriteChunk(pSubNode, CI_X, val.x);
  //    WriteChunk(pSubNode, CI_Y, val.y);
  //  }
  //}


  //template<> inline void WriteChunk<Angles>(ChunkNode* pNode, const char* itemName, Angles const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("ANGLE");
  //    WriteChunk(pSubNode, CI_YAW,   val.yaw);
  //    WriteChunk(pSubNode, CI_PITCH, val.pitch);
  //    WriteChunk(pSubNode, CI_ROLL,  val.roll);
  //  }
  //}


  //template<> inline void WriteChunk< TVertex3fArray >(ChunkNode* pNode, const char* itemName, TVertex3fArray const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("VECTOR3F_ARRAY");
  //    std::stringstream ss;
  //    for ( size_t i = 0; i < val.size(); ++ i )
  //      ss << std::setprecision(10) << val[ i ].x << " " << val[ i ].y << " " << val[ i ].z << " ";
  //    pSubNode->Add( CI_VALS, ss.str() );
  //  }
  //}

  //template<> inline void WriteChunk<TVertex2fArray>(ChunkNode* pNode, const char* itemName, TVertex2fArray const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("VECTOR2F_ARRAY");
  //    std::stringstream ss;
  //    for ( size_t i = 0; i < val.size(); ++ i )
  //      ss << std::setprecision(10) << val[ i ].x << " " << val[ i ].y << " ";
  //    pSubNode->Add( CI_VALS, ss.str() );
  //  }
  //}

  //template<> inline void WriteChunk<TColorArray>(ChunkNode* pNode, const char* itemName, TColorArray const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("COLORB_ARRAY");
  //    std::stringstream ss;
  //    for ( size_t i = 0; i < val.size(); ++ i )
  //      ss << (uint)val[ i ].r << " " 
  //      << (uint)val[ i ].g << " " 
  //      << (uint)val[ i ].b << " " 
  //      << (uint)val[ i ].a << " ";
  //    pSubNode->Add( CI_VALS, ss.str() );
  //  }
  //};

  //template<> inline void WriteChunk<TIndexArray>(ChunkNode* pNode, const char* itemName, TIndexArray const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("INDEX_ARRAY");
  //    std::stringstream ss;
  //    for ( size_t i = 0; i < val.size(); ++ i )
  //    {
  //      ss << val[ i ];
  //      if ( i < val.size() - 1 )
  //        ss << " ";
  //    }
  //    pSubNode->Add( CI_VALS, ss.str() );
  //  }
  //};

  //template<> inline void WriteChunk<TFloatArray>(ChunkNode* pNode, const char* itemName, TFloatArray const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("FLOAT_ARRAY");
  //    std::stringstream ss;
  //    for ( size_t i = 0; i < val.size(); ++ i )
  //      ss << val[ i ] << " ";
  //    pSubNode->Add( CI_VALS, ss.str() );
  //  }
  //};

  //template<> inline void WriteChunk<TDoubleArray>(ChunkNode* pNode, const char* itemName, TDoubleArray const& val)
  //{
  //  if (ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("DOUBLE_ARRAY");
  //    std::stringstream ss;
  //    for (size_t i = 0; i < val.size(); ++i)
  //      ss << val[i] << " ";
  //    pSubNode->Add(CI_VALS, ss.str());
  //  }
  //};

  //template<> inline void WriteChunk<TIntArray>(ChunkNode* pNode, const char* itemName, TIntArray const& val)
  //{
  //  if (ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("INT_ARRAY");
  //    std::stringstream ss;
  //    for (size_t i = 0; i < val.size(); ++i)
  //      ss << val[i] << " ";
  //    pSubNode->Add(CI_VALS, ss.str());
  //  }
  //};

  //template<> inline void WriteChunk<TAnglesArray>(ChunkNode* pNode, const char* itemName, TAnglesArray const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("ANGLES_ARRAY");
  //    std::stringstream ss;
  //    for ( size_t i = 0; i < val.size(); ++ i )
  //      ss << std::setprecision(10) << val[ i ].yaw << " " << val[ i ].pitch << " " << val[ i ].roll << " ";
  //    pSubNode->Add( CI_VALS, ss.str() );
  //  }
  //}

  //template<class T> inline void WriteChunkVector(ChunkNode* pNode, const char* itemName, std::vector<T> const& val)
  //{
  //  if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //  {
  //    pSubNode->SetBrowsType("ARRAY");
  //    for ( size_t i = 0; i < val.size(); ++ i )
  //      WriteChunk( pSubNode, chunk_fmt::va("%d", i ), val[ i ] );
  //  }
  //}

}
