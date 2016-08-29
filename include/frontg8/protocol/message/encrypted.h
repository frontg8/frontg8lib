#ifndef FRONTG8LIB_PUBLIC_PROTOCOL_MESSAGE_ENCRYPTED_H
#define FRONTG8LIB_PUBLIC_PROTOCOL_MESSAGE_ENCRYPTED_H

#include "frontg8/error.h"
#include "frontg8/visibility.h"

#include <stdbool.h>
#include <stdlib.h>

/**
 * @file
 */

#ifdef __cplusplus
extern "C"
  {
#endif

  typedef struct fg8_protocol_message_encrypted * fg8_protocol_message_encrypted_t;
  typedef struct fg8_protocol_message_encrypted const * fg8_protocol_message_encrypted_const_t;

  /**
   * @author Felix Morgner
   * @since 0.1.0
   *
   * @brief Create an encrypted message
   *
   * @param content The content of new message. Might be NULL.
   * @param length The length of the data pointed to by @p content. Passing in 0 will result in an empty message.
   * @param error A pointer to an error object. Might be NULL.
   *
   * @return An encrypted message if construction succeedes. Otherwise, NULL is returned and if @p error is not NULL, it will
   * be set to a new error object.
   */
  FG8_DLL_EXPORT
  fg8_protocol_message_encrypted_t fg8_protocol_message_encrypted_create(char const * const content,
                                                                         size_t const length,
                                                                         fg8_error_t * const error);

  /**
   * @author Felix Morgner
   * @since 0.1.0
   *
   * @brief Create an encrypted message by copying an existing one
   *
   * @param other The source of the copy.
   * @param error A pointer to an error object. Might be NULL.
   *
   * @note Passing an NULL object for @p other will result in an error.
   *
   * @return An encrypted message if copy construction succeedes. Otherwise, NULL is returned and if @p error is not NULL, it will
   * be set to a new error object.
   */
  FG8_DLL_EXPORT
  fg8_protocol_message_encrypted_t fg8_protocol_message_encrypted_copy(fg8_protocol_message_encrypted_const_t other,
                                                                       fg8_error_t * const error);

  /**
   * @author Felix Morgner
   * @since 0.1.0
   *
   * @brief Cleanup and destroy an encrypted message
   *
   * @param instance An existing encrypted message. Might be NULL.
   *
   * @note You must use this function to cleanup messages you no longer need. Accessing an encrypted message object after
   * destruction might lead to undefined behaviour.
   */
  FG8_DLL_EXPORT
  void fg8_protocol_message_encrypted_destroy(fg8_protocol_message_encrypted_t const instance);

  /**
   * @author Felix Morgner
   * @since 0.1.0
   *
   * @brief Create an encrypted message from serialized data
   *
   * @param data A string pointing to serialized data. Might be NULL.
   * @param length The length of the data pointed to by @p data
   * @param error A pointer to an error object. Might be NULL.
   *
   * @note Passing in NULL for @p content will result in a default constructed encrypted message being returned.
   *
   * @return An encrypted message if deserialization succeedes. Otherwise, NULL is returned and if @p error is not NULL, it will
   * be set to a new error object.
   */
  FG8_DLL_EXPORT
  fg8_protocol_message_encrypted_t fg8_protocol_message_encrypted_deserialize(char const * const data,
                                                                              size_t length,
                                                                              fg8_error_t * const error);

  /**
   * @author Felix Morgner
   * @since 0.1.0
   *
   * @brief Serialize an encrypted message into a byte array
   *
   * @param instance The message to be serialized. Must not be NULL.
   * @param length A pointer to a variable in which the size of the returned array will be stored. Might be NULL.
   * @param error A pointer to an error object. Might be NULL.
   *
   * @return A pointer to the first byte of the serialized data. The memory is owned by the client and must be freed
   * appropriately. If serialization fails, a NULL pointer is returned and error is set accordingly if a non NULL value was
   * passed in.
   */
  FG8_DLL_EXPORT
  char * fg8_protocol_message_encrypted_serialize(fg8_protocol_message_encrypted_const_t const instance,
                                                  size_t * length,
                                                  fg8_error_t * const error);
  /**
   * @author Felix Morgner
   * @since 0.1.0
   *
   * @brief Get the content of an encrypted message
   *
   * @param instance An encrypted message. Must not be NULL.
   * @param length A pointer to a variable in which the size of the returned array will be stored. Might be NULL.
   * @param error A pointer to an error object. Might be NULL.
   *
   * @return A string containing the content data of @p instance or NULL if the encrypted message has no content (e.g is
   * default-initialized). The memory is managed by the instance and must not be freed. If @p error is not NULL and an error
   * occurs, it will be set to point to a new error object.
   */
  FG8_DLL_EXPORT
  char const * fg8_protocol_message_encrypted_get_content(fg8_protocol_message_encrypted_const_t const instance,
                                                          size_t * const length,
                                                          fg8_error_t * const error);

  /**
   * @author Felix Morgner
   * @since 0.1.0
   *
   * @brief Set the content of an encrypted message
   *
   * @param instance An encrypted message. Must not be NULL.
   * @param content The new content of the message. Passing in NULL will clear the message content.
   * @param length The length of the data pointed to by @p content.
   * @param error A pointer to an error object. Might be NULL.
   *
   * @note If an error occurs, @p instance will remain unchanged and @p error will be set accordingly if a non NULL value was
   * passed in
   */
  FG8_DLL_EXPORT
  void fg8_protocol_message_encrypted_set_content(fg8_protocol_message_encrypted_t const instance,
                                                  char const * const content,
                                                  size_t const length,
                                                  fg8_error_t * const error);

  /**
   * @author Felix Morgner
   * @since 0.1.0
   *
   * @brief Check if an encrypted message is in a valid state (e.g has content)
   *
   * @param instance An encrypted message.
   *
   * @returns true if the message is valid, false otherwise
   */
  FG8_DLL_EXPORT
  bool fg8_protocol_message_encrypted_is_valid(fg8_protocol_message_encrypted_const_t const instance);

  /**
   * @author Felix Morgner
   * @since 0.1.0
   *
   * @brief Compare two encrypted messages for equality
   *
   * @param left An encrypted message ("left-hand side")
   * @param right An encrypted message ("right-hand side")
   *
   * @note Two messages are considered equal iff they have the same content. NULL values always compare unequal.
   *
   * @returns true if the messages are equal, false otherwise
   */
  FG8_DLL_EXPORT
  bool fg8_protocol_message_encrypted_compare_equal(fg8_protocol_message_encrypted_const_t const left,
                                                    fg8_protocol_message_encrypted_const_t const right);
#ifdef __cplusplus
  }
#endif

#endif
