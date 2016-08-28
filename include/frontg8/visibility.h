#ifndef FRONTG8LIB_PUBLIC_VISIBILITY_H
#define FRONTG8LIB_PUBLIC_VISIBILITY_H

#ifndef FG8_DLL_EXPORT
#define FG8_DLL_EXPORT __attribute__((visibility("default")))
#endif

#endif
