// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "spvm_utf8proc.h"

const char* FILE_NAME = "SPVM/Encode.c";

int32_t SPVM__Encode__code_point(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_str = stack[0].oval;
  
  const char* str = env->get_chars(env, stack, obj_str);
  int32_t str_len = env->length(env, stack, obj_str);
  
  int32_t* offset_ref = stack[1].iref;
  
  if (*offset_ref < 0 || *offset_ref > str_len - 1) {
    stack[0].ival = -1;
    return 0;
  }
  
  spvm_utf8proc_int32_t dst;
  int32_t code_point_len = (int32_t)spvm_utf8proc_iterate((const spvm_utf8proc_uint8_t*)(str + *offset_ref), str_len, &dst);
  
  int32_t code_point;
  if (code_point_len > 0) {
    code_point = dst;
    *offset_ref += code_point_len;
  }
  else if (code_point_len == 0) {
    code_point = -1;
  }
  else if (code_point_len == SPVM_UTF8PROC_ERROR_INVALIDUTF8) {
    code_point = -2;
  }
  
  stack[0].ival = code_point;
  
  return 0;
}

int32_t SPVM__Encode__code_point_to_utf8(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t code_point = stack[0].ival;
  
  char tmp_utf8_char[4];
  int32_t utf8_char_length = (int32_t)spvm_utf8proc_encode_char((spvm_utf8proc_int32_t)code_point, (spvm_utf8proc_uint8_t*)tmp_utf8_char);
  
  if (utf8_char_length == 0) {
    stack[0].oval = NULL;
    return 0;
  }
  
  void* obj_utf8_char = env->new_string(env, stack, NULL, utf8_char_length);
  
  char* utf8_char = (char*)env->get_chars(env, stack, obj_utf8_char);
  memcpy((char*)utf8_char, tmp_utf8_char, utf8_char_length);
  
  stack[0].oval = obj_utf8_char;
  
  return 0;
}

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
