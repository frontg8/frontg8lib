#include "frontg8/error.h"
#include "frontg8/protocol/message/encrypted.h"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/xml_listener.h>

void test_message_nullptr()
  {
  ASSERT(!fg8_error_message(nullptr));
  }

void test_message_no_error()
  {
  fg8_error_t error{};
  auto msg = fg8_protocol_message_encrypted_create("", 0, &error);

  ASSERT(msg);
  ASSERT(!fg8_error_message(error));
  fg8_error_destroy(error);
  }

void test_message_error()
  {
  fg8_error_t error{};
  auto msg = fg8_protocol_message_encrypted_get_content(nullptr, nullptr, &error);

  ASSERT(!msg);
  ASSERT(fg8_error_message(error));
  fg8_error_destroy(error);
  }

int main(int argc, char * * argv)
  {
  auto suite = cute::suite{};

  suite += CUTE(test_message_nullptr);
  suite += CUTE(test_message_no_error);
  suite += CUTE(test_message_error);

  cute::xml_file_opener xml{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xml.out};
  auto runner = cute::makeRunner(listener, argc, argv);

  return !runner(suite, "fg8_error_t Suite");
  }
