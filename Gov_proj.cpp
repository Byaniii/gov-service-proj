// Pre-processor Directives
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <stdlib.h>
#include <cstdio>
#include <algorithm>
using namespace std;

// Global Variables
int tin, profile_count = 0;
double monthly1Salary = 0;
string UserName;

// Function Prototypes 
bool validSalary(const string& input);
void Start_Menu();
void Main_Menu();
void registration();
void login();
void IncorrectLogin();
void register_profile();
void View_Profile();
void TIN();
double thirteenmonthpay(double salary);
double annual_salary(double salary);
double tax_incomeTable(int choose, double ms, double thirteenmonthpay);
double regular_Tax(double monthly1Salary, double tmp, double AS);
double valueAddedTax();
double partTimefullTimeTax();
double combinedTax();
long corporateTax();
bool UserNameValid(string UserInput);
bool MatchUsernameDataBase(string Username);
bool ValidPhoneNumber(string UserPhoneNumber);

// Struct for User Profile
struct Profile{
	string name, address, phone_number;
	double monthly1salary;
};


int main(){
    Start_Menu();
    return 0;
}

void Start_Menu(){ // Display Starting Menu
    system("cls"); // clears system terminal
    system("color 03");
    int option;
    cout << "=================Program  Name=================\n"; // Name of Program
    cout << "[1] LOGIN\n";
    cout << "[2] REGISTRATION\n";
    cout << "[3] EXIT PROGRAM\n";
    cout << "Enter option: ";
    cin >> option;
    
    switch(option){
        case 1:
            system("cls");
            login();
            break;
        case 2:
            system("cls");
            registration();
            break;
        case 3:
            system("cls");
            return;
            break;
        default:
            system("color 04");
            cout << "\nPlease enter a valid option!\n";
            system("color 03");
            Start_Menu();
    }
}

void Main_Menu(){ // Main Menu Display
    system("cls"); // clears system terminal
    cout << "Welcome " << UserName <<"!"<<endl;
    system("color 03");
    int option;
    cout << "[1] TAX CALCULATOR\n";
    cout << "[2] PART/FULL TIME TAX\n";
    cout << "[3] VALUE ADDED TAX\n";
    cout << "[4] TIN\n";
    cout << "[5] VIEW PROFILE\n";
    cout << "[6] LOGOUT\n";
    cout << "[7] CORPORATE TAX\n";
    cout << "Enter option: ";
    cin >> option;
    switch(option){
        case 1:
            regular_Tax(monthly1Salary, 0, 0);
            break;
        case 2:
            partTimefullTimeTax();
            break;
        case 3:
            valueAddedTax();
            break;
        case 4:
            TIN();
            break;
        case 5:
            View_Profile();
            break;
        case 6:
            Start_Menu();
            break;
        case 7:
            corporateTax();
            break;
    }
}

void registration(){
    ofstream UsernameInput("Usernames.txt", ios::app); // opens Usernames text file to append user input 

    string Register_Username, RegisterPassword;
    bool valid = false, UserIsValid = false;

    cin.ignore(1,'\n'); // clears input buffer
        
    do{
        system("cls");
        cout << "\nRegister Username(Must not contain whitespace): ";
        getline(cin, Register_Username);
        UserIsValid = (UserNameValid(Register_Username)&& (!(MatchUsernameDataBase(Register_Username))));
    }while(!UserIsValid); // While loop validating username with specific criteria && not matching database
    
    UsernameInput << Register_Username << "\n"; // Appends username into the text file

    UsernameInput.close(); // closes Usernames text file

    ofstream PasswordInput("Passwords.txt", ios::app); // opens Passwords text file to append user input


    do{ // do-while loop for password criteria
        system("cls"); // clears terminal
        bool Capital = false, Number = false, WhiteSpace = false;
        cout << "Register Password: ";
        getline(cin, RegisterPassword);

        for (int i = 0; i < RegisterPassword.length(); i++) { // Password criteria
            if (isupper(RegisterPassword[i])) { // checks if index is uppercased
                Capital = true; 
            }
            if (isdigit(RegisterPassword[i])) { // checks if index is a digit
                Number = true; 
            }
            if (isspace(RegisterPassword[i])) { // checks if index is a white space
                WhiteSpace = false; 
                break; 
            }
        } // password turns valid if it meets criteria
        if (Capital & Number & !WhiteSpace){
            PasswordInput << RegisterPassword <<'\n';
            system("Color 03");
            system("cls");
            cout << "\nSuccessfully registered " << Register_Username <<'!'<<endl;
            valid = true;
            break;
        }
        else{ // repeats loop if password is invalid
            system("Color 04"); // changes system terminal color
            cout << "Ensure that your password contains a capital letter, atleast one number, and no white spaces;\n";
        }
    }while(!valid);
    PasswordInput.close(); // closes file
    register_profile(); // goes to register profile function
}

