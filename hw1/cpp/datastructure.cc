#include "datastructure.hh"
#include <vector>
#include <iostream>

Datastructure::Datastructure()
{
}

Datastructure::~Datastructure()
{
}

//mergeSort, which slices the data in small pieces and then sends it to merge
void Datastructure::mergeSort(int alku, int loppu, std::string tyyppi) {
    int keski;
    if (alku < loppu && loppu != -1) {
        //Recursively slicing the vector into pieces
        keski = (alku+loppu)/2;
        mergeSort(alku, keski, tyyppi);
        mergeSort(keski+1, loppu, tyyppi);
        merge(alku, keski, loppu, tyyppi);
    }
}

//Sorts the data with merge sort logic.
void Datastructure::merge(int alku, int keski, int loppu, std::string tyyppi) {
    //Lets keep those first values in memory
    int a1 = alku;
    int a2 = alku;
    int k = keski+1;
    //Lets go through the data piece
    while ((a1 <= keski) && (k <= loppu)) {
        //If we are making the sort for leaderboards according to points
        if (tyyppi == "lead") {
            if (slotit[a1].nysset > slotit[k].nysset) {
                apuslotit.at(a2) = slotit.at(a1);
                ++a1;
	    //If destroyed busses are the same with 2 players, 
	    //then sort with passengers
            } else if (slotit[a1].nysset == slotit[k].nysset) {
                if (slotit[a1].passengers > slotit[k].passengers) {
                    apuslotit.at(a2) = slotit.at(a1);
                    ++a1;
                } else {
                    apuslotit.at(a2) = slotit.at(k);
                    ++k;
                }
            } else {
                apuslotit.at(a2) = slotit.at(k);
                ++k;
            }
        //Or if we are going to sort the data alphabetically
        } else if (tyyppi == "alph") {
            if (slotit[a1].name < slotit[k].name) {
                apuslotit.at(a2) = slotit.at(a1);
                ++a1;
            } else {
                apuslotit.at(a2) = slotit.at(k);
                ++k;
            }
        }
        ++a2;
    }
    if (a1>keski) {
        for (int i = k; i <= loppu; ++i) {
            apuslotit.at(a2) = slotit.at(i);
            ++a2;
        }
    } else {
        for (int i = a1; i <= keski; ++i) {
            apuslotit.at(a2) = slotit.at(i);
            ++a2;
        }
    }
    //Lets place the sorted data from apuslotit to slotit.
    for (int i = alku; i <=loppu; ++i) {
    slotit.at(i) = apuslotit.at(i);
    }
}
// Placeholders for functions

// Adds new player
void Datastructure::add(std::string name, unsigned int brokenNysse, 
			unsigned int sufferingPeople)
{
    slotit.push_back({name, brokenNysse, sufferingPeople});
    apuslotit.push_back({"", 0, 0});
    current_sort = 0;
}

void Datastructure::printAlphabetically()
{
    //If the data isnt sorted alpabetically, then sort it.
    if (current_sort != 2) {
        mergeSort(0, slotit.size()-1, "alph");
        current_sort = 2;
    }
    //Print data on screen
    for (unsigned int i = 0; i < slotit.size(); ++i) {
        std::cout << slotit.at(i).name << ": " << slotit.at(i).nysset << " buses, " << slotit.at(i).passengers << " passengers" << std::endl;
    }
}


// Finds player with key stored in term
void Datastructure::findPerson(std::string term)
{
    //If the data isnt sorted with points, then sort it.
    if (current_sort != 1) {
        mergeSort(0, slotit.size()-1, "lead");
        current_sort = 1;
    }
    //Print data on screen
    for (unsigned int i = 0; i < slotit.size(); ++i) {
        if (slotit[i].name == term) {
            std::cout << i+1 << ". " << slotit.at(i).name << ": " << slotit.at(i).nysset << " buses, " << slotit.at(i).passengers << " passengers" << std::endl;
            return;
        }
    }
    std::cout << "Player " << term << " was not found." << std::endl;
}

// Print leaderboard. Sorts only if necessary
void Datastructure::printLeaderBoard()
{
    //If the data isnt sorted with points, then sort it.
    if (current_sort != 1) {
        mergeSort(0, slotit.size()-1, "lead");
        current_sort = 1;
    }
    //Print data on screen
    for (unsigned int i = 0; i < slotit.size(); ++i) {
        std::cout << i+1 << ". " << slotit.at(i).name << ": " << slotit.at(i).nysset << " buses, " << slotit.at(i).passengers << " passengers" << std::endl;
    }
}

// Prints worst player stats
void Datastructure::worstPlayer()
{
    //If the data isnt sorted with points, then sort it.
    if (current_sort != 1) {
        mergeSort(0, slotit.size()-1, "lead");
        current_sort = 1;
    }
    //Print data on screen
    std::cout << slotit.size() << ". " << slotit.back().name << ": " << slotit.back().nysset << " buses, " << slotit.back().passengers << " passengers" << std::endl;
}

// Prints best player stats
void Datastructure::bestPlayer()
{
    //If the data isnt sorted with points, then sort it.
    if (current_sort != 1) {
        mergeSort(0, slotit.size()-1, "lead");
        current_sort = 1;
    }
    //Print data on screen
    std::cout << "1. " << slotit.front().name << ": " << slotit.front().nysset << " buses, " << slotit.front().passengers << " passengers" << std::endl;
}

// Empties the datastructure
void Datastructure::empty()
{
    //Clear all data, including apuslotit and current sort so that the program doesnt think its sorted in any way
    slotit.clear();
    apuslotit.clear();
    current_sort = 0;
}
