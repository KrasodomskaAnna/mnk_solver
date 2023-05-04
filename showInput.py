import glob, os
import subprocess
import filecmp
import sys

program_path = "out/build/x64-Debug/NKMSolver.exe"
meld_path = 'C:/Program Files (x86)/Meld/Meld.exe'
meld_args = ""
failed = []

os.chdir("./tests")
files = glob.glob("*.in")
os.chdir("..")
for file in files:
    basename = os.path.splitext(file)[0]
    in_path = "./tests/"+basename+".in"
    out_path = './res/'+basename+'.out'
    ref_path = "./tests/"+basename+".out"
    myinput = open(in_path)
    myoutput = open(out_path)

    if(myinput and myoutput):
        if(not filecmp.cmp(out_path, ref_path, shallow=False)):
            failed.append(basename)


if(len(sys.argv) == 1):
    print("Type test number")
    exit()
else:
    number = sys.argv[1]
    in_path = "./tests/"+number+".in"
    out_path = './res/'+number+'.out'
    ref_path = "./tests/"+number+".out"
    meld_args = meld_args+" --diff "+ in_path + " " + out_path
#print(meld_args)
subprocess.call(meld_path+meld_args)
#os.system(meld_path)