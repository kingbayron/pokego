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
unsigned t0,t1,t2,t3;
static std::random_device rd;  // Random device engine, usually based on /dev/random on UNIX-like systems
static std::mt19937_64 rng(rd());
typedef pair<int, vector<int> > par;
typedef pair<int, int > parint;
struct Pokeparada{ 														//estructura
	int id;
	int cluster;
	double x;
	double y;
	int beneficios;
};
struct Centroide{
	double x;
	double y;
};
Centroide busquedacentroide(vector<Pokeparada>a ){
	double x,y;
	for (int i = 0; i < a.size(); ++i){
		x=x+a[i].x;
		y=y+a[i].y;
	}
	Centroide centro;
	centro.x=x/a.size();
	centro.y=y/a.size();
	return centro;

}
int nodocentroide(Centroide a, vector<Pokeparada> b){
	int nodo=0;
	double distancia=sqrt(pow((a.x - b[0].x),2)+pow((a.y - b[0].y),2));
	for (int i = 1; i < b.size(); ++i){
		double dist1=sqrt(pow((a.x - b[i].x),2)+pow((a.y - b[i].y),2));
		if(dist1<distancia){
			distancia=dist1;
			nodo=i;
		}
	}
	return nodo;
}
void imprimirStruct(vector<Pokeparada> a){
	for (int j = 0; j < a.size(); j++) {								// imprime arreglo de struct pokeparada con id, cluster al que pertenece y beneficios
		cout<<"La pokepara numero "<<a[j].id<<endl;
		cout<<"Pertenece al cluster "<< a[j].cluster<<endl;
		cout<<"Tiene unos beneficios de "<<a[j].beneficios<<endl;
		cout<<"----------------------------------"<<endl;
	}
}
void printVec(vector<int> vect){
    ///imprime vector
	for(int i = 0; i < vect.size(); i++)
		cout<<vect[i]<<" ";
	cout<<endl;
}
void printVec2(vector<double> vect){
    ///imprime vector
	for(int i = 0; i < vect.size(); i++)
		cout<<vect[i]<<" ";
	cout<<endl;
}
vector<int> structaint(vector<Pokeparada> a){
	vector<int> b;
	for (int i = 0; i < a.size(); ++i){
		b.push_back(a[i].id);
	}
	return b;
}
vector<Pokeparada> intastruc(vector<int>a,vector<Pokeparada> b){
	vector<Pokeparada> aux;
	for (int i = 0; i < a.size(); ++i){
		aux.push_back(b[a[i]]);
	}
	return aux;
}
void printmatrix(vector<vector<double> > a){
	for (int i = 0; i < a.size(); ++i){
		for (int j = 0; j < a.size(); ++j){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
		cout<<"-----------------"<<endl;
	}
}
map<int,int> mapaverif(int numcluster){
	map<int,int> a;
	for (int i = 0; i < numcluster; ++i){
		a.insert(parint(i,0));
	}
	return a;
}
double calculaValor(vector<int> vect,vector<vector<double> > ciudades){
	double costo =0;
	if(vect.size()==0){
		return costo;
	}														
	int anterior,siguiente;
	anterior=vect[0];													//primer nodo del tour
	for (int i = 1; i < vect.size(); ++i){									// evalua los costos desde el primer nodo con el segundo, el segundo con el tercero....y n-1 con n
		siguiente=vect[i];												//asignacion de siguiente (sigueitne nodo a anterior )
		costo=costo+ciudades[anterior][siguiente];						//suma de costos
		anterior=siguiente;												//nodo sigueinte pasa a ser anterior 
	}
	costo=costo+ciudades[vect[0]][vect[vect.size()-1]];
	return costo;
}
map<int,vector<int> > cluster(int numcluster,vector<Pokeparada> b){
	map<int, vector<int> > clusters;
	vector<int> a;
	for (int i = 0; i < numcluster; ++i){
		clusters.insert(par(i,a));
	}
	for (int i = 0; i < b.size() ; ++i){
		clusters[b[i].cluster].push_back(b[i].id);
	}
	return clusters;

}
bool allclustersvisited(map<int,int> a){
	int clus=0;
	for (int i = 0; i < a.size(); ++i){
		if(a[i]==1){
			clus++;
		}
	}
	if(clus==a.size()){
		return true;
	}else{
		return false;
	}
}
vector<int> valorenmapa(int a,map<int,vector<int> > b){
	vector<int> aux;
	map<int, vector<int> >::iterator p = b.begin();
	while (p != b.end() ){
		for (int i = 0; i < p->second.size(); ++i){
			if(p->second[i]==a){
				aux= p->second;
			}
		}
		p++;
	}
	return aux;
}
vector<int> eliminarnodosdecluster(vector<int>a,vector<int>b){
	vector<int> aux=a;
	for (int i = 0; i < b.size(); ++i){
		for (int j = 0; j < aux.size(); ++j){
			if(aux[j]==b[i]){
				aux.erase(aux.begin()+j);
				break;
			}
		}
	}
	return aux;
}
int nodomenordistancianodovector(int a,vector<int> b,vector<vector<double> > c){
	double costo;
	int nodo;
	costo=c[a][b[0]];
	nodo=b[0];
	for (int i = 0; i < b.size(); ++i){
		if(costo>c[a][b[i]] && c[a][b[i]]!=0){
			costo=c[a][b[i]];
			nodo=b[i];
		}
	}
	return nodo;
}
void clustervisita(map<int,int> &a,map<int,vector<int> >b,int nodovisitado){
	map<int, vector<int> >::iterator p = b.begin();
	while (p != b.end() ){
		for (int i = 0; i < p->second.size(); ++i){
			if(p->second[i]==nodovisitado){
				a[p->first]=1;
				break;
			}
		}
		p++;
	}

}
void printmap(map<int,int>a){
	cout<<"--------------------"<<endl;
	map<int, int >::iterator p = a.begin();
	while (p != a.end() ){
		cout << setw(10) << p->first << setw(10)<<p->second<<endl;
		p++;
	}
	cout<<"--------------------"<<endl;
}
vector<int> complementosol(vector<int>solucion,vector<int>complemento){
	if(solucion.size()==0){
		return complemento;
	}else{
		vector<int> a=complemento;
		vector <int> b=solucion;
		std::sort (b.begin(),b.end());
		for (int i = 0; i < b.size(); ++i){
			a[b[i]]=-1;
		}
		vector<int> complementosolucion;
		for (int i = 0; i < a.size(); ++i){
			if(a[i]!=-1){
				complementosolucion.push_back(a[i]);
			}
		}
		return complementosolucion;
	}
	
}
void escribirfile(ofstream &outputFile,vector<int> vect,vector<vector<double> > a){
	outputFile<<"Posible solucion"<<endl;
	for(int i = 0; i < vect.size(); i++)
		outputFile<<vect[i]<<" ";
	outputFile<<endl;
	outputFile<<"Costo Solucion: "<<calculaValor(vect,a)<<endl;
	outputFile<<"La solucion tiene un largo de: "<<vect.size()<<endl;
}
string fecha(){
	time_t now=time(0);
	tm *time=localtime(&now);
	string dia =to_string(time->tm_mday);
	string mes = to_string(time->tm_mon+1);
	string year= to_string(time->tm_year+1900);
	string hour= to_string(time->tm_hour);
	string min= to_string(time->tm_min);
	string seg= to_string(time->tm_sec);
	string fecha=dia+"M"+mes+"Y"+year+"_H"+hour+"M"+min+"S"+seg;
	return fecha;

}
void crearGML(vector<int>nuevasolucion,vector<int>complementosolucion ,char*a,int clusters,vector<Pokeparada> b){
	ofstream Graphics(strcat(a,"/Grafico.gml"));
	vector<string> colors ={"#FF0000","#00FF00","#0000FF","#FFFF00","#00FFFF","#FF00FF","#5E5E5E","#000080","#000000","#008000","#008080"};
	vector<string> formas ={"Rectangle","roundrectangle","diamond","circle","fat arrow","hexagon","octagon","star","parallelogram","trapezoid"};
	vector<Centroide> formaycolor;
	int F=0;
	int C=0;
	for (int i = 0; i < clusters; ++i){
		if(F<formas.size()){
			Centroide a;
			a.x=F;
			a.y=C;
			formaycolor.push_back(a);
			F++;
		}else{
			F=0;
			C++;
		}
		
	}
	if (!Graphics.is_open()) { // check for successful opening
		cout << "Output file could not be opened Terminating" << endl;
		exit(-1);
	}
	Graphics << "graph [ hierarchic 1 directed 1" << endl;

	for ( int j = 0; j < complementosolucion.size(); j++){

		Graphics << "node [ id " << complementosolucion[j]<< " "
		<< "graphics [ x " << b[complementosolucion[j]].x * 10 << " "
		<< "y " << b[complementosolucion[j]].y * 10 << " "
		<< "w 11  h 11 type \""<<formas[formaycolor[b[j].cluster].x]<<"\" fill  \""<<colors[formaycolor[b[j].cluster].y]<< "\"] LabelGraphics"
		<< " " << "[text " << " " << "\"" << complementosolucion[j]
		<< "\"" << " " << "fontSize 7 ] ]" << endl;

	}
	if(nuevasolucion.size()!=0){
		Graphics << "node [ id " << nuevasolucion[0] << " "
		<< "graphics [ x " << b[nuevasolucion[0]].x * 10 << " "
		<< "y " << b[nuevasolucion[0]].y * 10  << " "
		<< "w 11  h 11 type \"triangle\" fill  \"#643200\"] LabelGraphics"
		<< " " << "[text " << " " << "\""
		<< nuevasolucion[0] << "\"" << " " << "fontSize 7 ] ]" << endl;
		for (int i = 1; i < nuevasolucion.size(); i++){
			Graphics << "node [ id " << nuevasolucion[i] << " "
			<< "graphics [ x " << b[nuevasolucion[i]].x * 10 << " "
			<< "y " << b[nuevasolucion[i]].y * 10  << " "
			<< "w 11  h 11 type \"triangle\" fill  \"#FF6600\"] LabelGraphics"
			<< " " << "[text " << " " << "\""
			<< nuevasolucion[i] << "\"" << " " << "fontSize 7 ] ]" << endl;
		}

		for (int l = 1; l < nuevasolucion.size(); ++l)
		{
			Graphics << "edge [ source " << " " << nuevasolucion[l-1];

			Graphics << " " << "target" << " "
			<< nuevasolucion[l] << " " << "graphics [ fill \""
			<< "#5E5E5E" << "\" targetArrow \"standard\" ] ]"
			<< endl;
		}
		Graphics << "edge [ source " << " " << nuevasolucion[nuevasolucion.size()-1];

		Graphics << " " << "target" << " "
		<< nuevasolucion[0] << " " << "graphics [ fill \""
		<< "#5E5E5E" << "\" targetArrow \"standard\" ] ]"
		<< endl;
	}
	Graphics << "]" << endl;
	Graphics.close();
}
vector<double> distanciascentroide(Centroide a, vector<Pokeparada> b){
	vector<double> dist;
	for (int i = 0; i < b.size(); ++i){
		dist.push_back(sqrt(pow((a.x - b[i].x),2)+pow((a.y - b[i].y),2)));
	}
	return dist;
}
double promdistcentroide(vector<double> a){
	double aux=0;
	for (int i = 0; i < a.size(); ++i){
		aux=aux+a[i];
	}
	return aux/a.size();
}
vector<int> nodosausar(vector<int>a,double b,vector<double>c){
	vector<int> aux;
	for (int i = 0; i < c.size(); ++i){
		if(c[i]<=b){
			aux.push_back(a[i]);
		}
	}
	return aux;
}
bool acompare(Centroide lhs, Centroide rhs) {
	return lhs.x < rhs.x;
}
vector<int> greedy(vector<int>a,vector<vector<double> >b,map<int,vector<int> >c,map<int,int>d,ofstream &outputFile,double presupuesto,int nodos,vector<Pokeparada> auxpokeparada, char* str1){
	Centroide centro;
	vector<Pokeparada> poke = intastruc(a,auxpokeparada);
	centro=busquedacentroide(poke);

	vector<int> nuevasolucion=structaint(auxpokeparada);
	vector<Pokeparada> complementostruc = intastruc(nuevasolucion,auxpokeparada);
	vector<double> dist=distanciascentroide(centro,complementostruc);
	vector<Centroide> centros;
	for (int i = 0; i < dist.size(); ++i){
		Centroide aux;
		aux.x=dist[i];
		aux.y=nuevasolucion[i];
		centros.push_back(aux);
	}
	sort(centros.begin(),centros.end(),acompare);
	int iter=0;

	vector<int> solucion;
	vector<int> aux=a;
	map<int,int> aux2=d;
	map<int,int> aux3=d;
	double costo;
	int primernodo=centros[iter].y;
	cout<<"primer nodo"<<primernodo<<endl;
	int primernodo2=primernodo;
	solucion.push_back(primernodo);
	costo=calculaValor(solucion,b);
	escribirfile(outputFile,solucion,b);
	clustervisita(aux2,c,primernodo);
	bool verdad=allclustersvisited(aux2);
	while(verdad!=true && costo<=presupuesto){
		aux=eliminarnodosdecluster(aux,valorenmapa(primernodo,c));
		primernodo=nodomenordistancianodovector(primernodo,aux,b);
		solucion.push_back(primernodo);
		escribirfile(outputFile,solucion,b);
		clustervisita(aux2,c,primernodo);
		verdad=allclustersvisited(aux2);
		costo=calculaValor(solucion,b);
	}
	escribirfile(outputFile,solucion,b);
	costo=calculaValor(solucion,b);
	while(costo>presupuesto){
		iter++;
		cout<<iter<<endl;
		aux2=aux3;
		solucion.erase(solucion.begin(),solucion.begin()+solucion.size());
		aux=a;
		primernodo=centros[iter].y;
		primernodo2=primernodo;
		solucion.push_back(primernodo);
		costo=calculaValor(solucion,b);
		escribirfile(outputFile,solucion,b);
		clustervisita(aux2,c,primernodo);
		verdad=allclustersvisited(aux2);
		while(verdad!=true && costo<=presupuesto){
			aux=eliminarnodosdecluster(aux,valorenmapa(primernodo,c));
			primernodo=nodomenordistancianodovector(primernodo,aux,b);
			solucion.push_back(primernodo);
			escribirfile(outputFile,solucion,b);
			clustervisita(aux2,c,primernodo);
			verdad=allclustersvisited(aux2);
			costo=calculaValor(solucion,b);
		}
		escribirfile(outputFile,solucion,b);
		costo=calculaValor(solucion,b);
	}
	return solucion;
}
vector<int> mejorcaminoconnuevonodo(int nodoagregado, vector<int> a, vector<vector<double> > b, double presupuesto){
	vector<int>aux=a;
	vector<int>posible;
	vector<int>::iterator it;
	int cont=0;
	it=aux.begin();
	it=aux.insert(it,nodoagregado);
	posible=aux;
	double costo=calculaValor(aux,b);
	aux=a;
	for (it=it+1; it < aux.end(); ++it){
		it=aux.insert(it,nodoagregado);
		if(calculaValor(aux,b)<=calculaValor(posible,b) && calculaValor(aux,b)<=presupuesto){
			posible=aux;
		}
		aux=a;
	}
	return posible;
}

vector<int> greedy2(vector<int> a,vector<vector<double> > b,vector<int> todoslosnodos,ofstream &outputFile,double presupuesto,vector<Pokeparada> c){
	Centroide centro;
	vector<Pokeparada> poke = intastruc(a,c);
	centro=busquedacentroide(poke);
	vector<int> nuevasolucion=complementosol(a,todoslosnodos);
	vector<Pokeparada> complementostruc = intastruc(nuevasolucion,c);
	vector<double> dist=distanciascentroide(centro,complementostruc);
	double promediodisst=promdistcentroide(dist);
	nuevasolucion=nodosausar(nuevasolucion,promediodisst,dist);
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(nuevasolucion.begin(),nuevasolucion.end(),std::default_random_engine(seed));
	vector<int> aux=a;
	double costo=calculaValor(aux,b);
	int i=0;
	while(costo<=presupuesto && i<nuevasolucion.size()){
		aux=mejorcaminoconnuevonodo(nuevasolucion[i],aux,b,presupuesto);
		i++;
		costo=calculaValor(aux,b);
		if(costo>presupuesto){
			int pos;
			for (int j=0; j < aux.size(); ++j){
				if(aux[j]==nuevasolucion[i-1]){
					pos=j;
				}
			}
			aux.erase(aux.begin()+pos);
		}
	}
	return aux;

}
vector<int> nuevogreedy(vector<int> a, vector<vector<double> > b){
	double promediodistancias=calculaValor(a,b)/a.size();
	vector<int> aristassobreprom;
	for (int i = 1; i < a.size(); ++i){
		if(b[i][i-1]>promediodistancias){
			aristassobreprom.push_back(1);
		}else{
			aristassobreprom.push_back(0);
		}
	}
	if(b[0][b.size()-1]>promediodistancias){
		aristassobreprom.push_back(1);
	}else{
		aristassobreprom.push_back(0);
	}
	vector<int>nuevo;
	for (int i = 0; i < aristassobreprom.size(); ++i){
		
	}

	

}

/*vector<int> shuffle(vector<int> a) {
	vector<int> vect=a;
	int inicio, fin;
	inicio = 1+rand()%(a.size()-2);
	fin = 1+rand()%(a.size()-2);
    //cout<<inicio<<" "<<fin<<endl;
	swap(vect[inicio],vect[fin]);
	//printVec(vect);
	return vect;
}*/















vector<int> twooptswap(vector<int>a,int pos1,int pos2){
	vector<int> aux=a;
	swap(aux[pos1],aux[pos2]);
	return aux;
}
vector<int> twoopt(vector<int> &a, vector<vector<double> > b){
	vector<int> aux=a;
	int costo=calculaValor(aux,b);
	for (int i = 0; i < aux.size()-1; ++i){
		for (int j = i+1; j < aux.size(); ++j){
			vector<int> aux2=twooptswap(aux,i,j);
			int costo1=calculaValor(aux2,b);
			if(costo1<costo){
				aux=aux2;
				costo=costo1;
			}
		}
	}
	
	return aux;
}
vector<int> treeoptswap(vector<int>a,int pos1,int pos2,int pos3,vector<vector<double> >b){
	vector<int> aux1=a;
	vector<int> aux2=a;
	swap(aux2[pos2],aux2[pos3]);
	vector<int> aux3=a;
	swap(aux3[pos1],aux3[pos2]);
	vector<int> aux4=a;
	swap(aux4[pos1],aux4[pos3]);
	swap(aux4[pos1],aux4[pos2]);
	vector<int> aux5=a;
	swap(aux5[pos2],aux5[pos3]);
	swap(aux5[pos1],aux5[pos2]);
	vector<int> aux6=a;
	swap(aux6[pos1],aux6[pos3]);
	vector<vector<int> > combinaciones;
	combinaciones.push_back(aux1);
	combinaciones.push_back(aux4);
	combinaciones.push_back(aux5);
	combinaciones.push_back(aux6);
	double costo=calculaValor(aux1,b);
	int pos=0;
	for (int i = 1; i < combinaciones.size() ; ++i){
		if(calculaValor(combinaciones[i],b)<costo){
			costo=calculaValor(combinaciones[i],b);
			pos=i;
		}
	}
	return combinaciones[pos];
}
vector<int> treeopt(vector<int> &a, vector<vector<double> > b){
	vector<int> aux=a;
	vector<int> ciudadesaleatorias;
	for (int i = 0; i < 10; ++i){
		ciudadesaleatorias.push_back(rand()%(a.size()));
	}
	ciudadesaleatorias.erase( unique( ciudadesaleatorias.begin(), ciudadesaleatorias.end() ), ciudadesaleatorias.end() );
	int costo=calculaValor(aux,b);
	for (int i = 0; i < ciudadesaleatorias.size(); ++i){
		for (int j = 0; j < aux.size()-1; ++j){
			for (int k = j+1; k < aux.size(); ++k){
				vector<int> aux2=treeoptswap(aux,ciudadesaleatorias[i],j,k,b);
				int costo1=calculaValor(aux2,b);
				if(costo1<costo){
					aux=aux2;
					costo=costo1;
				}
			}
		}
	}	
	return aux;
}
double random_real(double initial, double last) {
	std::uniform_real_distribution<double> distribution(initial, last);
    return distribution(rng);  // Use rng as a generator
}
map<int,vector<int> > cluster2(int numcluster,vector<Pokeparada> aux,vector<int> b){
	map<int, vector<int> > clusters;
	vector<int> a;
	for (int i = 0; i < numcluster; ++i){
		clusters.insert(par(i,a));
	}
	for (int i = 0; i < b.size()-1 ; ++i){
		clusters[aux[b[i]].cluster].push_back(b[i]);
	}
	return clusters;

}
void imprimirnodosvisitados(map<int,vector<int> > a){
	map<int, vector<int> >::iterator p = a.begin();
	while (p != a.end() )
	{
		cout << setw(10) << p->first << setw(10); 
		for (int i = 0; i < p->second.size(); ++i){
			cout<<p->second[i]<<" ";
		};
		cout<<endl;
		p++;
	}
}
vector<int> eliminarnodo(vector<int> a,int numcluster,vector<Pokeparada> b,double presupuesto,vector<vector<double> >c){
	if(a.size()==numcluster){
		return a;
	}
	vector<int> aux;
	int dondedeletea;
	int terminator;
	double mayor;
	int lugar=0;
	map<int,vector<int> > mapaclustervisitados = cluster2(numcluster,b,a);
	vector<int> ndosxcluster;
	for (int i = 0; i < numcluster; ++i){
		ndosxcluster.push_back(mapaclustervisitados[i].size());
	}

	vector<Pokeparada>solucion = intastruc(a,b);
	vector<double>distanciaalcentroide = distanciascentroide(busquedacentroide(b),solucion);
	for(int i=0;i<distanciaalcentroide.size();i++){
		if(mayor<distanciaalcentroide[i]){
			mayor=distanciaalcentroide[i];
			lugar=i;
		}
	}
	for(terminator=0;terminator<solucion.size();terminator++){
		int cluster = solucion[lugar].cluster;
		if(ndosxcluster[cluster]>1){
			solucion.erase(solucion.begin()+lugar);
			aux = structaint(solucion);
			return aux;
		}else{
			distanciaalcentroide[lugar] = -1;
			mayor=0;
			terminator++;
			for(int i=0;i<distanciaalcentroide.size();i++){
				if(mayor<distanciaalcentroide[i]){
					mayor=distanciaalcentroide[i];
					lugar=i;
				}
			}	
		}
	}
	return a;
}

vector<int> eliminarnodoxcadacluster(vector<int> a,int numcluster,vector<Pokeparada> b,double presupuesto,vector<vector<double> >c){
	if(a.size()==numcluster){
		return a;
	}
	vector<int> aux;
	vector<int> aux2 = a;
	vector<int> clustconmasde1nodo;
	vector<int> ndosxcluster;
	double mayor=0;
	int numero;
	int lugar=0;

	map<int,vector<int> > mapaclustervisitados = cluster2(numcluster,b,a);

	for (int i = 0; i < numcluster; ++i){
		ndosxcluster.push_back(mapaclustervisitados[i].size());
	}

	for (int i = 0; i < ndosxcluster.size(); ++i){
		if(ndosxcluster[i]>3){
			clustconmasde1nodo.push_back(i);
		}
	}
	for(int i = 0; i<clustconmasde1nodo.size();i++){
		aux = mapaclustervisitados[clustconmasde1nodo[i]];
		vector<Pokeparada> auxi = intastruc(aux,b);
		vector<double> distroide = distanciascentroide(busquedacentroide(b),auxi);
		for(int i=0;i<distroide.size();i++){
			if(mayor<distroide[i]){
				mayor=distroide[i];
				lugar=i;
				numero = aux[lugar];
			}
		}
		for(int i = 0; i<aux2.size(); i++){
			if(aux2[i] == numero){
				aux2.erase(aux2.begin()+i);
			}
		}
		mayor=0;
	}
	return aux2;
}
vector<int> agregarnodoalazar(vector<int> solucion_actual,vector<vector<double> > distancias,  double presupuesto, vector<Pokeparada> todoslosnodos){
	vector<int> copiasolucion = solucion_actual;
	vector<int> complemento_solucion= structaint(todoslosnodos);
	complemento_solucion=complementosol(copiasolucion,complemento_solucion);
	Centroide centro = busquedacentroide(todoslosnodos);
	vector<double> distroide = distanciascentroide(centro,intastruc(complemento_solucion,todoslosnodos));
	int pos = 0;
	double distancia_menor= distroide[0];
	for (int i = 1; i < distroide.size(); ++i){
		if(distancia_menor>distroide[i]){
			distancia_menor=distroide[i];
			pos=i;
		}
	}
	vector<int>::iterator it;
	it = copiasolucion.begin();
	int random=rand()%copiasolucion.size();
	it=it+random;
	it=copiasolucion.insert(it,complemento_solucion[pos]);
	if(calculaValor(copiasolucion,distancias)<presupuesto){
		return copiasolucion;
	}else{
		int fin=0;
		while(fin<(solucion_actual.size()*3) || calculaValor(copiasolucion,distancias)<presupuesto){
			copiasolucion.erase(copiasolucion.begin()+random);
			random=rand()%copiasolucion.size();
			it = copiasolucion.begin();
			it=it+random;
			it=copiasolucion.insert(it,complemento_solucion[pos]);
			if(calculaValor(copiasolucion,distancias)<presupuesto){
				return copiasolucion;
			}
			fin++;
		}
		return solucion_actual;
	}


}
vector<int> elimniararistayagregarnodo(vector<int> solucionactual,vector<Pokeparada>todoslosnodos,vector<vector<double> > costos, double presupuesto){
	vector<int> nodos = structaint(todoslosnodos);
	vector<int> copiasolucion = solucionactual;
	vector<int> complementosolucion = complementosol(solucionactual,nodos);
	vector<int> posiblesol=nodos;
	vector<vector<int> > posibles_soluciones;
	vector<double> posibles_costos;
	vector<int>::iterator it;
	it = copiasolucion.begin();
	int pos=0;
	int posicion=0;
	while(it!= copiasolucion.end()){
		for (int i = 0; i < complementosolucion.size(); ++i){
			it=copiasolucion.insert(it,complementosolucion[i]);
			posibles_soluciones.push_back(copiasolucion);
			posibles_costos.push_back(calculaValor(copiasolucion,costos));
			copiasolucion.erase(copiasolucion.begin()+posicion);
		}
		int pos=0;
		for (int i = 1; i < posibles_soluciones.size(); ++i){
			if(posibles_costos[i]<=posibles_costos[pos]){
				pos=i;
			}
		}
		if(posibles_costos[pos]<=presupuesto && posibles_costos[pos]<= calculaValor(solucionactual,costos)*1.1){
			copiasolucion = posibles_soluciones[pos];
			it++;
			posicion++;
			posibles_soluciones.erase(posibles_soluciones.begin(),posibles_soluciones.end());
			posibles_costos.erase(posibles_costos.begin(),posibles_costos.end());
			complementosolucion = complementosol(copiasolucion,nodos);
		}
		posibles_soluciones.erase(posibles_soluciones.begin(),posibles_soluciones.end());
		posibles_costos.erase(posibles_costos.begin(),posibles_costos.end());
		it++;
		posicion++;
	}	
	return copiasolucion;
}
int nodoaagregarentrenodos(int nodoorigen, int nododestino,vector<vector<double> > costos){
	vector<double> costosdesdeorigen = costos[nodoorigen];
	double costo_origen_destino = costos[nodoorigen][nododestino];
	vector<int> nodosmenoresalcosto;
	for (int i = 0; i < costosdesdeorigen.size(); ++i){
		if(costosdesdeorigen[i]<costo_origen_destino && costosdesdeorigen[i]>0 ){
			nodosmenoresalcosto.push_back(i);
		}
	}
	vector<double> costosconunnuevonodo;
	for (int i = 0; i < nodosmenoresalcosto.size(); ++i){
		costosconunnuevonodo.push_back(costos[nodoorigen][nodosmenoresalcosto[i]]+costos[nodosmenoresalcosto[i]][nododestino]);
	}
	int pos=0;
	for (int i = 1; i < costosconunnuevonodo.size(); ++i){
		if(costosconunnuevonodo[i]<costosconunnuevonodo[pos] && costosconunnuevonodo[i]<=costo_origen_destino*1.05){
			pos=i;
		}
	}
	if(pos==0){
		if(costosconunnuevonodo[pos]<=costo_origen_destino*1.05 ){
			return nodosmenoresalcosto[pos];
		}
		else{
			return -1;
		}
	}else{
		return nodosmenoresalcosto[pos];
	}
}
int nodonoingresado(vector<int> solucionactual,int nodoagregar){
	int nodoagregado=nodoagregar;
	for (int i = 0; i < solucionactual.size(); ++i){
		if(nodoagregar==solucionactual[i]){
			nodoagregar=-1;
			break;
		}
	}
	return nodoagregar;
}

void eliminararistamasgrandequepromedio(vector<int> &solucionactual,vector<Pokeparada>todoslosnodos,vector<vector<double> > costos, double presupuesto){
	double promedioaristas = (calculaValor(solucionactual,costos)/solucionactual.size());
	vector<int> nodosmayoralpromedio2;
	for (int i = 0; i < solucionactual.size()-1; ++i){
		if(costos[solucionactual[i]][solucionactual[i+1]]>promedioaristas){
			nodosmayoralpromedio2.push_back(i);
		}
	}
	if(costos[solucionactual[solucionactual.size()-1]][solucionactual[0]]>promedioaristas){
		nodosmayoralpromedio2.push_back(solucionactual.size()-1);
	}	
	int cont = 0;
	vector<int> copiasolucion = solucionactual;
	vector<int>::iterator it;
	it = copiasolucion.begin();
	vector<vector<int> > solucionesprimernodo;
	vector<double> costossolucion1;
	if(nodosmayoralpromedio2.size()!=0){
		for (int k = 0; k < nodosmayoralpromedio2.size(); ++k){
			vector<int> posibles;
			vector<int>posibles2;
			if(nodosmayoralpromedio2[k]==solucionactual.size()-1){
				double distancia=costos[solucionactual[solucionactual.size()-1]][solucionactual[0]];
				for (int i = 0; i < todoslosnodos.size(); ++i){
					if(costos[solucionactual[nodosmayoralpromedio2[k]]][i]<distancia && costos[solucionactual[nodosmayoralpromedio2[k]]][i]!=0){
						posibles.push_back(i);
					}
				}
				for (int i = 0; i < todoslosnodos.size(); ++i){
					if(costos[solucionactual[0]][i]<distancia && costos[solucionactual[0]][i]!=0){
						posibles2.push_back(i);
					}
				}
			}else{
				double distancia=costos[solucionactual[nodosmayoralpromedio2[k]]][solucionactual[nodosmayoralpromedio2[k]+1]];
				for (int i = 0; i < todoslosnodos.size(); ++i){
					if(costos[solucionactual[nodosmayoralpromedio2[k]]][i]<distancia && costos[solucionactual[nodosmayoralpromedio2[k]]][i]!=0){
						posibles.push_back(i);
					}
				}
				for (int i = 0; i < todoslosnodos.size(); ++i){
					if(costos[solucionactual[nodosmayoralpromedio2[k]+1]][i]<distancia && costos[solucionactual[nodosmayoralpromedio2[k]+1]][i]!=0){
						posibles2.push_back(i);
					}
				}
			}
			if(posibles.size()==0 || posibles2.size()==0){
				break;
			}
			vector<int>repetidos;
			for (int i = 0; i < posibles.size(); ++i){
				for (int j = 0; j < posibles2.size(); ++j){
					if(posibles[i]<posibles2[j]){
						break;
					}
					if(posibles[i]==posibles2[j]){
						repetidos.push_back(posibles[i]);
					}
				}
			}
			if(repetidos.size()!=0){
				vector<int> repetidos2;
				int si=0;
				for (int i = 0; i < repetidos.size(); ++i){
					for (int j = 0; j < solucionactual.size(); ++j){
						if(repetidos[i]==solucionactual[j]){
							si=1;
						}
					}
					if(si==0){
						repetidos2.push_back(repetidos[i]);
					}
				}
				for (cont; cont < nodosmayoralpromedio2[k]+1; ++cont){
					it++;
				}
				if(repetidos2.size()!=0){
					for (int i = 0; i < repetidos2.size(); ++i){
						it=copiasolucion.insert(it,repetidos2[i]);
						if(calculaValor(copiasolucion,costos)<presupuesto &&calculaValor(copiasolucion,costos)<calculaValor(solucionactual,costos)*1.1){
							solucionesprimernodo.push_back(copiasolucion);
							costossolucion1.push_back(calculaValor(copiasolucion,costos));
						}
						copiasolucion=solucionactual;
					}

				}
			}		
		}
	}
	
	if(costossolucion1.size()!=0){
		int aux=0;
		for (int i = 1; i < costossolucion1.size(); ++i){
			if(costossolucion1[i]<costossolucion1[aux]){
				aux=i;
			}
		}
		cout<<"agrego un nodomas"<<endl;
		solucionactual=solucionesprimernodo[aux];
	}

}
 
 vector<int> iteratedlocalsearch(vector<int>a,vector<vector<double> >b,map<int,vector<int> >c,map<int,int>d,ofstream &outputFile,double presupuesto,int nodos,vector<Pokeparada> auxpokeparada, char* str1,string &shuffl,string &shuflleaumentaprecio,int numcluster){
	
	vector<int> s=greedy(a,b,c,d,outputFile,presupuesto,nodos,auxpokeparada,str1);
	cout<<"termino greedy"<<endl;
	vector<int> todoslosnodos=structaint(auxpokeparada);
	vector<int> Sposisble=s;
	vector<int>complementosolucion=complementosol(s,todoslosnodos);
	s=treeopt(s,b);
	cout<<"termino 3opt"<<endl;
	s=greedy2(s,b,todoslosnodos,outputFile,presupuesto,auxpokeparada);
	int history=0;
	int n=100;
	for (int i = 0; i < n; ++i){
		double random=random_real(0,1);
		if(random<0.1){
			double random2=random_real(0,1);
			if(random2<0.7){
				s = eliminarnodo(s,numcluster,auxpokeparada,presupuesto,b);
			}else{
				s = eliminarnodoxcadacluster(s,numcluster,auxpokeparada,presupuesto,b);
			}
		}else if(random>=0.1 && random<0.2){
			vector<int> s1=s;
			for (int j = 1; j < n/2 ; ++j){
				int rand1 = rand()%s.size();
				int rand2 = rand()%s.size();
				while(rand1==rand2){
					rand2 = rand()%s.size();
				}
				swap(s1[rand1],s1[rand2]);
				if(calculaValor(s1,b)>calculaValor(s,b)*1.1 || calculaValor(s1,b)>presupuesto){
					swap(s1[rand1],s1[rand2]);
				}
			}
			s=s1;
		}
		random=random_real(0,1);
		if(random<0.8){
			s=twoopt(s,b);
		}else{
			double costoS=calculaValor(s,b);
			for (int j = 0; j < auxpokeparada.size(); ++j){
				int rand1 = rand()%s.size();
				int rand2 = rand()%s.size();
				while(rand1==rand2){
					rand2 = rand()%s.size();
				}
				swap(s[rand1],s[rand2]);
				if(calculaValor(s,b)>costoS*1.1 ||calculaValor(s,b)>presupuesto){
					swap(s[rand1],s[rand2]);
				}
			}
		}
		s=greedy2(s,b,todoslosnodos,outputFile,presupuesto,auxpokeparada);
		s=elimniararistayagregarnodo(s,auxpokeparada,b,presupuesto);
		int larg=s.size();
		eliminararistamasgrandequepromedio(s,auxpokeparada,b,presupuesto);
			if(s.size()>larg){
			cout<<"se agrego un nodo"<<endl;
		}
		history++;
		if(Sposisble.size()<s.size()){
			Sposisble=s;
			history=0;
		}
		if(history==50){
			s=treeopt(s,b);
			history=0;
			cout<<"entro a 3opt"<<endl;
		}
	}
	escribirfile(outputFile,Sposisble,b);
	return Sposisble;
}
void csv(vector<int> a,vector<int> cantidadnodos,vector<double>time){
	double avgnodos,avgtime;
	for (int i = 0; i < cantidadnodos.size(); ++i){
		avgnodos=avgnodos+cantidadnodos[i];
		avgtime=avgtime+time[i];
	}
	avgnodos=avgnodos/cantidadnodos.size();
	avgtime=avgtime/cantidadnodos.size();
	ofstream outData;
	outData.open("outfile.csv", ios::app);
	outData <<","<<","<<","<<a.size()<<","<<","<<avgnodos<<","<<","<<avgtime<<endl;
	outData.close();
}


int main(int argc, char* argv[]){
	string lineainstancias,instancia,valor;
	ifstream instanciaarchivo;
	instanciaarchivo.open(argv[1],ios::in);
	while(!instanciaarchivo.eof()){
		getline(instanciaarchivo,lineainstancias);
		int espacio=0;
		for (int i = 0; i < lineainstancias.size(); ++i){
			if(lineainstancias[i]==' '){
				espacio=i;
				break;
			}
		}
		instancia=lineainstancias.substr(0,espacio);
		valor=lineainstancias.substr(espacio+1,lineainstancias.size());
		t0=clock();
		srand(time(NULL));
		char str[100];
		char str1[100];
		strcpy(str,instancia.c_str());
		strcat(str,"_");
		strcat(str,valor.c_str());
		strcat(str,"_");
		strcat(str,"D");
		strcat(str,fecha().c_str());

		//cout<<fecha()<<endl;

		mkdir(str,0777);
		strcpy(str1,str);
		ofstream outputFile(strcat(str,"/Soluciones.txt"));		
		outputFile<<"Se esta estudiando el archivo "<<instancia<< endl;			// archivo que e leera en ese omento
		outputFile<<"Con un presupuesto maximo de: "<<valor<<endl;
		string linea,arbol;												// string para lectura archivo
		int nodos;														// numero de nodos
		int clusters;													// numero de clusters
		char linea1[100];												// arreglo de caracteres para el uso de tokenizar
		int id;															// id del nodo
		int clust;														// cluster al que pertenece el nodo
		int pokeparada;													// beneficios de la pokeparada
		char *ptr;														// ptr para tokenizar
		int posx;
		int posy;
		int x;															// coordenada x para costo de viaje entre nodos
		int y;															// coordenada y para costo de viaje entre nodos
		double costo;													// costo de viaje entre nodos
		ifstream archivo;												// creacion de archivo
		archivo.open(instancia,ios::in);									// apertura de archivo
		getline(archivo,linea);											// obtencion linea del archivo
		strcpy(linea1,linea.c_str());									// pasar string a arreglo de caracteres
		ptr = strtok(linea1," ");										//  tokenizar arreglo de caracteres
		while(ptr != NULL){		
			if(strcmp(ptr,"Nodes")==0){
				ptr = strtok(NULL, " ");
				nodos=atoi(ptr);										// ingreso numero de nodos a la variable
				
				//cout<<"Existen este numero de nodos "<<nodos<<endl;

			}
			ptr = strtok(NULL, " ");
		}
		getline(archivo,linea);									//obtencion nueva linea de archivo
		strcpy(linea1,linea.c_str());
		ptr = strtok(linea1," ");
		while(ptr != NULL){
			if(strcmp(ptr,"Clusters")==0){
				ptr = strtok(NULL, " ");
				clusters=atoi(ptr)+1;										//ingreso numero de cluster a variable
				
				//cout<<"Existen este nuemro de clusters "<<clusters<<endl;

			}
			ptr = strtok(NULL, " ");
		}
		cout<<"----------------------"<<endl;
		double precios[nodos][nodos];									// matriz de precios de viajar de un nodo a otro
		vector<Pokeparada> pokeparadas;									// vector de Struct Pokeparada
		for (int i = 0; i < nodos; i++) {								// ingreso Struct a Arreglo "pokeparada"
			getline(archivo,linea);
		strcpy(linea1,linea.c_str());
		ptr = strtok(linea1," ");
		ptr = strtok(NULL, " ");
			id=atoi(ptr);												// id struct
			ptr = strtok(NULL, " ");
			clust=atoi(ptr);											// cluster struc
			ptr = strtok(NULL, " ");
			posx=atoi(ptr);
			ptr = strtok(NULL, " ");
			posy=atoi(ptr);
			pokeparada=1+rand()%(8);
			Pokeparada a;												// beneficios Struct
			a.id=id;													//ingreso de variables a struct
			a.cluster=clust;
			a.beneficios=pokeparada;
			a.x=posx;
			a.y=posy;
			pokeparadas.push_back(a);									// ingreso struct a vector de struct
		}
		vector< vector<double>> vecotorcosotos;							//vector de vectores de double
		vector<Pokeparada> auxpokeparada=pokeparadas;
    	vector<double> precio;											//vector de double
    	
    	//imprimirStruct(pokeparadas);
		
		while(!archivo.eof()){											// lectura de archivpo para obtencion de costos deviaje entre nodos
			getline(archivo,linea);
			if(linea.empty()){
				break;
			}
			strcpy(linea1,linea.c_str());
			ptr = strtok(linea1," ");
			ptr = strtok(NULL, " ");
			x=atoi(ptr);												// obtencion coordenada x (nodo partida)
			ptr = strtok(NULL, " ");
			y=atoi(ptr);												// obtencion coordenada y (nodo llegada)
			ptr = strtok(NULL, " ");
			costo=atof(ptr);											// obtencion costo viaje
			precios[x][y]=costo;										// ingreso costo a la matriz con x,y /partida, llegada
			precios[y][x]=costo;										// ingreso costo a matriz con y, x / llegada, partida
		}
		for (int i = 0; i < nodos; ++i){
			precios[i][i]=0;
		}
		for (int i = 0; i < nodos; ++i){								// algoritmo para psar de matriz a vector de vectores de double
			for (int j = 0; j < nodos; ++j){
				precio.push_back(precios[i][j]);						// ingreso de valores a vector de double
			}
			vecotorcosotos.push_back(precio);							// ingreso de vector de double a vector
			precio.erase(precio.begin(),precio.begin()+precio.size());	// borrado de vector de double para reiniciar ingreso
		}
		map<int,vector<int> > mapaclusters = cluster(clusters,pokeparadas);
		map<int,int> mapaverificacion=mapaverif(clusters);
		map<int, vector<int> >::iterator p = mapaclusters.begin();

		/*while (p != mapaclusters.end() ){
			cout << setw(10) << p->first << setw(10); 
			for (int i = 0; i < p->second.size(); ++i){
				cout<<p->second[i]<<" ";
			};
			cout<<endl;
			p++;
		}*/

		string shuffle="False";
		string shuffleaumentavalor="False";
		vector<int> complementosolucion=structaint(pokeparadas);
		vector<int> nodosinstacia;
		vector<double> tiempo;
		vector<int> mejor;
		t1=clock();
		double time1 = (double(t1-t0)/CLOCKS_PER_SEC);
		for (int i = 0; i < 10; ++i){
			cout<<"iteracion: "<<i<<endl;
			t2=clock();
			complementosolucion=structaint(pokeparadas);
			vector<int>	complementosolucion2=complementosolucion;
			vector<int> solucion=structaint(pokeparadas);
			solucion=iteratedlocalsearch(solucion,vecotorcosotos,mapaclusters,mapaverificacion,outputFile,stod(valor),nodos,auxpokeparada,str1,shuffle,shuffleaumentavalor,clusters);

			//solucion=greedy(solucion,vecotorcosotos,mapaclusters,mapaverificacion,outputFile,stod(valor),nodos,auxpokeparada,str1);
			//cout<<"Greedy"<< endl;
			//printVec(solucion);
			//solucion=greedy2(solucion,vecotorcosotos,complementosolucion,outputFile,stod(valor),pokeparadas);
			//cout<<"Greedy2, largo: "<<solucion.size()<< " , costo: "<<calculaValor(solucion,vecotorcosotos)<<endl;
			//printVec(solucion);//eliminarnodo(solucion,clusters,auxpokeparada,atof(argv[2]),vecotorcosotos);
			//eliminararistamasgrandequepromedio(solucion,auxpokeparada,vecotorcosotos,stod(valor));
			//cout<<"eliminar aristamasgrandeque promedio, largo: "<<solucion.size()<< " , costo: "<<calculaValor(solucion,vecotorcosotos)<<endl;
			//printVec(solucion);
			//cout<<"luego "<<endl;
			//printVec(solucion);
			//cout<<"eliminar arista"<<endl;
			//printVec(solucion);
			//solucion=agregarnodoalazar(solucion,vecotorcosotos,stod(valor),auxpokeparada);
			//printVec(solucion);
			//solucion=agregarnodoalazar(solucion,vecotorcosotos,stod(valor),auxpokeparada);
			//printVec(solucion);

			nodosinstacia.push_back(solucion.size());
			if(mejor.size()<solucion.size()){
				mejor=solucion;
			}
			t3=clock();
			double time = (double(t3-t2)/CLOCKS_PER_SEC);
			tiempo.push_back(time+time1);
		}

		//void eliminarnodo(vector<int> &a,int numcluster,vector<Pokeparada> b,double presupuesto,vector<vector<double> >c)
		//greedy(vector<int>a,vector<vector<double> >b,map<int,vector<int> >c,map<int,int>d,ofstream &outputFil,double presupuesto,int nodos,vector<Pokeparada> auxpokeparada char*str1)
		//solucion=iteratedlocalsearch(solucion,vecotorcosotos,mapaclusters,mapaverificacion,outputFile,atof(argv[2]),nodos,auxpokeparada,str1,shuffle,shuffleaumentavalor,clusters);
		//vector<int> greedy2(vector<int> a,vector<vector<double> > b,vector<int> todoslosnodos,ofstream &outputFile,double presupuesto)
		//solucion=greedy2(solucion,vecotorcosotos,complementosolucion,outputFile,atof(argv[2]));
		//vector<int> mejorcaminoconnuevonodo(int nodoagregado, vector<int> a, vector<vector<double> > b, double presupuesto)

		complementosolucion=complementosol(mejor,complementosolucion);

		printVec(mejor);
		cout<<"largo solucion"<<mejor.size()<<endl;
		cout<<"tiene un costo de: "<<calculaValor(mejor,vecotorcosotos)<<endl;
		cout << "........................\n";
		crearGML(mejor,complementosolucion,str1,nodos,auxpokeparada);
		csv(mejor,nodosinstacia,tiempo);
	}
	
}
