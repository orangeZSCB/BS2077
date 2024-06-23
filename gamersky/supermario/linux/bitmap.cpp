//-----------------------------------------------------------------------------
//
// Copyright (C) July 24, 2000 by Zhang Yong
// Email: z-meng@yeah.net
// This source is available for distribution and/or modification
// only under the terms of the GPL license.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the GPL.txt for more details.
//
//-----------------------------------------------------------------------------


#include <vgagl.h>
#include <vga.h>
#include <stdio.h>
#include "../bitmap.h"


#define BI_RGB        0L

#pragma pack(2)
typedef struct { // bmfh 
    WORD    bfType; 
    DWORD   bfSize; 
    WORD    bfReserved1; 
    WORD    bfReserved2; 
    DWORD   bfOffBits; 
} BITMAPFILEHEADER; 
#pragma pack()

typedef struct { // bmih 
    DWORD  biSize; 
    LONG   biWidth; 
    LONG   biHeight; 
    WORD   biPlanes; 
    WORD   biBitCount; 
    DWORD  biCompression; 
    DWORD  biSizeImage; 
    LONG   biXPelsPerMeter; 
    LONG   biYPelsPerMeter; 
    DWORD  biClrUsed; 
    DWORD  biClrImportant; 
} BITMAPINFOHEADER; 
 
typedef struct { // rgbq 
    BYTE    rgbBlue; 
    BYTE    rgbGreen; 
    BYTE    rgbRed; 
    BYTE    rgbReserved; 
} RGBQUAD; 



CBitmap::CBitmap()
{
	m_width = m_height = 0;
	m_bits = NULL;
}


void CBitmap::Release()
{
	if( m_bits )
		delete []m_bits;
	
	m_width = m_height = 0;
	m_bits = NULL;
}


BOOL CBitmap::Load( char *filename )
{
	FILE *fp = fopen( filename, "rb" );
	if( !fp )
	{
		printf( "Can not open file %s\n", filename );
		return FALSE;
	}
	printf( "Loading %s...\n", filename );
	
	BITMAPFILEHEADER	bf;
	BITMAPINFOHEADER	bi;
	RGBQUAD				rgb[256];

	fread( &bf, sizeof(bf), 1, fp );
	if( bf.bfType != 0x4d42 )
	{
		printf( "Not a bitmap file.\n" );
		fclose( fp );
		return FALSE;
	}
	fread( &bi, sizeof(bi), 1, fp );
	m_width = bi.biWidth;
	m_height = bi.biHeight;
	
	if( bi.biBitCount != 8 || bi.biCompression != BI_RGB )
	{
		printf( "Not an uncompressed 256-color bitmap.\n" );
		return FALSE;
	}

	fread( rgb, sizeof(RGBQUAD), 256, fp );
	
	int size = bi.biWidth * bi.biHeight;
	m_bits = new BYTE[size];
	int offset = size;
	for( int i = 0; i < bi.biHeight; i ++ )
	{
		offset -= bi.biWidth;
		fread( m_bits + offset, bi.biWidth, 1, fp );
	}

	// since gl_putbox only support color 0 mask,
	// we must translate manully
	for( int i = 0; i < size; i ++ )
	{
		if( m_bits[i] == 0x01 )
			m_bits[i] = 0x00;
		else if( m_bits[i] == 0x00 )
			m_bits[i] = 0x02;
	}
	fclose( fp );
}


void CBitmap::Draw( int x, int y, RECT &rc )
{
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	
	BYTE *buf = new BYTE[ width * height ];
	BYTE *dest = buf;
	BYTE *src = m_bits + rc.top * m_width + rc.left;
	for( int i = 0; i < height; i ++ )
	{
		memcpy( dest, src, width );
		src += m_width;
		dest += width;
	}
	
	gl_putboxmask( x, y, width, height, buf );
	
	delete []buf;
}
