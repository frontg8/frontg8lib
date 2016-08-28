#include "impl/protocol/message/encrypted.hpp"

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

      encrypted::encrypted(std::string const & content)
        {
        m_message.set_encrypted_data(content);
        }

      encrypted encrypted::from_data(std::string const & data)
        {
        auto message = encrypted{};
        message.m_message.ParseFromString(data);
        return message;
        }

      std::string const & encrypted::content() const
        {
        return m_message.encrypted_data();
        }

      void encrypted::content(std::string const & data)
        {
        return m_message.set_encrypted_data(data);
        }

      void encrypted::clear()
        {
        m_message.Clear();
        }

      encrypted::operator bool() const
        {
        return m_message.IsInitialized();
        }

      bool encrypted::operator==(encrypted const & other) const
        {
        return content() == other.content();
        }

      std::ostream & operator<<(std::ostream & stream, encrypted const & message)
        {
        message.m_message.SerializeToOstream(&stream);
        return stream;
        }

      std::istream & operator>>(std::istream & stream, encrypted & message)
        {
        message.m_message.Clear();
        google::protobuf::io::IstreamInputStream zeroCopyStream{&stream};
        message.m_message.ParseFromZeroCopyStream(&zeroCopyStream);
        return stream;
        }

      }

    }

  }
