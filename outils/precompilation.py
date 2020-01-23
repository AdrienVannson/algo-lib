import re, os.path

dossiersInclusion = [ os.getcwd() ]
for i in range(int(input())):
	dossiersInclusion.append(os.path.abspath(input()))

fichiersSources = []
for i in range(int(input())):
	fichiersSources.append(os.path.abspath(input()))


resultats = open('output.cpp', 'w')

fichiersInclus = []
motsVus = set() # Utilisé pour les inclusions facultatives


def inclure (chemin, inclureRecursivement=True):
	chemin = os.path.realpath(chemin)

	if chemin in fichiersInclus:
		return
	fichiersInclus.append(chemin)

	contenu = open(chemin, 'r').read().split('\n')

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


inclure('main.cpp')

for nomFichier in fichiersInclus:
	nomFichier = re.sub("^(.+)\\.h(pp)?$", "\\1.cpp", nomFichier)

	if not nomFichier == 'main.cpp' and os.path.exists(nomFichier):
		inclure(nomFichier, False)

for fichierSource in fichiersSources:
	inclure(fichierSource, False)