void login(){ // Log-in Function
    system("color 03"); // changes terminal color 
    string UserPassword, UserComparison, PasswordComparison, UserData, PasswordData;
    bool found = false;
    profile_count = 0; // profile count used for corresponding profile data with user credentials

    ifstream users("Usernames.txt"), passwords("Passwords.txt"); // opens "Usernames" and "Passwords" text file for reading
    cin.ignore (1, '\n');
    cout << "\nUsername: ";
    getline(cin, UserName);

    cout << "Password: ";
    getline(cin, UserPassword);
    
    while(getline(users, UserData) && getline(passwords, PasswordData)){ // retrieves line from text file
        profile_count++; // a global count used for corresponding user database with profile data base
        istringstream issUser(UserData), issPass(PasswordData); // initializes variables to process data from string to streams
        while(issUser >> UserComparison && issPass >> PasswordComparison){ // passes data 
            if (UserName == UserComparison && UserPassword == PasswordComparison){ // Compares user input with text file data base
                found = true; // declares the user's input found within the data base
            }
        }
        if (found){ // breaks while loop if database match
            break;
        }
    }  
    if(!found){ // Asks user to repeat due to incorrect or non-existent credentials
        system("color 04");
        cout << "\nUsername/Password is either Not Found or Incorrect Please try Again!";
        IncorrectLogin();
    }
    Main_Menu();    
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
            Start_Menu();
            break;
        default:
            
            system("color 04");
            cout << "\nPlease enter a valid option!\n";
            IncorrectLogin();
    }
}
bool ValidSalary(string input) //This function checks if the input is a valid number
{   
    int string_count = 0;
    if (input.empty()) // checks if input is empty
    {
        return false;
    }

    for (int i = 0; i < input.length(); i++){ // criteria for salary (no punctuations/whitespace/letters)
        if(ispunct(input[i]) || isspace(input[i]) || isalpha(input[i])){
            return false; // returns false if fails to meet criteria
        }    
    }
    return true; // returns true if input meets criteria
}
void register_profile(){
	Profile profile; // declares profile struct 
	string user_Input;
	ofstream profile_input("profiles.txt", ios::app); // opens profiles.txt file for appending/writting
    bool PhoneNumberIsValid = false;

    while(profile.name.find_first_not_of(' ') == string::npos){ // checks first position of string for any whitespace(not allowed)
        system("cls");
        cout << "Enter Your name(Must not be empty): ";
	    getline(cin, profile.name);
    }
    while(profile.address.find_first_not_of(' ') == string::npos){ // checks first position of string for any whitespace(not allowed)
        system("cls");
        cout << "Enter Address(Must not be empty): ";
	    getline(cin, profile.address);
        
    }	

	while(!PhoneNumberIsValid){ // Loop repeats if user is unable to meet criteria
        system("cls");
        cout << "Enter Phone Number(Must not be empty/whitespace/alphabetical): ";
	    getline(cin, profile.phone_number);
        PhoneNumberIsValid = (ValidPhoneNumber(profile.phone_number)); // (boolean value) Validates Phone Number (Not empty/whitespace/letter)
    }

    do { // Monthly Salary Input
        system("cls"); // clears terminal 
        cout << "Enter your Monthly Salary: ";
        getline(cin, user_Input);

        if (!ValidSalary(user_Input)) // returns monthly salary is invalid (must be consecutive integers/numbers)
        {
            cout << "Invalid input! Please enter a valid number!" << endl;
        }
        else
        {
            istringstream(user_Input) >> profile.monthly1salary; // inputs stream into monthly1salary struct profile
            break;
        }

    } while (true);
    
	profile_input << profile.name <<endl<< profile.address <<endl<< profile.phone_number <<endl<< profile.monthly1salary<<endl;
	profile_input.close();
    Start_Menu();
}

