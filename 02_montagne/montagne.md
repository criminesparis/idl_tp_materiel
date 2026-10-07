# Ma montagne mémoire

Machine: MacBook Pro M4 Pro

Le programme utilise 4 compteurs pour avoir 4 sommes indépendantes et ainsi pouvoir paralléliser. Avec un seul accumulateur, le début maximal passe de ~105 Go/s à ~85 Go/s. Ce n'est pas 4 fois plus lent.

| Niveau | Taille déduite de la courbe | Taille annoncée (TP 1) | Débit (Go/s) |
| ------ | --------------------------- | ---------------------- | ------------ |
| L1d    | 128 Ko                      | 200 Ko                 | 58           |
| L2     | 16 Mo                       | 4 Mo                   | 18           |
| SLC    |                             |                        |              |
| RAM    | 64 Mo et plus               | 24 Go                  | 4            |

Taille de ligne déduite du pas: 96 octets (annoncée: 128 octets).

Réponses aux questions 1 à 5:

1. Pour un pas de 16, sur Apple M, les marches sont plus nettes qu'à pas 1. Elle sont reportées dans le tableau ci-dessus. Le SLC est un cache commun au GPU/CPU/etc. et se situe entre la RAM et le processeur. C'est donc une couche intermédiaire entre la L2 et la RAM. Pour le premier cache, on ne remplit que le cache L1d des données et non celui des instructions.
2. On a un rapport 14.5 entre le cache L1 et la RAM (à pas 16).
3. C'est une conséquence de la baisse de localité spatiale, avec un pas faible on ne va pas "sauter" d'octets (ils seront tous lus) mais au fur et à mesure que le pas augmente la lignée chargée en cache sera de moins en moins utilisée et il faudra au total plus de lecture dans la RAM. Lorsque l'on en vient à un pas qui dépasse la taille de la ligne de cache, il faut dans tous les cas charger une ligne par octet peu importe le pas d'où un débit constant. La taille de ligne est cohérente avec le TP 1.
4. Pour une taille qui tient en L1, il n'y a pas besoin de lire dans la RAM et le pas n'a donc pas d'effet vu que l'array est stocké tout entier au plus proche du processeur.
