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


#include "../input.h"
#include <vgakeyboard.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/joystick.h>
#include <stdio.h>


CInput::CInput()
{
	m_joystick = -1;
}


BOOL CInput::Create()
{
	keyboard_init();
	keyboard_translatekeys( TRANSLATE_CURSORKEYS );

	m_joystick = open( "/dev/js0", O_RDONLY );
	if( m_joystick < 0 )
		printf( "no joystick present\n" );
	else
		fcntl( m_joystick, F_SETFL, O_NONBLOCK );	

	return TRUE;
}


void CInput::Destroy()
{
	keyboard_close();
	if( m_joystick >= 0 )
		close( m_joystick );
}


BOOL CInput::GetKey( BYTE &input )
{
	input = 0;
	keyboard_update();

	if( keyboard_keypressed(SCANCODE_CURSORUP) )
		input |= KEY_UP;
	else if( keyboard_keypressed(SCANCODE_CURSORDOWN) )
		input |= KEY_DOWN;
	if( keyboard_keypressed(SCANCODE_CURSORLEFT) )
		input |= KEY_LEFT;
	else if( keyboard_keypressed(SCANCODE_CURSORRIGHT) )
		input |= KEY_RIGHT;
	if( keyboard_keypressed(SCANCODE_LEFTSHIFT) )
		input |= KEY_ACC;
	if( keyboard_keypressed(SCANCODE_LEFTCONTROL) )
		input |= KEY_JUMP;

	// read joystick data
	if( m_joystick >= 0 ) 
	{
		struct js_event js;
		static BYTE joyinput = 0;

		if( read( m_joystick, &js, sizeof(js) ) != sizeof(js) )
		{
			input |= joyinput;
			return TRUE;
		}
			
		if( js.value )
		{
			switch( js.type & ~JS_EVENT_INIT )
			{
			case JS_EVENT_BUTTON:
				if( js.number == 0 )
					joyinput |= KEY_ACC;
				else if( js.number == 1 )
					joyinput |= KEY_JUMP;
				break;
			
			case JS_EVENT_AXIS:
				if( js.number == 0 )
				{
					if( js.value < 0 )
						joyinput |= KEY_LEFT;
					else
						joyinput |= KEY_RIGHT;
				}
				else if( js.number == 1 )
				{
					if( js.value < 0 )
						joyinput |= KEY_UP;
					else 
						joyinput |= KEY_DOWN;
				}
				break;
			}
		}
		else
		{
			switch( js.type & ~JS_EVENT_INIT )
			{
			case JS_EVENT_BUTTON:
				if( js.number == 0 )
					joyinput &= ~KEY_ACC;
				else if( js.number == 1 )
					joyinput &= ~KEY_JUMP;
				break;
			
			case JS_EVENT_AXIS:
				if( js.number == 0 )
				{
					joyinput &= ~KEY_LEFT;
					joyinput &= ~KEY_RIGHT;
				}
				else if( js.number == 1 )
				{
					joyinput &= ~KEY_UP;
					joyinput &= ~KEY_DOWN;
				}
				break;
			}
		}
		input |= joyinput;
	}

	return TRUE;
}

