/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */

#include "maths.h"

// **************************************************************************************
// ********************************** VEC2 **********************************************
// **************************************************************************************

Vec2::Vec2( float value ) : x( value ), y( value ) {}
Vec2::Vec2( float _x, float _y ) : x( _x ), y( _y ) {}
Vec2::Vec2( const Vec2& ref ) : x( ref.x ), y( ref.y ) {}
Vec2::~Vec2(){}

Vec2& Vec2::operator=( const Vec2& ref ) { x = ref.x; y = ref.y; return *this; }
bool Vec2::operator==( const Vec2& ref ) const { return ( FEQ( x, ref.x ) && FEQ( y, ref.y ) ); }
bool Vec2::operator!=( const Vec2& ref ) const { return !operator==( ref ); }
Vec2& Vec2::operator+=( const Vec2& ref ) { x += ref.x; y += ref.y; return *this; }
Vec2& Vec2::operator-=( const Vec2& ref ) { x -= ref.x; y -= ref.y; return *this; }
Vec2& Vec2::operator*=( const Vec2& ref ) { x *= ref.x; y *= ref.y; return *this; }
Vec2& Vec2::operator*=( float ref ) { x *= ref; y *= ref; return *this; }
Vec2& Vec2::operator/=( const Vec2& ref ) { x /= ref.x; y /= ref.y; return *this; }
Vec2& Vec2::operator/=( float ref ) { x /= ref; y /= ref; return *this; }

Vec2 Vec2::operator+( const Vec2& ref ) const { return Vec2( x + ref.x, y + ref.y ); }
Vec2 Vec2::operator-( const Vec2& ref ) const { return Vec2( x - ref.x, y - ref.y ); }
Vec2 Vec2::operator*( const Vec2& ref ) const { return Vec2( x * ref.x, y * ref.y ); }
Vec2 Vec2::operator*( float ref ) const { return Vec2( x * ref, y * ref ); }
Vec2 Vec2::operator/( const Vec2& ref ) const { return Vec2( x / ref.x, y / ref.y ); }
Vec2 Vec2::operator/( float ref ) const { return Vec2( x / ref, y / ref ); }

Vec2 Vec2::Normalize( const Vec2& ref ) { Vec2 vec = ref; vec.Normalize(); return vec; }
Vec2 Vec2::Rotate( const Vec2& ref, float angle ) { Vec2 vec = ref; vec.Rotate( angle ); return vec; }
Vec2 Vec2::Lerp( const Vec2& from, const Vec2& to, float factor ) { return ( from + ( to - from ) * factor ); }

Vec2& Vec2::Normalize() { return operator/=( Length() ); }
Vec2& Vec2::Rotate( float angle )
{
    float c = cos( angle );
    float s = sin( angle );

    float new_x = x * c - y * s;
    float new_y = x * s - y * c;

    x = new_x;
    y = new_y;

    return *this;
}

Vec2& Vec2::Lerp( const Vec2& to, float factor ) { return operator+=( ( to - *this ) * factor ); }
Vec2& Vec2::Set( float _x, float _y ) { x = _x; y = _y; return *this; }
float Vec2::Dot( const Vec2& ref ) const { return ( x * ref.x + y * ref.y ); }
float Vec2::Cross( const Vec2& ref ) const { return ( x * ref.y - y * ref.x ); }
float Vec2::Max() const { return ( x > y ? x : y ); }
float Vec2::Min() const { return ( x < y ? x : y ); }
float Vec2::Length() const { return sqrt( x*x + y*y ); }

// **************************************************************************************
// ********************************** POINT *********************************************
// **************************************************************************************

Point2::Point2( int value ) : x( value ), y( value ) {}
Point2::Point2( int _x, int _y ) : x( _x ), y( _y ) {}
Point2::Point2( const Point2& ref ) : x( ref.x ), y( ref.y ) {}
Point2::Point2( const Vec2& ref ) : x( (int)ref.x ), y( (int)ref.y ) {}
Point2::~Point2() {}

Point2& Point2::operator=( const Point2& ref )
{
    x = ref.x;
    y = ref.y;
    return *this;
}

bool Point2::operator==( const Point2& ref ) const
{
    return ( x == ref.x && y == ref.y );
}

bool Point2::operator!=( const Point2& ref ) const
{
    return !operator==( ref );
}

Point2& Point2::operator+=( const Point2& ref )
{
    x += ref.x;
    y += ref.y;
    return *this;
}

Point2& Point2::operator-=( const Point2& ref )
{
    x -= ref.x;
    y -= ref.y;
    return *this;
}

Point2& Point2::operator*=( const Point2& ref )
{
    x *= ref.x;
    y *= ref.y;
    return *this;
}

