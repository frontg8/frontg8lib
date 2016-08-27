#include <google/protobuf/stubs/common.h>

/**
 * @internal
 * @file lifetime.cpp
 * @author Felix Morgner
 * @since 0.1.0
 *
 * @brief Manage library lifetime
 *
 * Protobuf initializes its own internal state by itself. In order to be good citizens when we get loaded/unloaded at runtime,
 * we need to cleanly shutdown this internal state. Also, protobuf logs to stderr by default. We don't want to polute the users
 * output with possible error, thus we register a "do nothing" logger.
 */

namespace fg8
  {

  namespace
    {
    auto log(google::protobuf::LogLevel, const char *, int, const std::string &){}

    static const struct lifetime_processor
      {
      lifetime_processor()
        {
        google::protobuf::SetLogHandler(log);
        }

      ~lifetime_processor()
        {
        google::protobuf::ShutdownProtobufLibrary();
        }
      } kLifetimeProcessor{};
    }

  }
