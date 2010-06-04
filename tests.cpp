
#include "common.h"
#include "knaspackProblem.h"
#include "beesAlgorithm.h"

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
		KnaspackProblem k1(10+i,10,100);
		k1.toString();
		cout <<"Debug T.1"<<endl;
		try{
			cout <<i <<"\t"<< KnaspackProblemSolutinUsingBeeAlgorithm(bagSize, k1, 4, 15, i);
			cout <<"Debug T.2"<<endl;
			cout <<"\t"<< k1.getBruteForceValue(bagSize) << endl;
		}catch( string &e ){
			cout << e << endl; //wypisanie bledu
		}		
	}
	//	bruteForce= k1.getBruteForceValue(bagSize);
	//	cout <<"Metoda zachlanna: "	<< bruteForce << endl;

}

///funkcja main
int main(int argc, char ** argv){


   /* initialize random seed: */
   srand ( time(NULL) );
	tests();

	return 0;
}

