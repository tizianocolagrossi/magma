#! /usr/bin/python3

from collections import defaultdict
import subprocess
from pathlib import Path
from rich.prompt import Prompt
from rich import print
import argparse
import tempfile
import tarfile
import shutil
import os
###
# Global Variables
###
global WORKDIR 
global FUZZERS 
global MAINDICT
global TMP_DIR
TMP_DIR = tempfile.mkdtemp()

MAGMA_FUZZERS_RUN_PREFIX = 'ar'
MAGMA_FINDINGS           = 'findings'
AFL_DEFAULT              = 'default'
AFL_CRASHES              = 'crashes'
RUN_DATA_COMPRESSED_NAME = 'ball.tar'

CRASHID_ANALISYS         = 'crash_id'


BUGPREFIX_LIBRARY = {
    'PNG': 'libpng', 
    'TIF': 'libtiff', 
    'XML': 'libxml2', 
    'PDF': 'poppler', 
    'SSL': 'openssl', 
    'SQL': 'sqlite3', 
    'PHP': 'php', 
    'LUA': 'lua', 
    'SND': 'libsndfile' }

dod = lambda: defaultdict(dod)

## used in def parseAFLNaming(elem) for 
## info about item 
CRASH_LABEL = 'crash'
QUEUE_LABEL = 'queue'
ID    = 'id'
SRC   = 'src'
TIME  = 'time'
EXECS = 'execs'
OP    = 'op'
ORIG  = 'orig'


def untar(pathTarFile, outputDir):
    with tarfile.open(pathTarFile, 'r') as tf:
        print("opened tarfile")
        tf.extractall(path=outputDir)
        print("all file extracted")
    return

def getCrashPaths(tarfile_path):
    tar = tarfile.open(tarfile_path, 'r')
    crashes = [x for x in tar.getmembers() if 'crashes' in x.name]
    return crashes

def hasCrash(tarfile_path):
    return True if len(getCrashPaths(tarfile_path)) > 1 else False

def analyzeRun(fuzzer, library, sut):
    
    global TMP_DIR
    
    output_path = os.path.join(TMP_DIR, f'magma_id_result_run')
    if not os.path.isdir(output_path):
        os.mkdir(output_path)
    
    for irun in os.listdir(os.path.join(WORKDIR,MAGMA_FUZZERS_RUN_PREFIX, fuzzer, library, sut)):
        
        tar_path = os.path.join(WORKDIR,MAGMA_FUZZERS_RUN_PREFIX, fuzzer, library, sut, irun, RUN_DATA_COMPRESSED_NAME)
        
        if not hasCrash(tar_path):
            print('no crash in ',tar_path)
            continue
  
        print('crash in ',tar_path)
        
        
        print('analizyng ',fuzzer, library, sut, irun)
        tar = tarfile.open(tar_path, 'r')
        
        crashToMagmaId(tar_path, output_path)
    
    
    return

def crashToMagmaId(tarfile_path, output_path):   
    global TMP_DIR
    
    path_component = tarfile_path.split('/')
    fuzzer  = path_component[-5]
    library = path_component[-4]
    sut     = path_component[-3]
    irun    = path_component[-2]
    # print(path_component)
    print(fuzzer, library, sut, irun)
    
    tar = tarfile.open(tarfile_path, 'r')
    for member in tar.getmembers():
            if 'crashes' not in member.name:
                continue            
            tar.extract(member, path=TMP_DIR)
    
    extracted_crash_path = os.path.join(TMP_DIR, MAGMA_FINDINGS, AFL_DEFAULT, AFL_CRASHES)
    

    dir_file_path = os.path.dirname(os.path.realpath(__file__))
    # build_analisys_container_path = os.path.join(dir_file_path,'buildAnalisys.sh')
    start_analisys_path = os.path.join(dir_file_path,'start_analisys.sh')
    # print(start_analisys_path)
    env = os.environ
    
    print(fuzzer,library,sut)
    
    
    # p = subprocess.Popen( [build_analisys_container_path],env=env, stdout=subprocess.PIPE )
    
    env["FUZZER"]     = fuzzer
    env["TARGET"]     = library
    env["PROGRAM"]    = sut
    env["ANALISYS"]   = CRASHID_ANALISYS
    env["INPUT_DIR"]  = extracted_crash_path+'/'
    env["OUTPUT_DIR"] = output_path+'/'
    env["IRUN"]       = irun
    
    p = subprocess.Popen( [start_analisys_path],env=env, stdout=subprocess.PIPE )
    out, err = p.communicate()
    print(out.decode(), err)
    p.wait()
    
    shutil.rmtree(extracted_crash_path)
    
    return 

def main():
    opt = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)

    opt.add_argument('-p', help="program to analize")
    opt.add_argument('-c', help="crash id to analize", required=True)
    opt.add_argument('path_workdir_magma', nargs=argparse.REMAINDER, help="Path to magma workdir")
    args = opt.parse_args()

    global WORKDIR 
    WORKDIR = args.path_workdir_magma[0]
    
    global MAGMA_FUZZERS_RUN_PREFIX
    global FUZZERS 
    FUZZERS = os.listdir( os.path.join(WORKDIR,MAGMA_FUZZERS_RUN_PREFIX) )
    
    print(FUZZERS) 
    fuzzer_selected = Prompt.ask("Select crashes of which fuzzer? ", choices=FUZZERS, default=FUZZERS[-1])
    print(fuzzer_selected) 
    
    global MAINDICT
    MAINDICT = dod()
    for fuzzer in FUZZERS:
        for library in os.listdir( os.path.join(WORKDIR,MAGMA_FUZZERS_RUN_PREFIX, fuzzer) ):
            for sut in os.listdir( os.path.join(WORKDIR,MAGMA_FUZZERS_RUN_PREFIX, fuzzer, library) ):
                MAINDICT[fuzzer][library][sut]=os.listdir( os.path.join(WORKDIR,MAGMA_FUZZERS_RUN_PREFIX, fuzzer, library, sut) )
    # print(MAINDICT)
    
    
    print(args.c)
    sut = args.p
    library = BUGPREFIX_LIBRARY[args.c[:3]]
    if not sut:  
        for sut in MAINDICT[fuzzer_selected][library]:
            print(fuzzer_selected,library,sut)
            analyzeRun(fuzzer_selected,library,sut)
    else:
            analyzeRun(fuzzer_selected,library,sut)
        
        


if __name__ == "__main__":
    main()
