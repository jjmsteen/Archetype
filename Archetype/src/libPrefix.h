// LibPrefix.h
// 
// To be included in all header files, conditionally 
// #defines a dll prefix to functions that require it
// on specific platforms

#ifdef WIN32

#define DLLEXPORT __declspec(dllexport)

#else

#define DLLEXPORT

#endif