Point2& Point2::operator*=( int value )
{
    x *= value;
    y *= value;
    return *this;
}

Point2& Point2::operator/=( const Point2& ref )
{
    x /= ref.x;
    y /= ref.y;
    return *this;
}

Point2& Point2::operator/=( int value )
{
    x /= value;
    y /= value;
    return *this;
}

Point2 Point2::operator+( const Point2& ref ) const
{
    return Point2( x+ref.x, y+ref.y );
}

Point2 Point2::operator-( const Point2& ref ) const
{
    return Point2( x-ref.x, y-ref.y );
}

Point2 Point2::operator*( const Point2& ref ) const
{
    return Point2( x*ref.x, y*ref.y );
}

Point2 Point2::operator*( int value ) const
{
    return Point2( x*value, y*value );
}

Point2 Point2::operator/( const Point2& ref ) const
{
    return Point2( x/ref.x, y/ref.y );
}

Point2 Point2::operator/( int value ) const
{
    return Point2( x/value, y/value );
}

// **************************************************************************************
// ********************************** VEC3 **********************************************
// **************************************************************************************

Vec3::Vec3( float value ) : x( value ), y( value ), z( value ) {}
Vec3::Vec3( float _x, float _y, float _z ) : x( _x ), y( _y ), z( _z ) {}
Vec3::Vec3( const Vec3& ref ) : x( ref.x ), y( ref.y ), z( ref.z ) {}
Vec3::~Vec3(){}

Vec3& Vec3::operator=( const Vec3& ref )
{
    x = ref.x;
    y = ref.y;
    z = ref.z;
    return *this;
}

bool Vec3::operator==( const Vec3& ref ) const
{
    return ( FEQ( x, ref.x ) && FEQ( y, ref.y ) && FEQ( z, ref.z ) );
}

bool Vec3::operator!=( const Vec3& ref ) const
{
    return !operator==( ref );
}

Vec3& Vec3::operator+=( const Vec3& ref ) { x += ref.x; y += ref.y; z += ref.z; return *this; }
Vec3& Vec3::operator-=( const Vec3& ref ) { x -= ref.x; y -= ref.y; z -= ref.z; return *this; }
Vec3& Vec3::operator*=( const Vec3& ref ) { x *= ref.x; y *= ref.y; z *= ref.z; return *this; }
Vec3& Vec3::operator*=( float ref ) { x *= ref; y *= ref; z *= ref; return *this; }
Vec3& Vec3::operator/=( const Vec3& ref ) { x /= ref.x; y /= ref.y; z /= ref.z; return *this; }
Vec3& Vec3::operator/=( float ref ) { x /= ref; y /= ref; z /= ref; return *this; }

Vec3 Vec3::operator+( const Vec3& ref ) const { return Vec3( x + ref.x, y + ref.y, z + ref.z ); }
Vec3 Vec3::operator-( const Vec3& ref ) const { return Vec3( x - ref.x, y - ref.y, z - ref.z ); }
Vec3 Vec3::operator*( const Vec3& ref ) const { return Vec3( x * ref.x, y * ref.y, z * ref.z ); }
Vec3 Vec3::operator*( float ref ) const { return Vec3( x * ref, y * ref, z * ref ); }
Vec3 Vec3::operator/( const Vec3& ref ) const { return Vec3( x / ref.x, y / ref.y, z / ref.z ); }
Vec3 Vec3::operator/( float ref ) const { return Vec3( x / ref, y / ref, z / ref ); }

Vec3 Vec3::Normalize( const Vec3& ref ) { Vec3 vec = ref; vec.Normalize(); return vec; }
Vec3 Vec3::Rotate( const Vec3& ref, const Vec3& a_xis, float angle ) { Vec3 vec = ref; vec.Rotate( a_xis, angle ); return vec; }
Vec3 Vec3::Abs( const Vec3& ref ) { Vec3 vec = ref; vec.Abs(); return vec; }
Vec3 Vec3::Lerp( const Vec3& from, const Vec3& to, float factor ) { return ( from + ( to - from ) * factor ); }

Vec3 Vec3::Cross( const Vec3& ref ) const
{
    float _x = ( y * ref.z ) - ( z * ref.y );
    float _y = ( z * ref.x ) - ( x * ref.z );
    float _z = ( x * ref.y ) - ( y * ref.x );
    return Vec3( _x, _y, _z );
}

float Vec3::Length() const { return sqrt( x*x + y*y + z*z ); }
float Vec3::Dot( const Vec3& ref ) const { return ( x * ref.x + y * ref.y + z * ref.z ); }
float Vec3::Max() const
{
    float m = ( x > y ? x : y );
    if( z > m )
        m = z;
    return m;
}
float Vec3::Min() const
{
    float m = ( x < y ? x : y );
    if( z < m )
        m = z;
    return m;
}
Vec3& Vec3::Normalize()
{
    float len = Length();
    if( len < EPSILON )
        x = y = z = 0.0f;
    else
        operator/=( len );
    return *this;
}

