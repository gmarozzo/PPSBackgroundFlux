import requests
import sys
import os

output_file = open('runfiles.txt','w')
input_file = open('runfilestemp.txt','r')

for line in input_file:
    
    output_file.write(' inputFiles_.push_back("root://cms-xrd-global.cern.ch/')
    output_file.write(line.split()[0]+'");')
    output_file.write("\n")

input_file.close()
output_file.close()
#os.remove("runfilestemp.txt")
