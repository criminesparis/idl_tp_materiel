# Ma montagne mémoire

Machine: AMD Ryzen 5 4500U (WSL2 / Linux)

| Niveau | Taille déduite de la courbe | Taille annoncée (TP 1) | Débit (Go/s) |
|---|---|---|---|
| L1 | Chute après 32 K | 32 KiB | ~60 Go/s |
| L2 | Chute après 512 K | 512 KiB | ~50 Go/s |
| L3 | Chute majeure entre 2 M et 4 M | 4 MiB | ~18 Go/s |
| RAM | Au-delà de 4 M | 3,5 Go (WSL2) | ~10 Go/s |

Taille de ligne déduite du pas: 64 octets (annoncée: 64 octets)

Réponses aux questions 1 à 5:

### Question 1 : 
Sur la coupe à pas 1 (`mountain_stride1.png`), on observe des inflexions et des chutes de débit à trois seuils caractéristiques :
- Vers 32 KiB : légère baisse du débit, correspondant à la sortie du cache de données L1d (32 KiB par cœur).
- Vers 512 KiB : fin du palier du cache L2 (512 KiB par cœur).
- Entre 2 MiB et 4 MiB : chute brutale du débit, marquant la limite du cache L3 partagé (4 MiB au total). Au-delà de 4 MiB, les données ne tiennent plus en cache et proviennent de la RAM.

Ces seuils concordent avec la topologie relevée au TP 1.

### Question 2 :
D'après les mesures à pas 1 :
- Débit en L1 : ~60 Go/s
- Débit en L2 : ~50 Go/s
- Débit en L3 : ~18 à 50 Go/s (selon le niveau d'occupation)
- Débit en RAM : ~10 Go/s 

Rapport L1 / RAM : Le débit en cache L1d (~60 Go/s) est environ 6 fois supérieur au débit moyen de la mémoire vive RAM (~10 Go/s).


### Question 3 : 
Pour 64 Mo, en mémoire RAM :
1. Pourquoi le débit décroît : La mémoire vive transfère les données par blocs complets de 64 octets (lignes de cache). Lorsque le pas augmente, on saute des éléments et on exploite moins de mots utiles par ligne chargée dans le processeur (perte de localité spatiale).
2. Pourquoi il cesse de décroître : À partir du pas 8 (soit 8 × 8 octets = 64 octets), chaque accès mémoire pointe vers une nouvelle ligne de cache. Charger un pas de 8, 12, 16 ou 32 demande alors exactement le même travail d'aller-retour mémoire : rapatrier une ligne de 64 octets pour n'en lire qu'un seul mot.
3. Déduction de la taille de ligne de cache : 8 (pas de saturation) x 8 octets = 64 octets. Cette valeur correspond exactement à celle donnée par getconf LEVEL1_DCACHE_LINESIZE (64 octets).



### Question 4 : 
Sur le graphique 3D, le pas n'a aucun effet pour la taille L1 (jusqu'à 32K): la surface semble plutôt plate et haute tout au long de l'axe des pas?
Pourquoi??


### Question 5 :
- Sur x86-64 (AMD Zen 2) : Les paliers L1 → L2 → L3 → RAM sont très nettement marqués en "marches d'escalier", avec une chute très raide au niveau de la RAM.
- Sur Apple Silicon (Apple M1/M2/M3) : La coupe à pas 1 est beaucoup plus plate grâce à une mémoire unifiée à très large bus (jusqu'à 100-400 Go/s) et un préchargeur matériel (*hardware prefetcher*) extrêmement agressif qui masque la latence des accès séquentiels en RAM. Les caches y sont plus visibles en faisant varier le pas (*stride*) qu'en faisant varier la taille.
