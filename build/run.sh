#!/bin/bash

# Loop over values of ftheta from 0 to 90 in steps of 0.1 degrees
for i in $(seq 0 1 90)
do
  # Format the value of ftheta for this macro file
  ftheta=$(printf "%.0f" $i)

  # Set the output filename for this simulation

  # Create the macro file with the appropriate value of ftheta
  echo "/run/initialize" > run_${ftheta}.mac
  echo "/control/verbose 2" >> run_${ftheta}.mac
  echo "/run/verbose 2" >> run_${ftheta}.mac
  echo "/event/verbose 0" >> run_${ftheta}.mac
  echo "/tracking/verbose 0" >> run_${ftheta}.mac
  echo "/gun/ftheta ${ftheta}" >> run_${ftheta}.mac
  echo "/run/beamOn 10000" >> run_${ftheta}.mac

  # Run the simulation with this macro file and output filename
  ./FiSim run_${ftheta}.mac

  # Move and rename the output file
  mv output.root /home/felipe/Thesis/g4sim/SingleFiberSim/data/reach_sensitive_double_cladding/angle_${ftheta}.root
  rm run_${ftheta}.mac 
done

