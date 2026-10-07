# TP 2: la montagne mémoire

Objectif: mesurer le débit de lecture de la mémoire de votre machine en
fonction de la taille des données et du pas d'accès, et en déduire la
hiérarchie de caches. C'est la figure du cours (_memory mountain_, Bryant et
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

1. Sur la coupe à pas 1, repérez les paliers. À quelles tailles le débit
   chute-t-il? Comparez avec les tailles de L1, L2 et L3 du TP 1.
2. Quel est le débit en L1, en L2, en L3, en mémoire vive? Quel rapport
   entre L1 et la mémoire?
3. Pour une taille qui tient en mémoire vive seulement (64 Mo ou plus),
   tracez le débit en fonction du pas. Pourquoi décroît-il, et pourquoi
   cesse-t-il de décroître à partir d'un certain pas? Déduisez-en la taille
   de ligne de cache. Comparez avec `getconf LEVEL1_DCACHE_LINESIZE` ou
   `sysctl hw.cachelinesize`.
4. Pour une taille qui tient en L1, le pas a-t-il un effet? Pourquoi?
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
  l'écriture doive d'abord charger la ligne (_write-allocate_)?
- Lancez deux copies de `mountain` en même temps sur deux cœurs. Quels
  niveaux de la hiérarchie sont partagés?
- Le préchargeur matériel (_prefetcher_) devine les accès réguliers.
  Remplacez l'accès avec un pas fixe par un parcours de liste chaînée dont
  les éléments sont dans un ordre aléatoire (_pointer chasing_). Vous mesurez
  alors la **latence** et non plus le débit: combien de nanosecondes pour un
  accès en L1, L2, L3, mémoire? Convertissez en cycles.
