#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include <fstream>
#include <math.h>
#include <vector>
#include <climits>
#include <sys/resource.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <random>
#include <functional>
#include <signal.h>
#include <unistd.h>

double MAX_RUN_TIME;

using namespace std;


//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------

class CITY{
    public:
        ~CITY();
        CITY();
        CITY(int i, string is, int x, string xs, int y, string ys);
        CITY(const CITY& city);
        CITY& operator=(const CITY& city);
        int getID();
        int getX();
        int getY();
        void printCity();
        long int distanceTo(CITY* city);
    private:
        int* id;
        int* xCord;
        int* yCord;
        string* id_str;
        string* xCord_str;
        string* yCord_str;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------

CITY::~CITY(){
    if(id){
        delete id;
    }
    if(id_str){
        delete id_str;
    }
    if(xCord){
        delete xCord;
    }
    if(xCord_str){
        delete xCord_str;
    }
    if(yCord){
        delete yCord;
    }
    if(yCord_str){
        delete yCord_str;
    }
}

CITY::CITY(){
    id = new int(-1);
    id_str = new string("NONE_GIVEN_AT_START");
    xCord = new int(-1);
    xCord_str = new string("NONE_GIVEN_AT_START");
    yCord = new int(-1);
    yCord_str = new string("NONE_GIVEN_AT_START");
}

CITY::CITY(int i, string is, int x, string xs, int y, string ys){
    id = new int(i);
    id_str = new string(is);
    xCord = new int(x);
    xCord_str = new string(xs);
    yCord = new int(y);
    yCord_str = new string(ys);
}

CITY::CITY(const CITY& city){
    id = new int (*city.id);
    id_str = new string(*city.id_str);
    xCord = new int(*city.xCord);
    xCord_str = new string (*city.xCord_str);
    yCord = new int(*city.yCord);
    yCord_str = new string(*city.yCord_str);
}

CITY& CITY::operator=(const CITY& city){
    if(&city != this){
        id = new int (*city.id);
        id_str = new string(*city.id_str);
        xCord = new int(*city.xCord);
        xCord_str = new string (*city.xCord_str);
        yCord = new int(*city.yCord);
        yCord_str = new string(*city.yCord_str);
    }
    return *this;
}

int CITY::getID(){
    return *id;
}

int CITY::getX(){
    return *xCord;
}

int CITY::getY(){
    return *yCord;
}

void CITY::printCity(){
    cout << "ID: " << *id_str  << ", X: " << *xCord_str << ", Y: " << *yCord_str << endl;
}

long int CITY::distanceTo(CITY* city){
    return nearbyint( ( sqrt( pow(this->getX() - city->getX(), 2 ) + pow(this->getY() - city->getY(), 2))));
}


//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------

class TOUR{
    public:
        ~TOUR();
        TOUR(char* file);
        void printCities();
        void printTour();
        void printScratch();
        void printTourFile(string file);
        long int tourDistance(string vectorToSum);
        long int tourSize(string vec);
        void tourClear(string vec);
        void tourImportScratch();
        void scratchImportTour();
        void scratchImportCities();
        size_t findNearest(string vec, CITY *from);
        void runGreedy(long start);
        void rearrangeScratch(int low, int high, long int tobeat);
        void twoOpt(clock_t start);
    private:
        std::vector <CITY*> cities;
        std::vector <CITY*> tour;
        std::vector <CITY*> scratch;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------

TOUR::~TOUR(){
    int i;
    for(i = 0; i < cities.size(); i++){
        CITY* c = cities[i];
        delete c;
    }
    for(i = 0; i < scratch.size(); i++){
        CITY* c = scratch[i];
        delete c;
    }
    for(i = 0; i < tour.size(); i++){
        CITY* c = tour[i];
        delete c;
    }
    cities.clear();
    scratch.clear();
    tour.clear();
}

TOUR::TOUR(char* file){
    ifstream infile;
    string word;
    infile.open(file);
    while(infile >> word){
        string s_id = word;
        int i_id = atoi(word.c_str());
        infile >> word;
        string s_xCord = word;
        int i_xCord = atoi(word.c_str());
        infile >> word;
        string s_yCord = word;
        int i_yCord = atoi(word.c_str());
        CITY* inCity = new CITY(i_id, s_id, i_xCord, s_xCord, i_yCord, s_yCord);
        CITY* inCity2 = new CITY(i_id, s_id, i_xCord, s_xCord, i_yCord, s_yCord);
        cities.push_back(inCity);
        scratch.push_back(inCity2);
    }
    infile.close();
}

void TOUR::printCities(){
    for(size_t i = 0; i < cities.size(); i++){
        cities.at(i)->printCity();
    }
}

void TOUR::printTour(){
    for(size_t i = 0; i < tour.size(); i++){
        tour.at(i)->printCity();
    }
}

void TOUR::printScratch(){
    for(size_t i = 0; i < scratch.size(); i++){
        scratch.at(i)->printCity();
    }
}

void TOUR::printTourFile(string file){
    ofstream outfile;
    outfile.open(file.c_str());
    long int d = this->tourDistance("tour");
    outfile << d << endl;
    for(size_t i = 0; i < tour.size(); i++){
        int t = tour.at(i)->getID();
        outfile << t << endl;
    }
    outfile.close();

}

long int TOUR::tourDistance(string vectorToSum){
    size_t i;
    long int len = 0;
    int switchKey;
    if(vectorToSum == "tour"){
        switchKey = 1;
    }
    else if(vectorToSum == "cities"){
        switchKey = 2;
    }
    else{
        switchKey = 3;
    }

    switch(switchKey){
    case 1:
        for(i = 0; i < tour.size()-1; i++){
            len +=  tour.at(i)->distanceTo(tour.at(i+1));
        }
        len +=  tour.at(0)->distanceTo(tour.at(tour.size()-1));
        break;
    case 2:
        for(i = 0; i < cities.size()-1; i++){
            len +=  cities.at(i)->distanceTo(cities.at(i+1));
        }
        len +=  cities.at(0)->distanceTo(cities.at(cities.size()-1));
        break;
    case 3:
        for(i = 0; i < scratch.size()-1; i++){
            len +=  scratch.at(i)->distanceTo(scratch.at(i+1));
        }
        len +=  scratch.at(0)->distanceTo(scratch.at(scratch.size()-1));
        break;
    default:
        return -1;
    }
    return len;
}

long int TOUR::tourSize(string vec){
    int switchKey;
    long int size;
    if(vec == "tour"){
        switchKey = 1;
    }
    else if(vec == "cities"){
        switchKey = 2;
    }
    else{
        switchKey = 3;
    }
    switch(switchKey){
    case 1:
        size = tour.size();
        break;
    case 2:
        size = cities.size();
        break;
    case 3:
        size = scratch.size();
        break;
    default:
        return -1;
    }
    return size;
}

void TOUR::tourClear(string vec){
    int switchKey, i;
    long int size;
    CITY* t;
    if(vec == "tour"){
        switchKey = 1;
    }
    else if(vec == "cities"){
        switchKey = 2;
    }
    else{
        switchKey = 3;
    }

    switch(switchKey){
        case 1:
            for(i = 0; i < tour.size(); i++){
                t = tour.at(i);
                delete t;
            }
            tour.clear();
            break;
        case 2:
            for(i = 0; i < cities.size(); i++){
                t = cities.at(i);
                delete t;
            }
            cities.clear();
            break;
        case 3:
            for(i = 0; i < scratch.size(); i++){
                t = cities.at(i);
                delete t;
            }
            scratch.clear();
            break;
    }

}

void TOUR::tourImportScratch(){
    long int items = scratch.size();
    long int i;
    for(i =0; i < items; i++){
        tour[i] = scratch[i];
    }
}

void TOUR::scratchImportTour(){
    //scratch.clear();
    long int items = tour.size();
    long int i;
    CITY* t;
    for(i =0; i < items; i++){
        t = new CITY(*tour.at(i));
        scratch.push_back(t);
    }
}

void TOUR::scratchImportCities(){
    //scratch.clear();
    long int items = cities.size();
    long int i;
    CITY* t;
    for(i =0; i < items; i++){
        t = new CITY(*cities.at(i));
        scratch.push_back(t);
    }
}

size_t TOUR::findNearest(string vec, CITY* from){
    size_t i;
    long int len = 9999999999;
    int index;
    long int temp;
    int switchKey;
    if(vec == "tour"){
        switchKey = 1;
    }
    else if(vec == "cities"){
        switchKey = 2;
    }
    else{
        switchKey = 3;
    }

    switch(switchKey){
        case 1:
            for(i = 0; i < tour.size(); i++){
                temp = from->distanceTo(tour.at(i));
                if(temp < len){
                    len = temp;
                    index = i;
                }
            }
            break;
        case 2:
            for(i = 0; i < cities.size(); i++){
                temp = from->distanceTo(cities.at(i));
                if(temp < len){
                    len = temp;
                    index = i;
                }
            }
            break;
        case 3:
            for(i = 0; i < scratch.size(); i++){
                temp = from->distanceTo(scratch.at(i));
                if(temp < len){
                    len = temp;
                    index = i;
                }
            }
            break;
        default:
            return -1;
    }
    return index;
}

void TOUR::runGreedy(long int start){
    size_t items = scratch.size();
    size_t nearest;
    CITY* t = new CITY(*scratch.at(start));
    tour.push_back(t);
    t = scratch.at(start);
    delete t;
    scratch.erase((scratch.begin()+(int)start));
    while(scratch.size() > 0){
        nearest = this->findNearest("scratch", tour.back());
        CITY* t2 = new CITY(*scratch.at(nearest));
        tour.push_back(t2);
        t2 = scratch.at(nearest);
        delete t2;
        scratch.erase((scratch.begin() + (int)nearest));
    }
}

void TOUR::rearrangeScratch(int low, int high, long int tobeat){
	int x, y, z;
	int run = -1;
	bool jump = false;
	long int new_length;
	int best = tobeat;
	run1:
	for(x = high; x < tour.size(); x++){ 
		scratch.push_back(tour[x]); 
	}
    for(y = low; y < high; y++){
        scratch.push_back(tour[y]);
    }
    for(z = 0; z < low; z++){
        scratch.push_back(tour[z]);
    }
    if(jump == true){ goto endswap;}
    new_length = this->tourDistance("scratch");
    if(new_length < best){
    	run = 1;
    	best = new_length;
    }
    scratch.clear();
    run2:
    for(x = low; x < high; x++){
        scratch.push_back(tour[x]);
    }
    for(y = 0; y < low; y++){
        scratch.push_back(tour[y]);
    }
    for(z = high; z < tour.size(); z++){
        scratch.push_back(tour[z]);
    }  
    if(jump == true){ goto endswap;}
    new_length = this->tourDistance("scratch");
    if(new_length < best){
    	run = 2;
    	best = new_length;
    }
    scratch.clear();
    run3:
    for(x = 0; x < low; x++){
        scratch.push_back(tour[x]);
    }
    for(y = high; y < tour.size(); y++){
        scratch.push_back(tour[y]);
    }
    for(z = low; z < high; z++){
        scratch.push_back(tour[z]);
    } 
    if(jump == true){ goto endswap;}
    new_length = this->tourDistance("scratch");
    if(new_length < best){
    	run = 3;
    	best = new_length;
    }
    scratch.clear();
    run4:
    for(x = high; x < tour.size(); x++){
        scratch.push_back(tour[x]);
    }
    for(y = 0; y < low; y++){
        scratch.push_back(tour[y]);
    }
    for(z = low; z < high; z++){
        scratch.push_back(tour[z]);
    } 
    if(jump == true){ goto endswap;}
    new_length = this->tourDistance("scratch");
    if(new_length < best){
    	run = 4;
    	best = new_length;
    }
    scratch.clear();
    run5:
    for(x = 0; x < low; x++){
    	scratch.push_back(tour[x]);
    }
    for(y = high; y < tour.size(); y++){
    scratch.push_back(tour[y]);
    }
    for(z = low; z < high; z++){
        scratch.push_back(tour[z]);
    } 
    if(jump == true){ goto endswap;}
    new_length = this->tourDistance("scratch");
    if(new_length < best){
    	run = 5;
    	best = new_length;
    }
    scratch.clear();

    switch(run){
    	case 1:
    		jump = true;
    		goto run1;
    		break;	
    	case 2:
    		jump = true;
    		goto run2;
    		break;
    	case 3:
    		jump = true;
    		goto run3;
    		break;
    	case 4:
    		jump = true;
    		goto run4;
    		break;
    	case 5:
    		jump = true;
    		goto run5;
    		break;
    	default:
    		goto endswap;
    }
    endswap: ;

}

void TOUR::twoOpt(clock_t start){
    clock_t end, final;
    long int to_beat = this->tourDistance("tour");
    CITY * temp;
    int pos1, pos2, pos3, pos4, low, high;
    end = clock();
    final = (double)(end - start) / CLOCKS_PER_SEC;
    while(final < MAX_RUN_TIME){
        typedef std::chrono::high_resolution_clock myclock;
        myclock::time_point beginning = myclock::now();
        myclock::duration d = myclock::now() - beginning;
        unsigned seed = d.count();

        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distribution(0, tour.size()-1);
        auto dice = std::bind (distribution, generator);
        
        pos1 = dice();
        pos2 = dice();
        while(pos1 == pos2){
            pos2 = dice();
        }
        
        if(pos1 < pos2){
            low = pos1;
            high = pos2;
        }
        else{
            low = pos2;
            high = pos1;
        }
        this->rearrangeScratch(low, high, to_beat);
        this->tourImportScratch();
    	scratch.clear();
        end = clock();
        final = (double)(end - start) / CLOCKS_PER_SEC;
    }
    end = clock();
    final = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Time constraint met. ( " << final << " )" << endl
    << "Printing tour and exiting..." << endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------
TOUR* sig_catch_cleanup;

void my_handler(int s){
           printf("Caught signal %d\n",s);
           delete sig_catch_cleanup;
           exit(1); 
}


int main(int argc, char* argv[]){
        MAX_RUN_TIME = atoi(argv[2]);
        clock_t start = clock();
        signal(SIGINT, my_handler);
        long int best, temp, start_index;
        string name(argv[1]);
        cout << "Creating new TOUR object from file: " << argv[1] << endl;
        TOUR * theTour = new TOUR(argv[1]);
        sig_catch_cleanup = theTour;
        long int len = theTour->tourSize("cities");
        if(len >= 2000){
            if(len == 2000){
                cout << "Running greedy algorithm using known optimal path from city 638." << endl <<
                "May Skip optimization due to number of cities and time constraint." << endl;
                theTour->runGreedy(638);
                clock_t end = clock();
        		clock_t final = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "Greedy done. Elapsed time: " << final << endl;	
            }
            else if(len == 5000){
                cout << "Running greedy algorithm using known optimal path starting at 1981." << endl <<
                "May skip optimization due to number of cities and time constraint." << endl;
                theTour->runGreedy(1981);
                clock_t end = clock();
        		clock_t final = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "Greedy done. Elapsed time: " << final << endl;
            }
            else{
                cout << "Running greedy with optimization on set size greater than 2000." << endl
             	<< "Defaulting to city 0 start."<< endl 
             	<< "May skip optimization due to number of cities and time constraint." << endl;
             	/*
                for(long int j = 0; j < len;j++){
                    theTour->runGreedy(j);
                    temp = theTour->tourDistance("tour");
                    if(temp < best || j == 0){
                        best = temp;
                        start_index = j;
                    }
                    theTour->scratchImportCities();
                    theTour->tourClear("tour");
                }
                theTour->runGreedy(start_index);
                */
                theTour->runGreedy(0);
                clock_t end = clock();
        		clock_t final = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "Greedy done. Elapsed time: " << final << endl;
            }
            theTour->twoOpt(start);
            theTour->printTourFile((string)(name+".tour"));
        }
        else{
            cout << "Finding optimal greedy algorithm path start..." << endl;
            for(long int i = 0; i < len;i++){
                theTour->runGreedy(i);
                temp = theTour->tourDistance("tour");
                if(temp < best || i == 0){
                    best = temp;
                    start_index = i;
                }
                theTour->scratchImportCities();
                theTour->tourClear("tour");
            }
            cout << "Optimal greedy path start found." << endl;
            theTour->runGreedy(start_index);
            cout << "Running 2-OPT optimization algorithm..." << endl;
            theTour->twoOpt(start);
            theTour->printTourFile((string)(name+".tour"));
        }

        delete theTour;
        return 0;
}