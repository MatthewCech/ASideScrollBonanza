/*!***************************************************************************
@file    Defines.hpp
@author  Reverie Wisp
@par     Email: contact@rw0.pw
@date    11/19/2016

@brief
Lifted from my ASCIIPlayer project.

FMOD Sound System, copyright © Firelight Technologies Pty, Ltd., 1994-2015.
*****************************************************************************/
#pragma once
#pragma warning(push, 0)
#include "FMOD/fmod.hpp"
#pragma warning(pop)
#include <iostream>



  //////////////////////////////
 // OS and Compiler-Specific //
//////////////////////////////
#pragma warning(push, 0)
#if defined (DEBUG) | (_DEBUG)
  #define AUDIO_DEBUG
#endif
#pragma warning(pop)

  //////////////////////////
 // Types and "Keywords" //
//////////////////////////
// Using
using ChannelHandle = FMOD::Channel*;     // Channel handle for FMOD
using AudioHandle   = FMOD::Sound;        // Sound object handle for FMOD
using Channelgroup  = FMOD::ChannelGroup; // Channel object handle for FMOD
using APUnique      = unsigned long long;

// Defines
#define DJ_ABSTRACT =0
#define UNUSED(x) (void)(x)

  ///////////
 // Enums //
///////////
enum AudioDataStyle
{
  aSpectrum = 0,
  aWaveform = 1,
  
  aNO_STYLE
};

  /////////////////////////////////
 // Fun witchcr-- I mean macros //
/////////////////////////////////
// Debug Printing
#ifdef AUDIO_DEBUG
  #define DEBUG_PRINT(x) do{ std::cout << x << std::endl; } while (0)
#else
  #define DEBUG_PRINT(x) 
#endif