void View_Profile(){ // NEEDS TO BE UPDATED
    system("cls");
	string output, tempfile2;
    int count = 0;
	ifstream profile_output("profiles.txt"), AnnualSalaryOutput("AnnualSalaryDataBase.txt"); // opens profiles and AnnualSalaryDataBase for reading
	while(getline(profile_output,output)){
        if (count < 4){
        switch(count){
            case 0:
            cout << "Name: ";
            break;
            case 1:
            cout << "Address: ";
            break;
            case 2:
            cout << "Phone Number: ";
            break;
            case 3:
            cout << "Monthly Salary: ";
            break;
            case 4:
            cout << "Annual Salary: ";
        }
        cout << output << endl;
        count ++; // increments count for displaying user profile
	    }
    }
	profile_output.close(); // closes text file
    int option;
    cout << "=================Program  Name=================\n"; // Name of Program
    cout << "[1] MAIN MENU\n";
    cout << "[2] LOG-OUT\n";
    cout << "[3] EXIT PROGRAM\n";
    cout << "Enter option: ";
    cin >> option;
    
    switch(option){
        case 1:
            Main_Menu();
            break;
        case 2:
            Start_Menu();
            break;
        case 3:
            return;
        default:
            system("color 04"); // changes system color
            cout << "\nPlease enter a valid option!\n";
            system("color 03"); // changes system color 
            
            View_Profile(); // Calls view profile function 
    }

}

void TIN () //This function will display the TIN number and the details of the user
{
	int tin;
    srand(time(0)); 
	int tin1 = rand() % 1000 + 1; //Generates a random number for the TIN number
	int tin2 = rand() % 1000 + 1;
	int tin3 = rand() % 1000 + 1;
    system("cls");
	cout << "Your TIN number is: " << tin1 << "-" << tin2 << "-" << tin3 << "-" << "00000" <<endl<< endl;	
    int option;
    cout << "=================Program  Name=================\n"; // Name of Program
    cout << "[1] MAIN MENU\n";
    cout << "[2] LOG-OUT\n";
    cout << "Enter option: ";
    cin >> option;
    
    switch(option){
        case 1:
            Main_Menu(); // Calls Main Menu Function
            break;
        case 2:
            Start_Menu(); // Calls Start Menu Function 
            break;
        default:
            system("color 04"); // Changes system color 
            cout << "\nPlease enter a valid option!\n";
            system("color 03"); // Cahnges system color 
            
            Main_Menu(); // Calls Main Menu function
    }
}
double thirteenmonthpay(double salary){
    if(salary > 90000)
    {
        double monthly_salary = salary - 90000;
        return monthly_salary;
    }
    else
    {
        double monthly_salary = 0;
        return monthly_salary;
    }
    return salary;
}
double annual_salary(double salary){
    int x = salary * 12;
    return x;
}
double tax_incomeTable(int choose, double ms, double thirteenmonthpay) //This function represents the latest tax table from BIR
{
    double mS = ms;
    double MS = ms * 12 + thirteenmonthpay;
    switch(choose)
    {
        case 1:
            cout<<"Your monthly tax is: ";
            if (mS>=666667)
            {
                double x = ((ms - 666667) * 0.35) + 200833.33;
                return x;
            }
            else if (mS<=666666 && mS>=166667)
            {
                double x = ((ms - 166667 ) * 0.30) + 40833.33;
                return x;
            }
            else if (mS<=166667 && mS>= 66667)
            {
                double x = ((ms - 66667) * 0.25) + 10833.33;
                return x;
            }
            else if (mS<=66666 && mS>=33333)
            {
                double x = ((ms - 66666) * 0.20) + 2500;
                return x;
            }   
            else if (mS<=33332 && mS>=20833)
            {
                double x = ((ms - 33332) * 0.15);
                return x;
            }
            else 
            {
                cout<<"No withholding tax.";
                return 0;
            }
        case 2:
            cout<<"Your annual tax is: ";
            if (MS>=8000000)
            {
                double x = ((MS - 8000000) * 0.35) + 2410000;
                return x;
            }
            else if (MS<=8000000 && MS>=2000000)
            {
                double x = ((MS - 2000000) * 0.32) + 490000;
                return x;
            }
            else if (MS<=2000000 && MS>=800000)
            {
                double x = ((MS - 800000) * 0.30) + 130000;
                return x;
            }
            else if (MS<=800000 && MS>=400000)
            {
                double x = ((MS - 400000) * 0.25) + 30000;
                return x;
            }
            else if (MS<=400000 && MS>=250000)
            {
                double x = ((MS - 250000) * 0.20);
                return x;
            }
            else
            {
                cout<<"No withholding tax.";
                return 0;
            }
    }
}

