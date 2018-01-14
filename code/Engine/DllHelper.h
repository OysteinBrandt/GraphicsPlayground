#pragma once

#ifndef _ENGINE_DLLHELPER_H_
#define _ENGINE_DLLHELPER_H_

#if defined _WIN32 || defined __CYGWIN__
#define OBR_HELPER_DLL_IMPORT __declspec(dllimport)
#define OBR_HELPER_DLL_EXPORT __declspec(dllexport)
#define OBR_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4
#define OBR_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#define OBR_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#define OBR_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define OBR_HELPER_DLL_IMPORT
#define OBR_HELPER_DLL_EXPORT
#define OBR_HELPER_DLL_LOCAL
#pragma warning Unknown dynamic link import/export semantics.
#endif
#endif

#ifdef OBR_DLL														// Defined if compiled as a DLL
#ifdef OBR_DLL_EXPORTS									// Defined if building the DLL (instead of using it)
#define OBR_API OBR_HELPER_DLL_EXPORT
#else
#define OBR_API OBR_HELPER_DLL_IMPORT
#endif
#define OBR_LOCAL OBR_HELPER_DLL_LOCAL
#else																			// Static lib
#define OBR_API
#define OBR_LOCAL
#endif

#endif	//_ENGINE_DLLHELPER_H_