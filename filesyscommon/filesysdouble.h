// --------------------------------------------------------------------------
// File system double floating-point types
// --------------------------------------------------------------------------

#ifndef _FILESYSDOUBLE_H_
#define _FILESYSDOUBLE_H_

// ----- Doubles -----

CFileSysEntry( "float64", TYPE_DOUBLE, "TYPE_DOUBLE", "f", "double",
        "ReadDouble", "WriteDouble", "WriteNamedDouble",
        "ReadBinaryDouble", "WriteBinaryDouble" ),

CFileSysEntry( "double", TYPE_DOUBLE, "TYPE_DOUBLE", "f", "double",
        "ReadDouble", "WriteDouble", "WriteNamedDouble",
        "ReadBinaryDouble", "WriteBinaryDouble" ),

// ----- Vectors -----

CFileSysEntry( "v2d", TYPE_VECTOR2D, "TYPE_VECTOR2D", "v2d", "CVector2d",
        "ReadVec2d", "WriteVec2d", "WriteNamedVec2d",
        "ReadBinaryVec2d", "WriteBinaryNamedVec2d" ),

CFileSysEntry( "vec2d", TYPE_VECTOR2D, "TYPE_VECTOR2D", "v2d", "CVector2d",
        "ReadVec2d", "WriteVec2d", "WriteNamedVec2d",
        "ReadBinaryVec2d", "WriteBinaryNamedVec2d" ),

CFileSysEntry( "vector2d", TYPE_VECTOR2D, "TYPE_VECTOR2D", "v2d", "CVector2d",
        "ReadVec2d", "WriteVec2d", "WriteNamedVec2d",
        "ReadBinaryVec2d", "WriteBinaryNamedVec2d" ),

CFileSysEntry( "vertex2d", TYPE_VECTOR2D, "TYPE_VECTOR2D", "v2d", "CVector2d",
        "ReadVec2d", "WriteVec2d", "WriteNamedVec2d",
        "ReadBinaryVec2d", "WriteBinaryNamedVec2d" ),

CFileSysEntry( "v3d", TYPE_VECTOR3D, "TYPE_VECTOR3D", "v3d", "CVector3d",
        "ReadVec3d", "WriteVec3d", "WriteNamedVec3d",
        "ReadBinaryVec3d", "WriteBinaryNamedVec3d" ),

CFileSysEntry( "vec3d", TYPE_VECTOR3D, "TYPE_VECTOR3D", "v3d", "CVector3d",
        "ReadVec3d", "WriteVec3d", "WriteNamedVec3d",
        "ReadBinaryVec3d", "WriteBinaryNamedVec3d" ),

CFileSysEntry( "vector3d", TYPE_VECTOR3D, "TYPE_VECTOR3D", "v3d", "CVector3d",
        "ReadVec3d", "WriteVec3d", "WriteNamedVec3d",
        "ReadBinaryVec3d", "WriteBinaryNamedVec3d" ),

CFileSysEntry( "vertex3d", TYPE_VECTOR3D, "TYPE_VECTOR3D", "v3d", "CVector3d",
        "ReadVec3d", "WriteVec3d", "WriteNamedVec3d",
        "ReadBinaryVec3d", "WriteBinaryNamedVec3d" ),

CFileSysEntry( "v4d", TYPE_VECTOR4D, "TYPE_VECTOR4D", "v4d", "CVector4d",
        "ReadVec4d", "WriteVec4d", "WriteNamedVec4d",
        "ReadBinaryVec4d", "WriteBinaryNamedVec4d" ),

CFileSysEntry( "vec4d", TYPE_VECTOR4D, "TYPE_VECTOR4D", "v4d", "CVector4d",
        "ReadVec4d", "WriteVec4d", "WriteNamedVec4d",
        "ReadBinaryVec4d", "WriteBinaryNamedVec4d" ),

