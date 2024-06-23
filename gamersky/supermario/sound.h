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

#ifndef _SOUND_H
#define _SOUND_H

#ifdef _WIN32
#include <dsound.h>
#else
#include "type.h"
#endif


#define NUM_SOUND_EFFECTS	5

enum EFFECT
{
	EFFECT_FIRE,
	EFFECT_EXPLODE,
	EFFECT_HIT,
	EFFECT_PICK,
	EFFECT_LIFE
};


class CSound
{
public:
	CSound();
	~CSound();

	BOOL	Create();
	void	Destroy();
	BOOL	Play( EFFECT sfx );
	void	Stop( EFFECT sfx );
	BOOL	LoadEffect( EFFECT sfx );

#ifdef _WIN32
private:
	LPDIRECTSOUND			m_pDS;
	LPDIRECTSOUNDBUFFER		m_pdsBuffer[NUM_SOUND_EFFECTS];
#endif
};



BOOL PlayMidi(char *sFileName);
BOOL PauseMidi();
BOOL ResumeMidi();
BOOL StopMidi();
BOOL ReplayMidi();


#endif
