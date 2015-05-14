#if !defined(MATH_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */

#include <cmath>

#define PI 3.14159265358979323846264338f
#define EPSILON 0.0001f
#define FEQ(a,b) ( fabs(a-b) < EPSILON )
#define ToRadians(d) ( d * ( 180.0f / PI ) )
#define LERP(a,b,f) ((a)+((b)-(a))*(f))

struct Vec2
{
    Vec2( float value = 0.0f );
    Vec2( float _x, float _y );
    Vec2( const Vec2& ref );
    virtual ~Vec2();

    Vec2& operator=( const Vec2& ref );
    bool operator==( const Vec2& ref ) const;
    bool operator!=( const Vec2& ref ) const;
    Vec2& operator+=( const Vec2& ref );
    Vec2& operator-=( const Vec2& ref );
    Vec2& operator*=( const Vec2& ref );
    Vec2& operator*=( float ref );
    Vec2& operator/=( const Vec2& ref );
    Vec2& operator/=( float ref );
    Vec2 operator+( const Vec2& ref ) const;
    Vec2 operator-( const Vec2& ref ) const;
    Vec2 operator*( const Vec2& ref ) const;
    Vec2 operator*( float ref ) const;
    Vec2 operator/( const Vec2& ref ) const;
    Vec2 operator/( float ref ) const;

    static Vec2 Normalize( const Vec2& ref );
    static Vec2 Rotate( const Vec2& ref, float angle );
    static Vec2 Lerp( const Vec2& from, const Vec2& to, float factor );
        
    Vec2&   Normalize();
    Vec2&   Rotate( float angle );
    Vec2&   Lerp( const Vec2& to, float factor );
    Vec2&   Set( float x, float y );
    float   Dot( const Vec2& ref ) const;
    float   Cross( const Vec2& ref ) const;
    float   Max() const;
    float   Min() const;
    float   Length() const;
    
    float   x, y;
};

struct Point
{
    Point( int value = 0 );
    Point( int x, int y );
    Point( const Vec2& ref );
    Point( const Point& ref );
    virtual ~Point();

    Point& operator=( const Point& ref );
    bool operator==( const Point& ref ) const;
    bool operator!=( const Point& ref ) const;
    
    Point& operator+=( const Point& ref );
    Point& operator-=( const Point& ref );
    Point& operator*=( const Point& ref );
    Point& operator*=( int value );
    Point& operator/=( const Point& ref );
    Point& operator/=( int value );
    
    Point operator+( const Point& ref ) const;
    Point operator-( const Point& ref ) const;
    Point operator*( const Point& ref ) const;
    Point operator*( int value ) const;
    Point operator/( const Point& ref ) const;
    Point operator/( int value ) const;

    int x, y;
};

struct Quat;
struct Vec3
{
    Vec3( float value = 0.0f );
    Vec3( float _x, float _y, float _z );
    Vec3( const Vec3& ref );
    virtual ~Vec3();

    Vec3& operator=( const Vec3& ref );
    bool operator==( const Vec3& ref ) const;
    bool operator!=( const Vec3& ref ) const;
    Vec3& operator+=( const Vec3& ref );
    Vec3& operator-=( const Vec3& ref );
    Vec3& operator*=( const Vec3& ref );
    Vec3& operator*=( float ref );
    Vec3& operator/=( const Vec3& ref );
    Vec3& operator/=( float ref );
    Vec3 operator+( const Vec3& ref ) const;
    Vec3 operator-( const Vec3& ref ) const;
    Vec3 operator*( const Vec3& ref ) const;
    Vec3 operator*( float ref ) const;
    Vec3 operator/( const Vec3& ref ) const;
    Vec3 operator/( float ref ) const;

    static Vec3 Normalize( const Vec3& ref );
    static Vec3 Rotate( const Vec3& ref, const Vec3& axis, float angle );
    static Vec3 Abs( const Vec3& ref );
    static Vec3 Lerp( const Vec3& from, const Vec3& to, float factor );

    Vec3    Cross( const Vec3& ref ) const;
    float   Length() const;
    float   Dot( const Vec3& ref ) const;
    float   Max() const;
    float   Min() const;
    Vec3&   Normalize();
    Vec3&   Rotate( const Vec3& axis, float angle );
    Vec3&   Rotate( const Quat& rotation );
    Vec3&   Abs();
    Vec3&   Lerp( const Vec3& to, float factor );
    Vec3&   Set( float x, float y, float z );
        
    float   x, y, z;
};

struct Point3
{
    Point3( int value = 0 );
    Point3( int x, int y, int z );
    Point3( const Point3& ref );
    Point3( const Vec3& ref );
    virtual ~Point3();
    
    Point3& operator=( const Point3& ref );
    bool operator==( const Point3& ref ) const;
    bool operator!=( const Point3& ref ) const;
    Point3& operator+=( const Point3& ref );
    Point3& operator-=( const Point3& ref );
    Point3& operator*=( const Point3& ref );
    Point3& operator*=( int value );
    Point3& operator/=( const Point3& ref );
    Point3& operator/=( int value );
    Point3 operator+( const Point3& ref ) const;
    Point3 operator-( const Point3& ref ) const;
    Point3 operator*( const Point3& ref ) const;
    Point3 operator*( int value ) const;
    Point3 operator/( const Point3& ref ) const;
    Point3 operator/( int value ) const;

