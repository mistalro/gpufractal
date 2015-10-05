// --------------------------------------------------------------------------
// File system floating-point types
// --------------------------------------------------------------------------

#ifndef _FILESYSFLOAT_H_
#define _FILESYSFLOAT_H_

// ----- Floats -----

CFileSysEntry( "float32", TYPE_FLOAT, "TYPE_FLOAT", "f", "float",
        "ReadFloat", "WriteFloat", "WriteNamedFloat",
        "ReadBinaryFloat", "WriteBinaryFloat" ),

CFileSysEntry( "float", TYPE_FLOAT, "TYPE_FLOAT", "f", "float",
        "ReadFloat", "WriteFloat", "WriteNamedFloat",
        "ReadBinaryFloat", "WriteBinaryFloat" ),

// ----- Vectors -----

CFileSysEntry( "v2f", TYPE_VECTOR2F, "TYPE_VECTOR2F", "v2f", "CVector2f",
        "ReadVec2f", "WriteVec2f", "WriteNamedVec2f",
        "ReadBinaryVec2f", "WriteBinaryNamedVec2f" ),

CFileSysEntry( "vec2f", TYPE_VECTOR2F, "TYPE_VECTOR2F", "v2f", "CVector2f",
        "ReadVec2f", "WriteVec2f", "WriteNamedVec2f",
        "ReadBinaryVec2f", "WriteBinaryNamedVec2f" ),

CFileSysEntry( "vector2f", TYPE_VECTOR2F, "TYPE_VECTOR2F", "v2f", "CVector2f",
        "ReadVec2f", "WriteVec2f", "WriteNamedVec2f",
        "ReadBinaryVec2f", "WriteBinaryNamedVec2f" ),

CFileSysEntry( "CVector2f", TYPE_VECTOR2F, "TYPE_VECTOR2F", "v2f", "CVector2f",
        "ReadVec2f", "WriteVec2f", "WriteNamedVec2f",
        "ReadBinaryVec2f", "WriteBinaryNamedVec2f" ),

CFileSysEntry( "vertex2f", TYPE_VECTOR2F, "TYPE_VECTOR2F", "v2f", "CVector2f",
        "ReadVec2f", "WriteVec2f", "WriteNamedVec2f",
        "ReadBinaryVec2f", "WriteBinaryNamedVec2f" ),

CFileSysEntry( "v3f", TYPE_VECTOR3F, "TYPE_VECTOR3F", "v3f", "CVector3f",
        "ReadVec3f", "WriteVec3f", "WriteNamedVec3f",
        "ReadBinaryVec3f", "WriteBinaryNamedVec3f" ),

CFileSysEntry( "vec3f", TYPE_VECTOR3F, "TYPE_VECTOR3F", "v3f", "CVector3f",
        "ReadVec3f", "WriteVec3f", "WriteNamedVec3f",
        "ReadBinaryVec3f", "WriteBinaryNamedVec3f" ),

CFileSysEntry( "vector3f", TYPE_VECTOR3F, "TYPE_VECTOR3F", "v3f", "CVector3f",
        "ReadVec3f", "WriteVec3f", "WriteNamedVec3f",
        "ReadBinaryVec3f", "WriteBinaryNamedVec3f" ),

CFileSysEntry( "vertex3f", TYPE_VECTOR3F, "TYPE_VECTOR3F", "v3f", "CVector3f",
        "ReadVec3f", "WriteVec3f", "WriteNamedVec3f",
        "ReadBinaryVec3f", "WriteBinaryNamedVec3f" ),

CFileSysEntry( "CVector3f", TYPE_VECTOR3F, "TYPE_VECTOR3F", "v3f", "CVector3f",
        "ReadVec3f", "WriteVec3f", "WriteNamedVec3f",
        "ReadBinaryVec3f", "WriteBinaryNamedVec3f" ),

