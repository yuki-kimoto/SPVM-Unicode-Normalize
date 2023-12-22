// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "spvm_utf8proc.h"

const char* FILE_NAME = "SPVM/Encode.c";

int32_t SPVM__Encode__NFC(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_string = stack[0].oval;
  
  if (!obj_string) {
    return env->die(env, stack, "$string must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* string = env->get_chars(env, stack, obj_string);
  
  spvm_utf8proc_uint8_t *string_nfc_tmp;
  
  int32_t string_nfc_length = spvm_utf8proc_map(string, 0, &string_nfc_tmp, SPVM_UTF8PROC_NULLTERM | SPVM_UTF8PROC_STABLE |
    SPVM_UTF8PROC_DECOMPOSE);
  
  if (string_nfc_length < 0) {
    return env->die(env, stack, "spvm_utf8proc_map failed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_string_nfc = env->new_string(env, stack, NULL, string_nfc_length);
  
  char* string_nfc = (char*)env->get_chars(env, stack, obj_string_nfc);
  
  memcpy(string_nfc, string_nfc_tmp, string_nfc_length);
  
  free(string_nfc_tmp);
  
  stack[0].oval = obj_string_nfc;
  
  return 0;
}
