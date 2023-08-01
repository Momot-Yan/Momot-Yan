#pragma once

#include "chunk_defs.h"
#include "chunk.h"

namespace chunk
{
  template<> inline void Read<ttstring>(ChunkItem const* pItem, ttstring& obj)  { obj = pItem->GetString(); }
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
  inline   void ReadChunk(ChunkNode const* pNode, const ttchar* itemName, T& val, T const* defValPtr = 0)
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
      ChunkUtils::Read<T>(pItem, val);
  }
  template<> RTL_API void ReadChunk<math::Color4f>    (ChunkNode const*, const ttchar* name, math::Color4f& val,    math::Color4f const* defValPtr);
  template<> RTL_API void ReadChunk<math::Vector2f>   (ChunkNode const*, const ttchar* name, math::Vector2f& val,   math::Vector2f const* defValPtr);
  template<> RTL_API void ReadChunk<math::Vector3f>   (ChunkNode const*, const ttchar* name, math::Vector3f& val,   math::Vector3f const* defValPtr);
  template<> RTL_API void ReadChunk<math::Vector3d>   (ChunkNode const*, const ttchar* name, math::Vector3d& val,   math::Vector3d const* defValPtr);
  template<> RTL_API void ReadChunk<math::Vector4f>   (ChunkNode const*, const ttchar* name, math::Vector4f& val,   math::Vector4f const* defValPtr);
  template<> RTL_API void ReadChunk<math::Angles>    (ChunkNode const*, const ttchar* name, math::Angles & val,   math::Angles  const* defValPtr);
  template<> RTL_API void ReadChunk<math::Matrix4x4f>   (ChunkNode const*, const ttchar* name, math::Matrix4x4f& val,   math::Matrix4x4f const* defValPtr);
  template<> RTL_API void ReadChunk<math::AABoundingBox>   (ChunkNode const*, const ttchar* name, math::AABoundingBox& val,   math::AABoundingBox const* defValPtr);
  template<> RTL_API void ReadChunk<math::Quaternion  >(ChunkNode const* pNode, const ttchar* name, math::Quaternion& val, math::Quaternion const* defValPtr);

}


