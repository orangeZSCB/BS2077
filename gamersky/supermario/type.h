#ifndef _TYPE_H
#define _TYPE_H

typedef int				BOOL;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;
typedef long			LONG;
typedef unsigned char	BYTE;

#define FALSE			0
#define TRUE			1

struct RECT {
	int		left;
	int		top;
	int		right;
	int		bottom;
};


struct PALETTEENTRY
{
	BYTE peRed;
	BYTE peGreen;
	BYTE peBlue;
	BYTE peFlags;
};


#endif
