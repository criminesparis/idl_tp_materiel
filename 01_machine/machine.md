# Ma machine

| Question | Réponse |
|---|---|
| Processeur, architecture | Apple M1 Pro, ARM64 / ARMv8.4-A |
| Sockets / cœurs / threads | 1 socket / 8 cœurs / 8 threads |
| Cœurs P / E | 6 P-cores / 2 E-cores |
| Fréquence de base / max | 1,7 GHz / 3,1 GHz (mesuré) |
| L1d / L2 / L3, ligne | L1d : 128 KiB (P) + 64 KiB (E), L2 : 12 MiB (P) + 4 MiB (E), L3 pas mentionnée. Ligne : 128 B |
| Caches partagés? | Oui : L2 partagé. 24 MiB de System Level Cache partagé par le SoC |
| SIMD et largeur | ARM NEON / Advanced SIMD, 128 bits |
| Mémoire: capacité, type, canaux | 32 Go LPDDR5-6400, mémoire unifiée, bus 256 bits |
| FMA | Pas mentionné dans l'inventaire, mais l'architecture ARM M1 Pro précise que oui|

## Crête

- Double précision: 77 Gflop/s
- Simple précision: 154 Gflop/s
- Bande passante mémoire théorique: 200 Go/s
- Intensité arithmétique d'équilibre: pour FP32 0,77 flop/octet, pour FP64 0,39 flop/octet

## Énergie (optionnel)

- Au repos: 211 mW
- Un cœur occupé: 4219 mW
