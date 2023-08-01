#pragma once
#include <assert.h>
#include "chunk_defs.h"

#define AS_CHUNK_POINT_2f(pt) chunk::Vector2f((float)(pt).x, (float)(pt).y)
#define AS_CHUNK_POINT_3f(pt) chunk::Vector3f((float)(pt).x, (float)(pt).y, (float)(pt).z)
#define AS_CHUNK_POINT_3d(pt) chunk::Vector3d((pt).x, (pt).y, (pt).z)
#define AS_CHUNK_ANGLES(cpr) chunk::Angles((float)(cpr).course, (float)(cpr).pitch, (float)(cpr).roll)


namespace chunk
{
  template<class Scalar>
  static chunk::Vector3f ToChunkPoint(const cg::point_t<Scalar, 3> &pt)
  {
    // x->x, y->z, z->y
    return chunk::Vector3f(
      static_cast<float>( pt.x ),
      static_cast<float>( pt.z ),
      static_cast<float>( pt.y ) );
  }

  template<class Scalar>
  static chunk::Vector3d ToChunkPointd(const cg::point_t<Scalar, 3> &pt)
  {
    // x->x, y->z, z->y
    return chunk::Vector3d(
      static_cast<double>( pt.x ),
      static_cast<double>( pt.z ),
      static_cast<double>( pt.y ) );
  }

  template<class Scalar>
  static chunk::Vector2f ToChunkPoint(const cg::point_t<Scalar, 2> &pt)
  {
    // x->x, y->z, z->y
    return chunk::Vector2f(
      static_cast<float>( pt.x ),
      static_cast<float>( pt.y ) );
  }

  template<class Scalar>
  static chunk::Color4f ToChunkColor(const cg::colora_t<Scalar> &c)
  {
    cg::coloraf cf = c;
    chunk::Color4f cc;
    cc.r = static_cast<float>( cf.r );
    cc.g = static_cast<float>( cf.g );
    cc.b = static_cast<float>( cf.b );
    cc.a = static_cast<float>( cf.a );
    return cc; 
  }

  inline chunk::Color4b ToChunkColorb(const cg::colorab &c)
  {
    return chunk::Color4b( c.r, c.g, c.b, c.a );
  }

  inline chunk::Color4f ToChunkfColorb(const cg::colorab &c)
  {
    return chunk::Color4f( (float)c.r / 255.0f, (float)c.g / 255.0f, (float)c.b / 255.0f, (float)c.a / 255.0f );
  }

  inline chunk::Color4b ToChunkbColorf(const cg::coloraf &c)
  {
    chunk::Color4b color;
    cg::bound(c.r, 0.0f, 1.0f);
    cg::bound(c.g, 0.0f, 1.0f);
    cg::bound(c.b, 0.0f, 1.0f);
    cg::bound(c.a, 0.0f, 1.0f);
    color.r = (unsigned char)(c.r * 255.999);
    color.g = (unsigned char)(c.g * 255.999);
    color.b = (unsigned char)(c.b * 255.999);
    color.a = (unsigned char)(c.a * 255.999);
    return color;
  }

  static bool GetColorFromIndex( const chunk::ChunkNode* pConfigTopNode, uint uiColorIndex, cg::coloraf &vColor )
  {
    chunk::ChunkNode* pLightProps = 0;
    assert(pConfigTopNode && pConfigTopNode->isGood());
    if (pConfigTopNode && pConfigTopNode->isGood())
      pLightProps = pConfigTopNode->GetNode("light_props");

    if ( !pLightProps || !pLightProps->isGood() )
    {
      //         g_err << "Failed to find light_props config node!" << endl;
      return false;
    }

    std::string sColorNode = chunk_fmt::fmt("color%d", uiColorIndex);
    const chunk::ChunkNode* pLColorPrp = pLightProps->GetNode(sColorNode);
    if ( !pLColorPrp || !pLColorPrp->isGood() )
    {
      //g_wrn << "Failed to get light color from index: " << uiColorIndex << ". White color will be used." << endl;
      vColor = cg::coloraf(1.0f, 1.0f, 1.0f, 1.0f);
      return true;
    }

    chunk::Color4f chunkColor; 
    chunk::ReadChunk(pLightProps, sColorNode.c_str(), chunkColor, &chunkColor );
    vColor.r = chunkColor.r;
    vColor.g = chunkColor.g;
    vColor.b = chunkColor.b;
    vColor.a = 1.0f;

    return true;
  }

} // namespace chunk
