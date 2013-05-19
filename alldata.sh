#!/usr/bin/env bash
algorithms=(Euler Verlet VerletLeapFrog VelocityVerlet RK4)
for a in "${algorithms[@]}"
do
    echo "Executing ${a} with constant total time..."
    ./gatherdata_consttmax.py "$a" $@ > "data-ct/${a}.dat"
#    echo "Executing ${a} with constant iteration number..."
#    ./gatherdata_constiterations.py "$a" $@ > "data-ci/${a}.dat"
done

#./alltime.sh $@ > "data-ci/times.dat"
