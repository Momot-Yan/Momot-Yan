#pragma once
#include "chunk_utils.h"

namespace chunk
{

  //template<> inline void WriteChunk<cg::cprf>( ChunkNode* pNode, const char* itemName, cg::cprf const & val )
  //{
  //   if(ChunkNode* pSubNode = OpenNodeWrite(pNode, itemName))
  //   {
  //      pSubNode->SetBrowsType("ANGLE");
  //      WriteChunk(pSubNode, CI_YAW, val.course);
  //      WriteChunk(pSubNode, CI_PITCH, val.pitch);
  //      WriteChunk(pSubNode, CI_ROLL, val.roll);
  //   }
  //}

  //template<> inline void WriteChunk<cg::point_3>(ChunkNode* pNode, const char* itemName, cg::point_3 const& val)
  //{
  //   WriteChunkPoint( pNode, itemName, val );
  //}

}
