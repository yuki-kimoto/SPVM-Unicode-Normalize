package SPVM::Unicode::Normalize;

our $VERSION = "0.003";

1;

=encoding utf8

=head1 Name

SPVM::Unicode::Normalize - Normalizing UTF-8

=head1 Description

The Unicode::Normalize class in L<SPVM> has methods to normalize UTF-8.

=head1 Usage

  use Unicode::Normalize;
   
  my $NFD_string  = Unicode::Normalize->NFD($string);
  
  my $NFC_string  = Unicode::Normalize->NFC($string);
  
  my $NFKD_string = Unicode::Normalize->NFKD($string);
  
  my $NFKC_string = Unicode::Normalize->NFKC($string);

=head1 Class Methods

=head2 NFC

C<static method NFC : string ($string : string);>

Returns the Normalization Form C (formed by canonical decomposition followed by canonical composition).

=head2 NFD

C<static method NFD : string ($string : string);>

Returns the Normalization Form D (formed by canonical decomposition).

=head2 NFKC

C<static method NFKC : string ($string : string);>

Returns the Normalization Form KC (formed by compatibility decomposition followed by canonical composition).

=head2 NFKD

C<static method NFKD : string ($string : string);>

Returns the Normalization Form KD (formed by compatibility decomposition).

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
