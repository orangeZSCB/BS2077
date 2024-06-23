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


#ifndef _TIME_H
#define _TIME_H


#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif


class CTime
{
public:
	void GetTime();
	float operator-( CTime &start );

private:
#ifdef _WIN32
	DWORD m_time;
#else
	struct timeval m_time;
#endif
};


#endif
