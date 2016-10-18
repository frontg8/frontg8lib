#include "frontg8/protocol/message/encrypted.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/xml_listener.h>

void test_default_construction()
  {
  fg8::protocol::message::encrypted const msg{};

  ASSERT(!msg);
  ASSERT_EQUAL("", msg.content());
  }

void test_construction_with_empty_string()
  {
  fg8::protocol::message::encrypted const msg{""};

  ASSERT(msg);
  ASSERT_EQUAL("", msg.content());
  }

void test_construction_with_string()
  {
  fg8::protocol::message::encrypted const msg{"CUTE"};

  ASSERT(msg);
  ASSERT_EQUAL("CUTE", msg.content());
  }

void test_construction_with_string_containing_null_bytes()
  {
  auto input = std::string{{0x34, 0x00, 0x01, 0x7F, 0x00, 0x00}};
  fg8::protocol::message::encrypted const msg{{input.cbegin(), input.cend()}};
  auto const content = msg.content();

  ASSERT(msg);
  ASSERT_EQUAL(input, content);
  }

void test_copy_construction()
  {
  fg8::protocol::message::encrypted original{"CUTE"};
  fg8::protocol::message::encrypted copy{original};

  ASSERT(copy);
  ASSERT_EQUAL(original, copy);
  }

void test_move_construction()
  {
  fg8::protocol::message::encrypted original{"CUTE"};
  fg8::protocol::message::encrypted copy{std::move(original)};

  ASSERT(copy);
  ASSERT(!original);
  ASSERT_NOT_EQUAL_TO(original, copy);
  }

void test_set_content_default_constructed()
  {
  auto msg = fg8::protocol::message::encrypted{};
  msg.content("CUTE");

  ASSERT_EQUAL("CUTE", msg.content());
  }

void test_set_content_constructed_with_empty_string()
  {
  auto msg = fg8::protocol::message::encrypted{""};
  msg.content("CUTE");

  ASSERT_EQUAL("CUTE", msg.content());
  }

void test_set_content_constructed_with_string()
  {
  auto msg = fg8::protocol::message::encrypted{"FG8"};
  msg.content("CUTE");

  ASSERT_EQUAL("CUTE", msg.content());
  }

void test_set_content_to_empty_string()
  {
  auto msg = fg8::protocol::message::encrypted{"FG8"};
  msg.content("");

  ASSERT(msg);
  ASSERT_EQUAL("", msg.content());
  ASSERT_EQUAL(0, msg.content().length());
  }

void test_set_content_to_string_containing_null_bytes()
  {
  auto input = std::string{{0x34, 0x00, 0x01, 0x7F, 0x00, 0x00}};
  fg8::protocol::message::encrypted msg{};
  msg.content(input);

  ASSERT(msg);
  ASSERT_EQUAL(input, msg.content());
  ASSERT_EQUAL(6, msg.content().size());
  }

void test_set_content_on_copy()
  {
  auto original = fg8::protocol::message::encrypted{"CUTE"};
  auto copy = original;

  copy.content("Not so CUTE");
  ASSERT(copy);
  ASSERT_NOT_EQUAL_TO(original, copy);
  ASSERT_EQUAL("CUTE", original.content());
  ASSERT_EQUAL("Not so CUTE", copy.content());
  }

void test_clear_default_constructed()
  {
  auto msg = fg8::protocol::message::encrypted{};
  msg.clear();

  ASSERT(!msg);
  ASSERT_EQUAL("", msg.content());
  }

void test_clear_constructed_with_empty_string()
  {
  auto msg = fg8::protocol::message::encrypted{""};
  msg.clear();

  ASSERT(!msg);
  ASSERT_EQUAL("", msg.content());
  }

void test_clear_constructed_with_string()
  {
  auto msg = fg8::protocol::message::encrypted{"CUTE"};
  msg.clear();

  ASSERT(!msg);
  ASSERT_EQUAL("", msg.content());
  }

void test_serialize_default_constructed()
  {
  auto const msg = fg8::protocol::message::encrypted{};
  auto const data = msg.serialize();

  ASSERT_EQUAL("", data);
  }

void test_serialize_constructed_with_empty_string()
  {
  auto const msg = fg8::protocol::message::encrypted{""};
  auto const data = msg.serialize();

  ASSERT_EQUAL((std::string{{0x0a, 0x00}}), data);
  }

void test_serialize_constructed_with_null_string()
  {
  auto const msg = fg8::protocol::message::encrypted{{0x00}};
  auto const data = msg.serialize();

  ASSERT_EQUAL((std::string{{0x0a, 0x01, 0x00}}), data);
  }

void test_serialize_constructed_with_string()
  {
  auto const input = std::string{{0x34, 0x00, 0x01, 0x7F, 0x00, 0x00}};
  auto const msg = fg8::protocol::message::encrypted{input};
  auto const data = msg.serialize();
  auto const expected = std::string{{0x0a, 0x06, 0x34, 0x00, 0x01, 0x7F, 0x00, 0x00}};

  ASSERT_EQUAL(expected, data);
  }

void test_deserialize_empty_string()
  {
  auto msg = fg8::protocol::message::encrypted::deserialize("");

  ASSERT(!msg);
  ASSERT_EQUAL("", msg.content());
  }

void test_deserialize_serialized_string()
  {
  auto input = std::string{{0x0a, 0x06, 0x34, 0x00, 0x01, 0x7F, 0x00, 0x00}};
  auto msg = fg8::protocol::message::encrypted::deserialize(input);

  ASSERT(msg);
  ASSERT_EQUAL((std::string{input.cbegin() + 2, input.cend()}), msg.content());
  }

int main(int argc, char * * argv)
  {
  auto lifetime_suite = cute::suite{};

  lifetime_suite += CUTE(test_default_construction);
  lifetime_suite += CUTE(test_construction_with_empty_string);
  lifetime_suite += CUTE(test_construction_with_string);
  lifetime_suite += CUTE(test_construction_with_string_containing_null_bytes);
  lifetime_suite += CUTE(test_copy_construction);
  lifetime_suite += CUTE(test_move_construction);

  auto content_suite = cute::suite{};

  content_suite += CUTE(test_set_content_default_constructed);
  content_suite += CUTE(test_set_content_constructed_with_empty_string);
  content_suite += CUTE(test_set_content_constructed_with_string);
  content_suite += CUTE(test_set_content_to_empty_string);
  content_suite += CUTE(test_set_content_to_string_containing_null_bytes);
  content_suite += CUTE(test_set_content_on_copy);
  content_suite += CUTE(test_clear_default_constructed);
  content_suite += CUTE(test_clear_constructed_with_empty_string);
  content_suite += CUTE(test_clear_constructed_with_string);

  auto serialization_suite = cute::suite{};

  serialization_suite += CUTE(test_serialize_default_constructed);
  serialization_suite += CUTE(test_serialize_constructed_with_empty_string);
  serialization_suite += CUTE(test_serialize_constructed_with_null_string);
  serialization_suite += CUTE(test_serialize_constructed_with_string);
  serialization_suite += CUTE(test_deserialize_empty_string);
  serialization_suite += CUTE(test_deserialize_serialized_string);

  cute::xml_file_opener xml{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xml.out};
  auto runner = cute::makeRunner(listener, argc, argv);

  return !(runner(lifetime_suite,      "fg8::protocol::message::encrypted Lifetime") &&
           runner(content_suite,       "fg8::protocol::message::encrypted Content") &&
           runner(serialization_suite, "fg8::protocol::message::encrypted Serialization"));
  }
