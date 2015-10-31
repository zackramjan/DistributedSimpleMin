#!/usr/bin/perl
$to = $ARGV[0] || 3;
$from = $to * -1;
for my $i ($from..$to) {
	for my $j ($from..$to) {
		for my $k ($from..$to) {
			my $e = 10;
			$e = 13 if $i+$j+$k % 3 == 0;
			$e = 23 if $i+$j+$k % 7 == 0;
			print "$e.0\t$i.0\t$j.0\t$k.0\n"
		}
	}
}
