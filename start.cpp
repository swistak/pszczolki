

extern int globalValue;


#include "common.h"
#include "element.h"
#include "knaspackProblem.h"
#include "beesAlgorithm.h"
#include "ctype.h"


void scientist(void);

void printMenu(void){
	write(1,"\E[H\E[2J",7);
	string string1 ="\t\t\t\tProgram BoxBeeCol";
	string string2 ="Znajduje rozwiazanie problemu plecakowego przy uzyciu algorytmu pszczelego";
	string string3 ="\t\tMenu (wybór potwierdzaj klawiszem [Enter]):";
	string string4 ="\t1. W celu uruchomienia programu wcisnij dowolny klawisz";
	string string5 ="\t2. Aby zakończyć wciśnij: q";
	string string6 ="\t3. By wywołać pomoc wciśnij: h";
	string string7 ="\t\tautorzy: Informatyka II rok inz. BO Grupa I";
	cout << endl << endl << string1<<endl<<endl;
	cout << string7<<endl<<endl;
	cout <<string2<<endl;
	cout <<string3<<endl;
	cout <<string4<<endl;
	cout <<string5<<endl;
	cout <<string6<<endl;


}

// Funkcja testowa, do usuniecia


///globalne parametry programu:

int BIteration;
int BWorkers;
int BSkauts;

int KMaxKnaspackWeight;
int KMaxElementPrice;
int KMaxElementWeight;


int readNumber(){

	int value =-1;
	bool cond = true;
	string string1;
	istringstream stream1;


	while(cond){
		istringstream stream1;
  		cin >> string1;
		if(string1 == "q"){
			cond = false; //niepotrzebne
			return -1;
		}else{
			//na chamca probujemy bez sprawdzenia typow. to zle!
			stream1.str(string1);
			stream1 >> value;
			if(value>1){
				cond = false;
			}else{
				cout << "Za mala wartosc parametru (musi byc wieksza od 1). Spróbuj jeszcze raz!" << endl;
			}
			//cout << "Bledny parametr. Podaj liczbe calkowita, np.: 14. (lub q jeśli zakocznyc)" << endl;
		}
	}
	return value;
}

