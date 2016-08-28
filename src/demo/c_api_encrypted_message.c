#include "frontg8.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main()
  {
  fg8_error_t error = NULL;
  fg8_protocol_message_encrypted_t msg = fg8_protocol_message_encrypted_create("Hello C!", 9, &error);

  if(error)
    {
    printf("Error: %s\n", fg8_error_message(error));
    fg8_error_destroy(error);
    return EXIT_FAILURE;
    }

  char const * const content = fg8_protocol_message_encrypted_get_content(msg, NULL, &error);

  if(error)
    {
    printf("Error: %s\n", fg8_error_message(error));
    fg8_error_destroy(error);
    fg8_protocol_message_encrypted_destroy(msg);
    return EXIT_FAILURE;
    }
  else
    {
    printf("Content: %s\n", content);
    }

  fg8_protocol_message_encrypted_t copy = fg8_protocol_message_encrypted_copy(msg, &error);

  if(error)
    {
    printf("Error: %s\n", fg8_error_message(error));
    fg8_error_destroy(error);
    fg8_protocol_message_encrypted_destroy(msg);
    return EXIT_FAILURE;
    }

  char const * const copy_content = fg8_protocol_message_encrypted_get_content(copy, NULL, &error);

  if(error)
    {
    printf("Error: %s\n", fg8_error_message(error));
    fg8_error_destroy(error);
    fg8_protocol_message_encrypted_destroy(msg);
    fg8_protocol_message_encrypted_destroy(copy);
    return EXIT_FAILURE;
    }
  else
    {
    printf("Copy-Content: %s\n", copy_content);
    }

  fg8_protocol_message_encrypted_set_content(msg, "Still rockin' C", 16, &error);
  if(error)
    {
    printf("Error: %s\n", fg8_error_message(error));
    fg8_error_destroy(error);
    fg8_protocol_message_encrypted_destroy(msg);
    fg8_protocol_message_encrypted_destroy(copy);
    return EXIT_FAILURE;
    }

  char const * const changed_content = fg8_protocol_message_encrypted_get_content(msg, NULL, &error);

  if(error)
    {
    printf("Error: %s\n", fg8_error_message(error));
    fg8_error_destroy(error);
    fg8_protocol_message_encrypted_destroy(msg);
    fg8_protocol_message_encrypted_destroy(copy);
    return EXIT_FAILURE;
    }
  else
    {
    char const * const copy_content = fg8_protocol_message_encrypted_get_content(copy, NULL, &error);
    if(error)
      {
      printf("Error: %s\n", fg8_error_message(error));
      fg8_error_destroy(error);
      fg8_protocol_message_encrypted_destroy(msg);
      fg8_protocol_message_encrypted_destroy(copy);
      return EXIT_FAILURE;
      }
    printf("Changed-Content: %s\n", changed_content);
    printf("Copy-Content: %s\n", copy_content);
    }

  fg8_protocol_message_encrypted_destroy(msg);
  fg8_protocol_message_encrypted_destroy(copy);
  return EXIT_SUCCESS;
  }
