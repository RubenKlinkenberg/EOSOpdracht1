#include <iostream>
#include <string>
#include "shell.h"
using namespace std;

int main(){
	string input;
	int fileD;
	if((fileD = syscall(SYS_open, "promptfile.txt", O_RDONLY)) == -1){
		cout << "Check promptfile!";
		return 1;
	}
	char by[512];
	string promptContent="";
	while (syscall(SYS_read, fileD, by, 1) == 1){
		promptContent += by;
		promptContent.pop_back();
	}



  while(true){
	cout << promptContent;                   // Print het promptt
    getline(cin, input);         // Lees een regel
    if (input == "new_file") new_file();   // Kies de functie
    else if (input == "ls") list();        //   op basis van
    else if (input == "src") src();        //   de invoer
    else if (input == "find") find();
    else if (input == "python") python();
    else if (input == "exit") return 0;
    else if (input == "quit") return 0;
    else if (input == "error") return 1;

    if (cin.eof()) return 0; } }      // EOF is een exit

void new_file(){ 
	string file_name;
	string file_tekst;
	while(file_name.empty()){
		cout << "Voer bestandsnaam in: ";
		getline(cin, file_name);
	}
	const char * f_name = file_name.c_str();
	int fd = syscall(SYS_open, f_name, O_WRONLY | O_CREAT, mode_t S_IRWXU);
	cout << "Schrijf hier je tekst: " << endl;
	getline(cin, file_tekst);
	file_tekst.append("<EOF>");
	const void * f_tekst = file_tekst.c_str();
	syscall(SYS_write, fd, f_tekst, file_tekst.size());
}

void list(){ 
	 pid_t pid = fork();
	 if (pid == 0){
		 execlp("ls", "ls", "-la", NULL);
	 }else{
		 wait(NULL);
	 }
}

void find(){ 													// ToDo: Implementeer volgens specificatie.
	 cout << "ToDo: Implementeer hier find()" << endl; }		// Deze lukt niet.

void python(){ 
	pid_t pid = fork();
	if (pid == 0){
		execlp("python", "python", NULL);
	}else{
		wait(NULL);
		
	}
}
void src(){ 													// Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
	int fd = syscall(SYS_open, "shelled.cpp", O_RDONLY, 0755); 	// Gebruik de SYS_open call om een bestand te openen.
	char byte[1];                                           	// 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
	while(syscall(SYS_read, fd, byte, 1))                  		// Blijf SYS_read herhalen tot het bestand geheel gelezen is,
	cout << byte; 												//   zet de gelezen byte in "byte" zodat deze geschreven kan worden.
} 																