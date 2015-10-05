// --------------------------------------------------------------------------
// File system data types
// --------------------------------------------------------------------------

#ifndef _FILESYSTYPES_H_
#define _FILESYSTYPES_H_

// --------------------------------------------------------------------------
// Subatomic particles
// --------------------------------------------------------------------------

#define TYPE_UNKNOWN -1
#define TYPE_BLOCK   0x0000

#define BIT_8BIT    0x00008	// These aren't used yet, but we'll
#define BIT_16BIT   0x00010	// define them anyway.
#define BIT_32BIT   0x00020
#define BIT_64BIT   0x00040

#define BIT_BOOLEAN 0x00080
#define BIT_INTEGER 0x00100
#define BIT_STRING  0x00200
#define BIT_VECTOR  0x00400
#define BIT_MATRIX  0x00800
#define BIT_FLOAT   0x01000
#define BIT_COLOR   0x02000
#define BIT_ARRAY   0x04000
#define BIT_DOUBLE  0x08000
#define BIT_BYTE    0x10000
#define BIT_SHORT   0x20000
#define BIT_LONG    0x40000
#define BIT_PLANE      0x80000
#define BIT_QUATERNION 0x100000

#define BIT_SCALAR 0x200000
#define BIT_2D     0x400000
#define BIT_3D     0x800000
#define BIT_4D    0x1000000
#define BIT_23D   0x2000000
#define BIT_32D   0x4000000
#define BIT_43D   0x8000000
#define BIT_34D  0x10000000
#define BIT_UNSIGNED 0x20000000

// --------------------------------------------------------------------------
// Basic data types
// --------------------------------------------------------------------------

#define TYPE_STRING    BIT_STRING         	 // string

#define TYPE_BOOL     (BIT_SCALAR|BIT_BOOLEAN)   // integer / int
#define TYPE_FLOAT    (BIT_SCALAR|BIT_FLOAT)     // float
#define TYPE_DOUBLE   (BIT_SCALAR|BIT_DOUBLE)	 // double 

#define TYPE_INT8     (BIT_SCALAR|BIT_INTEGER|BIT_8BIT)	    // Integer 8
#define TYPE_INT16    (BIT_SCALAR|BIT_INTEGER|BIT_16BIT)    // Integer 16
#define TYPE_INT32    (BIT_SCALAR|BIT_INTEGER|BIT_32BIT)    // Integer 32
#define TYPE_INT64    (BIT_SCALAR|BIT_INTEGER|BIT_64BIT)    // Integer 64

#define TYPE_UINT8    (BIT_SCALAR|BIT_INTEGER|BIT_8BIT)    // Integer 8
#define TYPE_UINT16   (BIT_SCALAR|BIT_INTEGER|BIT_16BIT)   // Integer 16
#define TYPE_UINT32   (BIT_SCALAR|BIT_INTEGER|BIT_32BIT)   // Integer 32
#define TYPE_UINT64   (BIT_SCALAR|BIT_INTEGER|BIT_64BIT)   // Integer 64

#define TYPE_INTEGER  (BIT_SCALAR|BIT_INTEGER)   // integer / int
#define TYPE_SHORT    (BIT_SCALAR|BIT_SHORT)	 // short 
#define TYPE_BYTE     (BIT_SCALAR|BIT_BYTE)	 // byte 
#define TYPE_LONG     (BIT_SCALAR|BIT_LONG)      // long  

#define TYPE_UBYTE    (BIT_SCALAR|BIT_BYTE|BIT_UNSIGNED)  // unsigned byte
#define TYPE_USHORT   (BIT_SCALAR|BIT_SHORT|BIT_UNSIGNED)  // unsigned short
#define TYPE_UINTEGER (BIT_SCALAR|BIT_INTEGER|BIT_UNSIGNED)  // unsigned short
#define TYPE_ULONG    (BIT_SCALAR|BIT_LONG|BIT_UNSIGNED)  // unsigned long

// ----- Boolean types -----

#define TYPE_BOOLARRAY1D (BIT_BOOLEAN|BIT_ARRAY|BIT_SCALAR) // Integer array 1D
#define TYPE_BOOLARRAY2D (BIT_BOOLEAN|BIT_ARRAY|BIT_2D)     // Integer array 2D
#define TYPE_BOOLARRAY3D (BIT_BOOLEAN|BIT_ARRAY|BIT_3D) // Integer array 3D

#define TYPE_BOOL2D (BIT_BOOLEAN|BIT_VECTOR|BIT_2D)        // integer2d / int2d
#define TYPE_BOOL3D (BIT_BOOLEAN|BIT_VECTOR|BIT_3D)        // integer3d / int3d
#define TYPE_BOOL4D (BIT_BOOLEAN|BIT_VECTOR|BIT_4D)        // integer4d / int4d

// ----- Floating-point values -----

#define TYPE_FLOATARRAY1D (BIT_FLOAT|BIT_ARRAY|BIT_SCALAR) // Float array 1D
#define TYPE_FLOATARRAY2D (BIT_FLOAT|BIT_ARRAY|BIT_2D)     // Float array 2D
#define TYPE_FLOATARRAY3D (BIT_FLOAT|BIT_ARRAY|BIT_3D)     // Float array 3D

#define TYPE_VECTOR2F (BIT_VECTOR|BIT_2D|BIT_FLOAT)  // v2f vec2f vector2f vertex2f
#define TYPE_VECTOR3F (BIT_VECTOR|BIT_3D|BIT_FLOAT)  // v3f vec3f vector3f vertex3f
#define TYPE_VECTOR4F (BIT_VECTOR|BIT_4D|BIT_FLOAT)  // v4f vec4f vector4f vertex4f

