#ifndef FRONTG8LIB_PUBLIC_PROTOCOL_MESSAGE_ENCRYPTED_HPP
#define FRONTG8LIB_PUBLIC_PROTOCOL_MESSAGE_ENCRYPTED_HPP

#include "frontg8/error.hpp"
#include "frontg8/protocol/message/encrypted.h"

#include <string>
#include <utility>

namespace fg8
  {

  namespace protocol
    {

    namespace message
      {

      struct encrypted
        {
        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Construct an empty encrypted message
         *
         * @exception std::runtime_error If construction of the underlying object fails
         */
        encrypted() :
          m_encrypted{fg8_protocol_message_encrypted_create(nullptr, 0, fg8::error{})}
          {

          }

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Construct an encrypted message with the supplied content
         *
         * @param content The content of the new message
         *
         * @exception std::runtime_error If construction of the underlying object fails
         */
        explicit encrypted(std::string const & content) :
          m_encrypted{fg8_protocol_message_encrypted_create(content.c_str(), content.size(), fg8::error{})}
          {

          }

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Copy-construct an encrypted message from an existing one
         *
         * @param other An instance of encrypted from which to copy
         *
         * @exception std::runtime_error If construction of the underlying object fails
         */
        encrypted(encrypted const & other) :
          m_encrypted{fg8_protocol_message_encrypted_copy(other.m_encrypted, fg8::error{})}
          {

          }

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Move-construct an encrypted message from an existing one
         *
         * @param other An instance of encrypted from which to move
         */
        encrypted(encrypted && other) noexcept
          {
          std::swap(m_encrypted, other.m_encrypted);
          }

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Desctruct an encrypted message
         *
         * @note You should pretty much never call this function. Of you are unsure, go read about C++ destructors.
         */
        ~encrypted()
          {
          fg8_protocol_message_encrypted_destroy(m_encrypted);
          }

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Serializes the encrypted message into a string.
         *
         * @note Serializing an empty message WILL produce output because an "empty" message is considered to be a message with
         * the empty string which can be meaningful. In contrast, a message that was never assigned content or that has been
         * cleared will cause #serialize to return "nothing" (e.g. the empty string).
         *
         * @see clear
         *
         * @return A string containing the serialized data
         *
         * @exception std::runtime_error If serialization of the underlying object fails
         */
        std::string serialize() const
          {
          std::size_t length{};
          auto const data = fg8_protocol_message_encrypted_serialize(m_encrypted, &length, error{});
          return {data, length};
          }

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Create an encrypted message from serialized data
         *
         * @param data A string containing the serialized data
         *
         * @exception std::runtime_error If deserialization of the data fails
         */
        static encrypted deserialize(std::string const & data)
          {
          auto message = encrypted{};
          message.m_encrypted = fg8_protocol_message_encrypted_deserialize(data.c_str(), data.size(), error{});
          return message;
          }

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Get the content of the message
         *
         * @return A string containing the content of the encrypted message
         *
         * @exception std::runtime_error If content acquisition from the underlying object fails
         */
        std::string content() const
          {
          std::size_t length{};
          auto const content = fg8_protocol_message_encrypted_get_content(m_encrypted, &length, error{});
          return {content, length};
          }

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Set the content of the encypted message
         *
         * @param content The new content of the message
         *
         * @exception std::runtime_error If setting the content of the underlying object fails
         */
        void content(std::string const & content)
          {
          fg8_protocol_message_encrypted_set_content(m_encrypted, content.data(), content.size(), error{});
          }

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Clear the message
         *
         * @note In contrast to setting the content to be the empty string, clearing the message will result in the message not
         * being considered 'valid' e.g. a call to #serialize will result in an empty string.
         */
        void clear()
          {
          fg8_protocol_message_encrypted_set_content(m_encrypted, nullptr, 0, error{});
          }

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Check if the encrypted message is valid
         *
         * @see clear
         * @see serialize
         *
         * @return true if the encrypted message is valid, false otherwise
         */
        operator bool() const noexcept
          {
          return fg8_protocol_message_encrypted_is_valid(m_encrypted);
          }

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Check if this encrypted message is equal to the other one
         *
         * @note Two encrypted messages are considered to be equal if the contain the same data.
         *
         * @return true iff both messages are equal
         */
        bool operator==(encrypted const & other) const noexcept
          {
          return this == &other || fg8_protocol_message_encrypted_compare_equal(m_encrypted, other.m_encrypted);
          }

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Check if this encrypted message is different the other one
         *
         * @see operator==
         *
         * @return true iff both messages are not equal
         */
        bool operator!=(encrypted const & other) const noexcept
          {
          return !(*this == other);
          }

        private:
          fg8_protocol_message_encrypted_t m_encrypted{};
        };

      }

    }

  }

#endif
