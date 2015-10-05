// --------------------------------------------------------------------------
// File system boolean types
// --------------------------------------------------------------------------

#ifndef _FILESYSMISC_H_
#define _FILESYSMISC_H_

// ----- Default map type -----
/*
CFileSysEntry( "unknown", TYPE_UNKNOWN, "TYPE_UNKNOWN", "U", "unknown",
        "ReadUnknown", "WriteNamedUnknown",
        "ReadBinaryUnknown", "WriteBinaryUnknown" ),
*/
// ----- Strings -----

CFileSysEntry( "string", TYPE_STRING, "TYPE_STRING", "s", "string",
        "ReadQuotedString", "WriteString", "WriteNamedString",
        "ReadBinaryString", "WriteBinaryNamedString" ),

// ----- Bytes ------

CFileSysEntry( "uint8", TYPE_BYTE, "TYPE_BYTE", "", "int8",
        "ReadByte", "WriteByte", "WriteNamedByte",
        "ReadBinaryByte", "WriteBinaryNamedByte" ),

CFileSysEntry( "int8", TYPE_BYTE, "TYPE_BYTE", "", "int8",
        "ReadByte", "WriteByte", "WriteNamedByte",
        "ReadBinaryByte", "WriteBinaryNamedByte" ),

// ----- Shorts -----

CFileSysEntry( "uint16", TYPE_SHORT, "TYPE_SHORT", "", "int16",
        "ReadShort", "WriteShort", "WriteNamedShort",
        "ReadBinaryShort", "WriteBinaryNamedShort" ),

CFileSysEntry( "int16", TYPE_SHORT, "TYPE_SHORT", "", "int16",
        "ReadShort", "WriteShort", "WriteNamedShort",
        "ReadBinaryShort", "WriteBinaryNamedShort" ),

// ----- Longs -----

CFileSysEntry( "uint64", TYPE_LONG, "TYPE_LONG", "", "long long",
        "ReadLong", "WriteLong", "WriteNamedLong",
        "ReadBinaryLong", "WriteBinaryNamedLong" ),

CFileSysEntry( "int64", TYPE_LONG, "TYPE_LONG", "", "long long",
        "ReadLong", "WriteLong", "WriteNamedLong",
        "ReadBinaryLong", "WriteBinaryNamedLong" ),

#endif
