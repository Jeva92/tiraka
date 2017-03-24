#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
#include <vector>

class Datastructure
{
public:
  Datastructure();
  ~Datastructure();

  //Sorting made with recursive merge sort
  void mergeSort(int alku, int loppu, std::string tyyppi);
  void merge(int alku, int keski, int loppu, std::string tyyppi);

  // Add value to the datastructure
  void add(std::string name, unsigned int brokenNysse, 
	   unsigned int sufferingPeople);

  // Prints leaderboard in descending order
  void printLeaderBoard();
  
  // Prints player data in alphabetical order.
  void printAlphabetically();

  // Print person with lowest score
  void worstPlayer();
  
  // Print person with highest score
  void bestPlayer();

  void findPerson(std::string searchTerm);
  
  // Empty the datastructure
  void empty();

  // Copy constructor is forbidden
  //Datastructre(const Datastructure&) = delete;
  // Assignment operator is forbidden
  //Datastructure& operator=(const Datastructure&) = delete;
  
private:
struct Slot
{
    std::string name;
    unsigned int nysset;
    unsigned int passengers;
};

//Data is saved in the vector slotit
std::vector<Slot> slotit;
std::vector<Slot> apuslotit;
//current_sort tells us in which order (points or aplhabetical) the data is ordered at the moment.
//0 = not sorted, 1 = sorted with points, 2 = sorted alphabetically
int current_sort = 0;
};

#endif
