#pragma once

#if defined(_WIN32) || defined(_WIN64)
#ifdef BOOSTBEAST_EXPORTS
#define BOOSTBEAST_API __declspec(dllexport)  // Export when building the DLL
#else
#define BOOSTBEAST_API __declspec(dllimport)  // Import when using the DLL
#endif
#else
#define BOOSTBEAST_API __attribute__((visibility("default")))  // For Linux/macOS
#endif