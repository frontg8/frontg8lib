#ifndef FRONTG8LIB_PUBLIC_ERROR_H
#define FRONTG8LIB_PUBLIC_ERROR_H

#include "frontg8/visibility.h"

/**
 * @file
 */

#ifdef __cplusplus
extern "C"
  {
#endif

  /**
   * @brief The opaque error pointer type
   *
   * This type carries generic error information. The library uses this type throughout the whole codebase to communicate error
   * conditions back to the your code. There is no way to construct objects of this type except indirectly by forcefully causing
   * a function to reach an error condition. See #fg8_error_message and #fg8_error_destroy for information on how to make use of
   * this type.
   *
   * @author Felix Morgner
   * @since 0.1.0
   */
  typedef struct fg8_error * fg8_error_t;

  /**
   * @brief Retrieve the error message contained in an #fg8_error_t object.
   *
   * Being an opaque type, it is not possible to directly read the content of the error object. You can use this function to
   * extract the error message contained in an #fg8_error_t object. Calling this function on a ``NULL`` object will return a
   * ``NULL`` pointer. The string (``char const *``) returned by the function is a standard ``NULL`` terminated C string. The
   * memory of the string is **owned by the error object**.
   *
   * @par Example
   * @rst
   * .. code-block:: c
   *    :linenos:
   *
   *    #include <frontg8/error.h>
   *    #include <stdio.h>
   *    // other includes ...
   *
   *    int main()
   *      {
   *      fg8_error_t error;
   *
   *      // Do something that might produce an error ...
   *
   *      if(error)
   *        {
   *        printf("ERROR: %s", fg8_error_message(error));
   *        }
   *
   *      // Do the rest ...
   *      }
   * @endrst
   *
   * @param[in] error The error object whose message should be retrieved. Might be ``NULL``.
   *
   * @return A pointer to the message contained in the error or ``NULL`` if there was no error. The memory of the message is
   * managed by the error object and the user code **MUST NEVER** call ``free()`` or equivalent on it.
   *
   * @author Felix Morgner
   * @since 0.1.0
   */
  FG8_DLL_EXPORT
  char const * fg8_error_message( fg8_error_t const error);

  /**
   * @brief Destroy an error object
   *
   * A lot of the libraries functions take a pointer to #fg8_error_t (see #fg8_protocol_message_encrypted_create for an example)
   * in order to be able to communicate error conditions back to the calling code. As long as you reuse the same error object,
   * you don't need to worry about memory management, the library will take care of that for you. There are some situations,
   * where **YOU need to take care of the error object**. For example, if you do not want to reuse the same error object or at
   * the end of the relevant scope, **you must use #fg8_error_destroy** to cleanly destroy the error object and release its
   * memory. Note that you **MUST NEVER** call ``free()`` or equivalent on an error object.
   *
   * @par Example
   * @rst
   * .. code-block:: c
   *    :linenos:
   *
   *    #include <frontg8/error.h>
   *    #include <stdio.h>
   *    // other includes ...
   *
   *    int main()
   *      {
   *      fg8_error_t error;
   *
   *      // Do something that stores an error in error ...
   *
   *      fg8_error_destroy(error);
   *      }
   * @endrst
   *
   * @param[in] error The error object to be destroyed
   *
   * @author Felix Morgner
   * @since 0.1.0
   *
   * @warning Calling destroy multiple times on the same error object will result in undefined behaviour
   * @warning All pointers to the message formerly contained in the error object may point to invalid memory after destruction.
   */
  FG8_DLL_EXPORT
  void fg8_error_destroy(fg8_error_t const error);

#ifdef __cplusplus
  }
#endif

#endif
