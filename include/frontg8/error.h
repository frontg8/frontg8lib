#ifndef FRONTG8LIB_PUBLIC_ERROR_H
#define FRONTG8LIB_PUBLIC_ERROR_H

#include "frontg8/visibility.h"

#ifdef __cplusplus
extern "C"
  {
#endif

  typedef struct fg8_error * fg8_error_t;

  FG8_DLL_EXPORT char const * fg8_error_message(fg8_error_t const error);

  FG8_DLL_EXPORT void fg8_error_destroy(fg8_error_t const error);

#ifdef __cplusplus
  }
#endif

#endif
