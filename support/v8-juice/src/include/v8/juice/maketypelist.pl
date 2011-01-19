#!/usr/bin/perl
########################################################################
# A quick hack to generate C++ class templates for use with the
# parsepp library.
#
# Usage:
#
#  $0 NUMBER (default=10)
#
# It generates master templates with NUMBER arguments and specializations
# for N arguments, where (0 > N < NUMBER).
#
# The generated classes are:
#
#  TypeList_N<N types>
#
#  TypeList<N types>
########################################################################
my $COUNT = @ARGV ? $ARGV[0] : 10;

if( $COUNT !~ /^\d+$/ ) {
    die "Usage: $0 NUMBER\n";
}
$COUNT =~ s/^(0+)?//;
print "// auto-generated [".localtime()."] by $0\n";
sub generateNumbered($)
{
  my $max = shift @_;
  for( my $i = 0; $i <= $max; ++$i ) {
      if ( 0 == $i ) {
          print "struct TypeList_0 : TypeChain<NilType,NilType> {};\n";
          print "\n";
          next;
      }
      if ( 1 == $i ) {
          print "template <class T1>\n";
          print "struct TypeList_1 : TypeChain<T1,NilType> {};\n";
          print "\n";
          next;
      }
      if ( 2 == $i ) {
          print "template <class T1, class T2>\n";
          print "struct TypeList_2 : TypeChain<T1, TypeChain<T2, NilType> > {};\n";
          print "\n";
          next;
      }
      my @tlist;
      for ( my $x = 2; $x <= $i; ++$x ) {
          push(@tlist, 'T'.$x );
      }
      my $Tlist = join(', ',@tlist);
      #my $TPlist = '('.join('), (',@tlist).')';

      my $typenames = 'class '.join(', class ',@tlist);
      print "template <class T1, ".$typenames." >\n";
      my $parent = "TypeChain<T1, TypeList_".($i-1)."< ".$Tlist." > >";
      print "struct TypeList_".$i." : ".$parent." {};\n";
      print "\n";
  }
}
sub generateUnnumbered($)
{
  my $max = shift @_;
  for ( my $i = $max; $i >= 0; --$i ) {
      my @nilfiller;
      for ( my $y = ($max-$i); $y > 0; --$y ) {
          my $kludge = -1;
          push( @nilfiller, "NilType" );
      }
      my $nils = join(', ',@nilfiller );
      if ( @nilfiller ) {
          $nils = ', '.$nils;
      }

      if ( 0 == $i ) {
          print "template <>\n";
          print "struct TypeList<> : TypeChain<NilType,NilType> {};\n";
          print "\n";
          next;
      }
      if ( 1 == $i ) {
          print "template <class T1>\n";
          print "struct TypeList<T1".$nils."> : TypeList_1<T1> {};\n";
          print "\n";
          next;
      }
      if ( 2 == $i ) {
          print "template <class T1, class T2>\n";
          print "struct TypeList<T1, T2".$nils."> : TypeList_2<T1,T2> {};\n";
          print "\n";
          next;
      }
      my @tlist;
      for ( my $x = 2; $x <= $i; ++$x ) {
          push(@tlist, 'T'.$x );
      }
      my $Tlist = join(', ',@tlist);

      my $typenames = 'class '.join(', class ',@tlist);

      my @tdecllistDefaults;
      my @tdecllist;
      my @nilfiller;
      for ( my $y = 2; $y <=$i; ++$y ) {
          push( @tdecllistDefaults, "class T".$y." = NilType" );
          push( @tdecllist, "class T".$y );
      }
      my $tdecllistDefaults = join(', ',@tdecllistDefaults);
      my $tdecllist = join(', ',@tdecllist);
      if ( $max != $i ) {       # Specialization
          print "template <class T1, ".$tdecllist.">\n";
          print "struct TypeList <T1, ".$Tlist.$nils."> : TypeList_".$i."<T1, ".$Tlist."> {};\n";
      } else {                  # Master template
          print "template <class T1 = NilType, ".$tdecllistDefaults.">\n";
          print "struct TypeList : TypeList_".$i."<T1, ".$Tlist."> {};\n";
      }
      print "\n";
  }
}

generateNumbered $COUNT;
generateUnnumbered $COUNT;
