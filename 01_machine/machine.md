# Ma machine

| Question | Réponse |
|---|---|
| Processeur, architecture | x86_64|
| Sockets / cœurs / threads | 1/8/2 |
| Cœurs P / E | 4P / 8E |
| Fréquence de base / max | 2.1 -> 4.7 GH |
| L1d / L2 / L3, ligne | 384KiB/10MiB/18MiB, ligne : 64 |
| Caches partagés? | privés par cœur |
| SIMD et largeur | SSE4_1, SSE4_2 (128 bits), AVX2 (256) |
| Mémoire: capacité, type, canaux | 7Go |
| FMA | oui (flag fma) |

## Crête

1)
Performance:
```bash
python3 peak.py --cores 4 --ghz 4.7 --simd-bits 128 --units 2 --fma
```

Efficacité :

```bash
python3 peak.py --cores 8 --ghz 3.4 --simd-bits 256 --units 1 --fma
```

- Double précision: 300.8 (P) + 217.6 (E) = 518.4 Gflop/s
- Simple précision: 601.6 (P) + 435.2 (E) = 1036.8 Gflop/s

3) Dans PowerShell:

```bash
Get-CimInstance Win32_PhysicalMemory | Select-Object PartNumber, Speed, ConfiguredClockSpeed, SMBIOSMemoryType
```
SMBIOSMemoryType = 35.
Fréquence effective : 5200.
Largeur du bus : 8 octets
Canaux : 2.


- Bande passante mémoire théorique: 83.2 Go/s
- Intensité arithmétique d'équilibre: 518/83 = 6.2 flop/octet

3)

## Énergie (optionnel)

- Au repos: … W
- Un cœur occupé: … W
