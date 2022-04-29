import re, os.path

dossiersInclusion = [ os.getcwd() ]
for i in range(int(input())):
    dossiersInclusion.append(os.path.abspath(input()))

fichiersSources = []
for i in range(int(input())):
    fichiersSources.append(os.path.abspath(input()))


isPreviousLineEmpty = True # Remove consecutive empty lines

includedFiles = []
words = set() # All the words contained in the files

firstLines = set() # Lines that should be added only once, at the beginning of the file
outputLines = []

def include(path, isRecursive):
    global isPreviousLineEmpty

    path = os.path.realpath(path)

    if path in includedFiles:
        return
    includedFiles.append(path)

    content = open(path, 'r').read().split('\n')

    # Words contained in the file
    currentWord = []
    for l in content:
        if re.match("^#include ", l):
            continue
        for c in l + ' ':
            if c.isalpha() or c.isdigit() or c == '_':
                currentWord.append(c)
            else:
                words.add(''.join(currentWord))
                currentWord = []

    for line in content:
        # The line should appear only once, at the beginning of the file
        if re.match("^#include <", line) or line == "using namespace std;":
            firstLines.add(line)

        # Include
        elif re.match("^#include \"*\"", line):
            if ' // ONLY_IF ' in line:
                line, motsRequis = line.split(' // ONLY_IF ')
                motsRequis = motsRequis.split()

                success = False
                for w in motsRequis:
                    if w in words:
                        success = True
                if not success:
                    continue

            if isRecursive:
                nouveauFichier = re.sub("^\\#include \"(.+)\"$", "\\1", line)

                succes = False

                for dossierInclusion in dossiersInclusion:
                    hauteur = 0

                    while True:
                        fichierSeul = os.path.basename(nouveauFichier)
                        dossier = os.path.realpath(dossierInclusion + '/' + (hauteur * '../') + os.path.dirname(nouveauFichier))
                        fichier = dossier + '/' + fichierSeul

                        if os.path.exists(fichier):
                            if not dossier in dossiersInclusion:
                                dossiersInclusion.append(dossier)

                            include(fichier, True)
                            succes = True
                            break

                        if os.path.realpath(dossierInclusion + '/' + (hauteur * '../')) == '/':
                            break

                        hauteur += 1

                if not succes:
                    print("ERREUR", nouveauFichier)

        # Empty line
        elif line == '':
            if not isPreviousLineEmpty:
                outputLines.append('')
                isPreviousLineEmpty = True

        # The header guards are not written in the output file
        elif not re.match("^#ifndef .*_HPP$", line) \
         and not re.match("^#define .*_HPP$", line) \
         and not re.match("^#endif .*_HPP", line):
               outputLines.append(line)
               isPreviousLineEmpty = False


include('main.cpp', True)

# Add the .cpp files corresponding to the .hpp files
for header in includedFiles:
    source = re.sub("^(.+)\\.h(pp)?$", "\\1.cpp", header)

    if not source == 'main.cpp' and os.path.exists(source):
        include(source, False)

for fichierSource in fichiersSources:
    include(fichierSource, False)

# Write output.cpp
output = open('output.cpp', 'w')

for l in sorted(list(firstLines)):
    output.write(l + '\n')
output.write('\n')

for l in outputLines:
    output.write(l + '\n')
