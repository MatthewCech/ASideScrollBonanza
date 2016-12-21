#pragma once


// Windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define OS_WINDOWS
#endif

// Defines
#define MU_ABSTRACT =0

// Typedefs
#if defined(OS_WINDOWS) && defined(_MSC_EXTENSIONS)
  /*alternately unsigned __int128*/
  #define O_ID unsigned long
#else
  #define O_ID unsigned long
#endif
