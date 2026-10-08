# TP 2: la montagne mémoire

Objectif: mesurer le débit de lecture de la mémoire de votre machine en
fonction de la taille des données et du pas d'accès, et en déduire la
hiérarchie de caches. C'est la figure du cours (*memory mountain*, Bryant et
O'Hallaron), reproduite sur votre machine. Durée: 2 h. Rendu: `mountain.csv`,
les figures, et les réponses dans `montagne.md`.

## 1. Le programme de mesure

`mountain.c` lit un tableau de `size` octets avec un pas de `stride`
éléments de 8 octets, et répète la lecture jusqu'à avoir lu au moins 256 Mo,
pour que la mesure dure assez longtemps. Il garde le meilleur de plusieurs
essais et affiche le débit en Mo/s. Lisez-le: la fonction `test` utilise
quatre accumulateurs; demandez-vous pourquoi, puis essayez avec un seul.

```bash
make
./mountain > mountain.csv        # 1 à 3 minutes, fermez les autres programmes
python3 plot_mountain.py mountain.csv
```

Le script produit `mountain_3d.png` (la montagne) et `mountain_stride1.png`
(une coupe à pas 1: débit en fonction de la taille).

## 2. Lire la montagne

Note : malgré plusieurs essais, je ne perçois pas de paliers clairs sur ma montagne.

1. Sur la coupe à pas 1, repérez les paliers. À quelles tailles le débit
   chute-t-il? Comparez avec les tailles de L1, L2 et L3 du TP 1.

Réponse : Le débit chute à 32K, 1M et 16 M.
Les tailles des caches du TP 1 sont de :
384KiB/10MiB/18MiB, soit 48KiB/1MiB par coeur (8 coeurs) pour L1 et L2. Le cache 3 est partagé entre les coeurs. Les tailles des coeurs et de palliers correspondent donc.

2. Quel est le débit en L1, en L2, en L3, en mémoire vive? Quel rapport
   entre L1 et la mémoire?

Réponse : En L1, le débit vaut 55 Go/s ; en L2, 44 Go/s ; et en L3, 10 Go/s. Plus la mémoire est proche du lieu de calcul, plus le débit est grand.


3. Pour une taille qui tient en mémoire vive seulement (64 Mo ou plus),
   tracez le débit en fonction du pas. Pourquoi décroît-il, et pourquoi
   cesse-t-il de décroître à partir d'un certain pas? Déduisez-en la taille
   de ligne de cache. Comparez avec `getconf LEVEL1_DCACHE_LINESIZE` ou
   `sysctl hw.cachelinesize`.

Réponse : Cf mountain_stride2.png (coupe à 128 M).
Le débit décroît jusqu'à un pas de 16 : on passe de 14 à 1.5 Go/s, soit une division par environ 9.
Ma taille de ligne est 64 octets (`getconf LEVEL1_DCACHE_LINESIZE`), soit 8 élements de 8 octets.
J'ai très mal compris.


4. Pour une taille qui tient en L1, le pas a-t-il un effet? Pourquoi?

Réponse : Cf mountain_stride2.png (coupe à 16K). A 64 Mo, le débit était divisé par 6 tandis que pour une taille qui tient dans le cache L1 (16 Ko), le pas n'a pas d'effet sensible (passage de 60 à 45 Go/s). Tout tient dans le cache, donc il n'y a pas besoin de passer à un cache plus éloigné.

5. Comparez votre montagne avec celle d'un camarade sur une autre
   architecture (Apple M contre x86-64, par exemple). Qu'est-ce qui
   change: les paliers, les débits, la pente?

## Note pour les Mac Apple Silicon

Sur un Apple M, la coupe à pas 1 est presque plate: la mémoire unifiée est
très rapide et le préchargeur matériel masque la latence des accès
séquentiels, si bien que le débit en mémoire vive approche celui du cache.
Les caches se voient mieux dans la dimension du pas: à grande taille, le
débit chute d'un facteur 10 entre le pas 1 et le pas 16, et ne bouge plus
au-delà. Que vaut 16 x 8 octets? Le pointeur chasing de la section 3 est la
mesure la plus parlante sur ces machines.

## 3. Pour aller plus loin

- Mesurez en écriture au lieu de la lecture. Que change le fait que
  l'écriture doive d'abord charger la ligne (*write-allocate*)?
- Lancez deux copies de `mountain` en même temps sur deux cœurs. Quels
  niveaux de la hiérarchie sont partagés?
- Le préchargeur matériel (*prefetcher*) devine les accès réguliers.
  Remplacez l'accès avec un pas fixe par un parcours de liste chaînée dont
  les éléments sont dans un ordre aléatoire (*pointer chasing*). Vous mesurez
  alors la **latence** et non plus le débit: combien de nanosecondes pour un
  accès en L1, L2, L3, mémoire? Convertissez en cycles.
