#!/bin/bash

rm timings
rm wallclock

echo 'Linearising'
echo 'Wallclock time for generating and solving PBES:' > wallclock

echo 'mcrl22lps:' >> wallclock

{ time mcrl22lps -nf --timings=timings mp_fts_prop5.mcrl2 | lpssumelm > mp_fts_prop5.lps ; } 2>> wallclock

echo 'lps2pbes:' >> wallclock

echo 'Converting to PBES'

{ time lps2pbes --timings=timings -f prop5.mcf mp_fts_prop5.lps | pbesconstelm --timings=timings | pbesparelm --timings=timings  > mp_fts_prop5.pbes ; } 2>> wallclock

echo 'Solving PBES'

echo 'pbespgsolve:' >> wallclock

{ time pbespgsolve --timings=timings -rjittyc -srecursive mp_fts_prop5.pbes ; } 2>> wallclock

rm *.lps
rm *.pbes
