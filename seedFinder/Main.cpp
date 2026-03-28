#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include "generator.h"

int main() {


    Generator g;
    setupGenerator(&g, MC_1_21, 0);

    uint64_t seed;
    for (seed = 0; ;seed++ ) {
        applySeed(&g, DIM_OVERWORLD, seed);

        int x = 0, y = 63, z = 0;
        int scale = 1;
        int spawnBiomeID = getBiomeAt(&g, scale, x, y, z);
        int biomeID = getBiomeAt(&g, scale, 1256, 69, 195);
        int biomeID1 = getBiomeAt(&g, scale, -1157, 63, 9);
        int biomeID2 = getBiomeAt(&g, scale, 412, 63, 1045);

		applySeed(&g, DIM_NETHER, seed);
		int netherBiomeID = getBiomeAt(&g, scale, 51, 76, 22);

        if (seed % 50000 == 0) {
            printf("Checked seed: %lld\n", seed);
        }

        if (spawnBiomeID != taiga) { continue; }
		if (biomeID != sunflower_plains) { continue; }
		if (biomeID1 != deep_frozen_ocean) { continue; }
		if (biomeID2 != desert) { continue; }
        
		printf("Found valid seed: %lld\n", seed);
    }

    return 0;
}