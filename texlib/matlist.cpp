/* Copyright (C) 2015 Dr. Michael Robb

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General License
   as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   The program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Public License for more details.

   You should have received a copy of the GNU Public License 
   along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */
// --------------------------------------------------------------------------
// Implementation file for the CMaterialList class
//
// Author Michael S. A. Robb
//
// Date   18th September 2002
// --------------------------------------------------------------------------

#include "texturelib.h"

// --------------------------------------------------------------------------
// Expand the list
//
// Inputs num - Number of units to expand list
//
// Outputs None
//
// Results None
//
// Effects The list is expanded to the desired size
// --------------------------------------------------------------------------

#ifdef OLDVERSION
void CMaterialList::Expand( int num )
{
CMaterial *pnew;
int pn;

if ( num <= m_listmax )			// Sanity check
	return;

pnew = new CMaterial[num];		// New list of pointers

if ( m_listdata )				// Previous list exists
	for ( pn = 0; pn < m_listnum; pn++ )	// For each element
		{
		pnew[pn] = m_listdata[pn];	// Copy pointer
		}

delete [] m_listdata;				// Delete old list

m_listdata = pnew;				// Set new pointer
m_listmax =  num;
}

// --------------------------------------------------------------------------
// Allocate a specified number of pointers
//
// Inputs num - Number of materials to store
//
// Outputs None
//
// Results None
//
// Effects The list is expanded to the desired size
// --------------------------------------------------------------------------

void CMaterialList::Allocate( int num )
{
Expand( num );
}

// --------------------------------------------------------------------------
// Reserve the selected number of pointers
//
// Inputs  num - Number of materials to reserve
//
// Outputs None
//
// Results Index position of first material in block
//
// Effects The list is expanded and a space in the specified list of 
//          materials is allocated.
// --------------------------------------------------------------------------

int CMaterialList::Reserve( int num )
{
int pos;

Expand( m_listnum + num );		// Make space

pos = m_listnum;				// Starting position

m_listnum += num;				// Allocate space

return( pos );					// Return position
}

// --------------------------------------------------------------------------
// Deallocate the material list
//
// Inputs  None
//
// Outputs None
//
// Results None
//
// Effects The material list is deallocated
// --------------------------------------------------------------------------

void CMaterialList::Deallocate( void )
{
delete [] m_listdata;

m_listdata= NULL;
m_pmatcur = NULL;
m_listnum = 0;
m_listmax = 0;
}

// --------------------------------------------------------------------------
// Append the material list
//
// Inputs  ptlist - Existing material list
//
// Outputs None
//
// Results None
//
// Effects The new material list is appended to the existing one
// --------------------------------------------------------------------------

void CMaterialList::Append( CMaterialList &ptlist )
{
int pos, pn;

Expand( m_listnum + ptlist.m_listnum );		// Make space
		
pos = m_listnum;			// Start of first position

for ( pn = 0; pn < ptlist.m_listnum; pn++ )		// Copy textures
	m_listdata[pos+pn] = ptlist.m_listdata[pn];

m_listnum += ptlist.m_listnum;				// Update total
}

// --------------------------------------------------------------------------
// Duplicate the material list
//
// Inputs ptlist - Existing material list
//
// Outputs None
//
// Results None
//
// Effects The existing material list is duplicated
// --------------------------------------------------------------------------

void CMaterialList::Duplicate( CMaterialList &ptlist )
{
Deallocate();

Append( ptlist );
}

// --------------------------------------------------------------------------
// Merge the two material lists
// 
// Inputs ptlist - Existing material list
//
// Outputs None
//
// Results None
//
// Effects The existing material list is merged
// --------------------------------------------------------------------------

void CMaterialList::Merge( CMaterialList &ptlist )
{
int pos, pn;

Expand( m_listnum + ptlist.m_listnum );		// Make space

pos = m_listnum;			// Start of first position

for ( pn = 0; pn < ptlist.m_listnum; pn++ )		// Copy textures
	m_listdata[pos+pn] = ptlist.m_listdata[pn];

m_listnum += ptlist.m_listnum;		// Update total

ptlist.Deallocate();			// Delete existing list
}
#endif
// --------------------------------------------------------------------------
// Find a material by name
//
// Inputs  name - Name to search for
//    	   offset - Offset to begin searching
//
// Outputs None
//
// Results The index number of the matching texture name
//
// Effects The index of the first matching texture is returned
// --------------------------------------------------------------------------

int CMaterialList::FindIndexNameOffset( char *name, int offset )
{
int pn;

for ( pn = offset; pn < m_listnum; pn++ )
	if ( strncmp( name, m_listdata[pn].m_name,MATHS_NAME_MAX ) == 0 )
		return( pn );

return( -1 );
}

// --------------------------------------------------------------------------
// Write the material list to a file
// 
// Inputs fp - Pointer to the file handler
//
// Outputs None
//
// Results None
//
// Effects The list of materials is written to the file
// --------------------------------------------------------------------------

void CMaterialList::FileWrite( FILE *fp )
{
int mn;

fprintf( fp, "{listdata\n" );
fprintf( fp, "{listnum %d}\n", m_listnum );

for ( mn = 0; mn < m_listnum; mn++ )
	m_listdata[mn].FileWrite( fp );

fprintf( fp, "}\n" );

// ... TODO Implement this ...
}

