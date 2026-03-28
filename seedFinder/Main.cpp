#define _CRT_SECURE_NO_WARNINGS
#define RED "\033[31m"
#define GREEN "\033[32m"
#define CYAN "\033[36m"
#define RESET "\033[0m"
#define YELLOW "\033[33m"

#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include<chrono>
#include<ctime>

#include "generator.h"

using namespace std;

int main() {

    std::cout << "\033[31mRUNNING\033[0m\n";
    time_t now;
    struct tm* date;
    Generator g;
    setupGenerator(&g, MC_1_21, 0);
	uint64_t lastSave = 0;
    


    
    std::ifstream Progress("Progress.txt");
    std::string line;
    fstream Candidates("Candidates.txt", ios::app);

    uint64_t seed;
	string seedSTR;

    if(Progress.peek() == ifstream::traits_type::eof()) {
        cout << "Autosave file empty. Starting from seed: 0." << endl;
    }else {
        while (getline(Progress, line)) {
            lastSave = stoull(line);
            cout << "Resuming from seed: " << lastSave << endl;
        }
    }
	lastSave = (lastSave / 50000) * 50000; 

    for (seed = lastSave; seed < (1ULL << 48); seed++) {
        applySeed(&g, DIM_OVERWORLD, seed);

        int x = 0, y = 63, z = 0;
        int scale = 1;
        int spawnBiomeID = getBiomeAt(&g, scale, x, y, z);
        int biomeID = getBiomeAt(&g, scale, 1256, 69, 195);
        int biomeID1 = getBiomeAt(&g, scale, -1157, 63, 9);
        int biomeID2 = getBiomeAt(&g, scale, 412, 63, 1045);

		//applySeed(&g, DIM_NETHER, seed);
		//int netherBiomeID = getBiomeAt(&g, scale, 51, 76, 22);

        
        if (seed % 200000 == 0) {
            time(&now);
            date = localtime(&now);
            string dateStr = asctime(date);
			dateStr.pop_back();

            cout << YELLOW << dateStr <<RESET << ":: Autosaved successfully at seed " << CYAN << seed << RESET<< ".\n";

            ofstream out("Progress.txt", ios::trunc);
            out << seed << "\n";
            out.close();
        }
        else if (seed % 50000 == 0) {
            date = localtime(&now);
            string dateStr = asctime(date);
            dateStr.pop_back();

            

            std::cout << YELLOW << dateStr << RESET << " :: Checked seed " << seed << " \n";


        }

        if (spawnBiomeID != taiga) { continue; }
		if (biomeID != sunflower_plains) { continue; }
		if (biomeID1 != deep_frozen_ocean) { continue; }
		if (biomeID2 != desert) { continue; }
        
		cout << "Found candidate seed: " << GREEN << seed << RESET << endl;
        Candidates << seed << "\n";
    }

    Candidates.close();
    Progress.close();
    return 0;
}