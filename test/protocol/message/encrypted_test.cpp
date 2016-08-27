#include "frontg8/protocol/message/encrypted.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/xml_listener.h>

#include <algorithm>
#include <sstream>

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

void test_construction_from_other_message()
  {
  fg8::protocol::message::encrypted const original{"CUTE"};
  auto const copy = original;

  ASSERT_EQUAL(original.content(), copy.content());
  }

void test_set_content()
  {
  fg8::protocol::message::encrypted msg{};
  msg.content("CUTE");

  ASSERT_EQUAL("CUTE", msg.content());
  }

void test_stream_output_without_content()
  {
  std::ostringstream buffer{};
  buffer << fg8::protocol::message::encrypted{};

  ASSERT_EQUAL(0, buffer.str().size());
  ASSERT_EQUAL("", buffer.str());
  }

void test_stream_output_with_empty_content()
  {
  std::ostringstream buffer{};
  buffer << fg8::protocol::message::encrypted{""};

  auto expected = std::string{{0x0a, 0x00}};

  ASSERT_EQUAL(expected, buffer.str());
  }

void test_stream_output_with_content()
  {
  std::ostringstream buffer{};
  buffer << fg8::protocol::message::encrypted{"CUTE"};

  auto expected = std::string{{0x0a, 0x04, 0x43, 0x55, 0x54, 0x45}};

  ASSERT_EQUAL(expected, buffer.str());
  }

void test_stream_input_from_empty_stream()
  {
  std::istringstream buffer{};
  fg8::protocol::message::encrypted msg{};

  buffer >> msg;
  ASSERT(!msg);
  }

void test_stream_input_from_stream_containing_empty_message()
  {
  std::istringstream buffer{{0x0a, 0x00}};
  fg8::protocol::message::encrypted msg{};

  buffer >> msg;
  ASSERT(msg);
  ASSERT_EQUAL("", msg.content());
  }

void test_stream_input_from_stream_containing_message()
  {
  std::istringstream buffer{{0x0a, 0x04, 0x43, 0x55, 0x54, 0x45}};
  fg8::protocol::message::encrypted msg{};

  buffer >> msg;
  ASSERT(msg);
  ASSERT_EQUAL("CUTE", msg.content());
  }

void test_from_data_empty()
  {
  auto msg = fg8::protocol::message::encrypted::from_data({});

  ASSERT(!msg);
  ASSERT_EQUAL("", msg.content());
  }

void test_from_data_real_data()
  {
  auto msg = fg8::protocol::message::encrypted::from_data({0x0a, 0x04, 0x43, 0x55, 0x54, 0x45});

  ASSERT(msg);
  ASSERT_EQUAL("CUTE", msg.content());
  }

void test_from_data_invalid_data()
  {
  auto msg = fg8::protocol::message::encrypted::from_data("INVALID");

  ASSERT(!msg);
  ASSERT_EQUAL("", msg.content());
  }

int main(int argc, char * * argv)
  {
  auto construction_suite = cute::suite{};

  construction_suite += CUTE(test_default_construction);
  construction_suite += CUTE(test_construction_with_empty_string);
  construction_suite += CUTE(test_construction_with_string);
  construction_suite += CUTE(test_construction_from_other_message);

  auto content_suite = cute::suite{};

  content_suite += CUTE(test_set_content);

  auto stream_output_suite = cute::suite{};

  stream_output_suite += CUTE(test_stream_output_without_content);
  stream_output_suite += CUTE(test_stream_output_with_empty_content);
  stream_output_suite += CUTE(test_stream_output_with_content);

  auto stream_input_suite = cute::suite{};

  stream_input_suite += CUTE(test_stream_input_from_empty_stream);
  stream_input_suite += CUTE(test_stream_input_from_stream_containing_empty_message);
  stream_input_suite += CUTE(test_stream_input_from_stream_containing_message);

  auto utilities_suite = cute::suite{};

  utilities_suite += CUTE(test_from_data_empty);
  utilities_suite += CUTE(test_from_data_real_data);
  utilities_suite += CUTE(test_from_data_invalid_data);

  cute::xml_file_opener xml{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xml.out};
  auto runner = cute::makeRunner(listener, argc, argv);

  return !(runner(construction_suite,  "fg8::protocol::message::encrypted Construction") &&
           runner(content_suite,       "fg8::protocol::message::encrypted Content") &&
           runner(stream_input_suite,  "fg8::protocol::message::encrypted Stream Input") &&
           runner(stream_output_suite, "fg8::protocol::message::encrypted Stream Output") &&
           runner(utilities_suite,     "fg8::protocol::message::encrypted Utilities"));
  }
