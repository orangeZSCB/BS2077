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


#include "../mytime.h"


void CTime::GetTime()
{
	gettimeofday( &m_time, 0 );
}


float CTime::operator-( CTime &start )
{
	if( m_time.tv_usec < start.m_time.tv_usec )
	{
		m_time.tv_usec += 1000000;
		m_time.tv_sec --;
	}
	long sec = m_time.tv_sec - start.m_time.tv_sec;
	long usec = m_time.tv_usec - start.m_time.tv_usec;
	return (sec + usec/1000000.0f);
}
