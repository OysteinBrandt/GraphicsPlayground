#pragma once

#ifndef _ENGINE_DLLHELPER_H_
#define _ENGINE_DLLHELPER_H_

#if defined _WIN32 || defined __CYGWIN__
  #define ENGINE_HELPER_DLL_IMPORT __declspec(dllimport)
  #define ENGINE_HELPER_DLL_EXPORT __declspec(dllexport)
  #define ENGINE_HELPER_DLL_LOCAL
  #define ENGINE_HELPER_DLL_DEPRECATED __declspec(deprecated("This function is deprecated."))
#elif __GNUC__ >= 4
  #define ENGINE_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
  #define ENGINE_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
  #define ENGINE_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #define ENGINE_HELPER_DLL_DEPRECATED __attribute__ ((deprecated ("This function is deprecated.")))
#else
  #define ENGINE_HELPER_DLL_IMPORT
  #define ENGINE_HELPER_DLL_EXPORT
  #define ENGINE_HELPER_DLL_LOCAL
  #define ENGINE_HELPER_DLL_DEPRECATED
  #error Unknown dynamic link import/export semantics.
#endif

#ifdef ENGINE_DLL													      // Defined if compiled as a DLL
  #ifdef ENGINE_DLL_EXPORT								      // Defined if building the DLL (instead of using it)
    #define ENGINE_API ENGINE_HELPER_DLL_EXPORT
  #else
    #define ENGINE_API ENGINE_HELPER_DLL_IMPORT
  #endif
  #define ENGINE_LOCAL ENGINE_HELPER_DLL_LOCAL
  #define ENGINE_DEPRECATED ENGINE_HELPER_DLL_DEPRECATED
#else																			      // Static lib
  #define ENGINE_API
  #define ENGINE_LOCAL
#endif

#endif	//_ENGINE_DLLHELPER_H_