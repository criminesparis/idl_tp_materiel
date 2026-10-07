# Ma machine

| Question | Réponse |
| Modèle de processeur, architecture (x86-64 ou AArch64) | AMD Ryzen 5 4500U with Radeon Graphics, x86-64 |
| Nombre de sockets, de cœurs physiques, de threads (SMT) | 1 socket, 6 cœurs physiques, 6 threads (1 thread/cœur, SMT désactivé/absent) |
| Cœurs performance et efficacité, le cas échéant (Apple M, Intel 12e gén. et plus) | Non applicable (architecture homogène Zen 2, tous les cœurs sont identiques) |
| Fréquence de base et fréquence maximale | Base : 2,38 GHz (2370 MHz mesurés) / Max : 4,0 GHz (doc constructeur AMD Ryzen 5 4500U) |
| Taille des caches L1 données, L2, L3 et taille de ligne |L1d : 32 KiB par cœur (192 KiB total), L2 : 512 KiB par cœur (3 MiB total), L3 : 4 MiB (partagé), Taille de ligne : 64 octets|
| Caches privés par cœur ou partagés | L1d, L1i et L2 : privés à chaque cœur, L3 : partagé entre les 6 cœurs |
| Extensions SIMD: SSE4, AVX2, AVX-512, NEON, SVE, et leur largeur en bits | SSE4.1/SSE4.2 (128 bits), AVX2 (256 bits), FMA3 (256 bits) |
| Mémoire vive: capacité, type (DDR4, DDR5, LPDDR5), canaux | Capacité allocable sous WSL2 : ~3,5 Go (RAM physique hôte généralement 8 Go ou 16 Go), Type & Canaux : LPDDR4 / DDR4 en Dual-Channel (non lisible directement sous WSL2) |
| Le processeur a-t-il des unités FMA (multiplication-addition fusionnée)? | Oui, flag fma présent |
|---|---|
| Processeur, architecture | |
| Sockets / cœurs / threads | |
| Cœurs P / E | |
| Fréquence de base / max | |
| L1d / L2 / L3, ligne | |
| Caches partagés? | |
| SIMD et largeur | |
| Mémoire: capacité, type, canaux | |
| FMA | |

## Crête

- Double précision: 384 Gflop/s
- Simple précision: 768 Gflop/s
- Bande passante mémoire théorique: 51,2 Go/s
- Intensité arithmétique d'équilibre: 7,5 flop/octet

## Énergie (optionnel)

- Au repos: … W
- Un cœur occupé: … W
