###################################### ######################################
###                 This file removes all macros from a source file
###                 (excl. those macros that are coming from a header)
###                 Includes are preserved...
###                 Call: remove_macros.py /path/inputfile.cpp /path/outputfile.cpp log-file.csv
###################################### ######################################
import argparse
import os
import subprocess
import sys
import re
import io

parser = argparse.ArgumentParser(description='Expand all macros from file while keeping includes')
parser.add_argument('file', type=str, nargs=1,
                   help='the file that we want to preprocess')
parser.add_argument('output', type=str, nargs=1,
                   help='output file')
parser.add_argument('csvfile', type=str, nargs=1,
                   help='csv file, number of lines before and after will be saved in csv')
args = parser.parse_args()

inputfile: str = args.file[0]
outputfile: str = args.output[0]
csvfile: str = args.csvfile[0]

#print(inputfile)
#print(outputfile)

try:
    ### Step 1. Read file and comment out all includes with //MACRO-REMOVAL
    lines = [line for line in io.open(inputfile, "r", encoding="iso-8859-1")]
    nooflinesbefore: int = len(lines)

    for lineindex in range(len(lines)):
        if lines[lineindex].startswith("#include "):
            lines[lineindex] = lines[lineindex].replace("#include","//MACRO-REMOVAL #include")
        elif "#include" in lines[lineindex]:
            if not (lines[lineindex].startswith("//") or lines[lineindex].startswith("/*")):
                raise Exception("was not able to comment out include")

    with io.open(outputfile, 'w', encoding="iso-8859-1") as file:
        for line in lines:
            file.write(line)

    ### Step 2. Call preprocessor
    cmdd_transform = ["clang++", outputfile, "-CC", "-E"]
    p = subprocess.run(cmdd_transform, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False, timeout=20)
    err, output = p.stdout, p.stderr # iwyu returns the output to stderr, so the other way round
    # if err != b'':
    #     print("Error for {} with {}".format(args.file, str(err)), file=sys.stderr)

    linesprep = [currow+"\n" for currow in err.decode("iso-8859-1").split("\n")]
    if linesprep[-1] == "\n":
        del linesprep[-1]

    ### Step 3. Remove all preprocessing debug information that are append at the beginning
    linesprepfinal = []
    for lineindex in range(len(linesprep)):
        rematch = re.search("^# [0-9].*", linesprep[lineindex])
        if not rematch:
            linesprepfinal.append(linesprep[lineindex])

    ### Step 4. Remove comment from all includes
    with io.open(outputfile, 'w', encoding="iso-8859-1") as file:
        for lineindex in range(len(linesprepfinal)):
            if linesprepfinal[lineindex].startswith("//MACRO-REMOVAL #include"):
                linesprepfinal[lineindex] = linesprepfinal[lineindex].replace("//MACRO-REMOVAL #include", "#include")
            file.write(linesprepfinal[lineindex])

    ### Step 5. Log number of lines before and after removing macros -- helpful to detect errors,
    # e.g. if some header was included by mistake

    with open(csvfile, "a") as currentfile:
        newstring: str = "{},{},{}\n".format(inputfile, nooflinesbefore, len(linesprepfinal))
        currentfile.write(newstring)


except Exception as e:
    print("ERROR for {}".format(inputfile), file=sys.stderr)
    print(str(e), file=sys.stderr)

    if os.path.exists(outputfile):
        os.remove(outputfile)















