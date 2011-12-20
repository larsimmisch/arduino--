#!/usr/bin/perl -w

use strict;

use Carp;

print "// Generated by $0\n\n";

while (my $line = <>) {
    chomp $line;

    next if $line !~ /^    D\((.*?)\);$/;
    my $port = $1;

    my $val;
    do {
	$line = <>;
	chomp $line;

	if ($line =~ /ldi\tr\d+, (0x[0-9a-fA-F]+)\t;/) {
	    $val = $1;
	} elsif ($line =~ /st\tZ,/) {
	    print "#define N$port $val\n";
	} else {
	  croak $line;
      }
    } while ($line !~ /st\tZ,/);
}