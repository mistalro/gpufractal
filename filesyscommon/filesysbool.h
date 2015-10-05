// --------------------------------------------------------------------------
// File system boolean types
// --------------------------------------------------------------------------

#ifndef _FILESYSBOOL_H_
#define _FILESYSBOOL_H_

// For just now, Booleans are stored as integers
CFileSysEntry( "bool", TYPE_BOOL, "TYPE_BOOL", "", "int32",
        "ReadInteger", "WriteInteger", "WriteNamedInteger",
        "ReadBinaryInteger", "WriteBinaryNamedInteger" ),

CFileSysEntry( "boolarray1d",TYPE_BOOLARRAY1D, "TYPE_BOOLARRAY1D", "b", "bool *",
        "ReadBoolArray1D", "WriteBoolArray1D", "WriteNamedBoolArray1D",
        "ReadBinaryBoolArray1D", "WriteBinaryNamedBoolArray1D" ),

CFileSysEntry( "boolarray2d",TYPE_BOOLARRAY2D, "TYPE_BOOLARRAY2D", "2b", "bool *",
        "ReadBoolArray2D", "WriteBoolArray2D", "WriteNamedBoolArray2D",
        "ReadBinaryBoolArray2D", "WriteBinaryNamedBoolArray2D" ),

CFileSysEntry( "boolarray3d",TYPE_BOOLARRAY3D, "TYPE_BOOLARRAY3D", "3b", "bool *",
        "ReadBoolArray3D", "WriteBoolArray3D", "WriteNamedBoolArray3D",
        "ReadBinaryBoolArray3D", "WriteBinaryNamedBoolArray3D" ),

#endif
