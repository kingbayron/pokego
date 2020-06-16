#include <iostream>
#include <fstream>
#include <stdbool.h>
#include <utility>
#include <stdio.h>
#include <iomanip>
#include <string.h>
#include <vector>
#include <map>
#include<cmath>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <algorithm>
#include <random>
#include <chrono>
#include<sys/stat.h>
using namespace std;
using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::sort;
int main(int argc, char* argv[]){
	string linea;
	ifstream archivo;
	archivo.open(argv[1],ios::in);
	getline(archivo,linea);
	cout<<"Linea del archivo"<<endl;
	while(!archivo.eof()){
		getline(archivo,linea);
		cout<<"Linea del archivo"<<endl;
	}
}