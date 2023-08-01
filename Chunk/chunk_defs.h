#pragma once
#include <assert.h>
#include <vector>

// some definition from vis600
#ifndef rgsizeof
#define rgsizeof(x)  (sizeof(x) / sizeof(x[0]))
#endif

#ifndef ARRAY_ARG
#define ARRAY_ARG(array)	array, sizeof(array)/sizeof(array[0])
#endif

//#ifndef ASSERT
//#define ASSERT(expr) _ASSERTE(expr)
//#endif 


#ifndef VERIFY
#define VERIFY(expr) ATLVERIFY(expr)
#endif 

#ifndef EMPTY_STRING
#define EMPTY_STRING ""
#endif


#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {  delete p; p=NULL; } 
#endif

#ifndef RTL_TYPES_H


typedef unsigned char     uint8;
typedef __int64           int64;
typedef char              int8;
typedef int               int32;
typedef unsigned int      uint;
typedef unsigned __int64  uint64;
typedef std::string       ttstring;
typedef char              ttchar;
typedef unsigned int      uint32;
typedef unsigned short    uint16;
typedef short             int16;
typedef long              HRESULT;


const uint32 MIN_INT32            = 0x80000000; 
const float  MIN_FLOAT            = -1.175494351e-38F;    // minimum float value
const float  MAX_FLOAT            = 3.402823466e+38F;     // maximum float value
const unsigned char   MIN_BYTE             = 0x00;                 // minimum byte value = min unsigned char value
const unsigned char   MAX_BYTE             = 0xff;                 // maximum byte value = max unsigned char value
const uint64 MIN_INT64            = 0x8000000000000000L;  // minimum int64 value
const uint64 MAX_INT64            = 0x7fffffffffffffffL;  // maximum int64 value
const uint32 MAX_INT32            = 0x7fffffff;           // maximum (signed) int32 value
const uint32 MIN_UINT32           = 0x00000000;           // minimum unsigned int32 value
const uint32 MAX_UINT32           = 0xffffffff;           // maximum unsigned int32 value

const uint32 MIN_UINT = MIN_UINT32;
const uint32 MAX_UINT = MAX_UINT32;

#define S_OK	0x00000000

#endif





namespace chunk
{
  static const char* CI_SI     = "startIdx";
  static const char* CI_EI     = "endIdx";
  static const char* CI_MI     = "matIdx";
  static const char* CI_PT     = "primType";
  static const char* CI_LMIDX  = "lmIdx";
  static const char* CI_LMSIZE = "lmSize";

  static const char* CI_VERTS  = "vertices";
  static const char* CI_NORMS  = "normals";
  static const char* CI_UVS    = "uvs";
  static const char* CI_LM_UVS = "lmUVs";
  static const char* CI_COLORS = "colors";
  static const char* CI_INDEX  = "indices";
  static const char* CI_ALPHAS = "alphas";
  static const char* CI_PRIMS  = "primitives";
  static const char* CI_MATS   = "materials";

  static const char* CI_MESHES     = "meshes";
  static const char* CI_MESHGEOM   = "meshGeometry";


  struct Color4f
  {
    Color4f( float rr = 0, float gg = 0, float bb = 0, float aa = 0 ) : r( rr ), g( gg ), b( bb ), a( aa ) {};
    float r,g,b,a;
  };

  struct Color4b
  {
    Color4b( unsigned char rr = 0, unsigned char gg = 0, unsigned char bb = 0, unsigned char aa = 0 ) : r( rr ), g( gg ), b( bb ), a( aa ) {};
    bool operator == ( const Color4b& c ) const
    {
      return r == c.r && g == c.g && b == c.b && a == c.a;
    }
    bool operator != ( const Color4b& c ) const
    {
      return !(*this == c);
    }
    unsigned char r,g,b,a;
  };

  struct Vector2f
  {
    Vector2f( float xx = 0, float yy = 0) : x( xx ), y( yy ){};
    float x,y;
  };
  struct Vector3f
  {
    Vector3f( float xx = 0, float yy = 0, float zz = 0 ) : x( xx ), y( yy ), z( zz ) {};
    float x, y, z;
    bool empty() const
    {
      return x == 0.0f && y == 0.0f && z == 0.0f;
    }
  };
  struct Vector3d
  {
    Vector3d( double xx = 0, double yy = 0, double zz = 0 ) : x( xx ), y( yy ), z( zz ) {};
    double x,y,z;
    bool empty() const
    {
      return x == 0.0 && y == 0.0 && z == 0.0;
    }
  };
  struct Vector4f
  {
    Vector4f( float xx = 0, float yy = 0, float zz = 0, float ww = 0) : x( xx ), y( yy ), z( zz ), w( ww ) {};
    float x,y,z,w;
  };
  struct Vector2i
  {
    Vector2i( int xx = 0, int yy = 0) : x( xx ), y( yy ){};
    int x,y;
  };
  struct Angles
  {
    Angles( float h = 0, float p = 0, float r = 0 ) : yaw( h ), pitch( p ), roll( r ) {};
    float yaw, pitch, roll;
    bool empty() const
    {
      return yaw == 0.0f && pitch == 0.0f && roll == 0.0f;
    }
  };

  struct AABoundingBox
  {
    AABoundingBox() {};
    AABoundingBox( Vector3f mn, Vector3f mx ) : Min( mn ), Max( mx ) {};

    Vector3f Min;
    Vector3f Max;
  };

  typedef std::vector<Vector3f> TVertex3fArray;
  typedef std::vector<Vector2f> TVertex2fArray;
  typedef std::vector<Color4b>  TColorArray;
  typedef std::vector<uint32>   TIndexArray;
  typedef std::vector<float>    TFloatArray;
  typedef std::vector<double>   TDoubleArray;
  typedef std::vector<Angles>   TAnglesArray;
  typedef std::vector<int>      TIntArray;

  typedef std::vector<std::string> TStringVector;

  const Color4b white_colorb = Color4b(255, 255, 255, 255);
  const Color4b black_colorb = Color4b(0, 0, 0, 0);

} // namespace chunk

using chunk::TVertex3fArray;
using chunk::TVertex2fArray;
using chunk::TColorArray;
using chunk::TIndexArray;
using chunk::TFloatArray;
