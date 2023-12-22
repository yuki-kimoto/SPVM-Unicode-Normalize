package SPVM::Encode;

our $VERSION = '0.05';

1;

=encoding utf8

=head1 Name

SPVM::Encode - Encode Utilities.

=head1 Description

The Encode class in L<SPVM> has methods to encode/docode strings.

=head1 Usage

  use Encode;
  
  my $string = "あいうえお";

=head1 Class Methods

=head2 ERROR_INVALID_UTF8

  static method INVALID_UTF8 : int ();

Returns -2.

=head2 is_unicode_scalar_value

  static method is_unicode_scalar_value : int ($code_point: int);

If the code point $code_point is a Encode scalar value, returns 1. Otherwise returns 0.

=head2 uchar_to_utf8

  static method uchar_to_utf8 : string ($unicode_code_point : int);

Converts the Encode codepoint $unicode_code_point to a UTF-8 character.

If the $unicode_code_point is invalid Encode code point, returns undef.

=head2 utf8_to_utf16

  static method utf8_to_utf16 : short[] ($string : string);

Converts the UTF-8 string $string to a UTF-16 string, and returns it.

=head2 decode_utf16

  static method decode_utf16 : string ($string : short[]);

Converts the UTF-16 string $string to a UTF-8 string, and returns it.

=head2 utf32_to_utf16

  static method utf32_to_utf16 : short[] ($string : int[]);

Converts the UTF-32 string $string to a UTF-16 string, and returns it.

=head2 utf16_to_utf32

  static method utf16_to_utf32 : int[] ($string : short[]);

Converts the UTF-16 string $string to a UTF-32 string, and returns it.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
