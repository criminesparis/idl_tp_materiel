"""Trace la montagne mémoire à partir du CSV produit par ./mountain.

Usage: python3 plot_mountain.py mountain.csv
Produit mountain_3d.png et mountain_stride1.png.
"""
import sys
import csv
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

path = sys.argv[1] if len(sys.argv) > 1 else "mountain.csv"
rows = list(csv.DictReader(open(path)))
sizes = sorted({int(r["size_bytes"]) for r in rows})
strides = sorted({int(r["stride"]) for r in rows})
Z = np.zeros((len(sizes), len(strides)))
for r in rows:
    Z[sizes.index(int(r["size_bytes"])), strides.index(int(r["stride"]))] = float(r["mbps"])

def ko(b):
    return f"{b // 1024}K" if b < 1 << 20 else f"{b >> 20}M"

# Surface 3D, axes en log2 comme dans le livre.
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection="3d")
S, T = np.meshgrid(np.log2(strides), np.log2(sizes))
ax.plot_surface( T,S, Z / 1000, cmap="viridis", edgecolor="k", linewidth=0.3)
ax.set_ylabel("pas (éléments de 8 octets)")
ax.set_xlabel("taille")
ax.set_zlabel("débit de lecture (Go/s)")
ax.set_yticks(np.log2(strides)); ax.set_yticklabels(strides)
ax.set_xticks(np.log2(sizes)[::2]); ax.set_xticklabels([ko(s) for s in sizes[::2]])
ax.invert_xaxis()
ax.invert_yaxis()

ax.view_init(elev=25, azim=-135)
plt.title("Montagne mémoire")
plt.tight_layout()
plt.savefig("mountain_3d.png", dpi=120)

# Coupe à pas 1: le débit en fonction de la taille révèle les niveaux de cache.
fig, ax = plt.subplots(figsize=(9, 5))
ax.plot(sizes, Z[:, 0] / 1000, "o-")
ax.set_xscale("log", base=2)
ax.set_xticks(sizes); ax.set_xticklabels([ko(s) for s in sizes], rotation=45)
ax.set_xlabel("taille du jeu de données")
ax.set_ylabel("débit de lecture, pas 1 (Go/s)")
ax.grid(True, which="both", alpha=0.3)
plt.title("Coupe à pas 1: où sont les caches?")
plt.tight_layout()
plt.savefig("mountain_stride1.png", dpi=120)
print("mountain_3d.png et mountain_stride1.png écrits")