Vec3& Vec3::Rotate( const Vec3& axis, float angle )
{
    return Rotate( Quat( axis, angle ) );
}

Vec3& Vec3::Rotate( const Quat& rotation )
{
    Quat conj = rotation.Conjugate();
    Quat res = ( rotation * *this ) * conj;

    x = res.x;
    y = res.y;
    z = res.z;

    return *this;
}

Vec3& Vec3::Abs() { x = fabs( x ); y = fabs( y ); z = fabs( z ); return *this; }
Vec3& Vec3::Lerp( const Vec3& to, float factor ) { return operator+=( ( to - *this ) * factor ); }
Vec3& Vec3::Set( float _x, float _y, float _z ) { x = _x; y = _y; z = _z; return *this; }

// **************************************************************************************
// ********************************** POINT3 ********************************************
// **************************************************************************************

Point3::Point3( int value ) : x( value ), y( value ), z( value ) {}
Point3::Point3( int _x, int _y, int _z ) : x( _x ), y( _y ), z( _z ) {}
Point3::Point3( const Point3& ref ) : x( ref.x ), y( ref.y ), z( ref.z ) {}
Point3::Point3( const Vec3& ref ) : x( (int)ref.x ), y( (int)ref.y ), z( (int)ref.z ) {}
Point3::~Point3(){}

Point3& Point3::operator=( const Point3& ref )
{
    x = ref.x;
    y = ref.y;
    z = ref.z;
    return *this;
}

bool Point3::operator==( const Point3& ref ) const
{
    return ( x == ref.x && y == ref.y && z == ref.z );
}

bool Point3::operator!=( const Point3& ref ) const
{
    return !operator==( ref );
}

Point3& Point3::operator+=( const Point3& ref )
{
    x += ref.x;
    y += ref.y;
    z += ref.z;
    return *this;
}

Point3& Point3::operator-=( const Point3& ref )
{
    x -= ref.x;
    y -= ref.y;
    z -= ref.z;
    return *this;
}

Point3& Point3::operator*=( const Point3& ref )
{
    x *= ref.x;
    y *= ref.y;
    z *= ref.z;
    return *this;
}

