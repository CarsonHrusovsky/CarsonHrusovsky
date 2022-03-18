//Graphing program designed to find the shortest path between two stations.
//NOTE: This program is designed to run with the 'stations.dat and 'trains.dat' file'.
#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;
const int maxtrain = 30; //10
const int maxstation = 25; //10
const int infinity = 700; //500


struct TRAINS
{
	int Dstation;   // Departure station
	int Astation;   // Arriaval station
	int Dtime;      // Departure time
	int Atime;      // Arrival time
	int travel;     // travel time on the train
	//int shortest;
};
void loadStations();
void loadTrains();
void stationPrinter();
void shortestPath(int i, int j);
void trainPrinter();
void path(int i, int j);
void dump();
void menuTravel(int & i, int & j);
void mainMenu();
void welcome();
void emptyArray();
void timeFinder(int i, int j);
void textMaker(int i, int j);
void AMPM (int p);
int	main(void);

int station_counter = 0;

TRAINS train [maxtrain][maxtrain];
string stations[maxstation];

int shortest [maxstation][maxstation]; //Holds shortest path
int midpoint [maxstation][maxstation]; //Path array
int	pathArray [maxstation]; //Array for finding path
int kp = 0;
int hourTravel = 0;
int minTravel = 0;
int reportTracker = 1;
int main(void)
{
	int i = 0; int j = 0;

	loadStations();
	loadTrains();
	shortestPath(i, j);
	emptyArray();
	bool menuloop = true;
	int choice;
	welcome();
	
	do{
		mainMenu();
		cin >> choice;
		switch(choice)
		{
			
			case 1:
				stationPrinter();
				break;
					
			case 2:
				menuTravel(i,j);
				kp = 1;
				pathArray[0] = i;
				path(i,j);
				timeFinder(i,j);
				textMaker(i,j);
				emptyArray();
				break;
						
			case 3:
				cout << "This is not currently available." << endl;
				break;
					
			case 4:
				menuloop = false;
				break;
		}
	}while (menuloop == true);
	
	
	return 0;
}

void welcome()
{
		cout << "                                                                             " << endl;
	cout << "    o o o o o o o . . .   ______________________________ _____=======_||____ " << endl;
	cout << "   o      _____           ||                            | |                 |" << endl;
	cout << " .][__n_n_|DD[  ====_____  |  Welcome to the Shortline! | |                 |" << endl;
	cout << ">(________|__|_[_________]_|____________________________|_|_________________|" << endl;
	cout << "_/oo OOOOO oo`  ooo   ooo  'o!o!o                  o!o!o` 'o!o         o!o`  " << endl;
	cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
	cout << "                                                                             " << endl;
}

void mainMenu()
{
	cout << "====================================================================" << endl;
	cout << "What would you like to do? Please enter the associated number below." << endl;
	cout << "1.) See all stations.                                               " << endl;
	cout << "2.) Find the shortest travel time on trains.                        " << endl;
	cout << "3.) Find the shortest time overall. [CURRENTLY DOWN FOR MAINTENANCE]" << endl;
	cout << "4.) Exit.                                                           " << endl;
	cout << "====================================================================" << endl;
	
	
}

void menuTravel(int & i, int & j)
{
	bool useless = false;
	do {
		useless = false;
		//cout << "===================================================================================" << endl;
		cout << "Please print the number associated with the station closest to you and press enter." << endl;
		cout << "Then print the number associated with the station you would like to travel to.     " << endl;
		//cout << "===================================================================================" << endl;
		cin >> i;
		cin >> j;
		if(i > maxstation || i < 0 || j < 0 || j > maxstation)
		{
			cout << "You entered an invalid station number! Please try again." << endl;
			cout << "====================================================================" << endl;
			useless = true;
		}
		if(i == j)
		{
			cout << "You are already here. Try again!" << endl;
			cout << "====================================================================" << endl;
			useless = true;
		}
		if(shortest[i][j] == infinity)
		{
			cout << "There is no train going from " << stations[i] << " to " << stations[j] << ". Try again." << endl;
			cout << "====================================================================" << endl;
			useless = true;			
		}
	} while(useless == true);
	
}