    int x, y, z;
};

struct Vec4
{
    Vec4( float value = 0.0f );
    Vec4( float _x, float _y, float _z, float _w );
    Vec4( const Vec3& ref, float _w );
    Vec4( const Vec4& ref );
    virtual ~Vec4();

    Vec4& operator=( const Vec4& ref );
    bool operator==( const Vec4& ref ) const;
    bool operator!=( const Vec4& ref ) const;
    Vec4& operator+=( const Vec4& ref );
    Vec4& operator-=( const Vec4& ref );
    Vec4& operator*=( const Vec4& ref );
    Vec4& operator*=( float ref );
    Vec4& operator/=( const Vec4& ref );
    Vec4& operator/=( float ref );
    Vec4 operator+( const Vec4& ref ) const;
    Vec4 operator-( const Vec4& ref ) const;
    Vec4 operator*( const Vec4& ref ) const;
    Vec4 operator*( float ref ) const;
    Vec4 operator/( const Vec4& ref ) const;
    Vec4 operator/( float ref ) const;

    static Vec4 Normalize( const Vec4& ref );
    static Vec4 Abs( const Vec4& ref );
    static Vec4 Lerp( const Vec4& from, const Vec4& to, float factor );

    float   Length() const;
    float   Max() const;
    float   Min() const;
    Vec4&   Normalize();
    Vec4&   Abs();
    Vec4&   Lerp( const Vec4& to, float factor );
    Vec4&   Set( float x, float y, float z, float w );
        
    float   x, y, z, w;
};

struct Mat4
{
    static const int BYTESIZE;

    Mat4();
    Mat4( const Mat4& ref );
    ~Mat4();

    Mat4& operator=( const Mat4& ref );
    bool operator==( const Mat4& ref ) const;
    bool operator!=( const Mat4& ref ) const;
    Mat4 operator*( const Mat4& ref ) const;
    Vec4 operator*( const Vec4& ref ) const;
    Mat4 Mul( const Mat4& ref ) const;

    float   Get( int x, int y ) const;
    void    Set( int x, int y, float value );

    Mat4&   Identity();
    Mat4&   Transpose();
    Mat4&   Translation( Vec3 translation );
    Mat4&   Translation( float x, float y, float z );
    Mat4&   Rotation( Vec3 rotation );
    Mat4&   Rotation( float x, float y, float z );
    Mat4&   Rotation( const Vec3& forward, const Vec3& up );
    Mat4&   Rotation( const Vec3& forward, const Vec3& up, const Vec3& right );
    Mat4&   Scale( Vec3 scale );
    Mat4&   Scale( float x, float y, float z );
    Mat4&   Perspective( float fov, float aspectRatio, float near, float far );
    Mat4&   Orthographic( float left, float right, float top, float bottom, float near, float far );

    static Mat4 MakeIdentity();
    static Mat4 MakeTranspose( const Mat4& ref );
    static Mat4 MakeTranslation( Vec3 translation );
    static Mat4 MakeTranslation( float x, float y, float z );
    static Mat4 MakeRotation( Vec3 rotation );
    static Mat4 MakeRotation( float x, float y, float z );
    static Mat4 MakeRotation( const Vec3& forward, const Vec3& up );
    static Mat4 MakeRotation( const Vec3& forward, const Vec3& up, const Vec3& right );
    static Mat4 MakeScale( Vec3 scale );
    static Mat4 MakeScale( float x, float y, float z );
    static Mat4 MakePerspective( float fov, float aspectRatio, float near, float far );
    static Mat4 MakeOrthographic( float left, float right, float top, float bottom, float near, float far );

    float   m[16];
};

struct Quat
{
    Quat();
    Quat( float _x, float _y, float _z, float _w );
    Quat( const Vec3& axis, float angle );
    Quat( const Quat& ref );
    virtual ~Quat();

    Quat& operator=( const Quat& ref );
    bool operator==( const Quat& ref ) const;
    bool operator!=( const Quat& ref ) const;
    Quat& operator*=( const Quat& ref );
    Quat& operator*=( const Vec3& ref );
    Quat operator*( const Quat& ref ) const;
    Quat operator*( const Vec3& ref ) const;

    static Quat Normalize( const Quat& ref );
    static Quat MakeRotation( const Vec3& axis, float angle );

    Quat    Conjugate() const;
    float   Length() const;
    Quat&   Normalize();

    Mat4    ToRotationMatrix() const;
    Quat&   InitRotation( const Vec3& axis, float angle );

    Vec3    GetForward() const;
    Vec3    GetBack() const;
    Vec3    GetUp() const;
    Vec3    GetDown() const;
    Vec3    GetLeft() const;
    Vec3    GetRight() const;

    float   x, y, z, w;
};

#define MATH_H
#endif
