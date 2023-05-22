#!/bin/bash
set -euo pipefail

if [ -z ${_CONDOR_SCRATCH_DIR+x} ]; then
  #running locally
  runninglocally=true
  _CONDOR_SCRATCH_DIR=$(mktemp -d)
  SUBMIT_DIR=$(pwd)
else
  runninglocally=false
  SUBMIT_DIR=$1
fi

cd $SUBMIT_DIR
eval $(scram ru -sh)

cp ../../../../../../bin/slc7_amd64_gcc10/FWLitePixelsFlux  $_CONDOR_SCRATCH_DIR
cd $_CONDOR_SCRATCH_DIR

echo 'Running at:' $(date)
echo path: `pwd`

#cmsRunStatus=   #default for successful completion is an empty file
./FWLitePixelsFlux section==315557 > log.txt

echo "Files on node:"
ls -la

#delete mela stuff and $USER.cc
#I have no idea what $USER.cc is
#rm -f br.sm1 br.sm2 ffwarn.dat input.DAT process.DAT "$USER.cc"

#delete submission scripts, so that they are not copied back (which fails sometimes)
#rm -f run_cfg.py batchScript.sh

echo '...done at' $(date)

#note cping back is handled automatically by condor
if $runninglocally; then
  cp testoutput.root* *.txt *.gz $SUBMIT_DIR
fi

exit $cmsRunStatus
