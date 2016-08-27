#ifndef LIBFRONTG8_PROTOCOL_MESSAGE_ENCRYPTED
#define LIBFRONTG8_PROTOCOL_MESSAGE_ENCRYPTED

#include <memory>
#include <iosfwd>
#include <string>

#ifndef LIBFRONTG8_DLL_EXPORT
#define LIBFRONTG8_DLL_EXPORT __attribute__ ((visibility ("default")))
#endif

namespace fg8
  {

  namespace protocol
    {

    namespace message
      {

      struct encrypted
        {
        LIBFRONTG8_DLL_EXPORT
        ~encrypted();

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Construct an empty encrypted message
         */
        LIBFRONTG8_DLL_EXPORT
        explicit encrypted();

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Construct an encrypted message with the given content
         */
        LIBFRONTG8_DLL_EXPORT
        explicit encrypted(std::string const & data);

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Construct an encrypted message as a copy of an existing one
         */
        LIBFRONTG8_DLL_EXPORT
        encrypted(encrypted const & other);

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Create an encrypted message from serialized data
         */
        LIBFRONTG8_DLL_EXPORT
        static encrypted from_data(std::string const & data);

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Get the content of the encrypted message
         */
        LIBFRONTG8_DLL_EXPORT
        std::string const & content() const;

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Set the content of the encrypted message
         */
        LIBFRONTG8_DLL_EXPORT
        void content(std::string const & data);

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Check if the instance is valid
         */
        LIBFRONTG8_DLL_EXPORT
        explicit operator bool() const;

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Check if two encrypted messages are the same
         *
         * Two encrypted messages are considered to be the same if they have the same content
         */
        LIBFRONTG8_DLL_EXPORT
        bool operator==(encrypted const & other) const;

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Write an encrypted message to an output stream
         *
         * This function write the raw serialized data to the stream. This data can be use to subsequently initialize an
         * encrypted message. This is useful for storing messages on disk or transferring them to remote systems.
         *
         */
        LIBFRONTG8_DLL_EXPORT
        friend std::ostream & operator<<(std::ostream & stream, encrypted const & message);

        /**
         * @author Felix Morgner
         * @since 0.1.0
         *
         * @brief Read an encrypted message from an input stream
         *
         * This function expects the input stream to contain a serialized message. This function is useful to read messages
         * that originate from another system or were serialized previously/
         */
        LIBFRONTG8_DLL_EXPORT
        friend std::istream & operator>>(std::istream & stream, encrypted & message);

        private:
          std::unique_ptr<struct encrypted_impl> m_impl;
        };

      }

    }

  }

#endif