CFileSysEntry( "vector4d", TYPE_VECTOR4D, "TYPE_VECTOR4D", "v4d", "CVector4d",
        "ReadVec4d", "WriteVec4d", "WriteNamedVec4d",
        "ReadBinaryVec4d", "WriteBinaryNamedVec4d" ),

CFileSysEntry( "vertex4d", TYPE_VECTOR4D, "TYPE_VECTOR4D", "v4d", "CVector4d",
        "ReadVec4d", "WriteVec4d", "WriteNamedVec4d",
        "ReadBinaryVec4d", "WriteBinaryNamedVec4d" ),

// ------ Matrices -----

CFileSysEntry( "matrix2d", TYPE_MATRIX2D, "TYPE_MATRIX2D", "m2d", "CMatrix2d",
        "ReadMatrix2d", "WriteMatrix2d", "WriteNamedMatrix2d",
        "ReadBinaryMat2d", "WriteBinaryNamedMat2d" ),

CFileSysEntry( "matrix3d", TYPE_MATRIX3D, "TYPE_MATRIX3D", "m3d", "CMatrix3d",
        "ReadMatrix3d", "WriteMatrix3d", "WriteNamedMatrix3d",
        "ReadBinaryMat3d", "WriteBinaryNamedMat3d" ),

CFileSysEntry( "matrix4d", TYPE_MATRIX4D, "TYPE_MATRIX4D", "m4d", "CMatrix4d",
        "ReadMatrix4d", "WriteMatrix4d", "WriteNamedMatrix4d",
        "ReadBinaryMat4d", "WriteBinaryNamedMat4d" ),

CFileSysEntry( "matrix32d", TYPE_MATRIX32D, "TYPE_MATRIX32D", "m32d", "CMatrix32d",
        "ReadMatrix32d", "WriteMatrix32d", "WriteNamedMatrix32d",
        "ReadBinaryMat32d", "WriteBinaryNamedMat32d" ),

CFileSysEntry( "matrix43d", TYPE_MATRIX43D, "TYPE_MATRIX43D", "m43d", "CMatrix43d",
        "ReadMatrix43d", "WriteMatrix43d", "WriteNamedMatrix43d",
        "ReadBinaryMat43d", "WriteBinaryNamedMat43d" ),


// ----- Colors -----

CFileSysEntry( "c3d", TYPE_COLOR3D, "TYPE_COLOR3D", "c3d", "CColor3d",
        "ReadColor3d", "WriteColor3d", "WriteNamedColor3d",
        "ReadBinaryColor3d", "WriteBinaryNamedColor3d" ),

CFileSysEntry( "col3d", TYPE_COLOR3D, "TYPE_COLOR3D", "c3d", "CColor3d",
        "ReadColor3d", "WriteColor3d", "WriteNamedColor3d",
        "ReadBinaryColor3d", "WriteBinaryNamedColor3d" ),

CFileSysEntry( "color3d", TYPE_COLOR3D, "TYPE_COLOR3D", "c3d", "CColor3d",
        "ReadColor3d", "WriteColor3d", "WriteNamedColor3d",
        "ReadBinaryColor3d", "WriteBinaryNamedColor3d" ),

CFileSysEntry( "c4d", TYPE_COLOR4D, "TYPE_COLOR4D", "c4d", "CColor4d",
        "ReadColor4d", "WriteColor4d", "WriteNamedColor4d",
        "ReadBinaryColor4d", "WriteBinaryNamedColor4d" ),

CFileSysEntry( "col4d", TYPE_COLOR4D, "TYPE_COLOR4D", "c4d", "CColor4d",
        "ReadColor4d", "WriteColor4d", "WriteNamedColor4d",
        "ReadBinaryColor4d", "WriteBinaryNamedColor4d" ),

CFileSysEntry( "color4d", TYPE_COLOR4D, "TYPE_COLOR4D", "c4d", "CColor4d",
        "ReadColor4d", "WriteColor4d", "WriteNamedColor4d",
        "ReadBinaryColor4d", "WriteBinaryNamedColor4d" ),

#endif	// _FILESYSDOUBLE_H_

