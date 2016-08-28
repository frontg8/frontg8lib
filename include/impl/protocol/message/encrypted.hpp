#ifndef LIBFRONTG8_IMPL_PROTOCOL_MESSAGE_ENCRYPTED_HPP
#define LIBFRONTG8_IMPL_PROTOCOL_MESSAGE_ENCRYPTED_HPP

#include <frontg8/base.pb.h>

#include <memory>
#include <iosfwd>
#include <string>

namespace fg8
  {

  namespace protocol
    {

    namespace message
      {

      struct encrypted
        {
        /**
         * @internal
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Construct an empty encrypted message
         */
        encrypted() = default;

        /**
         * @internal
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Construct an encrypted message with the given content
         */
        explicit encrypted(std::string const & content);

        /**
         * @internal
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Serialize the encrypted message into a string
         */
        std::string serialize() const;

        /**
         * @internal
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Create an encrypted message from serialized data
         */
        static encrypted deserialize(std::string const & data);

        /**
         * @internal
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Get the content of the encrypted message
         */
        std::string const & content() const;

        /**
         * @internal
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Set the content of the encrypted message
         */
        void content(std::string const & data);

        /**
         * @internal
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Clear the conent of the encrypted message
         */
        void clear();

        /**
         * @internal
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Check if the instance is valid
         */
        explicit operator bool() const;

        /**
         * @internal
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Check if two encrypted messages are the same
         *
         * Two encrypted messages are considered to be the same if they have the same content
         */
        bool operator==(encrypted const & other) const;

        /**
         * @internal
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Write an encrypted message to an output stream
         *
         * This function write the raw serialized data to the stream. This data can be use to subsequently initialize an
         * encrypted message. This is useful for storing messages on disk or transferring them to remote systems.
         *
         */
        friend std::ostream & operator<<(std::ostream & stream, encrypted const & message);

        /**
         * @internal
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Read an encrypted message from an input stream
         *
         * This function expects the input stream to contain a serialized message. This function is useful to read messages
         * that originate from another system or were serialized previously/
         */
        friend std::istream & operator>>(std::istream & stream, encrypted & message);

        private:
          frontg8::protocol::Encrypted m_message{};
        };

      }

    }

  }

#endif
