/*
file name: KnaspackProblem_beesAlgorithm.cpp
date: 2010-05-05, 2010-05-13
autor: Sebastian Kupny skupny@gmail.com

-------------------------------------------------------
Kolego:
Na samym dole jest main.
W main jest wywolana funkcja test
w test wykonywane sa wszystkie obliczenia.

Ciebie interesuje jedynie funkcja o oryginalnej nazwie: KnaspackProblemSolutinUsingBeeAlgorithm, opisana jest ponizej:
-------------------------------------------------------

Description:
functions:
double KnaspackProblemSolutinUsingBeeAlgorithm(double BagSize, KnaspackProblem &e,int SkautBeens, int WorkerBeens, int A_counOfIteration){
Funkcja ta kompleksowo rozwiazuje problem plecakowy uzywajac algorytmu pszczelego

paraterers:
	gdzie poszczegolne parametry to:
	-BagSize - rozmiar plecaka. Maksymalny rozmiar plecaka ograniczajacy wage elementow.
	-KnaspackProblem e - struktura danych przechowujaca informacje o liczbie elementow do wyboru oraz te elementy. Mozesz o niej poczytac (ale kod i komentarze) niestety dokumentacja w tworzeniu. Na jej rzecz mozna wywolac funkcje, ktora znajdzie zachlanne rozwiazanie problemu. Do zaadaptowania jest algorytm dynamiczny
	-SkautBeens - liczba skautow, ze wzgledu na ich odmienna funkcje podaje sie jako parametr. 
	-WorkerBeens - liczba robotnic. 
	-A_counOfIteration - liczba iteracji w jakich znajdowane bedzie optymalne rozwiazanie. 

returns:
	Funkcja zwraca maksymalna osiagnieta wartosc a dla niej zapamietana w kodzie jest kombinacja wybranych elementow.
	Mozna ja odczytac, ale nalezy zrobic to z poziomu tej funkcji KnaspackProblemSolutinUsingBeeAlgorithm.
Usage:
	W zaleznosci od danych wejsciowych mozna badac otrzymane z funkcji wyniki. Do ustalania parametrow problemu plecakowego nalezy uzyc 
	klasy KnaspackProblem

Compile:
		>g++ beesAlgorithm.cpp  -o beesAlgorithm.x


TODO: 
Zrobic dokumentacje z prawdziwego zdarzenia.
Mozna zrobic: podzielic ladnie plik na naglowki, pliki biblioteczne, napisac Makefilea i wiele innych przyjemnych rzeczy:))
*/

#include <string>
#include <iostream>
#include <sstream>

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <unistd.h> //sleep usleep
#include <limits.h>

#define DEBUG false //jaki tryb pracy programu: normalny czy debugowania  DEBUG={true,false}
#define INV false //INVESTIGATE

using namespace std;

