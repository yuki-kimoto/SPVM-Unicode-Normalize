// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "spvm_utf8proc.h"

const char* MFILE = "SPVM/Encode.c";

int32_t SPVM__Encode__code_point(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
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
  (void)env;
  
  int32_t code_point = stack[0].ival;
  
  char tmp_utf8_bytes[4];
  int32_t utf8_len = (int32_t)spvm_utf8proc_encode_char((spvm_utf8proc_int32_t)code_point, (spvm_utf8proc_uint8_t*)tmp_utf8_bytes);
  
  if (utf8_len == 0) {
    stack[0].oval = NULL;
    return 0;
  }
  
  void* obj_utf8_bytes = env->new_byte_array(env, stack, utf8_len);
  
  int8_t* utf8_bytes = env->get_elems_byte(env, stack, obj_utf8_bytes);
  memcpy((char*)utf8_bytes, tmp_utf8_bytes, utf8_len);
  
  void* utf8_string = env->new_string(env, stack, (char*)utf8_bytes, utf8_len);
  
  stack[0].oval = utf8_string;
  
  return 0;
}
