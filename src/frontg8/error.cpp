#include "impl/error.hpp"
#include "frontg8/error.h"

extern "C"
  {

  FG8_DLL_EXPORT char const * fg8_error_message(fg8_error_t const error)
    {
    if(error)
      {
      return error->message.c_str();
      }

    return NULL;
    }

  FG8_DLL_EXPORT void fg8_error_destroy(fg8_error_t const error)
    {
    delete error;
    }

  }
