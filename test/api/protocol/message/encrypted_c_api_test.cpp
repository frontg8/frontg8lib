#include "frontg8.h"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/xml_listener.h>

#include <algorithm>
#include <array>
#include <cstdlib>

#define EXPECTED(error) \
ASSERT(error);\
fg8_error_destroy((error));\
error = nullptr;

struct encrypted_message_tests
  {
  ~encrypted_message_tests() noexcept(false)
    {
    if(m_error)
      {
      auto error = fg8_error_message(m_error);
      throw std::string{"Unexpected error: "} + error;
      }

    fg8_error_destroy(m_error);
    fg8_protocol_message_encrypted_destroy(m_message);
    fg8_protocol_message_encrypted_destroy(m_copy);
    }

  protected:
    fg8_error_t m_error{};
    fg8_protocol_message_encrypted_t m_message{};
    fg8_protocol_message_encrypted_t m_copy{};
  };

struct lifetime_tests : encrypted_message_tests
  {
  void test_empty_construction()
    {
    m_message = fg8_protocol_message_encrypted_create(nullptr, 0, &m_error);

    ASSERT(m_message);
    ASSERT(!fg8_protocol_message_encrypted_is_valid(m_message));
    ASSERT(!m_error);
    ASSERT(!fg8_protocol_message_encrypted_get_content(m_message, nullptr, nullptr));
    }

  void test_empty_construction_with_non_zero_length()
    {
    m_message = fg8_protocol_message_encrypted_create(nullptr, 42, &m_error);

    ASSERT(m_message);
    ASSERT(!fg8_protocol_message_encrypted_is_valid(m_message));
    ASSERT(!m_error);
    ASSERT(!fg8_protocol_message_encrypted_get_content(m_message, nullptr, nullptr));
    }

  void test_construction_with_empty_string()
    {
    m_message = fg8_protocol_message_encrypted_create("", 0, &m_error);

    ASSERT(m_message);
    ASSERT(fg8_protocol_message_encrypted_is_valid(m_message));
    ASSERT(!m_error);
    ASSERT(fg8_protocol_message_encrypted_get_content(m_message, nullptr, nullptr));
    }

  void test_construction_with_string()
    {
    m_message = fg8_protocol_message_encrypted_create("CUTE", 4, &m_error);

    ASSERT(m_message);
    ASSERT(fg8_protocol_message_encrypted_is_valid(m_message));
    ASSERT(!m_error);
    ASSERT_EQUAL("CUTE", fg8_protocol_message_encrypted_get_content(m_message, nullptr, nullptr));
    }

  void test_construction_with_string_containing_null_bytes()
    {
    auto data = std::array<char, 6>{{0x43, 0x00, 0x55, 0x54, 0x45, 0x00}};
    m_message = fg8_protocol_message_encrypted_create(data.data(), data.size(), &m_error);

    ASSERT(m_message);
    ASSERT(fg8_protocol_message_encrypted_is_valid(m_message));
    ASSERT(!m_error);

    size_t length = 0;
    auto content = fg8_protocol_message_encrypted_get_content(m_message, &length, nullptr);
    ASSERT(std::equal(data.cbegin(), data.cend(), content));
    ASSERT_EQUAL(length, data.size());
    }

  void test_construction_from_default_other_message()
    {
    m_message = fg8_protocol_message_encrypted_create(nullptr, 0, nullptr);
    m_copy = fg8_protocol_message_encrypted_copy(m_message, &m_error);

    ASSERT(m_copy);
    ASSERT(!fg8_protocol_message_encrypted_is_valid(m_copy));
    ASSERT(!m_error);
    ASSERT(!fg8_protocol_message_encrypted_get_content(m_copy, nullptr, nullptr));
    ASSERT(m_message != m_copy);
    }

  void test_construction_from_other_message()
    {
    m_message = fg8_protocol_message_encrypted_create("CUTE", 4, nullptr);
    m_copy = fg8_protocol_message_encrypted_copy(m_message, &m_error);

    ASSERT(m_copy);
    ASSERT(fg8_protocol_message_encrypted_is_valid(m_copy));
    ASSERT(!m_error);
    ASSERT(fg8_protocol_message_encrypted_get_content(m_copy, nullptr, nullptr));
    ASSERT_EQUAL("CUTE", fg8_protocol_message_encrypted_get_content(m_copy, nullptr, nullptr));
    ASSERT_EQUAL(fg8_protocol_message_encrypted_get_content(m_message, nullptr, nullptr),
                 fg8_protocol_message_encrypted_get_content(m_copy, nullptr, nullptr));
    ASSERT(m_message != m_copy);
    }

  static cute::suite suite()
    {
    return cute::suite{{
      CUTE_SMEMFUN(lifetime_tests, test_empty_construction),
      CUTE_SMEMFUN(lifetime_tests, test_empty_construction_with_non_zero_length),
      CUTE_SMEMFUN(lifetime_tests, test_construction_with_empty_string),
      CUTE_SMEMFUN(lifetime_tests, test_construction_with_string),
      CUTE_SMEMFUN(lifetime_tests, test_construction_with_string_containing_null_bytes),
      CUTE_SMEMFUN(lifetime_tests, test_construction_from_default_other_message),
      CUTE_SMEMFUN(lifetime_tests, test_construction_from_other_message)
      }};
    }
  };

