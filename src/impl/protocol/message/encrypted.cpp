#include "impl/protocol/message/encrypted.hpp"

#include <frontg8/base.pb.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <iostream>
#include <stdexcept>

using namespace frontg8::protocol;

namespace fg8
  {

  namespace protocol
    {

    namespace message
      {

      struct encrypted_impl
        {
        encrypted_impl() = default;

        encrypted_impl(std::string const & data)
          {
          m_message.set_encrypted_data(data);
          }

        friend std::ostream & operator<<(std::ostream & stream, encrypted_impl const & message)
          {
          message.m_message.SerializeToOstream(&stream);
          return stream;
          }

        friend std::istream & operator>>(std::istream & stream, encrypted_impl & message)
          {
          message.m_message.Clear();
          google::protobuf::io::IstreamInputStream zeroCopyStream{&stream};
          message.m_message.ParseFromZeroCopyStream(&zeroCopyStream);
          return stream;
          }

        private:
          Encrypted m_message{};

          friend encrypted;
        };

      encrypted::~encrypted() = default;

      encrypted::encrypted() : m_impl{std::make_unique<encrypted_impl>()} { }

      encrypted::encrypted(std::string const & data) : m_impl{std::make_unique<encrypted_impl>(data)} { }

      encrypted::encrypted(encrypted const & other) : m_impl{std::make_unique<encrypted_impl>(*other.m_impl)} { }

      encrypted encrypted::from_data(std::string const & data)
        {
        auto message = encrypted{};
        message.m_impl->m_message.ParseFromString(data);
        return message;
        }

      std::string const & encrypted::content() const
        {
        return m_impl->m_message.encrypted_data();
        }

      void encrypted::content(std::string const & data)
        {
        return m_impl->m_message.set_encrypted_data(data);
        }

      void encrypted::clear()
        {
        m_impl->m_message.Clear();
        }

      encrypted::operator bool() const
        {
        return m_impl->m_message.IsInitialized();
        }

      bool encrypted::operator==(encrypted const & other) const
        {
        return content() == other.content();
        }

      std::ostream & operator<<(std::ostream & stream, encrypted const & message)
        {
        return stream << *message.m_impl;
        }

      std::istream & operator>>(std::istream & stream, encrypted & message)
        {
        return stream >> *message.m_impl;
        }

      }

    }

  }