// --------------------------------------------------------------------------
// Read the material list from a file
//
// Inputs fp - Pointer to the file handler
//
// Outputs None
//
// Results None
//
// Effects The list of materials is written to the file
// --------------------------------------------------------------------------

void CMaterialList::FileRead( FILE * /* fp */ )
{
// ... TODO Implement this ...
}

// --------------------------------------------------------------------------
// Begin a new material
//
// Inputs name - name of the material
//
// Outputs None
//
// Results None
//
// Effects A new material is created
// --------------------------------------------------------------------------

int CMaterialList::Begin( char *name )
{
int pos;

if ( m_pmatcur != NULL )	
	printf( "Error Matbegun but previous group not ended" );

Expand( m_listnum+1 );

pos = m_listnum;

m_pmatcur = m_listdata+pos;

strncpy( m_pmatcur->m_name, name, sizeof(CTextureName) );

return( pos );
}

// --------------------------------------------------------------------------
// End the current material
// 
// Inputs  None
//
// Outputs None
//
// Results None
// 
// Effects The material currently being completed is added to the list
// --------------------------------------------------------------------------

void CMaterialList::End( void )
{
if ( m_pmatcur == NULL )
	{
	printf( "Error No group has been begun" );
	return;
	}

m_pmatcur = NULL;
m_listnum += 1;
}

// --------------------------------------------------------------------------
// Set the color component of a material (floating point format)
// 
// Inputs  type - Which component 
//          fr   - Red
//          fg   - Green
//          fb   - Blue
//          fa   - Alpha
//
// Outputs None
//
// Results None
//
// Effects The specified color component is set
// --------------------------------------------------------------------------

void CMaterialList::Color4f( int type, float fr, float fg, float fb, float fa )
{
if ( m_pmatcur == NULL )
	{
	printf( "Error No material has been begun\n" );
	return;
	}

m_pmatcur->SetColor4f( type, fr, fg, fb, fa );
}

// --------------------------------------------------------------------------
// Set the color component of a material (vector format)
//
// Inputs type   - Which component
//         fcolor - Which color
//
// Outputs None
//
// Results None
// 
// Effects The specified color component is set
// --------------------------------------------------------------------------

void CMaterialList::Color4fv( int type, col4f &fcolor )
{
if ( m_pmatcur == NULL )
	{
	printf( "Error No material has been begun\n" );
	return;
	}

m_pmatcur->SetColor4fv( type, fcolor );
}

// --------------------------------------------------------------------------
// Set the shininess factor of a material
// 
// Inputs fshine
//
// Outputs None
//
// Results None
//
// Effects The specified color value is set
// --------------------------------------------------------------------------

void CMaterialList::SetValue( int type, float fvalue )
{
if ( m_pmatcur == NULL )
	{
	printf( "Error No material has been begun\n" );
	return;
	}

m_pmatcur->SetValue( type, fvalue );
}

// --------------------------------------------------------------------------
// Set the selected texture name of a particular layer of the material
// 
// Inputs  type - Type of texture
//			name - Name of texture
//
// Outputs None
//
// Results None
//
// Effects The specified color value is set
// --------------------------------------------------------------------------

void CMaterialList::SetTexture( int type, char *name )
{
if ( m_pmatcur == NULL )
	{
	printf( "Error No material has been begun\n" );
	return;
	}

m_pmatcur->SetTexture( type, name );
}

// --------------------------------------------------------------------------
// Set the selected matrix of a particular layer of the material
// 
// Inputs  type - Type of texture
//			name - Name of texture
//
// Outputs None
//
// Results None
//
// Effects The matrix is set
// --------------------------------------------------------------------------

void CMaterialList::SetMatrix( int type, mat4f &matrix )
{
if ( m_pmatcur == NULL )
	{
	printf( "Error No material has been begun\n" );
	return;
	}

m_pmatcur->SetMatrix( type, matrix );
}

// --------------------------------------------------------------------------
// Sort materials by transparency
//
// Inputs None
//
// Outputs None
//
// Results None
//
// Effects The list of materials is reordered by the transparency value
//          (Stored in the diffuse component of the material)
// --------------------------------------------------------------------------

int mat_sortproc( const void *ptra, const void *ptrb )
{
CMaterial *pmata, *pmatb;

pmata = (CMaterial *) ptra;
pmatb = (CMaterial *) ptrb;

return( pmata->m_diffuse.m_alpha < pmatb->m_diffuse.m_alpha );
}

void CMaterialList::SortByTransparency( void )
{
qsort( m_listdata, m_listnum, sizeof(CMaterial), mat_sortproc );
}

// --------------------------------------------------------------------------
// Match the textures to materials
//
// Inputs  None
//
// Outputs None
//
// Results None
//
// Effects The chosen texture names for each material is used to set the
//          texture index from the existing list
// --------------------------------------------------------------------------

void CMaterialList::FindTextures( CTextureList &texlist, 
                                  CMotionCubeMapList &cubelist )
{
int mn;

for ( mn = 0; mn < m_listnum; mn++ )	
	m_listdata[mn].FindTextures( texlist, cubelist );
}