struct content_tests : encrypted_message_tests
  {
  void test_get_content_default_constructed()
    {
    m_message = fg8_protocol_message_encrypted_create(nullptr, 0, nullptr);
    auto content = fg8_protocol_message_encrypted_get_content(m_message, nullptr, &m_error);

    ASSERT(!m_error);
    ASSERT(!content);
    }

  void test_get_content_constructed_with_empty_string()
    {
    m_message = fg8_protocol_message_encrypted_create("", 0, nullptr);
    auto content = fg8_protocol_message_encrypted_get_content(m_message, nullptr, &m_error);

    ASSERT(!m_error);
    ASSERT(content);
    ASSERT_EQUAL("", content);
    }

  void test_get_content_constructed_with_string()
    {
    m_message = fg8_protocol_message_encrypted_create("CUTE", 4, nullptr);
    auto content = fg8_protocol_message_encrypted_get_content(m_message, nullptr, &m_error);

    ASSERT(!m_error);
    ASSERT(content);
    ASSERT_EQUAL("CUTE", content);
    }

  void test_get_content_nullptr()
    {
    auto content = fg8_protocol_message_encrypted_get_content(nullptr, nullptr, &m_error);

    EXPECTED(m_error);
    ASSERT(!content);
    }

  void test_set_content_to_nothing_default_constructed()
    {
    m_message = fg8_protocol_message_encrypted_create(nullptr, 0, nullptr);
    fg8_protocol_message_encrypted_set_content(m_message, nullptr, 0, &m_error);
    auto content = fg8_protocol_message_encrypted_get_content(m_message, nullptr, nullptr);

    ASSERT(!m_error);
    ASSERT(!fg8_protocol_message_encrypted_is_valid(m_message));
    ASSERT(!content);
    }

  void test_set_content_to_nothing_constructed_with_string()
    {
    m_message = fg8_protocol_message_encrypted_create("CUTE", 4, nullptr);
    fg8_protocol_message_encrypted_set_content(m_message, nullptr, 0, &m_error);
    auto content = fg8_protocol_message_encrypted_get_content(m_message, nullptr, nullptr);

    ASSERT(!m_error);
    ASSERT(!fg8_protocol_message_encrypted_is_valid(m_message));
    ASSERT(!content);
    }

  void test_set_content_to_nothing_nullptr()
    {
    fg8_protocol_message_encrypted_set_content(nullptr, nullptr, 0, &m_error);

    EXPECTED(m_error);
    }

  void test_set_content_default_constructed()
    {
    m_message = fg8_protocol_message_encrypted_create(nullptr, 0, nullptr);
    fg8_protocol_message_encrypted_set_content(m_message, "CUTE", 4, &m_error);
    auto content = fg8_protocol_message_encrypted_get_content(m_message, nullptr, nullptr);

    ASSERT(!m_error);
    ASSERT(fg8_protocol_message_encrypted_is_valid(m_message));
    ASSERT_EQUAL("CUTE", content);
    }

  void test_set_content_constructed_with_string()
    {
    m_message = fg8_protocol_message_encrypted_create("FG8", 3, nullptr);
    fg8_protocol_message_encrypted_set_content(m_message, "CUTE", 4, &m_error);
    auto content = fg8_protocol_message_encrypted_get_content(m_message, nullptr, nullptr);

    ASSERT(!m_error);
    ASSERT(fg8_protocol_message_encrypted_is_valid(m_message));
    ASSERT_EQUAL("CUTE", content);
    }

  void test_set_content_including_null_bytes_constructed_with_string()
    {
    m_message = fg8_protocol_message_encrypted_create("FG8", 3, nullptr);
    auto data = std::array<char, 6>{{0x43, 0x00, 0x55, 0x54, 0x45, 0x00}};
    fg8_protocol_message_encrypted_set_content(m_message, data.data(), data.size(), &m_error);
    size_t length = 0;
    auto content = fg8_protocol_message_encrypted_get_content(m_message, &length, nullptr);

    ASSERT(!m_error);
    ASSERT(fg8_protocol_message_encrypted_is_valid(m_message));
    ASSERT(std::equal(data.cbegin(), data.cend(), content));
    ASSERT_EQUAL(length, data.size());
    }

  void test_set_content_to_zero_length_string()
    {
    m_message = fg8_protocol_message_encrypted_create("FG8", 3, nullptr);
    fg8_protocol_message_encrypted_set_content(m_message, "", 0, &m_error);
    size_t length = 3;
    auto content = fg8_protocol_message_encrypted_get_content(m_message, &length, nullptr);

    ASSERT(!m_error);
    ASSERT(fg8_protocol_message_encrypted_is_valid(m_message));
    ASSERT(content);
    ASSERT_EQUAL("", content);
    ASSERT_EQUAL(0, length);
    }

  void test_set_content_nullptr()
    {
    fg8_protocol_message_encrypted_set_content(nullptr, "CUTE", 4, &m_error);

    EXPECTED(m_error);
    }

  static cute::suite suite()
    {
    return cute::suite{{
      CUTE_SMEMFUN(content_tests, test_get_content_default_constructed),
      CUTE_SMEMFUN(content_tests, test_get_content_constructed_with_empty_string),
      CUTE_SMEMFUN(content_tests, test_get_content_constructed_with_string),
      CUTE_SMEMFUN(content_tests, test_get_content_nullptr),
      CUTE_SMEMFUN(content_tests, test_set_content_to_nothing_default_constructed),
      CUTE_SMEMFUN(content_tests, test_set_content_to_nothing_constructed_with_string),
      CUTE_SMEMFUN(content_tests, test_set_content_to_nothing_nullptr),
      CUTE_SMEMFUN(content_tests, test_set_content_default_constructed),
      CUTE_SMEMFUN(content_tests, test_set_content_constructed_with_string),
      CUTE_SMEMFUN(content_tests, test_set_content_including_null_bytes_constructed_with_string),
      CUTE_SMEMFUN(content_tests, test_set_content_to_zero_length_string),
      CUTE_SMEMFUN(content_tests, test_set_content_nullptr)
      }};
    }
  };

