#include "impl/error.hpp"
#include "impl/protocol/message/encrypted.hpp"

#include "frontg8/protocol/message/encrypted.h"

#include <cstring>
#include <stdexcept>

namespace
  {
  void throw_on_null_instance(fg8_protocol_message_encrypted_const_t instance)
    {
    if(!instance)
      {
      throw std::runtime_error{"Access on NULL instance of type fg8_protocol_message_encrypted"};
      }
    }
  }

extern "C"
  {

  using fg8_encrypted_t = fg8_protocol_message_encrypted_t;
  using fg8_encrypted_const_t = fg8_protocol_message_encrypted_const_t;

  struct fg8_protocol_message_encrypted
    {
    fg8_protocol_message_encrypted(char const * const content, size_t const length ) : impl{{content, length}} {}

    fg8_protocol_message_encrypted() = default;

    fg8_protocol_message_encrypted(fg8::protocol::message::encrypted && message) : impl{std::move(message)} {}

    fg8::protocol::message::encrypted impl;
    };

  fg8_encrypted_t fg8_protocol_message_encrypted_create(char const * const content, size_t const length,
                                                        fg8_error_t * const error)
    {
    fg8_encrypted_t object{};

    catch_to_error(error, [&]{
      if(content)
        {
        object = new fg8_protocol_message_encrypted{content, length};
        }
      else
        {
        object = new fg8_protocol_message_encrypted{};
        }
      });

    return object;
    }

  fg8_encrypted_t fg8_protocol_message_encrypted_copy(fg8_encrypted_const_t const other, fg8_error_t * const error)
    {
    fg8_encrypted_t object{};

    catch_to_error(error, [&]{
      throw_on_null_instance(other);

      object = new fg8_protocol_message_encrypted{*other};
      });

    return object;
    }

  void fg8_protocol_message_encrypted_destroy(fg8_protocol_message_encrypted_t const instance)
    {
    delete instance;
    }

  fg8_encrypted_t fg8_protocol_message_encrypted_deserialize(char const * const content, size_t length,
                                                             fg8_error_t * const error)
    {
    fg8_encrypted_t object{};

    if(content)
      {
      catch_to_error(error, [&]{
        object = new fg8_protocol_message_encrypted{fg8::protocol::message::encrypted::deserialize({content, length})};
        });
      }

    return object;
    }

  char * fg8_protocol_message_encrypted_serialize(fg8_encrypted_const_t const instance, size_t * length,
                                                  fg8_error_t * const error)
    {
    char * serialized{};

    catch_to_error(error, [&]{
      throw_on_null_instance(instance);

      auto data = instance->impl.serialize();

      if(!data.empty())
        {
        serialized = static_cast<char *>(std::malloc(data.size()));
        std::memcpy(serialized, data.c_str(), data.size());

        if(length)
          {
          *length = data.size();
          }
        }
      });

    return serialized;
    }

  char const * fg8_protocol_message_encrypted_get_content(fg8_encrypted_const_t const instance, size_t * const length,
                                                          fg8_error_t * const error)
    {
    char const * content{};

    catch_to_error(error, [&]{
      throw_on_null_instance(instance);

      if(instance->impl)
        {
        auto const & data = instance->impl.content();
        content = data.c_str();

        if(length)
          {
          *length = data.size();
          }
        }
      });

    return content;
    }

  void fg8_protocol_message_encrypted_set_content(fg8_encrypted_t const instance, char const * const content,
                                                  size_t const length, fg8_error_t * const error)
    {
    catch_to_error(error, [&]{
      throw_on_null_instance(instance);

      if(!content)
        {
        instance->impl.clear();
        }
      else
        {
        instance->impl.content({content, length});
        }
      });
    }

  bool fg8_protocol_message_encrypted_is_valid(fg8_encrypted_const_t const instance)
    {
    return instance && static_cast<bool>(instance->impl);
    }

  bool fg8_protocol_message_encrypted_compare_equal(fg8_encrypted_const_t const left, fg8_encrypted_const_t const right)
    {
    return left && right && left->impl == right->impl;
    }

  }
