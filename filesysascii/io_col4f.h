// --------------------------------------------------------------------------
// File:   io_color4f.h
//
// Purpose: Routines to handle byteenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#ifndef _IO_COLOR4F_H_
#define _IO_COLOR4F_H_

// --------------------------------------------------------------------------
// File system for byte management
// --------------------------------------------------------------------------

class CFileSystemColor4f : virtual public CFileSystemPar
{
// ----- Class members ------------------------------------------------------
public:

// ----- Read routines ------------------------------------------------------

inline void ReadColor4f( ifstream &stream, col4f &color )
	{
	stream >> color.m_red;
	stream >> color.m_green;
	stream >> color.m_blue;
	stream >> color.m_alpha;
	}

// ----- Write routines -----------------------------------------------------

inline void WriteColor4f( ostream &stream, col4f &color )
	{
	stream << color.m_red << " ";
	stream << color.m_green << " ";
	stream << color.m_blue << " ";
	stream << color.m_alpha << "}\n";
	}

inline void WriteNamedColor4f( ostream &stream, int depth, const char *pname,
                                                         col4f &color )
	{
	WriteTabbedDepth( stream, depth );

	stream << "{" << pname << " ";
	stream << color.m_red << " ";
	stream << color.m_green << " ";
	stream << color.m_blue << " ";
	stream << color.m_alpha << "}\n";
	}

inline void WriteNamedColor4f( ostream &stream, int depth, string &strname,
                                                        col4f &color )
	{
	WriteTabbedDepth( stream, depth );

	stream << "{" << strname.c_str() << " ";
	stream << color.m_red << " ";
	stream << color.m_green << " ";
	stream << color.m_blue << " ";
	stream << color.m_alpha << "}\n";
	}

};

#endif	// _IO_COLOR4F_H_
