// --------------------------------------------------------------------------
// File:   io_color3d.h
//
// Purpose: Routines to handle byteenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#ifndef _IO_COLOR3D_H_
#define _IO_COLOR3D_H_

// --------------------------------------------------------------------------
// File system for byte management
// --------------------------------------------------------------------------

class CFileSystemColor3d : virtual public CFileSystemPar
{
// ----- Class members ------------------------------------------------------
public:

// ----- Read routines ------------------------------------------------------

inline void ReadColor3d( ifstream &stream, col3d &color )
	{
	stream >> color.m_red;
	stream >> color.m_green;
	stream >> color.m_blue;
	}

// ----- Write routines -----------------------------------------------------

// ----- Plane data -------------------------------------------------------

inline void WriteColor3d( ostream &stream, col3d &color )
	{
	stream << color.m_red << " ";
	stream << color.m_green << " ";
	stream << color.m_blue;
	}

inline void WriteNamedColor3d( ostream &stream, int depth, const char *name,
                                                         col3d &color )
	{
	WriteTabbedDepth( stream, depth );

	stream << "{" << name << " ";
	stream << color.m_red << " ";
	stream << color.m_green << " ";
	stream << color.m_blue << "}\n";
	}

inline void WriteNamedColor3d( ostream &stream, int depth, string &strname,
                                                        col3d &color )
	{
	WriteTabbedDepth( stream, depth );

	stream << "{" << strname.c_str() << " ";
	stream << color.m_red << " ";
	stream << color.m_green << " ";
	stream << color.m_blue << "}\n";
	}
};

#endif	// _IO_COLOR3D_H_
