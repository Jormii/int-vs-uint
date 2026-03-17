import os
import numpy as np
import matplotlib.pyplot as plt

DPI = 72
WIDTH = 1920 // 2
HEIGHT = 1080 // 2

fs = [f for f in os.listdir(".") if f.endswith(".txt")]
for f in fs:
    ds = {}
    with open(f, mode="r") as fd:
        for _ in range(2):
            t = fd.readline().strip()
            ds[t] = []
            for _ in range(1 << 15):
                ds[t].append(float(fd.readline().strip()))

    arr = np.array([v for v in ds.values()]).T
    Q1 = np.percentile(arr, 25, axis=0)
    Q3 = np.percentile(arr, 75, axis=0)
    IQR = Q3 - Q1
    lower_bound = Q1 - 1.5 * IQR
    upper_bound = Q3 + 1.5 * IQR
    arr = np.ma.masked_where((arr < lower_bound) | (arr > upper_bound), arr)

    avg = np.mean(arr, axis=0)
    rel = avg[0] / avg[1]

    fig = plt.figure(figsize=(WIDTH / DPI, HEIGHT / DPI), dpi=DPI)

    _, edges, bars = plt.hist(
        arr,
        histtype="bar",
        label=[k for k in ds.keys()],
    )

    bin_centers = 0.5 * (edges[:-1] + edges[1:])
    plt.xticks(bin_centers)

    plt.gca().legend()
    plt.gca().ticklabel_format(useOffset=False)
    for b in bars:
        plt.gca().bar_label(b)
    plt.title(f"Avg {rel:.2f}x - {os.path.basename(f)}")
    plt.savefig(f"{os.path.basename(f)}.png", dpi=DPI)
    plt.close()
