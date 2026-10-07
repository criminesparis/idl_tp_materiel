# Ma machine

| Question                        | Réponse                                                                                                                                                                                                                                                                                                |
| ------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Processeur, architecture        | Apple M4 Pro, AArch64                                                                                                                                                                                                                                                                                  |
| Sockets / cœurs / threads       | 1 socket, 14 CPUs, 14 threads                                                                                                                                                                                                                                                                          |
| Cœurs P / E                     | 10 performance, 4 efficacité                                                                                                                                                                                                                                                                           |
| Fréquence de base / max         | Les fréquences atteignables par chacun des coeurs sont discrétisées: - Coeurs E: 1.020 GHz -> 2.592 GHz (7 paliers)- Coeurs P: 1.260 GHz -> 4.512 GHz (19 paliers)                                                                                                                                     |
| L1i / L1d / L2, ligne           | - Coeurs E: 65.536 Ko, 131.072 Ko, 4.194304 Mo, - Coeurs P: 131.072 Ko, 196.608 Ko, 16.777216 MoLigne: 128 octets                                                                                                                                                                                      |
| Caches partagés?                | Les caches L1d et L1 sont propres à chaque coeur tandis que les caches L2 sont partagés au sein de clusters de coeurs. L'inventaire donne: `hw.perflevel0.cpusperl2: 5` pour les coeurs P et `hw.perflevel1.cpusperl2: 4` pour les coeurs E. D'où- Coeurs E: 4 194 304 Mo- Coeurs P: 16 777 216 octets |
| SIMD et largeur                 | SIMD NEON en 128 bits.                                                                                                                                                                                                                                                                                 |
| Mémoire: capacité, type, canaux | 24 Go unifiée, LPDDR5.Apple annonce une largeur totale de bus de 256 bits. Comme la RAM est une LPDDR5 (largeur canal entrant de 16 bits), on a donc 256/16=16 canaux.                                                                                                                                 |
| FMA                             | Oui                                                                                                                                                                                                                                                                                                    |

## Crête

- Double précision: 721.9 Gflop/s (10 coeurs en régime maximal)
- Simple précision: 1443.8 Gflop/s
- Script Python: entre 10 et 20 Mflop/s soit un facteur 1/7000 à 1/3600 (en simple) et 1/60000 à 1/30000 (en double).
- Bande passante mémoire théorique: 273 Go/s
- Intensité arithmétique d'équilibre: temps de lecture d'un octet = 1/273 donc le processeur peut faire 721.9/273=2.64 opérations float en double précision et 1443.8/273=5.29 opérations en simple précision.

## Énergie (optionnel)

- Au repos: 60 mW, 6.491 W
- Un cœur occupé: ~ 6.43 W
