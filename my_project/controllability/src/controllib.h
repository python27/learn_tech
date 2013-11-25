//
// MATLAB Compiler: 4.14 (R2010b)
// Date: Mon Nov 25 15:45:32 2013
// Arguments: "-B" "macro_default" "-W" "cpplib:controllib" "-T" "link:lib"
// "getDriverNodeNumber" "getDriverNode" 
//

#ifndef __controllib_h
#define __controllib_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_controllib
#define PUBLIC_controllib_C_API __global
#else
#define PUBLIC_controllib_C_API /* No import statement needed. */
#endif

#define LIB_controllib_C_API PUBLIC_controllib_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_controllib
#define PUBLIC_controllib_C_API __declspec(dllexport)
#else
#define PUBLIC_controllib_C_API __declspec(dllimport)
#endif

#define LIB_controllib_C_API PUBLIC_controllib_C_API


#else

#define LIB_controllib_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_controllib_C_API 
#define LIB_controllib_C_API /* No special import/export declaration */
#endif

extern LIB_controllib_C_API 
bool MW_CALL_CONV controllibInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_controllib_C_API 
bool MW_CALL_CONV controllibInitialize(void);

extern LIB_controllib_C_API 
void MW_CALL_CONV controllibTerminate(void);



extern LIB_controllib_C_API 
void MW_CALL_CONV controllibPrintStackTrace(void);

extern LIB_controllib_C_API 
bool MW_CALL_CONV mlxGetDriverNodeNumber(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                         *prhs[]);

extern LIB_controllib_C_API 
bool MW_CALL_CONV mlxGetDriverNode(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_controllib_C_API 
long MW_CALL_CONV controllibGetMcrID();


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_controllib
#define PUBLIC_controllib_CPP_API __declspec(dllexport)
#else
#define PUBLIC_controllib_CPP_API __declspec(dllimport)
#endif

#define LIB_controllib_CPP_API PUBLIC_controllib_CPP_API

#else

#if !defined(LIB_controllib_CPP_API)
#if defined(LIB_controllib_C_API)
#define LIB_controllib_CPP_API LIB_controllib_C_API
#else
#define LIB_controllib_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_controllib_CPP_API void MW_CALL_CONV getDriverNodeNumber(int nargout, mwArray& ND, mwArray& eigenvalue, const mwArray& A);

extern LIB_controllib_CPP_API void MW_CALL_CONV getDriverNode(int nargout, mwArray& nodes, const mwArray& A);

#endif
#endif
