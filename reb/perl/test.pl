#!/usr/bin/env perl

use strict;
use warnings;

die("Usage: ./test.pl regexp file.in\n") if (@ARGV == 0);
my $re = shift(@ARGV);
while (<>) {
  chomp;
  print "$.:", $_, "\n" if (/$re/);
}
