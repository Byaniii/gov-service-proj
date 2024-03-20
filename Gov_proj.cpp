User

// Pre-processor directives
#include <iostream> 
#include <fstream>
#include <sstream>
#include <windows.h>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

// variables/arrays needed to be declared globally
typedef ifstream InFileStream;
typedef ofstream OutFileStream; 
typedef vector<int> ViolationArray;
typedef ios_base::openmode FileMode;
FileMode mode = mode;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
ViolationArray arr;
int count = 0;
typedef struct {
    string name, address, phone_number, car_model;
} Owner;
string PlateNumber;
// Function Prototypes
void menu();
void registration();
void login();
void IncorrectLogin();
void RegisterPlate();
void FindPlate();
void second_menu();
void register_violations();
void violations();
void violations_menu();// used to change terminal color



int main(){   
    bool ProgramRunning = true;
    while(ProgramRunning){ // used to loop options/menu until the program is exited
        menu();
        int choice;
        cin >> choice;
        switch (choice){
            case 1:
                login();
                break;
            case 2:
                registration();
                break;
            case 3:
                system("cls");
                ProgramRunning = false;
                break;
            default:
                system("cls");
                SetConsoleTextAttribute(h,4); 
                cout << "\nPlease enter a valid option!\n";
                SetConsoleTextAttribute(h,2);       
        }
        break;
    }
    return 0; 
}

/////////////////////////FUNCTIONS////////////////////////////////////

void menu(){ // Main Menu Function;
    SetConsoleTextAttribute(h,2);
    cout  <<"\n---------------LTO-MASTER-TERMINAL---------------\n";
    cout  <<"[1] Log-in"<<endl;
    cout  <<"[2] Register ID"<<endl;
    cout  <<"[3] Exit Program"<<endl;
    cout  <<"Enter choice: ";
}


void registration(){ // Registration function
    system("cls");
    string RegisterName, RegisterPassword;
    ofstream PasswordInput("passwords.txt", mode); // used to access and write files, opens the passwords text file
    
    // ofstream = writing, editing text files, InFileStream = reading files.
   
   // username registry
    cout << "\nRegister Username: "; 
    cin.ignore(1,'\n');
    getline(cin, RegisterName);
    ofstream RegisterInput("username.txt", mode); 
    RegisterInput << RegisterName<<' ';
    RegisterInput.close(); // this code syntax closes the file that was opened by the fstream directive
    bool valid = false;
    // password has strict implementations/qualifications in order to be valid; one capital letter, one number, no whitespace
    do{
        bool Capital = false, Number = false, WhiteSpace = false;
        cout << "Register Password: ";
        getline(cin, RegisterPassword);
        for (int i = 0; i < RegisterPassword.length(); i++) { // looping algorithm to identify the conditions needed to be met
            if (isupper(RegisterPassword[i])) {
                Capital = true; 
            }
            if (isdigit(RegisterPassword[i])) {
                Number = true; 
            }
            if (isspace(RegisterPassword[i])) {
                WhiteSpace = false; 
                break; 
            }
        } // password turns valid if it meets criteria
        if (Capital & Number & !WhiteSpace){
            system("cls");
            PasswordInput << RegisterPassword <<' ';
            SetConsoleTextAttribute(h,2); 
            cout << "\nSuccessfully registered " << RegisterName <<'!'<<endl;
            valid = true;
            break;
        }
        else{ // repeats loop if password is invalid
            SetConsoleTextAttribute(h,4); 
            cout << "Ensure that your password contains a capital letter, atleast one number, and no white spaces;\n";
        }
    }while(!valid);
    SetConsoleTextAttribute(h,2); 
    PasswordInput.close(); // closes file
    second_menu();
}

void login(){ // Log-in Function
    bool found = false;
    string users, UserInput, line, UserPassword, passwords;
    InFileStream UserOutput("username.txt"); 
    cout << "\nEnter Username: ";
    cin >> UserInput;
    InFileStream PasswordOutput("passwords.txt"); // opens file to be read
    cout << "Enter Password: ";
    cin >> UserPassword;

    // Username and Password input comparison within text file
    while (getline(UserOutput, line) && getline(PasswordOutput, passwords)) { 
        istringstream user(line); //stores contents of line into user variable
        istringstream pass(passwords); //stores contents of passwords into 'pass' variable
        while (user >> users && pass >> passwords ) { //passess the values of the file into a temporary variable in a loop until a match is found
            if (UserInput == users && UserPassword == passwords) { // compares the user's input into the text files 'password' and 'users'
                SetConsoleTextAttribute(h,2); // changes terminal color
                cout <<endl<<"Welcome "<< users << "!"<<endl; 
                second_menu();
                found = true;
                break; 
            }    
        }
        if (found) { // breaks while loop if UserInput and UserPassword is found within the text file
            break;
        }
    }   
    if (!found){ // if credentials are incorrect, calls the IncorrectLogin(); function
        system("cls");
        SetConsoleTextAttribute(h,4);
        cout << "\nUsername/Password not found!";
        IncorrectLogin();
    }       
    UserOutput.close();     
}

