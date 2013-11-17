#!/usr/bin/env perl

use strict;
use warnings;
use File::Slurp;
use File::Glob qw(glob);
use List::MoreUtils qw(apply);

my %complexity = split /\n|\s*,\s*/gig, read_file('complexity.csv');
my @name = ('part', 'section', 'subsection', 'subsubsection', 'paragraph');
my $part = 0;

sub rec {
  (-d (join '/', @_))? ((@_<3? '\\addtocontents{toc}{\\protect\\columnbreak}':'') . sprintf '\addcontentsline{toc}{%s}{%s}' . "\n" . '%s' . "\n", $name[@_-2], (ucfirst $_[@_-1]), join "\n", map {rec (split '/', $_)} glob((join '/', @_) . '/*')):
  (-f (join '/', @_)) && $_ =~ m/(\.(c|cc|cpp|java|py|sh)|vimrc)$/i?
    ''. '\\newpage' . "\n"
      . '\\' . $name[@_-2] . '{'. (apply {s{\-|\..+$}{ }g} $_[@_-1]) . ' - \texorpdfstring{$' . ($complexity{$_[@_-1]} || '?') . '$}{}}' . "\n"
      . '\\begin{lstlisting}' . "\n"
      . (join '', apply {s{¬}{!}g} read_file (join '/', @_)) . "\n"
      . '\\end{lstlisting}' . "\n":
  (-f (join '/', @_)) && $_ =~ m/\.tex$/i?
    ''. '\\newpage' . "\n"
      . read_file (join '/', @_) . "\n":
    ''}

print read_file('head.tpl');
print rec (split '/', $_) for <code/*>;
print read_file('foot.tpl');
