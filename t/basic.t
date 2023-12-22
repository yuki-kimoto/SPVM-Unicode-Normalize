use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Encode';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count();

{
  ok(SPVM::TestCase::Encode->uchar_to_utf8);
  ok(SPVM::TestCase::Encode->utf8_to_utf16);
  ok(SPVM::TestCase::Encode->utf16_to_utf8);
  ok(SPVM::TestCase::Encode->ERROR_INVALID_UTF8);
  ok(SPVM::TestCase::Encode->is_unicode_scalar_value);
}

# All object is freed
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
