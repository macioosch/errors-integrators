#!/usr/bin/env bash
algorithms=(Euler Verlet VerletLeapFrog VelocityVerlet RK4)
echo "# algorithm; time [ns] (1e6 iterations)"
for a in "${algorithms[@]}"
do
    T="$(date +%s%N)"
    ./gatherdata_constiterations.py "$a" $@ 1> /dev/null
    echo "\"$a\";$(($(date +%s%N)-T))"
done
