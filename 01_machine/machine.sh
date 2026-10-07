#!/bin/sh
# Inventaire de la machine: lance les commandes utiles selon le système.
# Usage: sh machine.sh > inventaire.txt
echo "## uname"; uname -a
case "$(uname -s)" in
Linux)
    echo "## lscpu"; lscpu
    echo "## caches"; getconf -a 2>/dev/null | grep -i CACHE
    echo "## mémoire"; free -g
    echo "## topologie (hwloc)"; command -v lstopo-no-graphics >/dev/null && lstopo-no-graphics || echo "installer hwloc"
    echo "## fréquences"; grep -m4 "MHz" /proc/cpuinfo
    ;;
Darwin)
    echo "## sysctl hw"; sysctl hw.model machdep.cpu.brand_string hw.ncpu hw.physicalcpu hw.logicalcpu hw.memsize hw.cachelinesize hw.l1dcachesize hw.l1icachesize hw.l2cachesize hw.l3cachesize 2>/dev/null
    echo "## niveaux de performance (Apple Silicon)"; sysctl hw.perflevel0 hw.perflevel1 2>/dev/null
    echo "## extensions"; sysctl hw.optional 2>/dev/null
    echo "## mémoire"; system_profiler SPMemoryDataType 2>/dev/null | head -20
    ;;
*)
    echo "système non reconnu: $(uname -s)"
    ;;
esac