double regular_Tax(double monthly1Salary, double tmp, double AS)
{
    string line, tempvar;
    int choice, count = 0, tempint;
    cout << "Choice:" << endl; // Asks for user choice
	cout << "1 - Monthly Tax" << endl; 
	cout << "2 - Annual  Tax" << endl;
	do
	{
		cout << "Enter your choice: ";
		cin >> choice;
	} while (choice != 1 && choice != 2);
    tempint = profile_count * 4; // Uses earlier profile count(Log-in Function) to determine the corresponding user details 
    ifstream MonthlySalaryOutput("profiles.txt"); // opens profiles.txt file for reading 
    while(getline(MonthlySalaryOutput, line)){ // extracts from MonthlySalaryOutput into line
        count++;
        if (count == tempint){
            monthly1Salary = stod(line);        // connverts stream in double    
        }
    }

tmp = thirteenmonthpay(monthly1Salary);
ofstream AnnualSalaryInput("AnnualSalaryDatabase.txt", ios::app); // opens AnnualSalaryDatabase.txt for appending
AS = annual_salary(monthly1Salary);      
cout << "\n"; //Displays output of the entire program
cout << "Monthly Salary: " << monthly1Salary << endl;
cout << "Your annual salary: " << AS << endl;
cout << tax_incomeTable(choice, monthly1Salary, tmp) << endl;
AnnualSalaryInput << AS << endl; // writes/appends to text file
AnnualSalaryInput.close(); // closes text file
    int option;
    cout << "=================Program  Name=================\n"; // Name of Program
    cout << "[1] MAIN MENU\n";
    cout << "[2] LOG-OUT\n";
    cout << "Enter option: ";
    cin >> option;
    
    switch(option){
        case 1:
            Main_Menu();
            break;
        case 2:
            Start_Menu();
            break;
        default:
            system("color 04");
            cout << "\nPlease enter a valid option!\n";
            system("color 03");
            
            Main_Menu();
    }
}

double valueAddedTax()
{
    double product;
    cout << "Enter the price of the product: ";
    cin >> product;
    double x = product * 0.12;
    cout << "The value added tax of the product is: " << x << endl;
    return x;
}

double partTimefullTimeTax()
{
    float annual_halfpartTimeFulltime_salary;
    double salary1, salary2, halfannual1Salary, halfannual2Salary, fullannualSalary, full_Salary, totalSalary;
    cout << "Enter your full-time salary: ";
    cin >> salary1;
    cout << "Enter your part-time salary: ";
    cin >> salary2;
    totalSalary = salary1 + salary2;
    thirteenmonthpay(totalSalary);
    fullannualSalary = salary1 * 12;
    salary1 *= 6;
    salary2 *= 6;
    annual_halfpartTimeFulltime_salary = salary1 + salary2;
    cout << "Your annual salary is: " << annual_halfpartTimeFulltime_salary << endl;

    cout << "Your Tax due is: " << endl;
    if (annual_halfpartTimeFulltime_salary>=8000000)
    {
        double x = ((annual_halfpartTimeFulltime_salary - 8000000) * 0.35) + 2410000;
        return x;
    }
    
    else if (annual_halfpartTimeFulltime_salary<=8000000 && annual_halfpartTimeFulltime_salary>=2000000)
    {
        double x = ((annual_halfpartTimeFulltime_salary - 2000000) * 0.32) + 490000;
        return x;
    }
    
    else if (annual_halfpartTimeFulltime_salary<=2000000 && annual_halfpartTimeFulltime_salary>=800000)
    {
        double x = ((annual_halfpartTimeFulltime_salary - 800000) * 0.30) + 130000;
        return x;
    }
    
    else if (annual_halfpartTimeFulltime_salary<=800000 && annual_halfpartTimeFulltime_salary>=400000)
    {
        double x = ((annual_halfpartTimeFulltime_salary - 400000) * 0.25) + 30000;
        return x;
    }
    else if (annual_halfpartTimeFulltime_salary<=400000 && annual_halfpartTimeFulltime_salary>=250000)
    {
        double x = ((annual_halfpartTimeFulltime_salary - 250000) * 0.20);
        return x;
    }
    else
    {
        cout<<"No withholding tax." << endl;
        return 0;
    }
}

