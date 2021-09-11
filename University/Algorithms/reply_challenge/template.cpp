// Nie czarodziejska tylko magiczna. I nie fujarka tylko flet. Magiczna flet. 
// Ciekawa Algorytm ~Piotr Marciniak 2021

#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

	int W, H;
    int N; // liczba budynkow
    int M; // liczba anten
    int R;

using namespace std;

//opoznienie przez dystans
//szybkosc od mocy 
struct building{
    int x;
    int y;
    int latency;
    int connection_speed;
} buildings[350000];

struct antena{
	int id;
	int range;
    int connection_speed;
} antenas[60000];

struct coord{
    int x = -1,y = -1,id;
} coords[60000];

int distance(int antena_x, int antena_y, building b){
    return abs(b.x - antena_x) + abs(b.y - antena_y);
}

int score(antena a, int antena_x, int antena_y, building b){
    return b.connection_speed * a.connection_speed - b.latency * distance(antena_x, antena_y, b);
}

bool reachable(antena a, int antena_x, int antena_y, building b){
    return distance(antena_x, antena_y, b) <= a.range;
}

bool inCoords(int x, int y) {
	for (int i = 0; i < M; ++i) {
		if( coords[i].x == x && coords[i].y == y)
			return true;
		if( coords[i].x == -1 || coords[i].y == -1)
			return false;
	}
	return false;
}

coord drawHeatMap(int antena_i) {

	int range = antenas[antena_i].range;

    int max_score = -1, temp_score;
    coord c = coord();

	for (int i = 0; i < N; ++i) {
		int x = buildings[i].x;
		int y = buildings[i].y;

		int k = 0;
		for (int j = y - range; j <= y + range; ++j) {
			for (int l = x - k; l <= x + k; ++l) {
				if( l >= 0 && l < W && j >= 0 && j < H){
                    //
                    temp_score = score(antenas[antena_i], l, j, buildings[i]);
                    if(temp_score > max_score && inCoords(l, j) == false){
                        max_score = temp_score;
                        c.x = l;
                        c.y = j;
                    }
                    //
                }
			}
			if(j >= y) 
				k -= 1;
			else
				k += 1;
		}
    }

	c.id = antenas[antena_i].id;
	return c;
}

void debug(int **map){
    //DEBUG MAP
	cout << "Width: " << W << "\nHeight: " << H << "\n";

	//DEBUG BUILDINGS /*
	for (int i = 0; i < N; ++i) {
		cout << "x: " << buildings[i].x << "\ty: " << buildings[i].y << "\tLatency: " << buildings[i].latency << "\tSpeed: " << buildings[i].connection_speed << "\n";
	} // */
	//DEBUG ANTENAS /*
	for (int i = 0; i < M; i++){
		cout << "Range: " << antenas[i].range << "\tSpeed: " << antenas[i].connection_speed << "\n";
	}  // */

	// HEAT MAP
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
}



int main (int argc, char *argv[]){
    
    //ios_base::sync_with_stdio(false);
	ofstream myFile;
	myFile.open(argv[1]);

	cin >> W >> H >> N >> M >> R;

	int max_range = -1;
	int hId = 0;
		
	//input
	for (int i = 0; i < N; ++i) {
		cin >> buildings[i].x >> buildings[i].y >> buildings[i].latency >> buildings[i].connection_speed;
	}
		
	for (int i = 0; i < M; i++){
		antenas[i].id = i;
		cin >> antenas[i].range >> antenas[i].connection_speed;
		
		//TODO SORTOWANIE STRUKTURY

		/*if(antenas[i].range > max_range) {
			hId = i;
			max_range = antenas[i].range;
		} */
	}

    sort(antenas, antenas+M,
        [](const antena &a, const antena &b) ->
        bool {
            return a.connection_speed > b.connection_speed;
        }
    );


    myFile << M << "\n";
	for (int i = 0; i < M; ++i) { // BARDZO NAIWNE WYZNACZANIE NAJLEPSZEGO USTAWIENIA ANTENY DLA STRUKTURY
        
        coords[i] = drawHeatMap(i);

        myFile << coords[i].id << " " << coords[i].x << " " << coords[i].y << "\n";
	}
	
	//debug(heat_map);
	myFile.close();
	return 0;
}


// 