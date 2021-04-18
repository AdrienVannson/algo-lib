import re, os.path

dossiersInclusion = [ os.getcwd() ]
for i in range(int(input())):
    dossiersInclusion.append(os.path.abspath(input()))

fichiersSources = []
for i in range(int(input())):
    fichiersSources.append(os.path.abspath(input()))


resultats = open('output.cpp', 'w')
isPreviousLineEmpty = True # Remove consecutive empty lines

fichiersInclus = []
motsVus = set() # Utilisé pour les inclusions facultatives

def include (path, includeRecursivement):
    global isPreviousLineEmpty

    path = os.path.realpath(path)

    if path in fichiersInclus:
        return
    fichiersInclus.append(path)

    contenu = open(path, 'r').read().split('\n')

    # Mise à jour des mots vus
    motActuel = []
    for l in contenu:
        if re.match("^#include ", l):
            continue
        for c in l:
            if c.isalpha() or c.isdigit() or c == '_':
                motActuel.append(c)
            else:
                motsVus.add(''.join(motActuel))
                motActuel = []

    for ligne in contenu:
        if re.match("^#include \"*\"", ligne): # Inclusion

            if ' // ONLY_IF ' in ligne:
                ligne, motsRequis = ligne.split(' // ONLY_IF ')
                motsRequis = motsRequis.split()

                succes = False
                for m in motsRequis:
                    if m in motsVus:
                        succes = True
                if not succes:
                    continue

            nouveauFichier = re.sub("^\\#include \"(.+)\"$", "\\1", ligne)

            if includeRecursivement:
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
        elif ligne == '':
            if not isPreviousLineEmpty:
                resultats.write('\n')
                isPreviousLineEmpty = True
        elif not re.match("^#ifndef .*_HPP$", ligne) \
         and not re.match("^#define .*_HPP$", ligne) \
         and not re.match("^#endif .*_HPP", ligne):
               resultats.write(ligne + '\n')
               isPreviousLineEmpty = False


include('main.cpp', True)

for nomFichier in fichiersInclus:
    nomFichier = re.sub("^(.+)\\.h(pp)?$", "\\1.cpp", nomFichier)

    if not nomFichier == 'main.cpp' and os.path.exists(nomFichier):
        include(nomFichier, False)

for fichierSource in fichiersSources:
    include(fichierSource, False)