void textMaker(int i, int j)
{
	kp = 0;
	cout << "====================================================================" << endl;
	cout << "REPORT " << reportTracker << ": Shortest time riding on Trains." << endl;
	reportTracker++;
	cout << "To go from " << stations[i] << " to " << stations[j] << " you will need to ride on trains for " << hourTravel << " hour(s) and " << minTravel << " minutes." << endl;
	cout << endl;
	cout << "You will take the following trains:" << endl;
	cout << endl;
	
	if(pathArray[1] == -1)
	{
		cout << "Leave " << stations[i] << " at "; 
		AMPM(train[i][j].Dtime);
		cout << " and arrive at " << stations[j]  << " at ";
		AMPM (train[i][j].Atime); 
		cout << "." << endl;		
	}
	else
	{
		int bufferCounter = 0;
		int departBuffer = pathArray[bufferCounter];
		int arrivalBuffer = pathArray[bufferCounter + 1];
		while(pathArray[bufferCounter + 1] != -1)
		{
			departBuffer = pathArray[bufferCounter]; //0
			bufferCounter++;
			arrivalBuffer = pathArray[bufferCounter]; //1	
			cout << "Leave " << stations[departBuffer] << " at ";
			AMPM(train[departBuffer][arrivalBuffer].Dtime);
			cout << " and arrive at " << stations[arrivalBuffer] << " at "; 
			AMPM(train[departBuffer][arrivalBuffer].Atime); 
			cout << "." <<endl; 
			
		}
		
		if(pathArray[bufferCounter] == -1)
		{
			cout << "Leave " << stations[departBuffer] << " at ";
			AMPM (train[departBuffer][j].Dtime); 
			cout << " and arrive at " << stations[j] << " at "; 
			AMPM (train[departBuffer][j].Atime);
			cout << "." << endl;
		}
		else
		{
			cout << "Leave " << stations[arrivalBuffer] << " at ";
			AMPM (train[arrivalBuffer][j].Dtime);
			cout << " and arrive at " << stations[j] << " at ";
			AMPM (train[arrivalBuffer][j].Atime);
			cout << "." << endl;
		}
	}
	cout << "END OF REPORT." << endl;
}
void AMPM(int p)
{
	int hr = 0;
	int min = 0;
	
	hr = p / 60;
	min = p % 60;
	
	if(p <= 719)
	{
		cout << hr << ":";
		if(min < 10)
		{
			cout << "0";
		}
		 cout << min << " AM";
	}
	else
	{
		if(hr != 12)
			{
				hr = hr - 12;
			}
		cout << hr << ":";
		if(min < 10)
		{
			cout << "0";
		}	
		cout << min << " PM";
	}
}

void timeFinder(int i, int j)
{
	int buffer = shortest[i][j];
	hourTravel = buffer / 60;
	minTravel = buffer % 60;
}

void emptyArray()
{
	for(int x = 0; x <= maxstation; x++)
	{
		pathArray[x] = -1;		
	}	
}

void loadStations()
{
	ifstream infile;
	infile.open("stations.dat");
	if(!infile)
	{
		cout << "Failed to open stations.dat" << endl;	
		return;
	} 
	station_counter = -1;
	int num;
	string name;
	while(!infile.eof())
	{
		
		infile>>num;
		infile>>name;
		stations[num] = name;
		station_counter++;
	}
	infile.close();
}

void stationPrinter()
{
	cout << "====================================================================" << endl;
	for (int i = 0; i<20; i++)
	{
		cout << i << ": " << stations[i] << endl;	
	}
	
}

void loadTrains()
{
	int x,y;
	ifstream infile; 
	
	for (int i = 0; i < maxtrain; i++)
		for (int j=0;j<maxtrain;j++)
			train[i][j].travel = infinity; 
		
	infile.open("trains.dat"); 
	if(!infile)
	{
		cout<<"Failed to open trains.dat"<<endl;
		return;
	}
	
	while(!infile.eof())  
	{
		infile>>x;  
		infile>>y;
	
	    
		train[x][y].Dstation = x;
		train[x][y].Astation = y;	
		infile>>train[x][y].Dtime; 
		infile>>train[x][y].Atime;

		train[x][y].travel = train[x][y].Atime - train[x][y].Dtime;
		
	}
	
	infile.close();
	
}

void trainPrinter()
{
	
	for(int x=0;x<maxtrain;x++)
	{
		cout<<x<<": ";
		for(int y=0;y<maxtrain;y++)
		{
			cout<<"  "<<shortest[x][y];
		}
		cout<<endl;
	}
}

void shortestPath(int i, int j)
{
	int k;
	int c = station_counter - 1;
	
	for(i=0; i <= c; i++) 
		for(j=0; j <= c; j++) 
		{
			shortest[i][j] = train[i][j].travel; //Copying info from train.travel into our shortest integer array
			midpoint[i][j] = -1; //Set midpoint values to 0
		}
	
	for(i=0; i <= c; i++)
		shortest[i][i] = 0;
		
	for(k=0; k <= c; k++)
		for(i=0; i <= c; i++)
			for(j=0; j <= c; j++)
				if((shortest[i][k] + shortest[k][j]) < (shortest[i][j]))
				{
					shortest[i][j] = (shortest[i][k] + shortest[k][j]);	
					midpoint[i][j] = k;
				}
}
void path(int i, int j)
{
	int k = midpoint[i][j];
	if(k == -1)
	{
		return;
	}
	path(i, k);
	pathArray[kp] = k;
	kp = kp + 1;
	path(k, j);
		
}
void dump()
{	
    cout << "== stations =======" << endl;
	cout << " Number  = " << station_counter << endl;
	
	for (int i = 0; i<station_counter; i++)
		cout << i << ": " << stations[i] << endl;
	
	cout << "== trains =======" << endl;
	for(int x=0;x<station_counter;x++)
	{
		cout << x <<" :";
		for(int y=0;y<station_counter;y++)
		{
			if ( train[x][y].travel == infinity)
			     cout << setw(4) << "-";
			else
			     cout<< setw(4) <<train[x][y].travel;
		}
		cout<<endl;
	}
	
    cout << "== shortpath =======" << endl;
	for(int x=0;x<station_counter;x++)
	{
		cout << x <<" :";
		for(int y=0;y<station_counter;y++)
		{
			if ( shortest[x][y] == infinity)
			     cout << setw(4) << "-";
			else
			     cout<< setw(4)<< shortest[x][y];
		}
		cout<<endl;
	}
	
    cout << "== midpoint =======" << endl;
	for(int x=0;x<station_counter;x++)
	{
		cout << x <<" :";
		for(int y=0;y<station_counter;y++)
		{
			cout<< setw(4)<< midpoint[x][y];
		}
		cout<<endl;
	}			
		
}	