long corporateTax()
{
    int option;
    long net_Sales, gross_Sales, gross_Income, allowable_Deductions, net_Income, mcit;
    cout << "Enter the net sales: ";
    cin >> net_Sales;
    cout << "Enter the gross sales: ";
    cin >> gross_Sales;
    cout << "Enter the allowable deductions: ";
    cin >> allowable_Deductions;

    gross_Income = net_Sales - gross_Sales;
    net_Income = gross_Income - allowable_Deductions;

    cout << "Enter the tax option: " << endl;
    cout << "[1] Domestic Corporation" << endl;
    cout << "[2] Resident Foreign Corporation" << endl;
    cout << "[3] Non-Resident Foreign Corporation" << endl;
    cout << "[4] Offshore Banking Units (OBU's)" << endl;
    cout << "[5] Regional Operating Headquarters (ROHQ)" << endl;
    cin >> option;

    switch (option)
    {
        case 1:
            if (net_Income > 100000000)
            {
                long x = (net_Income * 0.25);
                cout << "Your corporate tax is: " << x << endl;
                return x;
            }
            else if (net_Income <= 100000000 && net_Income >= 5000000)
            {
                long x = (net_Income * 0.20);
                cout << "Your corporate tax is: " << x << endl;
                return x;
            }
            else
            {
                cout << "No withholding Tax.";
                return 0;
            }
        case 2:
            if (net_Income > 1000000000)
            {
                long x = (net_Income * 0.25);
                cout << "Your corporate tax is: " << x << endl;
                return x;
            }
            else
            {
                cout << "No withholding Tax.";
                return 0;
            }
        case 3:
            if (net_Income > 100000000)
            {
                long x = (net_Income * 0.25);
                cout << "Your corporate tax is: " << x << endl;
                return x;
            }
            else
            {
                cout << "No withholding Tax.";
                return 0;
            }
        case 4:
            if (net_Income > 100000000)
            {
                long x = (net_Income * 0.25);
                cout << "Your corporate tax is: " << x << endl;
                return x;
            }
            else
            {
                cout << "No withholding Tax.";
                return 0;
            }
        case 5:
            if (net_Income > 100000000)
            {
                long x = (net_Income * 0.25);
                cout << "Your corporate tax is: " << x << endl;
                return x;
            }
            else
            {
                cout << "No withholding Tax.";
                return 0;
            }
        default:
            cout << "Invalid option.";
            return 0;
    }
}

bool MatchUsernameDataBase(string username){
    ifstream UsernameOutput("usernames.txt"); // opens username textfile for reading 

    bool found = false;
    string line, UserComparison;
    while (getline(UsernameOutput, line)){ // while loop determining if user registration entry matches database(returns invalid if true)
        istringstream issUser(line); 
        while(issUser >> UserComparison){
            if(username == UserComparison){
                found = true;
            }
            if(found){    // If found, restricts user from utilizing entry           
                cout << "\nUsername is Already Taken\n";
                return true; // returns true if entry matches the data base (invalid)
            }       
        }
    }
    return false; // returns false if entry does not match data base (allowed)
}

bool UserNameValid(string UserInput){ // Function to check if username registration has whitespace(invalid)
    bool valid = false; 
    for (int i = 0; i < UserInput.length(); i++){
        if (isspace(UserInput[i])){ // checks individual index of string for any whitespace 
            return false; // returns false (if username is not allowed)
        }
    }
    return true; // returns true (if username meets criteria)
}

bool ValidPhoneNumber(string UserPhoneNumber){ // Function to check if Phone number has letters/whitespaces(invalid)
    for (int i = 0; i < UserPhoneNumber.length(); i++){
        if(isalpha(UserPhoneNumber[i]) || (isspace(UserPhoneNumber[i]))){ // no whitespace/letter for any index in string
            return false; // returns false (Phone Number is not valid)
        }
    }
    return true; // returns true (Phone number is allowed)
}
