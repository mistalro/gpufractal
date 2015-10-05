// --------------------------------------------------------------------------
// File:   io_color3f.h
//
// Purpose: Routines to handle byteenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#ifndef _IO_COLOR3F_H_
#define _IO_COLOR3F_H_

// --------------------------------------------------------------------------
// File system for byte management
// --------------------------------------------------------------------------

class CFileSystemColor3f : virtual public CFileSystemPar
{
// ----- Class members ------------------------------------------------------
public:

// ----- Read routines ------------------------------------------------------

inline void ReadColor3f( ifstream &stream, col3f &color )
	{
	stream >> color.m_red;
	stream >> color.m_green;
	stream >> color.m_blue;
	}

// ----- Write routines -----------------------------------------------------

// ----- Plane data -------------------------------------------------------

inline void WriteColor3f( ostream &stream, col3f &color )
	{
	stream << color.m_red << " ";
	stream << color.m_green << " ";
	stream << color.m_blue;
	}

inline void WriteNamedColor3f( ostream &stream, int depth, const char *name,
                                                         col3f &color )
	{
	WriteTabbedDepth( stream, depth );

	stream << "{" << name << " ";
	stream << color.m_red << " ";
	stream << color.m_green << " ";
	stream << color.m_blue << "}\n";
	}

inline void WriteNamedColor3f( ostream &stream, int depth, string &strname,
                                                        col3f &color )
	{
	WriteTabbedDepth( stream, depth );

	stream << "{" << strname.c_str() << " ";
	stream << color.m_red << " ";
	stream << color.m_green << " ";
	stream << color.m_blue << "}\n";
	}

};

#endif	// _IO_COLOR3F_H_