Point3& Point3::operator*=( int value )
{
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

Point3& Point3::operator/=( const Point3& ref )
{
    x /= ref.x;
    y /= ref.y;
    z /= ref.z;
    return *this;
}

Point3& Point3::operator/=( int value )
{
    x /= value;
    y /= value;
    z /= value;
    return *this;
}

Point3 Point3::operator+( const Point3& ref ) const
{
    return Point3( x+ref.x, y+ref.y, z+ref.z );
}

Point3 Point3::operator-( const Point3& ref ) const
{
    return Point3( x-ref.x, y-ref.y, z-ref.z );
}

Point3 Point3::operator*( const Point3& ref ) const
{
    return Point3( x*ref.x, y*ref.y, z*ref.z );
}

Point3 Point3::operator*( int value ) const
{
    return Point3( x*value, y*value, z*value );
}

Point3 Point3::operator/( const Point3& ref ) const
{
    return Point3( x/ref.x, y/ref.y, z/ref.z );
}

Point3 Point3::operator/( int value ) const
{
    return Point3( x/value, y/value, z/value );
}

// **************************************************************************************
// ********************************** VEC4 **********************************************
// **************************************************************************************

Vec4::Vec4( float value ) : x( value ), y( value ), z( value ), w( value ) {}
Vec4::Vec4( float _x, float _y, float _z, float _w ) : x( _x ), y( _y ), z( _z ), w( _w ) {}
Vec4::Vec4( const Vec3& ref, float _w ) : x( ref.x ), y( ref.y ), z( ref.z ), w( _w ) {}
Vec4::Vec4( const Vec4& ref ) : x( ref.x ), y( ref.y ), z( ref.z ), w( ref.w ) {}
Vec4::~Vec4(){}

Vec4& Vec4::operator=( const Vec4& ref )
{
    x = ref.x;
    y = ref.y;
    z = ref.z;
    w = ref.w;
    return *this;
}

bool Vec4::operator==( const Vec4& ref ) const
{
    return ( FEQ( x, ref.x ) && FEQ( y, ref.y ) && FEQ( z, ref.z ) && FEQ( w, ref.w ) );
}

bool Vec4::operator!=( const Vec4& ref ) const
{
    return !operator==( ref );
}

Vec4& Vec4::operator+=( const Vec4& ref ) { x += ref.x; y += ref.y; z += ref.z; w += ref.w; return *this; }
Vec4& Vec4::operator-=( const Vec4& ref ) { x -= ref.x; y -= ref.y; z -= ref.z; w -= ref.w; return *this; }
Vec4& Vec4::operator*=( const Vec4& ref ) { x *= ref.x; y *= ref.y; z *= ref.z; z *= ref.w; return *this; }
Vec4& Vec4::operator*=( float ref ) { x *= ref; y *= ref; z *= ref; w *= ref; return *this; }
Vec4& Vec4::operator/=( const Vec4& ref ) { x /= ref.x; y /= ref.y; z /= ref.z; w /= ref.w; return *this; }
Vec4& Vec4::operator/=( float ref ) { x /= ref; y /= ref; z /= ref; w /= ref; return *this; }

Vec4 Vec4::operator+( const Vec4& ref ) const { return Vec4( x + ref.x, y + ref.y, z + ref.z, w + ref.w ); }
Vec4 Vec4::operator-( const Vec4& ref ) const { return Vec4( x - ref.x, y - ref.y, z - ref.z, w - ref.w ); }
Vec4 Vec4::operator*( const Vec4& ref ) const { return Vec4( x * ref.x, y * ref.y, z * ref.z, w * ref.w ); }
Vec4 Vec4::operator*( float ref ) const { return Vec4( x * ref, y * ref, z * ref, w * ref ); }
Vec4 Vec4::operator/( const Vec4& ref ) const { return Vec4( x / ref.x, y / ref.y, z / ref.z, w / ref.w ); }
Vec4 Vec4::operator/( float ref ) const { return Vec4( x / ref, y / ref, z / ref, w / ref ); }

Vec4 Vec4::Normalize( const Vec4& ref ) { Vec4 vec = ref; vec.Normalize(); return vec; }
Vec4 Vec4::Abs( const Vec4& ref ) { Vec4 vec = ref; vec.Abs(); return vec; }
Vec4 Vec4::Lerp( const Vec4& from, const Vec4& to, float factor ) { return ( from + ( to - from ) * factor ); }

float Vec4::Length() const { return sqrt( x*x + y*y + z*z + w*w ); }
float Vec4::Max() const
{
    float m = ( x > y ? x : y );
    if( z > m )
        m = z;
    if( w > m )
        m = w;
    return m;
}
float Vec4::Min() const
{
    float m = ( x < y ? x : y );
    if( z < m )
        m = z;
    if( w < m )
        m = w;
    return m;
}
Vec4& Vec4::Normalize() { return operator/=( Length() ); }

Vec4& Vec4::Abs() { x = fabs( x ); y = fabs( y ); z = fabs( z ); w = fabs( w ); return *this; }
Vec4& Vec4::Lerp( const Vec4& to, float factor ) { return operator+=( ( to - *this ) * factor ); }
Vec4& Vec4::Set( float _x, float _y, float _z, float _w ) { x = _x; y = _y; z = _z; w = _w; return *this; }

// **************************************************************************************
// ********************************** MATRIX ********************************************
// **************************************************************************************

const int Mat4::BYTESIZE = sizeof( float ) * 16;

Mat4::Mat4()
{
    for( int i=0; i<16; i++ )
        m[i] = 0.0f;
}

Mat4::Mat4( const Mat4& ref )
{
    for( int i=0; i<16; i++ )
        m[i] = ref.m[i];
}

Mat4::~Mat4()
{
}

Mat4& Mat4::operator=( const Mat4& ref )
{
    for( int i=0; i<16; i++ )
        m[i] = ref.m[i];
    return *this;
}

bool Mat4::operator==( const Mat4& ref ) const
{
    bool equal = true;
    for( int i=0; i<16 && equal; i++ )
        if( !FEQ( m[i], ref.m[i] ) )
            equal = false;
    return equal;
}
bool Mat4::operator!=( const Mat4& ref ) const { return !operator==( ref ); }

Mat4 Mat4::operator*( const Mat4& ref ) const
{
    Mat4 res;

    for( int i=0; i<4; i++ )
    {
        for( int j=0; j<4; j++ )
        {
            res.Set( i, j, Get( i, 0 ) * ref.Get( 0, j ) +
                                Get( i, 1 ) * ref.Get( 1, j ) +
                                Get( i, 2 ) * ref.Get( 2, j ) +
                                Get( i, 3 ) * ref.Get( 3, j ) );
        }
    }

    return res;
}

Vec4 Mat4::operator*( const Vec4& ref ) const
{
    Vec4 res;

    res.x = ref.x * Get( 0, 0 ) + ref.y * Get( 1, 0 ) + ref.z * Get( 2, 0 ) + ref.w * Get( 3, 0 );
    res.y = ref.x * Get( 0, 1 ) + ref.y * Get( 1, 1 ) + ref.z * Get( 2, 1 ) + ref.w * Get( 3, 1 );
    res.z = ref.x * Get( 0, 2 ) + ref.y * Get( 1, 2 ) + ref.z * Get( 2, 2 ) + ref.w * Get( 3, 2 );
    res.w = ref.x * Get( 0, 3 ) + ref.y * Get( 1, 3 ) + ref.z * Get( 2, 3 ) + ref.w * Get( 3, 3 );
    
    return res;
}

Mat4 Mat4::Mul( const Mat4& ref ) const
{
    Mat4 res;

    for( int i=0; i<4; i++ )
    {
        for( int j=0; j<4; j++ )
        {
            res.Set( i, j, Get( i, 0 ) * ref.Get( 0, j ) +
                                Get( i, 1 ) * ref.Get( 1, j ) +
                                Get( i, 2 ) * ref.Get( 2, j ) +
                                Get( i, 3 ) * ref.Get( 3, j ) );
        }
    }

    return res;
}

float Mat4::Get( int x, int y ) const { return m[x*4+y]; }
void Mat4::Set( int x, int y, float value ) { m[x*4+y] = value; }

Mat4& Mat4::Identity()
{
    m[0] = 1;   m[1] = 0;   m[2] = 0;   m[3] = 0;
    m[4] = 0;   m[5] = 1;   m[6] = 0;   m[7] = 0;
    m[8] = 0;   m[9] = 0;   m[10] = 1;  m[11] = 0;
    m[12] = 0;  m[13] = 0;  m[14] = 0;  m[15] = 1;

    return *this;
}

Mat4& Mat4::Transpose()
{
    float temp_m[16] = { m[0], m[1], m[2], m[3],
                         m[4], m[5], m[6], m[7],
                         m[8], m[9], m[10], m[11],
                         m[12], m[13], m[14], m[15] };

    for( int i=0; i<4; i++ )
    {
        for( int j=0; j<4; j++ )
        {
            m[i*4+j] = temp_m[j*4+i];
        }
    }

    return *this;
}

Mat4& Mat4::Translation( Vec3 translation ) { return Translation( translation.x, translation.y, translation.z ); }
Mat4& Mat4::Translation( float x, float y, float z )
{
    m[0] = 1;   m[1] = 0;   m[2] = 0;   m[3] = x;
    m[4] = 0;   m[5] = 1;   m[6] = 0;   m[7] = y;
    m[8] = 0;   m[9] = 0;   m[10] = 1;  m[11] = z;
    m[12] = 0;  m[13] = 0;  m[14] = 0;  m[15] = 1;

    return *this;
}

Mat4& Mat4::Rotation( Vec3 rotation ) { return Rotation( rotation.x, rotation.y, rotation.z ); }
Mat4& Mat4::Rotation( float x, float y, float z )
{
    Mat4 xrot;
    Mat4 yrot;
    Mat4 zrot;

    x = ToRadians( x );
    y = ToRadians( y );
    z = ToRadians( z );

    zrot.m[0]  = cos(z);    zrot.m[1]  = -sin(z);   zrot.m[2]  = 0;         zrot.m[3]  = 0;
    zrot.m[4]  = sin(z);    zrot.m[5]  = cos(z);    zrot.m[6]  = 0;         zrot.m[7]  = 0;
    zrot.m[8]  = 0;         zrot.m[9]  = 0;         zrot.m[10] = 1;         zrot.m[11] = 0;
    zrot.m[12] = 0;         zrot.m[13] = 0;         zrot.m[14] = 0;         zrot.m[15] = 1;

    xrot.m[0]  = 1;         xrot.m[1]  = 0;         xrot.m[2]  = 0;         xrot.m[3]  = 0;
    xrot.m[4]  = 0;         xrot.m[5]  = cos(x);    xrot.m[6]  = -sin(x);   xrot.m[7]  = 0;
    xrot.m[8]  = 0;         xrot.m[9]  = sin(x);    xrot.m[10] = cos(x);    xrot.m[11] = 0;
    xrot.m[12] = 0;         xrot.m[13] = 0;         xrot.m[14] = 0;         xrot.m[15] = 1;

    yrot.m[0]  = cos(y);    yrot.m[1]  = 0;         yrot.m[2]  = -sin(y);   yrot.m[3]  = 0;
    yrot.m[4]  = 0;         yrot.m[5]  = 1;         yrot.m[6]  = 0;         yrot.m[7]  = 0;
    yrot.m[8]  = sin(y);    yrot.m[9]  = 0;         yrot.m[10] = cos(y);    yrot.m[11] = 0;
    yrot.m[12] = 0;         yrot.m[13] = 0;         yrot.m[14] = 0;         yrot.m[15] = 1;

    operator=( zrot * ( yrot * xrot ) );

    return *this;
}

Mat4& Mat4::Rotation( const Vec3& forward, const Vec3& up )
{
    Vec3 f = Vec3::Normalize( forward );
    Vec3 r = Vec3::Normalize( up );
    r = r.Cross( f );
    Vec3 u = f.Cross( r );

    return Rotation( f, u, r );
}

Mat4& Mat4::Rotation( const Vec3& forward, const Vec3& up, const Vec3& right )
{
    Vec3 f = forward;
    Vec3 r = right;
    Vec3 u = up;

    m[0] = r.x;     m[1] = r.y;     m[2] = r.z;     m[3] = 0;
    m[4] = u.x;     m[5] = u.y;     m[6] = u.z;     m[7] = 0;
    m[8] = f.x;     m[9] = f.y;     m[10] = f.z;    m[11] = 0;
    m[12] = 0;          m[13] = 0;          m[14] = 0;          m[15] = 1;

    return *this;
}

Mat4& Mat4::Scale( Vec3 scale ) { return Scale( scale.x, scale.y, scale.z ); }
Mat4& Mat4::Scale( float x, float y, float z )
{
    m[0] = x;   m[1] = 0;   m[2] = 0;   m[3] = 0;
    m[4] = 0;   m[5] = y;   m[6] = 0;   m[7] = 0;
    m[8] = 0;   m[9] = 0;   m[10] = z;  m[11] = 0;
    m[12] = 0;  m[13] = 0;  m[14] = 0;  m[15] = 1;

    return *this;
}

/*Mat4& Mat4::Perspective( float fov, float aspectRatio, float near, float far )
{
    float tanHalfFOV = (float)tan( (double)fov/2 );
    float zRange = near - far;

    m[0] = 1.0f / ( tanHalfFOV * aspectRatio ); m[1] = 0;                   m[2] = 0;                   m[3] = 0;
    m[4] = 0;                                   m[5] = 1.0f / tanHalfFOV;   m[6] = 0;                   m[7] = 0;
    m[8] = 0;                                   m[9] = 0;                   m[10] =(-near-far)/zRange;  m[11]= 2 * far * near / zRange;
    m[12] = 0;                                  m[13] = 0;                  m[14] = 1;                  m[15]= 0;

    return *this;
    }*/

Mat4& Mat4::Perspective( float fov, float aspectRatio, float nearplane, float farplane )
{
    float tanHalfFOV = (float)tan( (double)fov / 2.0 );
    float zRange = nearplane - farplane;

    m[0] = 1.0f / ( tanHalfFOV * aspectRatio ); m[1] = 0;                   m[2] = 0;                             m[3] = 0;
    m[4] = 0;                                   m[5] = 1.0f / tanHalfFOV;   m[6] = 0;                             m[7] = 0;
    m[8] = 0;                                   m[9] = 0;                   m[10] = (-nearplane-farplane)/zRange; m[11] = 2 * farplane * nearplane / zRange;
    m[12] = 0;                                  m[13] = 0;                  m[14] = 1;                            m[15] = 0;

    return *this;
}

Mat4& Mat4::Orthographic( float left, float right, float top, float bottom, float nearplane, float farplane )
{
    float w = right - left;
    float h = top - bottom;
    float d = farplane - nearplane;

    m[0]  = 2/w;    m[1]  = 0;      m[2]  = 0;      m[3]  = -(right+left)/w;
    m[4]  = 0;      m[5]  = 2/h;    m[6]  = 0;      m[7]  = -(top+bottom)/h;
    m[8]  = 0;      m[9]  = 0;      m[10] = -2/d;   m[11] = -(farplane+nearplane)/d;
    m[12] = 0;      m[13] = 0;      m[14] = 0;      m[15] = 1;

    return *this;
}

Mat4 Mat4::MakeIdentity()
{
    Mat4 i;
    return i.Identity();
}

Mat4 Mat4::MakeTranspose( const Mat4& ref )
{
    Mat4 t = ref;
    return t.Transpose();
}

Mat4 Mat4::MakeTranslation( Vec3 position )
{
    Mat4 t;
    return t.Translation( position );
}

Mat4 Mat4::MakeTranslation( float x, float y, float z )
{
    Mat4 t;
    return t.Translation( x, y, z );
}

Mat4 Mat4::MakeRotation( Vec3 rotation )
{
    Mat4 r;
    return r.Rotation( rotation );
}

Mat4 Mat4::MakeRotation( float x, float y, float z )
{
    Mat4 r;
    return r.Rotation( x, y, z );
}

Mat4 Mat4::MakeRotation( const Vec3& forward, const Vec3& up )
{
    Mat4 r;
    return r.Rotation( forward, up );
}

Mat4 Mat4::MakeRotation( const Vec3& forward, const Vec3& up, const Vec3& right )
{
    Mat4 r;
    return r.Rotation( forward, up, right );
}

Mat4 Mat4::MakeScale( Vec3 scale )
{
    Mat4 s;
    return s.Scale( scale );
}

Mat4 Mat4::MakeScale( float x, float y, float z )
{
    Mat4 s;
    return s.Scale( x, y, z );
}

Mat4 Mat4::MakePerspective( float fov, float aspectRatio, float nearplane, float farplane )
{
    Mat4 p;
    return p.Perspective( fov, aspectRatio, nearplane, farplane );
}

Mat4 Mat4::MakeOrthographic( float left, float right, float top, float bottom, float nearplane, float farplane )
{
    Mat4 o;
    return o.Orthographic( left, right, top, bottom, nearplane, farplane );
}

// **************************************************************************************
// ********************************** QUATERNION ****************************************
// **************************************************************************************

Quat::Quat() : x( 0 ), y( 0 ), z( 0 ), w( 1.0f ) {}
Quat::Quat( float _x, float _y, float _z, float _w ) : x( _x ), y( _y ), z( _z ), w( _w ) {}
Quat::Quat( const Vec3& axis, float angle ) { InitRotation( axis, angle ); }
Quat::Quat( const Quat& ref ) : x( ref.x ), y( ref.y ), z( ref.z ), w( ref.w ) {}
Quat::~Quat(){}

Quat& Quat::operator=( const Quat& ref )
{ x = ref.x; y = ref.y; z = ref.z; w = ref.w; return *this; }

bool Quat::operator==( const Quat& ref ) const
{ return ( FEQ( x, ref.x ) && FEQ( y, ref.y ) && FEQ( z, ref.z ) && FEQ( w, ref.w ) ); }

bool Quat::operator!=( const Quat& ref ) const { return !operator==( ref ); }

Quat& Quat::operator*=( const Quat& ref )
{
    float _w = w * ref.w - x * ref.x - y * ref.y - z * ref.z;
    float _x = x * ref.w + w * ref.x + y * ref.z - z * ref.y;
    float _y = y * ref.w + w * ref.y + z * ref.x - x * ref.z;
    float _z = z * ref.w + w * ref.z + x * ref.y - y * ref.x;

    x = _x; y = _y; z = _z; w = _w;
    return *this;
}

Quat& Quat::operator*=( const Vec3& ref )
{
    float _w = -x * ref.x - y * ref.y - z * ref.z;
    float _x = w * ref.x + y * ref.z - z * ref.y;
    float _y = w * ref.y + z * ref.x - x * ref.z;
    float _z = w * ref.z + x * ref.y - y * ref.x;

    x = _x; y = _y; z = _z; w = _w;
    return *this;
}

Quat Quat::operator*( const Quat& ref ) const
{
    float _w = w * ref.w - x * ref.x - y * ref.y - z * ref.z;
    float _x = x * ref.w + w * ref.x + y * ref.z - z * ref.y;
    float _y = y * ref.w + w * ref.y + z * ref.x - x * ref.z;
    float _z = z * ref.w + w * ref.z + x * ref.y - y * ref.x;

    return Quat( _x, _y, _z, _w );
}

Quat Quat::operator*( const Vec3& ref ) const
{
    float _w = -x * ref.x - y * ref.y - z * ref.z;
    float _x = w * ref.x + y * ref.z - z * ref.y;
    float _y = w * ref.y + z * ref.x - x * ref.z;
    float _z = w * ref.z + x * ref.y - y * ref.x;

    return Quat( _x, _y, _z, _w );
}

Quat Quat::Normalize( const Quat& ref )
{
    Quat q = ref;
    return q.Normalize();
}

Quat Quat::MakeRotation( const Vec3& axis, float angle )
{
    Quat q;
    q.InitRotation( axis, angle );
    return q;
}

Quat Quat::Conjugate() const
{
    return Quat( -x, -y, -z, w );
}

float Quat::Length() const
{
    return sqrt( x * x + y * y + z * z + w * w );
}

Quat& Quat::Normalize()
{
    float len = Length();
    x /= len;
    y /= len;
    z /= len;
    w /= len;

    return *this;
}

Mat4 Quat::ToRotationMatrix() const
{
    Mat4 rot;
    return rot.Rotation( GetForward(), GetUp(), GetRight() );
}

Quat& Quat::InitRotation( const Vec3& axis, float angle )
{
    float sinHalfAngle = (float)sin( angle / 2.0 );
    float cosHalfAngle = (float)cos( angle / 2.0 );

    x = axis.x * sinHalfAngle;
    y = axis.y * sinHalfAngle;
    z = axis.z * sinHalfAngle;
    w = cosHalfAngle;

    return *this;
}

Vec3 Quat::GetForward() const { return Vec3( 2.0f * ( x * z - w * y ), 2.0f * ( y * z + w * x ), 1.0f - 2.0f * ( x * x + y * y ) ); }
Vec3 Quat::GetBack() const { return Vec3( -2.0f * ( x * z - w * y ), -2.0f * ( y * z + w * x ), -( 1.0f - 2.0f * ( x * x + y * y ) ) ); }
Vec3 Quat::GetUp() const { return Vec3( 2.0f * ( x * y + w * z ), 1.0f - 2.0f * ( x * x + z * z ), 2.0f * ( y * z - w * x ) ); }
Vec3 Quat::GetDown() const { return Vec3( -2.0f * ( x * y + w * z ), -( 1.0f - 2.0f * ( x * x + z * z ) ), -2.0f * ( y * z - w * x ) ); }
Vec3 Quat::GetRight() const { return Vec3( 1.0f - 2.0f * ( y * y + z * z ), 2.0f * ( x * y - w * z ), 2.0f * ( x * z + w * y ) ); }
Vec3 Quat::GetLeft() const { return Vec3( -( 1.0f - 2.0f * ( y * y + z * z ) ), -2.0f * ( x * y - w * z ), -2.0f * ( x * z + w * y ) ); }

// **************************************************************************************
// ********************************** RECT ***** ****************************************
// **************************************************************************************

Rect::Rect( float value ) : x( value ), y( value ), width( value ), height( value ) {}
Rect::Rect( float _x, float _y, float _w, float _h ) : x(_x), y(_y), width(_w), height(_h) {}
Rect::Rect( const Rect& ref ) : x(ref.x), y(ref.y), width(ref.width), height(ref.height) {}
Rect::~Rect(){}

Rect& Rect::operator=( const Rect& ref )
{
    x = ref.x;
    y = ref.y;
    width = ref.width;
    height = ref.height;
    return *this;
}

bool Rect::operator==( const Rect& ref )
{
    return ( FEQ( x, ref.x ) && FEQ( y, ref.y ) &&
             FEQ( width, ref.width ) && FEQ( height, ref.height ) );
}

bool Rect::operator!=( const Rect& ref )
{
    return !operator==( ref );
}

Rect& Rect::operator+=( const Vec2& ref )
{
    x += ref.x;
    y += ref.y;
    return *this;
}

Rect& Rect::operator-=( const Vec2& ref )
{
    x -= ref.x;
    y -= ref.y;
    return *this;
}

Rect Rect::operator+( const Vec2& ref ) const
{
    return Rect( x+ref.x, y+ref.y, width, height );
}

Rect Rect::operator-( const Vec2& ref ) const
{
    return Rect( x-ref.x, y-ref.y, width, height );
}

void Rect::Left( float value ) { x = value; }
void Rect::Right( float value ) { x = value - width; }
void Rect::Top( float value ) { y = value; }
void Rect::Bottom( float value ) { y = value - width; }
void Rect::Center( const Vec2& ref ) { x = ref.x+width*0.5f; y = ref.y+height*0.5f; }
void Rect::TopLeft( const Vec2& ref ) { Top( ref.y ); Left( ref.x ); }
void Rect::TopRight( const Vec2& ref ) { Top( ref.y ); Right( ref.x ); }
void Rect::BottomLeft( const Vec2& ref ) { Bottom( ref.y ); Left( ref.x ); }
void Rect::BottomRight( const Vec2& ref ) { Bottom( ref.y ); Right( ref.x ); }

float Rect::Left() const { return x; }
float Rect::Right() const { return x + width; }
float Rect::Top() const { return y; }
float Rect::Bottom() const { return y + height; }
Vec2 Rect::Center() const { return Vec2( x+width*0.5f, y+height*0.5f ); }
Vec2 Rect::TopLeft() const { return Vec2( Left(), Top() ); }
Vec2 Rect::TopRight() const { return Vec2( Right(), Top() ); }
Vec2 Rect::BottomLeft() const { return Vec2( Left(), Bottom() ); }
Vec2 Rect::BottomRight() const { return Vec2( Right(), Bottom() ); }

bool Rect::Contains( const Vec2& point )
{
    return ( point.x >= Left() &&
             point.x <= Right() &&
             point.y >= Top() &&
             point.y <= Bottom() );
}

bool Rect::Intersect( const Rect& bounds )
{
    if( bounds.Left() > Right() ) return false;
    if( bounds.Right() < Left() ) return false;
    if( bounds.Top() > Bottom() ) return false;
    if( bounds.Bottom() < Top() ) return false;
    return true;
}
