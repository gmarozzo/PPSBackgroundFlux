import os
import sys

runlist = open("../allruns.txt","r")
counter = 0
for line in runlist:
  if counter > 0:
    os.system("cp -r PPS_Chunk0 PPS_Chunk"+str(counter))
  run=line.strip()    
  os.system("sed -i 's/315257/"+run+"/g' PPS_Chunk"+str(counter)+"/batchScript.sh")
  counter=counter+1
