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
// File: templatelist.h
//
// Purpose: Template list class
//
// Author: Michael S. A. Robb
//
// Date: 18th April 2004
// --------------------------------------------------------------------------

#ifndef __TEMPLATELIST__
#define __TEMPLATELIST__

template <class T> class TList 
{
public:
int m_listnum;      // Current number of items
int m_listmax;      // Maximum number of items
T  *m_listdata;     // List of items

// ----- Constructor and Destructor -----------------------------------------

TList() { Init(); };
~TList() { Deallocate(); };

// ----- Functions and Procedures -------------------------------------------

void Init( void )
    {
    m_listnum = 0;
    m_listmax = 0;
    m_listdata= NULL;
    };

void Deallocate( void )
    {
    m_listnum = 0;
    m_listmax = 0;

    if ( m_listdata )
        delete [] m_listdata;

	m_listdata = NULL;
    };

void Allocate( int num )
    {
    Deallocate();

    m_listnum = 0;  
    m_listmax = num;
    m_listdata = new T[num];
    };

void Expand( int num )
    {
    T *pnew;
    int pn;

    if ( num < m_listmax )
        return;

    pnew = new T[num];

    if (m_listdata )
        {
        for ( pn = 0; pn < m_listnum; pn++ )
			{
            		pnew[pn] = m_listdata[pn];
	    		m_listdata[pn].Init();
			}

        delete [] m_listdata;	
        }   

    m_listdata = pnew;
    m_listmax  = num;
	pnew = NULL;
    };

int Reserve( int num )
    {
    int pos = m_listnum;

    Expand( m_listnum + num );

    m_listnum += num;

    return( pos );
    }

int  Add( T &item )
	{
    int pos = m_listnum;

    Expand( m_listnum+10 );

    m_listdata[m_listnum] = item;
    m_listnum++;
    
    return( pos );
    };

int AddTransferList( int num, T *pitem )
    {
    int pos = m_listnum;
    int pn;

    Expand( m_listnum+num );

    for ( pn = 0; pn < num; pn++ )
         {
         m_listdata[pn+m_listnum] = pitem[pn];
         pitem->Init();
         }

    m_listnum += num;

    return( pos );
    }

int AddDuplicateList( int num, T *pitem )
    {
    int pos = m_listnum;
    int pn;

    Expand( m_listnum+num );

    for ( pn = 0; pn < num; pn++ )
        m_listdata[pn+m_listnum].Duplicate( pitem[pn] );

    m_listnum += num;

    return( pos );
    }

int AddList( int num, T *pitem )
    {
    int pos = m_listnum;
    int pn;

    Expand( m_listnum+num );

    for ( pn = 0; pn < num; pn++ )
        m_listdata[pn+m_listnum] = pitem[pn];

    m_listnum += num;

    return( pos );
    }

void Insert( int pos, T &pitem )
    {
    int max = m_listnum;
    int pn;

    Expand( m_listnum+1 );

    for ( pn = max-1; pn >= pos; pn-- )
        m_listdata[pn+1] = m_listdata[pn];

    m_listdata[pos] = pitem;

    m_listnum++;
    }

void Delete( int pos )  
    {
    int pn;

    if ( pos >= m_listnum )
        return;

    for ( pn = pos; pn < m_listnum-1; pn++ )
        m_listdata[pn] = m_listdata[pn+1];

    m_listnum--;
    }

void Duplicate( class TList &listsrc )
    {
    int pn;

    Allocate( listsrc.m_listnum );

    for ( pn = 0; pn < listsrc.m_listnum; pn++ )
        m_listdata[pn] = listsrc.m_listdata[pn];    
    }

void Append( TList &listsrc )
    {
    int pn;

    if ( listsrc.m_listnum == 0 )
        return;

    if ( (m_listnum + listsrc.m_listnum) == 0 )
        return;

    Expand( m_listnum + listsrc.m_listnum );

    for ( pn = 0; pn < listsrc.m_listnum; pn++ )
        m_listdata[pn+m_listnum].Duplicate( listsrc.m_listdata[pn] );

    m_listnum += listsrc.m_listnum;
    }

void Transfer( TList &listsrc )
    {
    int pn;

    if ( (m_listnum + listsrc.m_listnum) == 0 )
       return;

    Expand( m_listnum + listsrc.m_listnum );

    for ( pn = 0; pn < listsrc.m_listnum; pn++ )
       {
       m_listdata[pn+m_listnum] = listsrc.m_listdata[pn];
       listsrc.m_listdata[pn].Init();
       }

    m_listnum += listsrc.m_listnum;

    listsrc.Deallocate();
    }


void Display( FILE *fp )
	{
	int pn;

	fprintf( fp, "{\n" );
	fprintf( fp, "\t{nelems %d}\n", m_listnum );
	fprintf( fp, "\t{\n" );

	for ( pn = 0; pn < m_listnum; pn++ )
		{
		fprintf( fp, "%d ", m_listdata[pn] );
		}

	fprintf( fp, "\n" );

	fprintf( fp, "\t}\n" );
	}

};

#endif


