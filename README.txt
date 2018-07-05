1.
Caloian George
332CC

2.
Utilizare Aplicatie
Taste
Jucator 1 - A - deplasare stanga
			D - deplasare dreapta
			S - Invincibilitate
			W - lovitura de sabie
Jucator 2 - Sageta stanga - deplasare stanga
			Sageata dreapta - deplasare dreapta
			Sageata jos - Invincibilitate
			P - Lovitura de sabie

3.
Structuri folosite : "Cavaler" folosita pentru cei 2 jucatori
					Contine campuri pentru:
						directie deplasare
						imposibilitate intrerupere animatie
						coordonate X Y
						vulnerabilitate lovituri
						stari : Idle , Run , Attack , Die , Block
						vectori pentru stocarea coordonatelor fiecarui frame al fiecare animatii
						valori viteze swap al frameurilor in diferite animatii

4.Probleme aparute
-Timing actiune->consecinta (lovitura - > cadere)
-Orientare Blocaj (atac de la spate)
-interpretare fisier XML
