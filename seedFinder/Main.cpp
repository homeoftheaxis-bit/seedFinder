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
#include<thread>

#include "generator.h"

using namespace std;

void writeCandidate(uint64_t seed) {
    ofstream out("Candidates.txt", ios::app);
    out << seed << "\n";
    out.close();
}

void progress1AutoSave(uint64_t seed) {
    ofstream out("progressFile\Progress1.txt", ios::trunc);
    out << seed << "\n";
    out.close();
    time_t now;
    struct tm* date;
    time(&now);
    date = localtime(&now);
    string dateStr = asctime(date);
    dateStr.pop_back();
    cout << YELLOW << dateStr << RESET << RED << "T1" << RESET<< ":: Autosaved successfully at seed " << CYAN << seed << RESET << ".\n";
}

void progress2AutoSave(uint64_t seed) {
    ofstream out("progressFile\Progress2.txt", ios::trunc);
    out << seed << "\n";
    out.close();
    time_t now;
    struct tm* date;
    time(&now);
    date = localtime(&now);
    string dateStr = asctime(date);
    dateStr.pop_back();
    cout << YELLOW << dateStr << RESET << RED << "T2" << RESET << ":: Autosaved successfully at seed " << CYAN << seed << RESET << ".\n";

}

void testSeed(uint64_t start, uint64_t end, int thread) {
	Generator g;
    uint64_t seed;
    Generator g;
    setupGenerator(&g, MC_1_21, 0);

    int x = 0, y = 63, z = 0;
    int scale = 1;
    int spawnBiomeID = getBiomeAt(&g, scale, x, y, z);
    int biomeID = getBiomeAt(&g, scale, 1256, 69, 195);
    int biomeID1 = getBiomeAt(&g, scale, -1157, 63, 9);
    int biomeID2 = getBiomeAt(&g, scale, 412, 63, 1045);

    if(seed % 200000 == 0){
        if(thread == 1) {
            progress1AutoSave(seed);
        } else {
            progress2AutoSave(seed);
		}
    }
    else if (seed % 50000 == 0) {
        time_t now;
        struct tm* date;
        time(&now);
        date = localtime(&now);
        string dateStr = asctime(date);
        dateStr.pop_back();
		cout << RED << "T" << thread << RESET << YELLOW << dateStr << RESET << " :: Checked seed " << seed << " \n";
    }

    for (seed = start; seed < end; seed++) {
		applySeed(&g, DIM_OVERWORLD, seed);
        if (spawnBiomeID != taiga) { continue; }
        if (biomeID != sunflower_plains) { continue; }
        if (biomeID1 != deep_frozen_ocean) { continue; }
        if (biomeID2 != desert) { continue; }

		cout << "Found candidate seed: " << GREEN << seed << RESET << endl;
		writeCandidate(seed);
    }
}

int main() {

    std::cout << "\033[31mRUNNING\033[0m\n";
    time_t now;
    struct tm* date;
    setupGenerator(&g, MC_1_21, 0);
	uint64_t lastSave1 = 0;
	uint64_t lastSave2 = 0;
    
    std::ifstream Progress1("progressFile\Progress1.txt");
	std::ifstream Progress2("progressFile\Progress2.txt");   
    std::string line;
    fstream Candidates("Candidates.txt", ios::app);

    uint64_t seed;
	string seedSTR;

    if(Progress1.peek() == ifstream::traits_type::eof()) {
        cout << "Autosave 1 file empty. Starting from seed: 0." << endl;
    }else {
        while (getline(Progress1, line)) {
            lastSave1 = stoull(line);
            cout << "Resuming from seed: " << lastSave1 << endl;
        }
    }
	lastSave1 = (lastSave1 / 50000) * 50000; 

    if (Progress2.peek() == ifstream::traits_type::eof()) {
        cout << "Autosave 2 file empty. Starting from seed: 0." << endl;
    }
    else {
        while (getline(Progress2, line)) {
            lastSave2 = stoull(line);
            cout << "Resuming from seed: " << lastSave2 << endl;
        }
    }
    lastSave1 = (lastSave1 / 50000) * 50000;

    Candidates.close();
    Progress1.close();
	Progress2.close();
    return 0;
}