struct utilities_tests : encrypted_message_tests
  {
  void test_deserialize_nullptr()
    {
    m_message = fg8_protocol_message_encrypted_deserialize(nullptr, 0, &m_error);

    ASSERT(!m_error);
    ASSERT(!m_message);
    }

  void test_deserialize_empty_data()
    {
    m_message = fg8_protocol_message_encrypted_deserialize("", 0, &m_error);

    ASSERT(!m_error);
    ASSERT(m_message);
    ASSERT(!fg8_protocol_message_encrypted_is_valid(m_message));
    }

  void test_deserialize_with_actual_data()
    {
    std::array<char, 6> data{{0x0a, 0x04, 0x43, 0x55, 0x54, 0x45}};
    m_message = fg8_protocol_message_encrypted_deserialize(data.data(), data.size(), &m_error);

    ASSERT(!m_error);
    ASSERT(m_message);
    ASSERT(fg8_protocol_message_encrypted_is_valid(m_message));

    size_t length = 0;
    ASSERT_EQUAL("CUTE", fg8_protocol_message_encrypted_get_content(m_message, &length, nullptr));
    ASSERT_EQUAL(4, length);
    }

  void test_deserialize_with_data_containing_null_bytes()
    {
    std::array<char, 8> data{{0x0a, 0x06, 0x43, 0x00, 0x55, 0x54, 0x45, 0x00}};
    m_message = fg8_protocol_message_encrypted_deserialize(data.data(), data.size(), &m_error);

    std::array<char, 6> expected{{0x43, 0x00, 0x55, 0x54, 0x45, 0x00}};

    ASSERT(!m_error);
    ASSERT(m_message);
    ASSERT(fg8_protocol_message_encrypted_is_valid(m_message));

    size_t length = 0;
    ASSERT(std::equal(expected.cbegin(), expected.cend(), fg8_protocol_message_encrypted_get_content(m_message, &length,
                                                                                                    nullptr)));
    }

  void test_serialize_default_constructed()
    {
    m_message = fg8_protocol_message_encrypted_create(nullptr, 0, nullptr);
    size_t length = 0;
    auto const serialized = fg8_protocol_message_encrypted_serialize(m_message, &length, &m_error);

    ASSERT(!serialized);
    ASSERT(!length);
    ASSERT(!m_error);
    }

  void test_serialize_empty_message()
    {
    m_message = fg8_protocol_message_encrypted_create("", 0, nullptr);
    size_t length = 0;
    auto const serialized = fg8_protocol_message_encrypted_serialize(m_message, &length, &m_error);

    auto expected = std::array<char, 2>{{0x0a, 0x00}};

    ASSERT(serialized);
    ASSERT(!m_error);
    ASSERT(std::equal(expected.cbegin(), expected.cend(), serialized));
    ASSERT_EQUAL(expected.size(), length);
    std::free(serialized);
    }

  void test_serialize_with_string()
    {
    m_message = fg8_protocol_message_encrypted_create("CUTE", 4, nullptr);
    size_t length = 0;
    auto const serialized = fg8_protocol_message_encrypted_serialize(m_message, &length, &m_error);

    std::array<char, 6> expected{{0x0a, 0x04, 0x43, 0x55, 0x54, 0x45}};

    ASSERT(serialized);
    ASSERT(!m_error);
    ASSERT(std::equal(expected.cbegin(), expected.cend(), serialized));
    ASSERT_EQUAL(expected.size(), length);
    std::free(serialized);
    }

  void test_serialize_with_data_containing_null_bytes()
    {
    std::array<char, 6> data{{0x43, 0x00, 0x55, 0x54, 0x45, 0x00}};
    m_message = fg8_protocol_message_encrypted_create(data.data(), data.size(), nullptr);
    size_t length = 0;
    auto const serialized = fg8_protocol_message_encrypted_serialize(m_message, &length, &m_error);

    std::array<char, 8> expected{{0x0a, 0x06, 0x43, 0x00, 0x55, 0x54, 0x45, 0x00}};

    ASSERT(serialized);
    ASSERT(!m_error);
    ASSERT(std::equal(expected.cbegin(), expected.cend(), serialized));
    ASSERT_EQUAL(expected.size(), length);
    std::free(serialized);
    }

  void test_compare_equal_on_equal_messages()
    {
    m_message = fg8_protocol_message_encrypted_create(nullptr, 0, nullptr);
    m_copy = fg8_protocol_message_encrypted_copy(m_message, &m_error);

    ASSERT(m_message);
    ASSERT(m_copy);
    ASSERT_NOT_EQUAL_TO(m_message, m_copy);
    ASSERT(fg8_protocol_message_encrypted_compare_equal(m_message, m_copy));
    }

  void test_compare_lhs_nullptr()
    {
    m_message = fg8_protocol_message_encrypted_create(nullptr, 0, nullptr);

    ASSERT(m_message);
    ASSERT(!fg8_protocol_message_encrypted_compare_equal(nullptr, m_message));
    }

  void test_compare_rhs_nullptr()
    {
    m_message = fg8_protocol_message_encrypted_create(nullptr, 0, nullptr);

    ASSERT(m_message);
    ASSERT(!fg8_protocol_message_encrypted_compare_equal(m_message, nullptr));
    }

  void test_compare_nullptr()
    {
    ASSERT(!fg8_protocol_message_encrypted_compare_equal(nullptr, nullptr));
    }

  static cute::suite suite()
    {
    return cute::suite{{
      CUTE_SMEMFUN(utilities_tests, test_deserialize_nullptr),
      CUTE_SMEMFUN(utilities_tests, test_deserialize_empty_data),
      CUTE_SMEMFUN(utilities_tests, test_deserialize_with_actual_data),
      CUTE_SMEMFUN(utilities_tests, test_deserialize_with_data_containing_null_bytes),
      CUTE_SMEMFUN(utilities_tests, test_serialize_default_constructed),
      CUTE_SMEMFUN(utilities_tests, test_serialize_empty_message),
      CUTE_SMEMFUN(utilities_tests, test_serialize_with_string),
      CUTE_SMEMFUN(utilities_tests, test_serialize_with_data_containing_null_bytes),
      CUTE_SMEMFUN(utilities_tests, test_compare_equal_on_equal_messages),
      CUTE_SMEMFUN(utilities_tests, test_compare_lhs_nullptr),
      CUTE_SMEMFUN(utilities_tests, test_compare_rhs_nullptr),
      CUTE_SMEMFUN(utilities_tests, test_compare_nullptr)
      }};
    }
  };

int main(int argc, char * * argv)
  {
  cute::xml_file_opener xml{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xml.out};
  auto runner = cute::makeRunner(listener, argc, argv);

  return !(runner(lifetime_tests::suite(),  "fg8_protocol_message_encrypted Construction") &&
           runner(content_tests::suite(),   "fg8_protocol_message_encrypted Content") &&
           runner(utilities_tests::suite(), "fg8_protocol_message_encrypted Utilities"));
  }