void IncorrectLogin(){ // If the user enters non-existent/incorrect credentials
    int option;

    cout <<"\n[1] Try Again?";
    cout <<"\n[2] Main Menu";
    cout <<"\nEnter choice: ";
    cin >> option;

    switch (option){
        case 1:
            login();
            break;
        case 2:;
            main();
            break;
        default:
            SetConsoleTextAttribute(h,4); 
            cout << "\nPlease enter a valid option!\n";
            SetConsoleTextAttribute(h,2);
            IncorrectLogin();
    }
}

void RegisterPlate(){ //function to register plate
    string UserPlate, UserName, HomeAddress, PhoneNumber, UserInput;
    ofstream input("plates.txt", mode); // opens plates txt to input the registry plates
    if (!input.is_open()) {
        cout << "Failed to open the file." <<endl;
        return; // Early return if file opening fails
    }

    // Asks for information such as name, address, number, car model and most importantly, plate number.
    cout << "Register Plate number: ";
    cin.ignore(); // Ensure we clear the newline character from the buffer
    getline(cin, UserPlate); 
    input << UserPlate << endl;

    cout << "Register Name: ";
    getline(cin, UserName);
    input << UserName << endl;

    cout << "Register Home Address: ";
    getline(cin, HomeAddress);
    input << HomeAddress << endl;

    cout << "Register Phone Number: ";
    getline(cin, PhoneNumber);
    input << PhoneNumber << endl;

    cout << "Register Car Model: ";
    getline(cin, UserInput);
    input << UserInput << endl;
    
    input.close();

    
    ofstream violationsFile("violations.txt", mode); 
    if (violationsFile.is_open()) {
        violationsFile << "0 0 0 0 "; 
        violationsFile.close(); 
    } else {
        cout << "Failed to open the violations file." << endl;
    }

    cout << "\nSuccessfully registered!\n";
    second_menu(); 
}


void FindPlate(){ // Function to find the plates
    InFileStream input("plates.txt"); // opens plates files to be read 
    if (!input.is_open()) {
        cout << "Error opening file." << endl;
        second_menu();
    }
    string lines_in_text, compare;
    bool found = false, valid = false;

    cin.ignore(1, '\n'); // to ignore unnecessary input buffer
    count = 0;
    bool capital = false, whitespace = true;
    do{
        system("cls");
        cout << "Find Plate Number(Ensure that the Plate Number is in all capital and has no spaces): ";
        getline(cin, PlateNumber);
        for (int i = 0; i < PlateNumber.length(); i++) {         // Finds Plate number but checks if the user input meets criteria
            if (isupper(PlateNumber[i])) {
                capital = true; 
            }
            if (isspace(PlateNumber[i])) {
                whitespace = true; 
                break; 
            }
        }
        if (capital & whitespace){ // ends loop if criteria is met
            valid = true;
            break;
        }
        else{
            SetConsoleTextAttribute(h,4); 
            cout << "Ensure that the Plate Number is in all capital and has no spaces\n";
        }
    }while(!valid);
    SetConsoleTextAttribute(h,2); 
    Owner owner;
        while (getline(input, lines_in_text)) { 
        count++; // count variable incremented to be used in finding the location of each number corresponding to the violation of the plate number
        istringstream output(lines_in_text);
        while (output >> compare) {            // Gets the lines from the plates text file
            if (PlateNumber == compare) {       // if plate number is found, display the next lines corresponding to its information
                found = true;
                    for (int i = 0; i < 7; i++){ 
                        if(getline(input,lines_in_text)){ // displays the lines within the text file correspondingly
                                switch (i){
                                    case 0:
                                        owner.name = lines_in_text;
                                        cout << "\nName: " << owner.name <<endl; // structs incorporated
                                        break;
                                    case 1:
                                        owner.address = lines_in_text;
                                        cout << "Address: "<< owner.address<<endl; // structs incorporated
                                        break;
                                    case 2:
                                        owner.phone_number = lines_in_text;
                                        cout << "Phone Number: "<<owner.phone_number<<endl; // structs incorporated
                                        break;
                                    case 3:
                                        owner.car_model = lines_in_text;
                                        cout << "Car Model: "<< owner.car_model<<endl; // structs incorporated
                                        break;                                
                                }   
                        }
                    }
                violations_menu();
                }
            }
        }
        if (!found){ // if plate not found return error
            SetConsoleTextAttribute(h,4); 
            cout << "PLATE NUMBER NOT FOUND\n";
            second_menu();
            SetConsoleTextAttribute(h,2);
        }    
    input.close(); // closes the file 
}

