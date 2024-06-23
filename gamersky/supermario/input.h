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

#ifndef _INPUT_H
#define _INPUT_H

#ifdef _WIN32
#include <dinput.h>
#else
#include "type.h"
#endif

#define KEY_RIGHT		0x01
#define KEY_UP			0x02
#define KEY_DOWN		0x04
#define KEY_LEFT		0x08
#define KEY_ACC			0x10
#define KEY_JUMP		0x20

class CInput
{
#ifdef _WIN32
friend BOOL CALLBACK EnumJoystickCB( LPCDIDEVICEINSTANCE pdinst, LPVOID pvRef );
#endif

public:
	CInput();
	~CInput(){ Destroy(); }

	BOOL	Create();
	void	Destroy();
	void	SetAcquire( BOOL active );
	BOOL	GetKey( BYTE &input );

#ifdef _WIN32
private:
	LPDIRECTINPUT			m_pDI;
	LPDIRECTINPUTDEVICE		m_pdevKeyboard;
	LPDIRECTINPUTDEVICE2	m_pdevJoystick;
#else
	int m_joystick;		// handle
#endif
};


#endif
