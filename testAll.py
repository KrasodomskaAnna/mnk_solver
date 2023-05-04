import glob, os
from subprocess import Popen, PIPE
import filecmp

program_path = "cmake-build-debug/mnksolver.exe"
meld_path = "C:/Program Files (x86)/Meld/Meld.exe"
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
    myoutput = open(out_path,'w')

    print("Test "+basename+":", end=" ")
    p = Popen([program_path],stdin=myinput, stdout=myoutput)
    p.wait()
    myoutput.flush()

    if(filecmp.cmp(out_path, ref_path, shallow=False)):
        print("✅")
    else:
        print("❌")
        failed.append(basename)