CFileSysEntry( "v4f", TYPE_VECTOR4F, "TYPE_VECTOR4F", "v4f", "CVector4f",
        "ReadVec4f", "WriteVec4f", "WriteNamedVec4f",
        "ReadBinaryVec4f", "WriteBinaryNamedVec4f" ),

CFileSysEntry( "vec4f", TYPE_VECTOR4F, "TYPE_VECTOR4F", "v4f", "CVector4f",
        "ReadVec4f", "WriteVec4f", "WriteNamedVec4f",
        "ReadBinaryVec4f", "WriteBinaryNamedVec4f" ),

CFileSysEntry( "vector4f", TYPE_VECTOR4F, "TYPE_VECTOR4F", "v4f", "CVector4f",
        "ReadVec4f", "WriteVec4f", "WriteNamedVec4f",
        "ReadBinaryVec4f", "WriteBinaryNamedVec4f" ),

CFileSysEntry( "vertex4f", TYPE_VECTOR4F, "TYPE_VECTOR4F", "v4f", "CVector4f",
        "ReadVec4f", "WriteVec4f", "WriteNamedVec4f",
        "ReadBinaryVec4f", "WriteBinaryNamedVec4f" ),

CFileSysEntry( "CVector4f", TYPE_VECTOR4F, "TYPE_VECTOR4F", "v4f", "CVector4f",
        "ReadVec4f", "WriteVec4f", "WriteNamedVec4f",
        "ReadBinaryVec4f", "WriteBinaryNamedVec4f" ),

// ------ Matrices -----

CFileSysEntry( "matrix2f", TYPE_MATRIX2F, "TYPE_MATRIX2F", "m2f", "CMatrix2f",
        "ReadMatrix2f", "WriteMatrix2f", "WriteNamedMatrix2f",
        "ReadBinaryMat2f", "WriteBinaryNamedMat2f" ),

CFileSysEntry( "matrix3f", TYPE_MATRIX3F, "TYPE_MATRIX3F", "m3f", "CMatrix3f",
        "ReadMatrix3f", "WriteMatrix3f", "WriteNamedMatrix3f",
        "ReadBinaryMat3f", "WriteBinaryNamedMat3f" ),

CFileSysEntry( "matrix4f", TYPE_MATRIX4F, "TYPE_MATRIX4F", "m4f", "CMatrix4f",
        "ReadMatrix4f", "WriteMatrix4f", "WriteNamedMatrix4f",
        "ReadBinaryMat4f", "WriteBinaryNamedMat4f" ),

CFileSysEntry( "matrix32f", TYPE_MATRIX32F, "TYPE_MATRIX32F", "m32f", "CMatrix32f",
        "ReadMatrix32f", "WriteMatrix32f", "WriteNamedMatrix32f",
        "ReadBinaryMat32f", "WriteBinaryNamedMat32f" ),

CFileSysEntry( "matrix43f", TYPE_MATRIX43F, "TYPE_MATRIX43F", "m43f", "CMatrix43f",
        "ReadMatrix43f", "WriteMatrix43f", "WriteNamedMatrix43f",
        "ReadBinaryMat43f", "WriteBinaryNamedMat43f" ),

// ----- Colors -----

CFileSysEntry( "c3f", TYPE_COLOR3F, "TYPE_COLOR3F", "c3f", "CColor3f",
        "ReadColor3f", "WriteColor3f", "WriteNamedColor3f",
        "ReadBinaryColor3f", "WriteBinaryNamedColor3f" ),

CFileSysEntry( "col3f", TYPE_COLOR3F, "TYPE_COLOR3F", "c3f", "CColor3f",
        "ReadColor3f", "WriteColor3f", "WriteNamedColor3f",
        "ReadBinaryColor3f", "WriteBinaryNamedColor3f" ),

CFileSysEntry( "color3f", TYPE_COLOR3F, "TYPE_COLOR3F", "c3f", "CColor3f",
        "ReadColor3f", "WriteColor3f", "WriteNamedColor3f",
        "ReadBinaryColor3f", "WriteBinaryNamedColor3f" ),