void second_menu(){ // second menu, calls functions for each case/scenario

    cout <<"--------MENU--------"<<endl;
    cout << "[1] FIND PLATE NUMBER" << endl;
    cout << "[2] REGISTER PLATE NUMBER" << endl;
    cout << "[3] MAIN MENU/LOG-OUT"<<endl;
    int answer;
    cout << "Enter option: ";
    cin >> answer;
    switch (answer){
        case 1: 
            FindPlate();
            break;
        case 2:
            RegisterPlate();
            break;
        case 3:
            system("cls");
            main();
            break;
        default:
            system("cls");
            SetConsoleTextAttribute(h,4);  
            cout << "\nPlease enter a valid option!\n";
            SetConsoleTextAttribute(h,2);
            second_menu();  
            break;   
    }
}

void violations_menu(){ // violations menu, calls functions for each case/scenario
    int option;
    cout << "[1] ENTER VIOLATION FOR THIS VEHICLE\n";
    cout << "[2] VIEW VEHICLE VIOLATIONS\n";
    cout << "[3] MENU\n";
    cout << "Enter option: ";
    cin >> option;
    switch(option){
        case 1:
            system("cls");
            register_violations();
            break;
        case 2:
            system("cls");
            violations();
            break;
        case 3:
            system("cls");
            second_menu();
            break;
        default:
            system("cls");
            SetConsoleTextAttribute(h,4);  
            cout << "\nPlease enter a valid option!\n";
            SetConsoleTextAttribute(h,2);
            violations_menu();
            break;
    }
}

void violations() {
    system("cls"); // clears terminal
    cout << "\nViolations\n";
    InFileStream input("violations.txt");

    // Count the number of violations
    int loop_count = 0;
    int tempInt;
    while (input >> tempInt) {
        loop_count++;
    }

    // Allocate dynamic array based on loop_count
    int* temparr = new int[loop_count];

    // Close and reopen the file to reset to the beginning
    input.close();
    input.open("violations.txt");

    // Read violations into temparr
    for (int i = 0; i < loop_count; ++i) {
        input >> temparr[i];
    }

    // Display violations
    for (int j = 0; j < 4; j++) {
        int tempcount = count;
        switch (j) {
            case 0:
                tempcount += j;
                cout << "Speeding Violations: " << temparr[tempcount] << endl;
                break;
            case 1:
                tempcount += j;
                cout << "Illegal Parking Violations: " << temparr[tempcount] << endl;
                break;
            case 2:
                tempcount += j;
                cout << "DRINKING UNDER THE INFLUENCE: " << temparr[tempcount] << endl;
                break;
            case 3:
                tempcount += j;
                if (temparr[tempcount] == 1) {
                    SetConsoleTextAttribute(h, 4);
                    cout << "\nThis Vehicle is Declared as Wanted!\n\n";
                    SetConsoleTextAttribute(h, 2);
                }
                break;
        }
    }

    // Free dynamically allocated memory
    delete[] temparr;

    second_menu();
}


void register_violations(){ // REGISTER VIOLATIONS FUNCTION
    int tempInt;
    int n = 0;
    
    InFileStream output("violations.txt");
    while(output >> tempInt){
        arr.push_back(tempInt); // Use push_back for vectors
    }

    int i = 0;
    char answer;
    int option;
    bool exitLoop = false;
        cout << "are you sure you want to enter violations for this vehicle? (y/n): ";
        cin >> answer;
    do {
        int tempcount = count;
        tempcount -=1;
        switch(answer){
            case 'y':
            case 'Y':     // SWITCH LOOP THAT CHANGES THE VALUE OF THE ARRAY
                cout << "[1] - SPEEDING VIOLATIONS\n";
                cout << "[2] - Illegal Parking Violation\n";
                cout << "[3] - Drinking Under the Influence\n";
                cout << "[4] - View Violations\n";
                cout << "[5] - Declare Vehicle as Wanted\n";
                cout << "[6] - Back to Menu\n";
                cin >> option;
                switch(option){
                    case 1:
                        arr[tempcount] += 1;
                        cout << "SPEEDING VIOLATION ADDED\n";
                        break;
                    case 2:
                        tempcount += 1;
                        arr[tempcount] += 1;
                        cout << "ILLEGAL PARKING VIOLATION ADDED\n";
                        break;
                    case 3:
                        tempcount += 2;
                        arr[tempcount] +=1;
                        cout << "DRINKING UNDER THE INFLUENCE VIOLATION ADDED\n";
                        break;
                    case 4:
                        exitLoop = true; 
                        violations();
                        break;  
                    case 5:
                        tempcount += 3;
                        if (arr[tempcount] > 1){
                            arr[tempcount] -= 1;
                        }
                        arr[tempcount] += 1;
                        cout << "Vehicle Declared as Wanted\n";
                        break;
                    case 6:
                        exitLoop = true; 
                        break;
                    default:
                        cout << "Invalid option. Please try again.\n";
                        break;
                }
                break;
            case 'n':
            case 'N':
                exitLoop = true;
                break;
            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
        ofstream input("violations.txt");
        for (int k = 0; k < arr.size(); k++){ 
            input << arr[k] << ' ';
        }  
    } while (!exitLoop);   
    second_menu();
}