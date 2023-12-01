#! /usr/bin/python3

from collections import defaultdict
import subprocess
from pathlib import Path
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
    'SQL': 'sqlite', 
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


# def parseAFLNaming(elem):
#     is_crash  = "findings/default/crashes" in elem
#     is_queued = "findings/default/queue"   in elem
    
#     metadata = os.path.basename(elem)
#     elem_dict = {}
        
#     for subelem in metadata.split(','):
#         try:
#             subelem_k, subelem_v = subelem.split(':')
#             elem_dict[subelem_k]=subelem_v
#         except:
#             elem_dict[subelem]=True
#     global CRASH_LABEL
#     global QUEUE_LABEL
    
#     if is_crash:
#         elem_dict[CRASH_LABEL]=True
#     if is_queued:
#         elem_dict[QUEUE_LABEL]=True    
#     return elem_dict


class QueueGraph:
    parentsOf = defaultdict(list)
    infoOf = {}
    origins = []
    crashes = []

    def _getElementInfo(self, element):
        is_crash  = "findings/default/crashes" in element
        is_queued = "findings/default/queue"   in element
        metadata = os.path.basename(element)
        elementInfo = {}
        for subelem in metadata.split(','):
            try:
                subelem_k, subelem_v = subelem.split(':')
                elementInfo[subelem_k]=subelem_v
            except:
                elementInfo[subelem]=True
        
        global CRASH_LABEL
        global QUEUE_LABEL
        if is_crash:
            elementInfo[CRASH_LABEL]=True
        if is_queued:
            elementInfo[QUEUE_LABEL]=True    
        
        return elementInfo
    
    def _updateParents(self, elementInfo, nodeName):
        if '+' in elementInfo[SRC]:
            src1, src2 = elementInfo['src'].split('+')
            self.parentsOf[nodeName].append(src1)
            self.parentsOf[nodeName].append(src2)
        else:
            self.parentsOf[nodeName].append(elementInfo[SRC])

    def addQueueElement(self, element):
        elementInfo = self._getElementInfo(element)
        
        nodeName = elementInfo[ID]

        self.infoOf[nodeName]=elementInfo
        if ORIG in elementInfo:
            self.origins.append(nodeName)
        else:
            self._updateParents(elementInfo, nodeName)

        return
    
    def addCrash(self, crash):
        if "README" in crash:
            return
        elementInfo = self._getElementInfo(crash)
        elementInfo['crash']=True

        nodeCrashName = 'C'+elementInfo['id']

        self.crashes.append(nodeCrashName)

        self.infoOf[nodeCrashName]=elementInfo
        self._updateParents(elementInfo, nodeCrashName)

        return
    
    def setAsNovelty(self, element):
        elementInfo = self._getElementInfo(element)
        nodeName = elementInfo[ID]
        if nodeName in self.infoOf:
            self.infoOf[nodeName]['novelty']=True
        return

    def _getGraphEdgesOfCrash(self, crash):
        queue = [crash]
        graphEdges = []

        while len(queue) != 0:
            currentNode = queue.pop(0)
            for parent in self.parentsOf[currentNode]:
                graphEdges.append( (parent, currentNode) )
                queue.append(parent)
        return graphEdges
    
    def _getGraphEdgesCrashes(self, showOnlyFromEnum=False, showOnlyNotFromEnums=False):
        totCrashPlotted = 0   
        totalGraphEdges = set()
        for crash in self.crashes:
            isFromEnum = self.crashIsFromFuzzyEnum(crash)
            if showOnlyFromEnum and not isFromEnum:
                continue
            if showOnlyNotFromEnums and isFromEnum:
                continue
            totCrashPlotted+=1
            crashEdges = self._getGraphEdgesOfCrash(crash)
            totalGraphEdges.update(crashEdges)

        return (list(totalGraphEdges),totCrashPlotted)
    
    def _calcGraphOfCrashBFS(self, crash):
        nodeVisited = []
        bfsQueue = [crash]
        bfsEdgesVisited=[] 
        while len(bfsQueue)!=0:

            currentNode = bfsQueue.pop(0)
            currentParents = self.parentsOf[currentNode]
            nodeVisited.append(currentNode)

            if 'novelty' in self.infoOf[currentNode] and '+cov' in self.infoOf[currentNode]:
                # avoud update queue if is a novelty element
                continue
            
            bfsQueue += currentParents

            for parents in currentParents:
                bfsEdgesVisited.append( (parents, currentNode) )
        return (bfsEdgesVisited, nodeVisited)

    def analizeCrash(self, crash):
        nodeVisited = []
        bfsQueue = [crash]
        bfsEdgesVisited=[] 
        noveltyEncountered = []
        originEncountered = []
        while len(bfsQueue)!=0:

            currentNode = bfsQueue.pop(0)
            currentParents = self.parentsOf[currentNode]
            nodeVisited.append(currentNode)

            if 'novelty' in self.infoOf[currentNode] and '+cov' in self.infoOf[currentNode]:
                # avoud update queue if is a novelty element
                noveltyEncountered.append(currentNode)
                continue
            
            bfsQueue += currentParents

            for parents in currentParents:
                bfsEdgesVisited.append( (parents, currentNode) )
        
        fromNovelty = True
        for origin in self.origins:
            if origin in nodeVisited:
                originEncountered.append(origin)
                fromNovelty = False

        # print(f'Crash: {crash}, #Novelty: {len(noveltyEncountered)}, #Origin: {len(originEncountered)}, Entirely derived from novelties {fromNovelty} ')
        return (crash, len(noveltyEncountered),len(originEncountered))

    def analizeCrashes(self):
        crashInfo = []
        noFromEnums         = 0
        fromEnums           = 0
        indirectlyFromEnums = 0

        for crash in self.crashes:
            crashInfo.append(self.analizeCrash(crash))

        for ci in crashInfo:
            if ci[1] == 0:
                # shore not from novelty enums:
                noFromEnums+=1
            if ci[2] == 0:
                fromEnums+=1
            if ci[1] != 0 and ci[2] != 0:
                indirectlyFromEnums +=1
        
        print(f'TOT: {len(crashInfo)}, from enums: {fromEnums}, indireclty from enums {indirectlyFromEnums}, not from enums {noFromEnums}')

        return

    def _getGraphEdgesOfCrashBFS(self, crash):
        
        edges, nodes = self._calcGraphOfCrashBFS(crash)
        
        return edges
    
    def _getGraphEdgesCrashesBFS(self,showOnlyFromEnum=False, showOnlyNotFromEnums=False):
        totCrashPlotted = 0   
        totalGraphEdgesBFS = set()
        for crash in self.crashes:

            isFromEnum = self.crashIsFromFuzzyEnum(crash)
            
            if showOnlyFromEnum and not isFromEnum:
                continue
            if showOnlyNotFromEnums and isFromEnum:
                continue   
            totCrashPlotted+=1
            crashEdgesBFS = self._getGraphEdgesOfCrashBFS(crash)
            totalGraphEdgesBFS.update(crashEdgesBFS)

        return (list(totalGraphEdgesBFS),totCrashPlotted)


    # return True if the crash is derived entirely from novelty 
    # exposed by fuzz enum
    def crashIsFromFuzzyEnum(self, crash):
        edges, nodes = self._calcGraphOfCrashBFS(crash)
        for origin in self.origins:
            if origin in nodes:
                return False
        return True
    
    def getReportCrashes(self):
        fuzzy = 0
        no_fuzzy = 0
        for crash in self.crashes:
            if self.crashIsFromFuzzyEnum(crash):
                fuzzy +=1
            else:
                no_fuzzy+=1
        print(f'fuzzy: {fuzzy}, no fuzzy: {no_fuzzy}')


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
    
    if not (fuzzer == 'enumetric_asan' and library == 'libtiff' and sut == 'tiff_read_rgba_fuzzer'):
        return
    
    global TMP_DIR
    
    output_path = os.path.join(TMP_DIR, 'magma_id_result')
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
    
    
        # qt = QueueGraph()
        # for member in tar.getmembers():
        #     if 'findings/default/queue'   not in member.name and \
        #     'findings/default/crashes' not in member.name:
        #         continue
        #     print(irun, member)
        #     if ID not in member.name:
        #         continue
            
        #     if "queue" in member.name:
        #         qt.addQueueElement(member.name)
        #     if "crashes" in member.name:
        #         qt.addCrash(member.name)
            
        #     metadata = parseAFLNaming(member.name)
        #     if ID not in metadata:
        #         continue
        #     print(metadata)
    
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
    start_analisys_path = os.path.join(dir_file_path,'start_analisys.sh')
    print(start_analisys_path)
    env = os.environ
    
    print(fuzzer,library,sut)
    
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

    # opt.add_argument('-c', help="path of crash")
    opt.add_argument('path_workdir_magma', nargs=argparse.REMAINDER, help="Path to magma workdir")
    args = opt.parse_args()

    global WORKDIR 
    WORKDIR = args.path_workdir_magma[0]
    
    global MAGMA_FUZZERS_RUN_PREFIX
    global FUZZERS 
    FUZZERS = os.listdir( os.path.join(WORKDIR,MAGMA_FUZZERS_RUN_PREFIX) )
    
    print(FUZZERS) 
    
    global MAINDICT
    MAINDICT = dod()
    for fuzzer in FUZZERS:
        for library in os.listdir( os.path.join(WORKDIR,MAGMA_FUZZERS_RUN_PREFIX, fuzzer) ):
            for sut in os.listdir( os.path.join(WORKDIR,MAGMA_FUZZERS_RUN_PREFIX, fuzzer, library) ):
                MAINDICT[fuzzer][library][sut]=os.listdir( os.path.join(WORKDIR,MAGMA_FUZZERS_RUN_PREFIX, fuzzer, library, sut) )
    print(MAINDICT)
    
    for fuzzer in MAINDICT:
        for library in MAINDICT[fuzzer]:
            for sut in MAINDICT[fuzzer][library]:
                analyzeRun(fuzzer,library,sut)
    
    


if __name__ == "__main__":
    main()
