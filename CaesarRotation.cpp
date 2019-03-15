#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string translate(string input, string variable){
	int key;
	istringstream bs (input);										//String 'input' naar integer
	bs >> key;

	string encryptedText = variable;
	for (size_t i = 0; i < variable.size(); i++){
		if (variable[i] == 32){										//Negeren van spaties
			continue;
		}else{
			if(variable[i] + key > 122){							//Als ASCII waarde boven die van 'z' gaat
				int temp = (variable[i] + key) - 122;				//Beweeg naar ASCII waarde van 'a'
				encryptedText[i] = 96 + temp;
			}else if(variable[i] + key > 90 && variable[i] <= 96){	//Als ASCII waarde boven die van 'Z' gaat
				int temp = (variable[i] + key) - 90;				//Beweeg naar ASCII waarde van 'A'
				encryptedText[i] = 64 + temp;
			}else{													//Standaardsituatie; ASCII waarde + input
				encryptedText[i] += key;
			}
		}
	}
	return encryptedText;
}
int main(int argc, char *argv[]){
	string s;
	
	if(argc != 2){
		cerr << "Deze functie heeft exact 1 argument nodig";
	return -1;
	}
	
	while(true){
		cin >> s;
		if (cin.eof()){
			return 0;
		}
		cout << translate(argv[1], s) << endl;
	}
}