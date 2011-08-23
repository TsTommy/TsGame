#!/bin/perl
use strict;
use warnings;
for my $line (<>) {
	chomp($line);
	print($line) if($line =~ m/\n/);
}
