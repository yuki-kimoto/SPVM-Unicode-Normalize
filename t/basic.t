use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Unicode::Normalize';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count();

{
  ok(SPVM::TestCase::Unicode::Normalize->decode_utf8);
  
  ok(SPVM::TestCase::Unicode::Normalize->encode_utf8);
  
  ok(SPVM::TestCase::Unicode::Normalize->decode_utf16);
  
  ok(SPVM::TestCase::Unicode::Normalize->encode_utf16);
  
  ok(SPVM::TestCase::Unicode::Normalize->decode_utf32);
  
  ok(SPVM::TestCase::Unicode::Normalize->encode_utf32);
  
}

# All object is freed
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
