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

#include "..\sound.h"
#include "wavread.h"
#include <stdio.h>

extern HWND g_hWnd;


// The fllowing midi code is taken from MSDN's sample code(Rockem3d)

//------------------------------------------------------------------
// 
// Function	: PlayMidi()
//
// Purpose	: Plays a midi file
//
//------------------------------------------------------------------

BOOL PlayMidi(char *sFileName)
{
    char buf[256];

    sprintf(buf, "open %s type sequencer alias MUSIC", sFileName);
    
    if (mciSendString("close all", NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }

    if (mciSendString(buf, NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }

    if (mciSendString("play MUSIC from 0", NULL, 0, g_hWnd) != 0)
    {
	return(FALSE);
    }
    
    // Yahoo!
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function	: PauseMidi()
//
// Purpose	: Pauses midi file
//
//------------------------------------------------------------------

BOOL PauseMidi()
{
    // Pause if we're not already paused...
    if (mciSendString("stop MUSIC", NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }

    
    // Yahoo!
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function	: ResumeMidi()
//
// Purpose	: Resumes playing of a midi file
//
//------------------------------------------------------------------

BOOL ResumeMidi()
{	
    // Resume midi
    if (mciSendString("play MUSIC notify", NULL, 0, g_hWnd) != 0)
    {
	return(FALSE);
    }

    // Yahoo!
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function	: StopMidi
//
// Purpose	: Stops a midi file playing
//
//------------------------------------------------------------------

BOOL StopMidi()
{
    if (mciSendString("close all", NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }	

    // Yahoo!
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function	: ReplayMidi()
//
// Purpose	: Replays a midi file
//
//------------------------------------------------------------------

BOOL ReplayMidi()
{
    // Replay midi
    if (mciSendString("play MUSIC from 0 notify", NULL, 0, g_hWnd) != 0)
    {
	return(FALSE);
    }

    // Yahoo!
    return TRUE;
}




#define SAFE_RELEASE(x)		if(x){ x->Release(); x = NULL; }

static char szSoundEffects[NUM_SOUND_EFFECTS][40] =
{
	"Gunfire.wav",
	"Bang.wav",
	"Hit.wav",
	"Peow.wav",
	"Fanfare.wav",
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSound::CSound()
{
	m_pDS = NULL;
	for( int i = 0; i < NUM_SOUND_EFFECTS; i ++ )
		m_pdsBuffer[i] = NULL;
}

CSound::~CSound()
{
	Destroy();
}


BOOL CSound::Create()
{
	// Create DirectSound
	if( FAILED(DirectSoundCreate( NULL, &m_pDS, NULL )) )
		return FALSE;

	m_pDS->SetCooperativeLevel( g_hWnd, DSSCL_NORMAL );

	// Create Sound buffer
	CWaveSoundRead waveSound;
	char filename[MAX_PATH];

	for( int i = 0; i < NUM_SOUND_EFFECTS; i ++ )
	{
		lstrcpy( filename, "sound\\" );
		lstrcat( filename, szSoundEffects[i] );
		if( FAILED(waveSound.Open( filename )) )
			continue;
		
		waveSound.Reset();
		
		DSBUFFERDESC	dsbd;
		ZeroMemory( &dsbd, sizeof(dsbd) );
		dsbd.dwSize = sizeof(dsbd);
		dsbd.dwFlags = DSBCAPS_STATIC;
		dsbd.dwBufferBytes = waveSound.m_ckIn.cksize;
		dsbd.lpwfxFormat = waveSound.m_pwfx;

		if( FAILED(m_pDS->CreateSoundBuffer(&dsbd, &m_pdsBuffer[i], NULL)) )
		{
			waveSound.Close();
			Destroy();
			return FALSE;
		}

		LPVOID lpvAudio;
		DWORD  dwBytes;
		m_pdsBuffer[i]->Lock(
				0,
				0,
				&lpvAudio,
				&dwBytes,
				NULL,
				NULL,
				DSBLOCK_ENTIREBUFFER);
		
		UINT cbBytesRead;
		waveSound.Read( dwBytes, (LPBYTE)lpvAudio, &cbBytesRead );
	
		m_pdsBuffer[i]->Unlock( lpvAudio, dwBytes, NULL, 0 );

		waveSound.Close();
	}

	return TRUE;
}


BOOL CSound::LoadEffect( EFFECT sfx )
{
	int idx = (int)sfx;

	CWaveSoundRead waveSound;
	char filename[MAX_PATH] = "sound\\";
	
	lstrcpy( filename, szSoundEffects[idx] );
	if( FAILED(waveSound.Open( filename )) )
		return FALSE;

	waveSound.Reset();
	
	LPVOID lpvAudio;
	DWORD  dwBytes;
	m_pdsBuffer[idx]->Lock(
			0,
			0,
			&lpvAudio,
			&dwBytes,
			NULL,
			NULL,
			DSBLOCK_ENTIREBUFFER);
		
	UINT cbBytesRead;
	waveSound.Read( dwBytes, (LPBYTE)lpvAudio, &cbBytesRead );
	
	m_pdsBuffer[idx]->Unlock( lpvAudio, dwBytes, NULL, 0 );

	waveSound.Close();

	return TRUE;
}


BOOL CSound::Play( EFFECT sfx )
{
	HRESULT hr;
	int idx = (int)sfx;
	if( !m_pdsBuffer[idx] )
		return FALSE;

	m_pdsBuffer[idx]->SetCurrentPosition(0);
	hr = m_pdsBuffer[idx]->Play( 0, 0, 0 );
	if( hr == DSERR_BUFFERLOST )
	{
		hr = m_pdsBuffer[idx]->Restore();
		LoadEffect( sfx );
	}

	if( FAILED(hr) )
		return FALSE;
	return TRUE;
}


void CSound::Stop( EFFECT sfx )
{
	int idx = (int)sfx;
	if( !m_pdsBuffer[idx] )
		return;

	m_pdsBuffer[idx]->Stop();
}


void CSound::Destroy()
{
	for( int i = 0; i < NUM_SOUND_EFFECTS; i ++ )
		SAFE_RELEASE( m_pdsBuffer[i] );
	SAFE_RELEASE( m_pDS );
}