import glob, os
from subprocess import Popen, PIPE
import filecmp
import sys

program_path = "cmake-build-debug/mnksolver.exe"
meld_path = "C:/Program Files (x86)/Meld/Meld.exe"
failed = []

if(len(sys.argv) == 1):
    print("Type test number")
    exit()

number = sys.argv[1]

in_path = "./tests/"+number+".in"
out_path = './res/'+number+'.out'
ref_path = "./tests/"+number+".out"
myinput = open(in_path)
myoutput = open(out_path,'w')

print("Test "+number+":", end=" ")
p = Popen([program_path],stdin=myinput, stdout=myoutput)
p.wait()
myoutput.flush()

if(filecmp.cmp(out_path, ref_path, shallow=False)):
    print("✅")
else:
    print("❌")


