#ifndef FRONTG8LIB_IMPL_ERROR_HPP
#define FRONTG8LIB_IMPL_ERROR_HPP

#include <stdexcept>
#include <string>

extern "C"
  {

  struct fg8_error
    {
    std::string message{};
    };

  }

template<typename Function>
auto catch_to_error(fg8_error * * const error, Function && function)
  {
  try
    {
    function();
    if(error)
      {
      delete *error;
      *error = nullptr;
      }
    }
  catch(std::exception const & exception)
    {
    if(error)
      {
      delete *error;
      *error = new fg8_error{exception.what()};
      }

    return false;
    }
  catch(...)
    {
    if(error)
      {
      delete *error;
      *error = new fg8_error{"Unknown error"};
      }

    return false;
    }

  return true;
  }

#endif
