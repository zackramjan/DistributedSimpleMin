#!/usr/bin/perl
for my $i (-10..10) {
	for my $j (-10..10) {
		for my $k (-10..10) {
			my $e = 10;
			$e = 13 if $i+$j+$k % 13 == 0;
			$e = 23 if $i+$j+$k % 23 == 0;
			print "$e $i $j $k\n"
		}
	}
}
