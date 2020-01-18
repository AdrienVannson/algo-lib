import re, os.path

dossiersInclusion = [ os.getcwd() ]
for i in range(int(input())):
	dossiersInclusion.append(os.path.abspath(input()))

fichiersSources = []
for i in range(int(input())):
	fichiersSources.append(os.path.abspath(input()))


resultats = open('output.cpp', 'w')

fichiersInclus = []


def inclure (chemin, inclureRecursivement=True):
	chemin = os.path.realpath(chemin)

	if chemin in fichiersInclus:
		return
	fichiersInclus.append(chemin)

	contenu = open(chemin, 'r').read().split('\n')

	for ligne in contenu:
		if re.match("^#include \"*\"", ligne): # Inclusion

			nouveauFichier = re.sub("^\\#include \"(.+)\"$", "\\1", ligne)

			if inclureRecursivement:
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

							inclure(fichier)
							succes = True
							break

						if os.path.realpath(dossierInclusion + '/' + (hauteur * '../')) == '/':
							break

						hauteur += 1

				if not succes:
					print("ERREUR", nouveauFichier)
		else:
			if not ligne == '' \
			   and not re.match("^#ifndef .*_HPP$", ligne) \
			   and not re.match("^#define .*_HPP$", ligne) \
			   and not re.match("^#endif .*_HPP", ligne):
				resultats.write(ligne + '\n')
				resultats.write(ligne + '\n')


inclure('main.cpp')

for nomFichier in fichiersInclus:
	nomFichier = re.sub("^(.+)\\.h(pp)?$", "\\1.cpp", nomFichier)

	if not nomFichier == 'main.cpp' and os.path.exists(nomFichier):
		inclure(nomFichier, False)

for fichierSource in fichiersSources:
	inclure(fichierSource, False)
