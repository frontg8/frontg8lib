#include "frontg8/error.hpp"
#include "frontg8/protocol/message/encrypted.h"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/xml_listener.h>

void test_empty_does_not_throw()
  {
  fg8::error{};
  }

void test_does_throw_on_error()
  {
  ASSERT_THROWS(fg8_protocol_message_encrypted_get_content(nullptr, nullptr, fg8::error{}), std::runtime_error);
  }

int main(int argc, char * * argv)
  {
  auto suite = cute::suite{};

  suite += CUTE(test_empty_does_not_throw);
  suite += CUTE(test_does_throw_on_error);

  cute::xml_file_opener xml{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xml.out};
  auto runner = cute::makeRunner(listener, argc, argv);

  return !runner(suite, "fg8::error Suite");
  }