//doublToStr funkcja konwertujaca wartosc liczbowa na string
string doublToStr(double number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

void printTable(int * t, int size){
		for(int i =0;i<size;i++)
			cout << t[i] << endl;
		return;
}
void printTable(double * t, int size){
		for(int i =0;i<size;i++)
			cout << t[i] << endl;
		return;
}


//Element z plecaka. Mozna bylo to lepiej zrobic bez seterow. ale nie moglem wtedy alokowac tablicy w klasie KnaspackProblem 
//To mozna poprawic ale trzeba sie douczyc. Jak alokowac pamiec dla elementow bez domyslnego konstruktora przy uzyciu operatora new.
//Klasa zawiera dwa pola i reperezentuje element ktory mozna zabrac. Posiada informacje o jego wadze oraz cenie calkowitej.
//
class Element{

private:
	double weight;	
	double price;

	void setWeight(double A_weight){
		weight = A_weight;
	}
	void setPrice(double A_price){
		price = A_price;
	}

public:
	
	Element(double A_weight=0., double A_price=0.){
		weight = A_weight;
	 	price = A_price;
	}
	double getWeight(){
		return weight;
	}
	double getPrice(){
		return price;
	}
	string toString(){
		string s = "{"+doublToStr(weight)+", "+doublToStr(price)+"}";
		return s;
	}	
	friend class KnaspackProblem;
};


//KnaspackProblem klasa ktora reprezentuje konkretny problem plecakowy. 
// Konstruktor inicjalizuje problem zadana jako argument iloscia elementow. Podane sa takze jako argumenty
// konstruktora  maksymalna cena oraz maksymalna waga elementu. Ktory moze sie w nim znalezc.
// Klasa inicjalizuje elementy wartosciami losowymi o rozkladzie "jednostajnym" na ile pozwala metoda rand.
// posiada takze metode do obliczenia rozwiazania problemu plecakowego metoda zachlanna:)
// oraz metode sortujaca elementy. Dzieku uzyciu domysnego operatora= dla klasy Element
// Zakomentowane sa fragmenty kodu dzialajacego pierwotnie na tablicach. Podejscie obiektowe ma jednak wygodniejsza forme i 
// zostanie tutaj uzyte. Mam nadzieje ze uchroni przed bledami ktore czesto pojawiaja sie przy uzywaniu tablic.

class KnaspackProblem{

	private:
		int countOfElements;
		//double  ** elements;	//waga = elements[x][0], cena = elements[x][1] <- KONWENCJA
		Element * elem;	
	public:
		//k-or
		KnaspackProblem(int A_countOfElements, double maxWeight, double maxPrice):countOfElements(A_countOfElements){
		
		elem = new Element[countOfElements];		
		for(int i =0; i< 	countOfElements;i++){
			elem[i].setWeight(((double)rand())/((double)RAND_MAX) * maxWeight);
			elem[i].setPrice(((double)rand())/((double)RAND_MAX) * maxPrice);
		}		
	}

	/*
	//k-or dla Klasy z uzyciem tablicy.
	KnaspackProblem(int A_countOfElements, double maxWeight, double maxPrice):countOfElements(A_countOfElements){
		
		elements = new double*[countOfElements];

		for(int i =0; i< 	countOfElements;i++)
			elements[i] = new double[2];

		for(int i =0; i< 	countOfElements;i++){
			elements[i][0] =  ((double)rand())/((double)RAND_MAX) * maxWeight;
			elements[i][1] = ((double)rand())/((double)RAND_MAX) * maxPrice;		
		}
   */
	Element getElementAt(int index){
		if(index <0 & index >= countOfElements){
			throw string ("ERROR: Nieprawidlowe odowlanie sie do indeksu elementu");
		}
		return elem[index];
	}
	int getCountOfElements(){
		return countOfElements;
	}

	//sortowanie po cenie jednostkowej
	void sortByUnitPrice(){

		Element tempE;
		double maxUnitPrice =0.;
		int IndexOfMax;

		for(int i =0; i< 	countOfElements;i++){
			maxUnitPrice =0.;
			for(int j =i; j< 	countOfElements;j++){
				if(elem[j].getWeight()==0){
					throw string("ERROR: Zerowa masa elementu, a nie mozna dzielic przez zero. Uruchom program jeszcze raz.");
				}
				if((elem[j].getPrice()/elem[j].getWeight()) > maxUnitPrice){
					maxUnitPrice = (elem[j].getPrice()/elem[j].getWeight());
					IndexOfMax = j;
				}			
			}
			tempE = 	elem[i];
			elem[i] = elem[IndexOfMax];
			elem[IndexOfMax] = tempE;
		}
	}
	//posortowanie elementow po cenie
	void sortByPrice(){

		Element tempE;
		double maxPrice =0.;
		int IndexOfMax;
		for(int i =0; i< 	countOfElements;i++){
			maxPrice =0.;
			for(int j =i; j< 	countOfElements;j++){
				if(elem[j].getPrice() > maxPrice){
						maxPrice = elem[j].getPrice();
						IndexOfMax = j;
				}			
			}
			tempE = 	elem[i];
			elem[i] = elem[IndexOfMax];
			elem[IndexOfMax] = tempE;
		}

	}
	//znalezienie rozwiazania metoda zachlanna sortowanie po cenie jednostkowej.
	double getBetterBruteForceValue(double BagSize){

		double currWeight =0.;
		double myPrice =0.;
		int index = 0;
		sortByUnitPrice();
		for(int i =0; i< 	countOfElements;i++){
			if((elem[i].getWeight()+currWeight) <=BagSize){ //jezeli element sie zmiesci to go dokladamy:))
				currWeight += elem[i].getWeight();
				myPrice    += elem[i].getPrice();
				//cout << "Dodaje=" << elem[i].toString()<<". ";	
			}
		}
		return myPrice;
	}

	//rozwiazanie metoda zachlanna. Sortowanie po cenie jednostkowej
	double getBruteForceValue(double BagSize){

		double currWeight =0.;
		double myPrice =0.;
		int index = 0;
		sortByPrice();
		for(int i =0; i< 	countOfElements;i++){
			if((elem[i].getWeight()+currWeight) <=BagSize){ //jezeli element sie zmiesci to go dokladamy:))
				currWeight += elem[i].getWeight();
				myPrice    += elem[i].getPrice();	
			}
		}
		return myPrice;
	}
	
	//znalezienie rozwiazania najprostrze.
	//do usuniecia, nawet za glupia na glupia
	double getDumpBruteForceValue(double BagSize){

		double currWeight =0.;
		double myPrice =0.;

		int index = 0;
		sortByPrice();
		//		for(int i =0; i< 	countOfElements, ;i++){
		while(index< countOfElements && ((currWeight+elem[index].getWeight())<=BagSize)){
			currWeight += elem[index].getWeight();
			myPrice    += elem[index].getPrice();
			index++;
		}
		return myPrice;
	}

	//funkcja ma tworzyc stringa, ale na razie wypisuje na konsole.
	void toString(){
		//doublToStr
		string KnaspackPString = "";
		cout << "W znajduja sie (waga, cena)" <<endl;
		for(int i =0; i< 	countOfElements;i++){		
			cout << "{"<< elem[i].getWeight() <<", "<< elem[i].getPrice()<<"}"<<endl;
		}
		return;
	}
	//d-or
	~KnaspackProblem(){
	    delete[] elem;
	}
};

//zwraca wskaznik do tablicy z permutacja liczb od 0 do size: [0;size]
int * getIndexRand(int size){

	int temp=0;;
	int toChange1=0, toChange2=0;
	int * wsk = new int[size];
//	srand(NULL);
	for(int i =0;i<size;i++){
		wsk[i]=i;
	}
	for(int i =0;i<10*size;i++){
		toChange1 = i%size; 
		toChange2 =rand()%size;
		//cout << toChange1 <<" "<< toChange2 << endl;
		temp = wsk[toChange2];
		wsk[toChange2] = wsk[toChange1];
		wsk[toChange1] = temp;
		//cout << wsk[toChange1] <<" "<< wsk[toChange2] << endl;
	}
	return wsk;
}


//funkcja do sprawdzania poprawnosci programu. Przyjmuje jako parametry problem plecakowy,
//wskaznik do tablicy z wybranymi indeksami oraz liczbe wybranych indeksow/elementow.
//zwraca mase wybranych elementow. Nie porownuje jej z masa dozwolona.
double sprawdzenieElementow(KnaspackProblem &e, int *bestPosition, int bestPositionIndex ){
	double tempW=0.;
	double tempP=0.;
	double sumW =0.;
	double sumP =0.;
	for(int i = 0 ;i <bestPositionIndex; i++){
		tempW = e.getElementAt(bestPosition[i]).getWeight();
		tempP = e.getElementAt(bestPosition[i]).getPrice();
		//cout << tempW << " " << tempP << endl;//", e=" << e.getElementAt(bestPosition[i]).toString << endl;
		sumW +=tempW;
		sumP +=tempP;
	}
	//cout << "SPRAWDZENIE: W=" << sumW << ", PRICE=" << sumP << endl;
	return sumW;
}

//funkcja oblicza dla danej tablicy o zadanym rozmiarze wartosc przchowywana w plecaku.
//jako parametr nalezy przekazac problem, tablice z indeksami wybranych elementow oraz rozmiar tablicy z indeksami.
double calculateSkautValue(KnaspackProblem &e, int * indTab, double A_BagSize, int &LastIndex, double &TotalWeight){

	double currWeight=0.;
	double myPrice =0.;
	//cout << "bag size: " << A_BagSize<<endl;

	int index =0;

	//	e.toString();
	while(index< e.getCountOfElements() && ((currWeight+e.getElementAt(indTab[index]).getWeight())<=A_BagSize)){
		currWeight += e.getElementAt(indTab[index]).getWeight();
		myPrice    += e.getElementAt(indTab[index]).getPrice();
		//cout <<"\t\tIteracja:"<<index<<" ("<<indTab[index] <<") +Elem:="<<e.getElementAt(indTab[index]).toString() <<endl;
		//cout<< " "<<indTab[index] << ": "<< e.getElementAt(indTab[index]).getWeight()<<" " << e.getElementAt(indTab[index]).getPrice() <<endl;
		index++;
	}
	LastIndex= index;
	TotalWeight = currWeight;
	return myPrice;
};


//funkcja oblicza cene oraz ciezar elementow wybranych. Ich indeksy sa w tablicy indTab, liczba wybranych to A_limit.
// Ponadto zwraca parametry: A_possible jezeli rozmiar plecaka (A_BagSize) zostal przekroczony.
double calculateValue(KnaspackProblem &e, int * indTab, int A_limit, double A_BagSize, double &TotalWeight, bool &A_possible){

	double currWeight=0.;
	double myPrice =0.;
	A_possible = false;	
	//	e.toString();
	for(int i = 0;i< A_limit ; i++){
		currWeight += e.getElementAt(indTab[i]).getWeight();
		myPrice    += e.getElementAt(indTab[i]).getPrice();		
	}

	if(DEBUG){cout << "#W calculateValue:==";sprawdzenieElementow(e,indTab,A_limit);}
	if(currWeight <= A_BagSize){

		A_possible = true;		
		TotalWeight = currWeight;
		return myPrice;
	}else{

		A_possible = false;		
		TotalWeight = 0.;
		return 0.;
	}

};

enum beeMission{ CHANGE, SUB};

class BeeStatus{
	public:
		BeeStatus(){
			success=false;
			whatTheyDid= CHANGE;
			Price= 0.;
			Weight =0.;
			indexLimit=0;
			swapIndex1=0;
			swapIndex2=0;
			addedIndex=0;
			removedIndex=0;
			int status=0;
		}
		bool success;
		enum beeMission whatTheyDid;
		double Price;
		double Weight;

		int indexLimit;

		int swapIndex1;
		int swapIndex2;

		int addedIndex;
		int removedIndex;

		int status;
};



BeeStatus beeFly(KnaspackProblem &e, int * indTab, double A_BagSize, int LimitIndex, beeMission whatToDo){

	bool success  = false;
	double tempWeight = 0;
	double tempPrice = 0.;
	bool zmiesciSie= false;	

	double temp;
	BeeStatus bb;

	int eCountOfElements  = e.getCountOfElements();
	int * tab = new int[eCountOfElements];

	for(int i =0; i< eCountOfElements; i++){
			tab[i] = indTab[i];
	}

	bb.whatTheyDid = whatToDo;

	switch(whatToDo){

		case CHANGE: 
				//dla kazdej pszczoly losujemy nowe elementy do wymiany.
					bb.indexLimit= LimitIndex;
					bb.status = 1;
					bb.swapIndex1 = rand()%LimitIndex; //zeby zamieniac element, ktory jest w zbiorze wybranych juz:))
					bb.swapIndex2 = rand()%(eCountOfElements-LimitIndex)+LimitIndex;
					//robimy swapa:
					temp = tab[bb.swapIndex1];
					tab[bb.swapIndex1] = tab[bb.swapIndex2];
					tab[bb.swapIndex2] = temp;
					/////////
					bb.Price = calculateValue(e, tab, LimitIndex, A_BagSize, tempWeight, zmiesciSie );					
					bb.success = zmiesciSie;
					bb.Weight = tempWeight;
					//jesli sie nie zmiesci to lipa:
					if(!bb.success){
						bb.status = 0;
						bb.Price = 0.;
					}else{					
						//sprobuj dodac:						
						bb.addedIndex = rand()%(eCountOfElements-LimitIndex)+LimitIndex; //losujemy z reszty
						if( (tempWeight + e.getElementAt( tab[bb.addedIndex] ).getWeight()) <=A_BagSize){

								bb.Price += e.getElementAt( tab[bb.addedIndex] ).getPrice();
								bb.Weight+= e.getElementAt( tab[bb.addedIndex] ).getWeight();
								bb.status =2;							
								bb.indexLimit= LimitIndex+1;//limit zwiekszamy o jeden //ale to chyba nie ma sensu								
						}
					}
					break;
		case SUB: 
					if(LimitIndex<2){
						bb.Price = 0.;
						bb.Weight = 0.;
						bb.status = 4;
						bb.success = false;
						break;
					}

					//wywalamy element z listy
					bb.indexLimit= LimitIndex-1;
					bb.status = 4;

					bb.removedIndex = rand()%LimitIndex; //losujemy element do wywalenia.
					temp = tab[bb.removedIndex];
					//przestawiamy wszystkie elementy //TODO: SPRAWDZIC KOD TEJ PETLI, CZY DOBRZE PRZESTAWIA I WSTAWIA ELEMENT
					for(int i = bb.removedIndex; i< LimitIndex; i++){
						tab[i] =tab[i+1];
					}

					tab[LimitIndex] = temp;

					//robimy zamiane!!!
					//dla kazdej pszczoly losujemy nowe elementy do wymiany.
					
					bb.swapIndex1 = (rand() % bb.indexLimit) ; //zeby zamieniac element, ktory jest w zbiorze wybranych juz:))

					bb.swapIndex2 = rand()%(eCountOfElements-bb.indexLimit)+bb.indexLimit;

					//robimy swapa:
					temp = tab[bb.swapIndex1];
					tab[bb.swapIndex1] = tab[bb.swapIndex2];
					tab[bb.swapIndex2] = temp;
					/////////

					bb.Price = calculateValue(e, tab, bb.indexLimit, A_BagSize, tempWeight, zmiesciSie );						

					bb.Weight = tempWeight;
					bb.success = zmiesciSie;
					//jesli sie nie zmiesci to lipa:
					if(bb.success){
						bb.status =3;	
					}else{
						bb.Price = 0.;
						bb.status =4;	
					}													

					break;
			default:
					break;
	}

	if(DEBUG && bb.success){ 
		cout << "**************"<<endl;
		cout <<"IN FUNC BeeFly: , W="<<bb.Weight << ", P="<<bb.Price << ", status="<<bb.status <<", Index= "<< bb.indexLimit;
		cout << ", (LimitIndex="<< LimitIndex <<" )"<<endl;
		sprawdzenieElementow(e, tab,bb.indexLimit);
		cout << "**************"<<endl;
	}

	delete[] tab;	
	return bb;
}

bool tableIsOK(int * tab, int size){

	bool ok =true;
	//inicjalizacja:
	bool * v = new bool[size];

	for(int i =0;i< size;i++){
		v[i] = false;
	}	
	//sprawdzenie czy sa wszystkie liczby
	for(int i =0;i< size;i++){
		for(int j =0;j< size;j++){
			if(tab[j] == i){	
				v[i]=true;
				break;
			}
		}
	}
	for(int i =0;i< size;i++){
		if(v[i] == false){
			ok = false;
		}
	}	
	delete[] v;
	return ok;
}

double KnaspackProblemSolutinUsingBeeAlgorithm(double BagSize, KnaspackProblem &e,int SkautBeens, int WorkerBeens, int A_counOfIteration){

	int iteration =0; //iterator numer iteracji
	int countOfIteration = A_counOfIteration;	//liczba zadanych iteracji
	int COUNT_SKAUT = SkautBeens;		//liczba skautow
	int COUNT_WORKER = WorkerBeens;	//liczba pracownic

	int eCountOfElements  = e.getCountOfElements();	//liczba elementow w problemie plecakowym
	if(eCountOfElements==0) throw string("ERROR: nie ma elementow do wyboru");
	double bestPrice =0.;	//wynik osiagniety przez algorytm
	double bestWeight =0.;
	int  * bestPosition = new int[eCountOfElements];
	int bestPositionIndex =0;			//liczba elementow
	
	//skauci:
	int  * localSkautPosition;// wskaznik dla lokalnej pozycji skautow
	int  localSkautIndex = 0; //liczba elementow wybranych
	double localSkautWeight =0.;	//tymczasowa masa plec

	double bestSkautPrice; //najlepsza wartosc osiagnieta przez skauta
	double bestSkautWeight=0.;
	int bestSkautIndex =0;

	//pracownice:
//	double * workerPrice = new double[COUNT_WORKER];	//tablica z wartosciami osiagnietymi przez pszczoly
	BeeStatus * bs = new BeeStatus[COUNT_WORKER];		//tablica ze statusami pszczol
	int bestWorkerBee=0;		//indeks najlepszej pszczoly

	//tempy:
	double tempPrice =0.;	
	double temp;
	enum beeMission tempOrder = CHANGE;
	if(DEBUG)cout <<"ALGORYTM PSZCZELI" << endl;

	for( iteration = 0; iteration<countOfIteration; iteration++){

			//zerowanie zmiennych:
			bestSkautPrice = bestPrice; 	
			bestSkautIndex	= bestPositionIndex;
			//wysylamy skautow: - losujemy nowe elementy i zapamietujemy pozycje tego ktory znajdzie najlepszy wynik
			//sprawdzamy ile z tych rzeczy wejdzie do plecaka i zapamietujemy indeks ostatniego elementu oraz wartosc plecaka
			//mozemy od razu z wylosowanych wybierac najlepsze, albo nie koniecznie - w granicy i tak powinnismy dostac optimum

			for(int i =0;i<COUNT_SKAUT;i++){ //po liczbie skautow

				localSkautPosition = getIndexRand(eCountOfElements);		//NOWY TEREN	
				tempPrice = calculateSkautValue(e, localSkautPosition, BagSize, localSkautIndex ,localSkautWeight);
			
				if (tempPrice > bestSkautPrice){
					if(INV)cout << "SKAUT "<< i <<" ZNALAZŁ COŚ LEPSZEGO (W="<<localSkautWeight << " PRICE="<< tempPrice << "),"  <<endl;
					//if(sprawdzenieElementow(e,localSkautPosition,localSkautIndex) !=localSkautWeight){
					//	throw string("Error 1: Niezgodna wartosc wagi");
					//}
					for(int j =0; j < eCountOfElements; j++){ //kopiujemy cala tablice
						bestPosition[j] =localSkautPosition[j];
					}
					bestPrice = bestSkautPrice = tempPrice;
					bestPositionIndex = bestSkautIndex = localSkautIndex;
					bestWeight = bestSkautWeight = localSkautWeight;
					//cout << i <<" skaut znalazl cos lepszego!:)"<<endl;
					//cout << "bestSkautIndex =" << bestSkautIndex << endl;
					//cout << "bestSkautPrice ="  << bestSkautPrice << endl;
				}
			}
			delete[] localSkautPosition;
			//skauci skonczyli swoja prace
			//informacja przechowywana jest w: bestPosition, bestSkautPrice, bestSkautIndex.
			//wysylamy robotnice. Zamieniaja dwa elementy indeksami ze zbioru kt
			BeeStatus * bs = new BeeStatus[COUNT_WORKER]; 


			for(int i =0; i< COUNT_WORKER; i++){
//BeeStatus beeFly(KnaspackProblem &e, int * indTab, double A_BagSize, int LimitIndex,beeDest whatToDo){
				if (rand()%2 == 1)  tempOrder = CHANGE;
				else tempOrder = SUB;

				bs[i] = 	beeFly(e,bestPosition,BagSize,bestSkautIndex, tempOrder );
			}

			//szukamy najlepszej pszczoly:
			tempPrice = bestPrice;
			for(int i =0 ; i< COUNT_WORKER; i++){ 
				if(bs[i].Price > tempPrice){
					//cout << "Najlepsza robotnica: "<< i<< ", workerPrice[i]= "<<workerPrice[i] << ", wczesniejsza=" << tempPrice<<endl;
					tempPrice = bs[i].Price;
					bestWorkerBee = i;					
				}				
			}
 			//jezeli najlepsza pszczola ma lepszy wynik od skauta to wybieramy te pozycje za wyjsciowa.
			//zazwyczaj tak bedzie ale trzeba sprawdzic bo to jest sekret sukcesu algorytmu:

			if(bs[bestWorkerBee].Price > bestPrice){
				if(INV){
					cout << "PSZCZOŁA "<< bestWorkerBee <<" ZNALAZŁA COŚ LEPSZEGO (";
					cout<< bs[bestWorkerBee].whatTheyDid <<", " << bs[bestWorkerBee].Price << "), W="<<cout<<bs[bestWorkerBee].Weight <<endl;
				}

				if(!bs[bestWorkerBee].success){
					throw string("ERROR 3: NAJLEPSZY BEZ SUKCESU! - anomalia");
					//rzuc wyjatkiem
				}
				switch(bs[bestWorkerBee].whatTheyDid){
					case CHANGE: 
						//robimy swapa:
						temp = bestPosition[bs[bestWorkerBee].swapIndex1];
						bestPosition[bs[bestWorkerBee].swapIndex1] = bestPosition[bs[bestWorkerBee].swapIndex2];
						bestPosition[bs[bestWorkerBee].swapIndex2] = temp;
						//jesli sie nie zmiesci to lipa:
						if(bs[bestWorkerBee].status == 2){							
							temp = bestPosition[bs[bestWorkerBee].addedIndex];
							bestPosition[bs[bestWorkerBee].addedIndex] = bestPosition[bs[bestWorkerBee].indexLimit-1];
							bestPosition[bs[bestWorkerBee].indexLimit-1] = temp;						
						}
						break;
					case SUB: 

						temp = bestPosition[bs[bestWorkerBee].removedIndex];
						//przestawiamy wszystkie elementy //TODO: SPRAWDZIC KOD TEJ PETLI, CZY DOBRZE PRZESTAWIA I WSTAWIA ELEMENT
						for(int i = bs[bestWorkerBee].removedIndex; i< bs[bestWorkerBee].indexLimit; i++){
							bestPosition[i] =bestPosition[i+1];
						}
						bestPosition[bs[bestWorkerBee].indexLimit] = temp;
	
						//jezeli nie bylo swapa to jest znow absurd
						if(!bs[bestWorkerBee].status == 3){
							throw string("ABSURD!");
						}
						if(bs[bestWorkerBee].status == 3){
							temp = bestPosition[bs[bestWorkerBee].swapIndex1];
							bestPosition[bs[bestWorkerBee].swapIndex1] = bestPosition[bs[bestWorkerBee].swapIndex2];
							bestPosition[bs[bestWorkerBee].swapIndex2] = temp;
						}							
						break;
					default:
						break;
				}
				if(!tableIsOK(bestPosition,eCountOfElements)) throw string("BŁĄD TABLICY- zła permutacja");				
				bestPrice = bs[bestWorkerBee].Price;
				bestPositionIndex = bs[bestWorkerBee].indexLimit;
				bestWeight = bs[bestWorkerBee].Weight;
				
				//if(sprawdzenieElementow(e, bestPosition,bs[bestWorkerBee].indexLimit)!=bestWeight){throw string("ERROR 5: Niezgodna wartosc wagi");};
			}			
			//cout << "Dzialanie algorytmu pszczelego: bestPrice="<<bestPrice <<" bPI:" << bestPositionIndex << " tW:"<< tempWeight << endl;
			//zapamietanie zmiennej dla najwyzszej wartosci wartosci plecaka.
			delete[] bs;

			
	}
	//cout << A_counOfIteration << "\tskauci="<<  SkautBeens<< "\tpracownice="<< WorkerBeens;
	//cout << "\tPRICE=" << bestPrice << "\tWeight="<< bestWeight<<"\tL.Elemntow=" << bestPositionIndex<<endl;

	/*
	if(sprawdzenieElementow(e,bestPosition, bestPositionIndex) !=bestWeight){
			throw string("Error 2: Niezgodna wartosc wagi: ");
	}	
	*/
	delete[] bestPosition;
	return bestPrice;

}


// Funkcja testowa, do usuniecia
void tests(){

	int *kkk;


	//try{
	//cout<<endl;
	//	cout <<"Rozwiazanie metoda brute force: "<< k1.getBruteForceValue(10.) << endl;
	//cout<<endl;
	//	cout <<"Rozwiazanie metoda better brute force: "<< k1.getBetterBruteForceValue(10.) << endl;

	//KnaspackProblemSolutinUsingBeeAlgorithm(13.,k1,30,30,100 );	
	//KnaspackProblemSolutinUsingBeeAlgorithm(13.,k1,100,100,100 );
	//cout << endl<<"Metoda zachlanna: "	<< k1.getBruteForceValue(13.) << endl;
	
	double bagSize = 13.;
	double bruteForce =0;
	//test 1.
	//poszukiwanie najistotniejszego parametru.
	/*
	KnaspackProblem k1(30,10,10);
	for(int i =1;i<50;i++){
		for(int j=1;j<50;j++){
			try{
				cout <<i <<"\t"<<j<<"\t"<< KnaspackProblemSolutinUsingBeeAlgorithm(bagSize, k1, i,j ,50 ) << endl;
			}catch( string &e ){
				cout << e << endl; //wypisanie bledu
			}		
		}
	}
	*/
/*
	//zachowanie algorytmu w zaleznosci od liczby iteracji:
	KnaspackProblem k1(30,10,10);
	for(int i=1;i<100;i++){
		try{
			cout <<i <<"\t"<< KnaspackProblemSolutinUsingBeeAlgorithm(bagSize, k1, 5, 15, i) <<"\t"<< KnaspackProblemSolutinUsingBeeAlgorithm(50., k1, 5, 15, i) << endl;
		}catch( string &e ){
			cout << e << endl; //wypisanie bledu
		}		
	}
*/
	//porownanie metod rozwiazan
	for(int i=1;i<100;i++){
		KnaspackProblem k1(10+i,10,10);
		try{
			cout <<i <<"\t"<< KnaspackProblemSolutinUsingBeeAlgorithm(bagSize, k1, 5, 15, i) <<"\t"<< k1.getBruteForceValue(bagSize) << endl;
		}catch( string &e ){
			cout << e << endl; //wypisanie bledu
		}		
	}
	//	bruteForce= k1.getBruteForceValue(bagSize);
	//	cout <<"Metoda zachlanna: "	<< bruteForce << endl;

}

//funkcja main
int main(int argc, char ** argv){


   /* initialize random seed: */
   srand ( time(NULL) );
	tests();

	return 0;
}

