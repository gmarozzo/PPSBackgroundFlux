import os,sys

inputA = open("runsA.txt","r")
outputA  =open("filesA.C","w")

outputA.write("void addfilenamesA (int run,std::vector<std::string>& inputFiles_, float& lumi){\n")
for line in inputA:
  outputA.write("  if(run =="+line.strip()+"){\n")
  os.system("dasgoclient -query='file,dataset=/ZeroBias/Run2018A-12Nov2019_UL2018-v2/AOD run="+line.strip()+"' > run.txt")   
  tempinput = open("run.txt","r")
  for line2 in tempinput:
    outputA.write('    inputFiles_.push_back("root://cms-xrd-global.cern.ch/'+line2.strip()+'");\n')
  tempinput.close()
  lumiA = open("LumiListA.txt","r")
  for line2 in lumiA:
    if(line.strip()==line2.split(":")[0].strip()):
      lumi=line2.split(":")[1].strip()
  outputA.write('    lumi = '+lumi+";\n")
  outputA.write("}\n")
outputA.write("}")

inputA.close()
outputA.close()

inputB = open("runsB.txt","r")
outputB  =open("filesB.C","w")

outputB.write("void addfilenamesB (int run,std::vector<std::string>& inputFiles_, float& lumi){\n")
for line in inputB:
  outputB.write("  if(run =="+line.strip()+"){\n")
  os.system("dasgoclient -query='file,dataset=/ZeroBias/Run2018B-12Nov2019_UL2018-v2/AOD run="+line.strip()+"' > run.txt")
  tempinput = open("run.txt","r")
  for line2 in tempinput:
    outputB.write('    inputFiles_.push_back("root://cms-xrd-global.cern.ch/'+line2.strip()+'");\n')
  tempinput.close()
  lumiB = open("LumiListB.txt","r")
  for line2 in lumiB:
    if(line.strip()==line2.split(":")[0].strip()):
      lumi=line2.split(":")[1].strip()
  outputB.write('    lumi = '+lumi+";\n")
  outputB.write("}\n")
outputB.write("}")

inputB.close()
outputB.close()

inputC = open("runsC.txt","r")
outputC  =open("filesC.C","w")

outputC.write("void addfilenamesC (int run,std::vector<std::string>& inputFiles_, float& lumi){\n")
for line in inputC:
  outputC.write("  if(run =="+line.strip()+"){\n")
  os.system("dasgoclient -query='file,dataset=/ZeroBias/Run2018C-12Nov2019_UL2018_rsb-v1/AOD run="+line.strip()+"' > run.txt")
  tempinput = open("run.txt","r")
  for line2 in tempinput:
    outputC.write('    inputFiles_.push_back("root://cms-xrd-global.cern.ch/'+line2.strip()+'");\n')
  tempinput.close()
  lumiC = open("LumiListC.txt","r")
  for line2 in lumiC:
    if(line.strip()==line2.split(":")[0].strip()):
      lumi=line2.split(":")[1].strip()
  outputC.write('    lumi = '+lumi+";\n")
  outputC.write("}\n")
outputC.write("}")

inputC.close()
outputC.close()

inputD = open("runsD.txt","r")
outputD  =open("filesD.C","w")

outputD.write("void addfilenamesD (int run,std::vector<std::string>& inputFiles_, float& lumi){\n")
for line in inputD:
  outputD.write("  if(run =="+line.strip()+"){\n")
  os.system("dasgoclient -query='file,dataset=/ZeroBias/Run2018D-12Nov2019_UL2018_rsb-v1/AOD run="+line.strip()+"' > run.txt")
  tempinput = open("run.txt","r")
  for line2 in tempinput:
    outputD.write('    inputFiles_.push_back("root://cms-xrd-global.cern.ch/'+line2.strip()+'");\n')
  tempinput.close()
  lumiD = open("LumiListD.txt","r")
  for line2 in lumiD:
    if(line.strip()==line2.split(":")[0].strip()):
      lumi=line2.split(":")[1].strip()
  outputD.write('    lumi = '+lumi+";\n")
  outputD.write("}\n")
outputD.write("}")

inputD.close()
outputD.close()

#os.system("dasgoclient -query='file,dataset=/ZeroBias/Run2018A-12Nov2019_UL2018-v2/AOD run=315557' > run.txt")
