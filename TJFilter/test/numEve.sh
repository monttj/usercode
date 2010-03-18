for (( i = 1 ;  i <= 18;  i++  )) 
do
edmEventSize -v rfio:/castor/cern.ch/user/t/tjkim/MinimumBias/BeamCommissioning09-PromptReco-v2/RECO/filterout_$i.root | grep Events
done