CFileSysEntry( "c4f", TYPE_COLOR4F, "TYPE_COLOR4F", "c4f", "CColor4f",
        "ReadColor4f", "WriteColor4f", "WriteNamedColor4f",
        "ReadBinaryColor4f", "WriteBinaryNamedColor4f" ),

CFileSysEntry( "col4f", TYPE_COLOR4F, "TYPE_COLOR4F", "c4f", "CColor4f",
        "ReadColor4f", "WriteColor4f", "WriteNamedColor4f",
        "ReadBinaryColor4f", "WriteBinaryNamedColor4f" ),

CFileSysEntry( "color4f", TYPE_COLOR4F, "TYPE_COLOR4F", "c4f", "CColor4f",
        "ReadColor4f", "WriteColor4f", "WriteNamedColor4f",
        "ReadBinaryColor4f", "WriteBinaryNamedColor4f" ),

// ----- Planes -----

CFileSysEntry( "plane4f", TYPE_PLANE4F, "TYPE_PLANE4F", "4f", "CPlane4f",
        "ReadPlane4f", "WritePlane4f", "WriteNamedPlane4f",
        "ReadBinaryPlane4f", "WriteBinaryNamedPlane4f" ),

CFileSysEntry( "pln4f", TYPE_PLANE4F, "TYPE_PLANE4F", "4f", "CPlane4f",
        "ReadPlane4f", "WritePlane4f", "WriteNamedPlane4f",
        "ReadBinaryPlane4f", "WriteBinaryNamedPlane4f" ),

CFileSysEntry( "p4f", TYPE_PLANE4F, "TYPE_PLANE4F", "4f", "CPlane4f",
        "ReadPlane4f", "WritePlane4f", "WriteNamedPlane4f",
        "ReadBinaryPlane4f", "WriteBinaryNamedPlane4f" ),

// ----- Quaternions -----

CFileSysEntry( "quaternion4f", TYPE_QUAT4F, "TYPE_QUAT4F", "4f", "CQuaternion",
        "ReadQuat4f", "WriteQuaternion4f", "WriteNamedQuaternion4f",
        "ReadBinaryQuat4f", "WriteBinaryNamedQuaternion4f" ),

CFileSysEntry( "quat4f", TYPE_QUAT4F, "TYPE_QUAT4F", "4f", "CQuaternion",
        "ReadQuat4f", "WriteQuaternion4f", "WriteNamedQuaternion4f",
        "ReadBinaryQuat4f", "WriteBinaryNamedQuaternion4f" ),

CFileSysEntry( "q4f", TYPE_QUAT4F, "TYPE_QUAT4F", "4f", "CQuaternion",
        "ReadQuat4f", "WriteQuaternion4f", "WriteNamedQuaternion4f",
        "ReadBinaryQuat4f", "WriteBinaryNamedQuaternion4f" ),

// ----- Float arrays -----

CFileSysEntry( "floatarray1d", TYPE_FLOATARRAY1D, "TYPE_FLOATARRAY1D", "fv", "float *",
        "ReadFloatArray1D", "WriteFloatArray1D", "WriteNamedFloatArray1D",
        "ReadBinaryFloatArray1D", "WriteBinaryNamedFloatArray1D" ),

CFileSysEntry( "floatarray2d", TYPE_FLOATARRAY2D, "TYPE_FLOATARRAY2D", "2fv", "float *",
        "ReadFloatArray2D", "WriteFloatArray2D", "WriteNamedFloatArray2D",
        "ReadBinaryFloatArray2D", "WriteBinaryNamedFloatArray2D" ),

CFileSysEntry( "floatarray3d", TYPE_FLOATARRAY3D, "TYPE_FLOATARRAY3D", "3fv", "float *",
        "ReadFloatArray3D", "WriteFloatArray3D", "WriteNamedFloatArray3D",
        "ReadBinaryFloatArray3D", "WriteBinaryNamedFloatArray3D" ),

#endif	// _FILESYSFLOAT_H_

