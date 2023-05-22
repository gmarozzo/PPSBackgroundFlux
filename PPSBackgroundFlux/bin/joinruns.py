runsA = open("runsA.txt","r")
runsB = open("runsB.txt","r")
runsC = open("runsC.txt","r")
runsD = open("runsD.txt","r")

runs = open("allruns.txt","w")

for line in runsA:
  runs.write(line)
for line in runsB:
  runs.write(line)
for line in runsC:
  runs.write(line)
for line in runsD:
  runs.write(line)

runs.close()
