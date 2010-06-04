

#include "knaspackProblem.h"


	void Element::setWeight(double A_weight){
		weight = A_weight;
	}
	void Element::setPrice(double A_price){
		price = A_price;
	}
	
	Element::Element(double A_weight, double A_price){
		weight = A_weight;
	 	price = A_price;
	}
	double Element::getWeight(){
		return weight;
	}
	double Element::getPrice(){
		return price;
	}
	string Element::toString(){
		string s = "{"+doublToStr(weight)+", "+doublToStr(price)+"}";
		return s;
	}	

	KnaspackProblem::KnaspackProblem(int A_countOfElements, double maxWeight, double maxPrice):countOfElements(A_countOfElements){
		
		elem = new Element[countOfElements];		
		for(int i =0; i< 	countOfElements;i++){
			elem[i].setWeight(((double)rand())/((double)RAND_MAX) * maxWeight);
			elem[i].setPrice(((double)rand())/((double)RAND_MAX) * maxPrice);
			if(elem[i].getWeight()==0) i--; //by powtorzyc losowanie 
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
	Element KnaspackProblem::getElementAt(int index){
		if((index <0) & (index >= countOfElements)){
			throw string ("ERROR: Nieprawidlowe odowlanie sie do indeksu elementu");
		}
		return elem[index];
	}
	int KnaspackProblem::getCountOfElements(){
		return countOfElements;
	}

	//sortowanie po cenie jednostkowej
	void KnaspackProblem::sortByUnitPrice(){

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
	void KnaspackProblem::sortByPrice(){

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
	double KnaspackProblem::getBetterBruteForceValue(double BagSize){

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
	double KnaspackProblem::getBruteForceValue(double BagSize){

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
	double KnaspackProblem::getDumpBruteForceValue(double BagSize){

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

	double KnaspackProblem::dynamicSolution(double ** elementy, double rozmiarPlecaka){
	
		int liczbaElementow = countOfElements;
		double rozwiazanie = INT_MAX;
	/*
		double ** P, ** Q;
		P = new double*[liczbaElementow];
		Q = new double*[liczbaElementow];
		for(int i =0; i< 	liczbaElementow;i++){
			P[i] = new double[liczbaElementow];
			Q[i] = new double[liczbaElementow];
		}

		//int P[liczbaElementow][rozmiarPlecaka]; //Tablica P najlepszych upakowań plecaka
		//int Q[liczbaElementow][rozmiarPlecaka]; //tablica rodzajów rzeczy Q, dołożonych w ostatnim dopakowaniu plecaka

		//zerowanie tablic:
		for(int i =0; i < liczbaElementow; i++){
			for(int j =0; j < rozmiarPlecaka; j++) {
				P[i][j]=0;
			   Q[i][j]=0;
			}
		}

		for(int i = 1; i < liczbaElementow; i++){
			for(int j = 1; j < rozmiarPlecaka; j++){
				if(j >= elementy[i][0]){
					if(P[i-1][j] < (P[i][j-elementy[i][0]]+elementy[i][1])){
						P[i][j]=P[i][j-elementy[i][0]]+elementy[i][1];
						Q[i][j]=i;
					}else{
						P[i][j]=P[i-1][j];
						Q[i][j]=Q[i-1][j];
					}
				}else{
					P[i][j]=P[i-1][j];
					Q[i][j]=Q[i-1][j];
				}
			}
		}

		std::cout << "P uzupelnione" << "\n";
		for(int i =1; i < liczbaElementow; i++){
			for(int j =1; j < rozmiarPlecaka; j++){
			 std::cout << P[i][j] << " ";
			}
			std::cout << "\n";
		}

		std::cout << "Q uzupelnione" << "\n";
		for(int i =1; i < liczbaElementow; i++){
			for(int j =1; j < rozmiarPlecaka; j++) std::cout << Q[i][j] << " ";
				std::cout << "\n";
			}
		int i;
		int q = rozmiarPlecaka-1;
		while(q > 0){
			i = Q[6][q];
			rozwiazanie += elementy[i][0]*elementy[i][1];
			q = q - elementy[i][0];
		}
	*/
		return rozwiazanie;
	} 

	//funkcja ma tworzyc stringa, ale na razie wypisuje na konsole.
	void KnaspackProblem::toString(){
		//doublToStr
		string KnaspackPString = "";
		cout << "W znajduja sie (waga, cena)" <<endl;
		for(int i =0; i< 	countOfElements;i++){		
			cout << "{"<< elem[i].getWeight() <<", "<< elem[i].getPrice()<<"}"<<endl;
		}
		return;
	}
	//d-or
	KnaspackProblem::~KnaspackProblem(){
	    delete[] elem;
	}


//end file knaspackProblem.cpp