#define TYPE_MATRIX2F (BIT_MATRIX|BIT_2D|BIT_FLOAT)  // m2f mat2f matrix2f 
#define TYPE_MATRIX3F (BIT_MATRIX|BIT_3D|BIT_FLOAT)  // m3f mat3f matrix3f
#define TYPE_MATRIX4F (BIT_MATRIX|BIT_4D|BIT_FLOAT)  // m4f mat4f matrix4f

#define TYPE_MATRIX32F (BIT_MATRIX|BIT_32D|BIT_FLOAT) // m32f mat32f matrix32f
#define TYPE_MATRIX43F (BIT_MATRIX|BIT_43D|BIT_FLOAT) // m43f mat43f matrix43f

#define TYPE_COLOR3F   (BIT_COLOR|BIT_3D|BIT_FLOAT)   // c3f col3f color3f
#define TYPE_COLOR4F   (BIT_COLOR|BIT_4D|BIT_FLOAT)   // c4f col4f color4f

#define TYPE_PLANE4F   (BIT_PLANE|BIT_FLOAT) 		// p4f
#define TYPE_QUAT4F    (BIT_QUATERNION|BIT_FLOAT)  // quat4f

// ----- Double values -----

#define TYPE_DOUBLEARRAY1D (BIT_DOUBLE|BIT_ARRAY|BIT_SCALAR) // Integer array 1D
#define TYPE_DOUBLEARRAY2D (BIT_DOUBLE|BIT_ARRAY|BIT_2D)     // Integer array 2D
#define TYPE_DOUBLEARRAY3D (BIT_DOUBLE|BIT_ARRAY|BIT_3D) // Integer array 3D

#define TYPE_VECTOR2D (BIT_VECTOR|BIT_2D|BIT_DOUBLE)  // v2f vec2f vector2f vertex2f
#define TYPE_VECTOR3D (BIT_VECTOR|BIT_3D|BIT_DOUBLE)  // v3f vec3f vector3f vertex3f
#define TYPE_VECTOR4D (BIT_VECTOR|BIT_4D|BIT_DOUBLE)  // v4f vec4f vector4f vertex4f

#define TYPE_MATRIX2D (BIT_MATRIX|BIT_2D|BIT_DOUBLE)  // m2f mat2f matrix2f 
#define TYPE_MATRIX3D (BIT_MATRIX|BIT_3D|BIT_DOUBLE)  // m3f mat3f matrix3f
#define TYPE_MATRIX4D (BIT_MATRIX|BIT_4D|BIT_DOUBLE)  // m4f mat4f matrix4f

#define TYPE_MATRIX32D (BIT_MATRIX|BIT_32D|BIT_DOUBLE) // m32f mat32f matrix32f
#define TYPE_MATRIX43D (BIT_MATRIX|BIT_43D|BIT_DOUBLE) // m43f mat43f matrix43f

#define TYPE_COLOR3D   (BIT_COLOR|BIT_3D|BIT_DOUBLE)   // c3f col3f color3f
#define TYPE_COLOR4D   (BIT_COLOR|BIT_4D|BIT_DOUBLE)   // c4f col4f color4f

#define TYPE_PLANE4D   (BIT_PLANE|BIT_DOUBLE) 		// p4f
#define TYPE_QUAT4D    (BIT_QUATERNION|BIT_DOUBLE)  // quat4f

// ----- Integer types -----

#define TYPE_INTARRAY1D (BIT_INTEGER|BIT_ARRAY|BIT_SCALAR) // Integer array 1D
#define TYPE_INTARRAY2D (BIT_INTEGER|BIT_ARRAY|BIT_2D)     // Integer array 2D
#define TYPE_INTARRAY3D (BIT_INTEGER|BIT_ARRAY|BIT_3D) // Integer array 3D

#define TYPE_VEC2I (BIT_VECTOR|BIT_2D|BIT_INTEGER)  // v2i vec2i vector2i vertex2i
#define TYPE_VEC3I (BIT_VECTOR|BIT_3D|BIT_INTEGER)  // v3i vec3i vector3i vertex3i
#define TYPE_VEC4I (BIT_VECTOR|BIT_4D|BIT_INTEGER)  // v4i vec4i vector4i vertex4i

#define TYPE_MATRIX2I  (BIT_MATRIX|BIT_2D|BIT_INTEGER)  // m2i mat2i matrix2i
#define TYPE_MATRIX3I  (BIT_MATRIX|BIT_3D|BIT_INTEGER)  // m3i mat3i matrix3i
#define TYPE_MATRIX4I  (BIT_MATRIX|BIT_4D|BIT_INTEGER)  // m4i mat4i matrix4i

#define TYPE_MATRIX32I (BIT_MATRIX|BIT_32D|BIT_INTEGER) // m32i mat32i matrix32i
#define TYPE_MATRIX43I (BIT_MATRIX|BIT_43D|BIT_INTEGER) // m43i mat43i matrix43i

#define TYPE_COLOR3I   (BIT_COLOR|BIT_3D|BIT_INTEGER)   // c3i col3i color3i
#define TYPE_COLOR4I   (BIT_COLOR|BIT_4D|BIT_INTEGER)   // c4i col4i color4i

#define TYPE_PLANE4I   (BIT_PLANE|BIT_INTEGER) 		// p4i
#define TYPE_QUAT4I    (BIT_QUATERNION|BIT_INTEGER)     // quat4i
#endif	// _FILESYSTYPES_H_
