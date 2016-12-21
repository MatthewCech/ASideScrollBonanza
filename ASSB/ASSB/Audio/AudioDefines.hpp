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
#if defined (DEBUG) | (_DEBUG)
  #define AP_DEBUG // As in, ascii-player debug
#endif


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
#ifdef AP_DEBUG
  #define AP_DEBUG_PRINT_VAL 1
#else
  #define AP_DEBUG_PRINT_VAL 0
#endif
#define DEBUG_PRINT(x) do{ if(AP_DEBUG_PRINT_VAL) { std::cout << x << std::endl; } } while (0)