int readNumber2(){

	int in=0;
	int out = 0;

//	sleep(2000);
	bool cond = true;
	while(cond){
		//cout << endl;
		cout << endl;
		in = 0;
		cin >> in;
		if(isdigit(in)){
			 out = in;
			if(out>1){
				cond = false;
			}else{
				cout << "Za mala wartosc parametru (musi byc wieksza od 1). Spróbuj jeszcze raz!" << endl;
			}
		}else if(in == 'q'){
			cond = false; //niepotrzebne
			return -1;
		}else{		
			cout << "Bledny parametr. Podaj liczbe calkowita, np.: 14. (lub q jeśli zakocznyc)" << endl;
		}		
	}
	return out;

}
/// \fn setParameters funkcja ta wywolywana jest w celu ustawienia parametrow problemu plecakowego oraz algorytmu
bool  setParameters(void){

	
	string strM1="Podaj parametry problemu plecakowego: ";
	string strM2=" (krok 1 z 6) Rozmiar plecaka (jego maksymalna dopuszczalna masa): ";
	string strM3=" (krok 2 z 6) Maksymalna waga jednego elementu: ";
	string strM4=" (krok 3 z 6) Maksymalna cena jednego elementu: ";
	string strB0= "Parametry dla algorymu pszczelego:";
	string strB1=" (krok 4 z 6) Liczba skautow: ";
	string strB2=" (krok 5 z 6) Liczba robotnic: ";
	string strB3=" (krok 6 z 6) Ilosc iteracji: ";

	cout << strM1 <<endl<< strM2<< endl;
	if((KMaxKnaspackWeight = readNumber())<0)
		return false;
	cout << strM3 <<endl;
	if((KMaxElementWeight = readNumber())<0)
		return false;
	cout << strM4 <<endl;
	if((KMaxElementPrice = readNumber())<0)
		return false;

	cout << strB0 << endl << strB1 <<endl;
	if((BSkauts = readNumber())<0)
		return false;
	cout << strB2 <<endl;
	if((BWorkers = readNumber())<0)
		return false;
	cout << strB3 <<endl;
	if((BIteration = readNumber())<0)
		return false;
	return true;
}
/// \fn funkcja wypisujaca pomoc w oknie konsoli
void printHelp(void){
	
	string commandS; ///<lancuch przechowujacy znaki wpisane przez uzytkownika. W tej funkcji nie ma znaczenia
	write(1,"\E[H\E[2J",7);
	string string2 ="Ten program znajduje rozwiazanie problemu plecakowego przy uzyciu algorytmu pszczelego";
	string string1 ="BoxBeeCol vesion 1.3.\t2010 (C)";
	cout <<"Pomoc do programu" <<endl;
	cout <<string1 <<endl<<endl;
	cout <<"Powtozmy jeszcze raz:"<<endl<< string2 <<endl;
	cout <<"Szczegolowy opis programu znajduje sie w jego dokumentacji. Tam zajdziesz jego dokladny opis."<<endl;
	cin >> commandS;
	
	return;
}
/// \fn user funkcja uruchamia tryb uzytkownika oraz interfejs do komunikacji z nim. Nie przyjmuje zadnych argumentow, tez nie zwraca zadnej wartosci
void user(){

	double beeAlgV = 0.; ///<wartosc zwrocona przez algorytm pszczeli
	double bruteForceV =0; ///<wartosc zwrocona przez algorytm zachłanny

	bool working = true;

	string commandS ="";
	char commandCH = 'q';

	bool ready= false;

	while(working){
		ready = false;
		printMenu();
		cin >> commandCH;
		switch(commandCH){

			case 'q':
					working = false;	
					break;
			case 'h':
					printHelp();
					break;
			case 's':
					sleep(1);
					scientist();
					break;
			default:
					ready = setParameters();
					break;
		}

		if(ready){
			cout <<"czekaj chwile, pracuje " <<endl;
			KnaspackProblem k1(KMaxKnaspackWeight,KMaxElementWeight,KMaxElementPrice);
			beeAlgV = KnaspackProblemSolutinUsingBeeAlgorithm(KMaxKnaspackWeight, k1, BSkauts, BWorkers, BIteration);
			bruteForceV = k1.getBruteForceValue(KMaxKnaspackWeight);
			cout <<endl;
			cout <<"Rozwiazanie: " << endl;
			cout <<" Wynik uzyskany algorymem  pszczelim: "<< beeAlgV << endl;
			cout <<" Wynik uzyskany algorymem zachlannym: "<< bruteForceV << endl;
			cin >> commandS;
		}
	}	
	return;

}


/// \fn scientist funkcja wykonujaca obliczenia w petli, przydatna do wykonania wykresow.
void scientist(void){
	cout <<endl<<"BoxBeeCol - Tryb naukowy" <<endl;

	int bagSize = 100;

	for(int i=1;i<10;i++){

		KnaspackProblem k1((int)bagSize,100,100);
		//cout <<"Debug T.1"<<endl;
		try{
			cout  <<"\t"<< KnaspackProblemSolutinUsingBeeAlgorithm(bagSize, k1, 1000, 1000, 10* i);
			//cout <<"Debug T.2"<<endl;
			cout <<"\t"<< k1.getBruteForceValue(bagSize) << endl;
		}catch( string &e ){
			cout << e << endl; //wypisanie bledu
		}		
	}
}

/// \fnfunkcja main - funkcja uruchamiajaca program, jesli jest podany chociaz jeden parametr to funkcja uruchomi tryb naukowy

int main(int argc, char ** argv){
///jesli nie zostanie podany zaden, to uruchomiony zostanie tryb  uzytkownika


   /* initialize random seed: */
   srand ( time(NULL) );
	if(argc>1){
		scientist();
	}else
	user();

	return 0;
}


