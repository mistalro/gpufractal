// --------------------------------------------------------------------------
// File system integer types
// --------------------------------------------------------------------------

#ifndef _FILESYSINT_H_
#define _FILESYSINT_H_

// ----- Bytes ------

CFileSysEntry( "uint8", TYPE_UINT8, "TYPE_UINT8", "", "uint8",
        "ReadByte", "WriteByte", "WriteNamedByte",
        "ReadBinaryByte", "WriteBinaryNamedByte" ),

CFileSysEntry( "int8", TYPE_INT8, "TYPE_INT8", "", "int8",
        "ReadByte", "WriteByte", "WriteNamedByte",
        "ReadBinaryByte", "WriteBinaryNamedByte" ),

// ----- Shorts -----

CFileSysEntry( "uint16", TYPE_USHORT, "TYPE_USHORT", "", "uint16",
        "ReadShort", "WriteShort", "WriteNamedShort",
        "ReadBinaryShort", "WriteBinaryNamedShort" ),

CFileSysEntry( "int16", TYPE_SHORT, "TYPE_SHORT", "", "int16",
        "ReadShort", "WriteShort", "WriteNamedShort",
        "ReadBinaryShort", "WriteBinaryNamedShort" ),

// ----- Integers -----

CFileSysEntry( "integer", TYPE_INTEGER, "TYPE_INTEGER", "", "int",
        "ReadInteger", "WriteInteger", "WriteNamedInteger",
        "ReadBinaryInteger", "WriteBinaryNamedInteger" ),

CFileSysEntry( "uint32", TYPE_UINT32, "TYPE_UINT32", "", "uint32",
        "ReadInteger", "WriteInteger", "WriteNamedInteger",
        "ReadBinaryInteger", "WriteBinaryNamedInteger" ),

CFileSysEntry( "int32", TYPE_INT32, "TYPE_INTEGER", "", "int32",
        "ReadInteger", "WriteInteger", "WriteNamedInteger",
        "ReadBinaryInteger", "WriteBinaryNamedInteger" ),

// ----- Longs -----

CFileSysEntry( "uint64", TYPE_UINT64, "TYPE_UINT64", "", "long long",
        "ReadLong", "WriteLong", "WriteNamedLong",
        "ReadBinaryLong", "WriteBinaryNamedLong" ),

CFileSysEntry( "int64", TYPE_INT64, "TYPE_LONG", "", "long long",
        "ReadLong", "WriteLong", "WriteNamedLong",
        "ReadBinaryLong", "WriteBinaryNamedLong" ),

// ----- Arrays -----

CFileSysEntry( "intarray1d", TYPE_INTARRAY1D, "TYPE_INTARRAY1D", "iv", "int *",
        "ReadIntegerArray1D", "WriteIntegerArray1D", "WriteNamedIntegerArray1D",
        "ReadBinaryIntegerArray1D", "WriteBinaryNamedIntegerArray1D" ),

CFileSysEntry( "intarray2d", TYPE_INTARRAY2D, "TYPE_INTARRAY2D", "2iv", "int *",
        "ReadIntegerArray2D", "WriteIntegerArray2D", "WriteNamedIntegerArray2D",
        "ReadBinaryIntegerArray2D", "WriteBinaryNamedIntegerArray2D" ),

CFileSysEntry( "intarray3d", TYPE_INTARRAY3D, "TYPE_INTARRAY3D", "3iv", "int *",
        "ReadIntegerArray3D", "WriteIntegerArray3D", "WriteNamedIntegerArray3D",
        "ReadBinaryIntegerArray3D", "WriteBinaryNamedIntegerArray3D" ),

CFileSysEntry( "int2d", TYPE_VEC2I, "TYPE_VEC2I", "2i", "CVector2i",
        "ReadVec2i", "WriteVec2i", "WriteNamedVec2i",
        "ReadBinaryVec2i", "WriteBinaryVec2i" ),

