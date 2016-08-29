#ifndef FRONTG8LIB_PUBLIC_ERROR_HPP
#define FRONTG8LIB_PUBLIC_ERROR_HPP

#include "frontg8/error.h"

#include <stdexcept>
#include <string>
#include <utility>

namespace fg8
  {

  struct error
    {
    ~error() noexcept(false)
      {
      if(m_error)
        {
        auto message = std::string(fg8_error_message(m_error));
        fg8_error_destroy(m_error);
        throw std::runtime_error{std::move(message)};
        }
      }

    operator fg8_error_t*()
      {
      return &m_error;
      }

    private:
      fg8_error_t m_error{};
    };

  }

#endif
