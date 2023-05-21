import os
import sys

lumilist = open("LumiListD.txt","w")

runlist = open("runsD.txt","r")

for line in runlist:
#if True:
  run=str(line.strip())
  #run="315557"
  json = open("DummyJSON.json","w")
  json.write('{"'+run+'": [[1, 10000]]}')
  json.close()
  os.system("brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json -u /nb -i DummyJSON.json --hltpath HLT_ZeroBias_v6 > temp.txt")
  txt = open("temp.txt","r")
  lumi=0.
  for line in txt:
    if line.startswith("#Sum recorded"):
      lumi=float((line.split(":")[1]).strip())
  lumilist.write(run+" : "+str(lumi)+"\n")
  print(run+" : "+str(lumi))

  os.system("rm temp.txt")

runlist.close()
lumilist.close()