CFileSysEntry( "integer2d", TYPE_VEC2I, "TYPE_VEC2I", "2i", "CVector2i",
        "ReadVec2i", "WriteVec2i", "WriteNamedVec2i",
        "ReadBinaryVec2i", "WriteBinaryVec2i" ),

CFileSysEntry( "int3d", TYPE_VEC3I, "TYPE_VEC3I", "3i", "CVector3i",
        "ReadVec3i", "WriteVec3i", "WriteNamedVec3i",
        "ReadBinaryVec3i", "WriteBinaryVec3i" ),

CFileSysEntry( "integer3d", TYPE_VEC3I, "TYPE_VEC3I", "3i", "CVector3i",
        "ReadVec3i", "WriteVec3i", "WriteNamedVec3i",
        "ReadBinaryVec3i", "WriteBinaryVec3i" ),

CFileSysEntry( "vec3i", TYPE_VEC3I, "TYPE_VEC3I", "3i", "CVector3i",
        "ReadVec3i", "WriteVec3i", "WriteNamedVec3i",
        "ReadBinaryVec3i", "WriteBinaryVec3i" ),

CFileSysEntry( "int4d", TYPE_VEC4I, "TYPE_VEC4I", "4i", "CVector4i",
        "ReadVec4i", "WriteVec4i", "WriteNamedVec4i",
        "ReadBinaryVec4i", "WriteBinaryVec4i" ),

CFileSysEntry( "vec4i", TYPE_VEC4I, "TYPE_VEC4I", "4i", "CVector4i",
        "ReadVec4i", "WriteVec4i", "WriteNamedVec4i",
        "ReadBinaryVec4i", "WriteBinaryVec4i" ),

CFileSysEntry( "integer4d", TYPE_VEC4I, "TYPE_VEC4I", "4i", "CVector4i",
        "ReadVec4i", "WriteVec4i", "WriteNamedVec4i",
        "ReadBinaryVec4i", "WriteBinaryVec4i" ),

CFileSysEntry( "mat2i", TYPE_MATRIX2I, "TYPE_MATRIX2I", "m2i", "CMatrix2i",
        "ReadMat2i", "WriteMatrix2i", "WriteNamedMatrix2i",
        "ReadBinaryMat43f", "WriteBinaryNamedMat43f" ),

CFileSysEntry( "mat3i", TYPE_MATRIX3I, "TYPE_MATRIX3I", "m3i", "CMatrix3i",
        "ReadMat3i", "WriteMatrix3i", "WriteNamedMatrix3i",
        "ReadBinaryMat3i", "WriteBinaryNamedMat3i" ),

CFileSysEntry( "mat4i", TYPE_MATRIX4I, "TYPE_MATRIX4I", "m4i", "CMatrix4i",
        "ReadMat4i", "WriteMatrix4i", "WriteNamedMatrix4i",
        "ReadBinaryMat4i", "WriteBinaryNamedMat4i" ),

CFileSysEntry( "matrix2i", TYPE_MATRIX2I, "TYPE_MATRIX2I", "m2i", "CMatrix2i",
        "ReadMat2i", "WriteMatrix2i", "WriteNamedMatrix2i",
        "ReadBinaryMat43f", "WriteBinaryNamedMat43f" ),

CFileSysEntry( "matrix3i", TYPE_MATRIX3I, "TYPE_MATRIX3I", "m3i", "CMatrix3i",
        "ReadMat3i", "WriteMatrix3i", "WriteNamedMatrix3i",
        "ReadBinaryMat3i", "WriteBinaryNamedMat3i" ),

CFileSysEntry( "matrix4i", TYPE_MATRIX4I, "TYPE_MATRIX4I", "m4i", "CMatrix4i",
        "ReadMat4i", "WriteMatrix4i", "WriteNamedMatrix4i",
        "ReadBinaryMat4i", "WriteBinaryNamedMat4i" ),

#endif

