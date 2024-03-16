
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <stdlib.h>
#include <cstdio>
#include <algorithm>
using namespace std;

int tin, profile_count = 0;
double monthly1Salary = 0;

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

struct Profile{
	string name, address, phone_number;
	double monthly1salary;
};


int main(){

    Start_Menu();

    return 0;
}

void Start_Menu(){ // Display Starting Menu
    system("cls");
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
            login();
            break;
        case 2:
            registration();
            break;
        case 3:
            return;
        default:
            system("color 04");
            cout << "\nPlease enter a valid option!\n";
            system("color 03");
            Start_Menu();
    }
}

void Main_Menu(){ // Main Menu Display
    system("cls");
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
    system("cls"); // clss system terminal
    ofstream UsernameInput("Usernames.txt", ios::app); // opens Usernames text file to append user input 

    string Register_Username, RegisterPassword;
    bool valid = false;

    cin.ignore(1, '\n'); // clss input buffer/queue
    while(Register_Username.find_first_not_of(' ') == string::npos){
        cout <<'\n';
        cout << "Register Username(Input must not be empty): ";
	    getline(cin, Register_Username);
        system("cls");
    }
    UsernameInput << Register_Username << "\n"; // Input Username into the text file

    UsernameInput.close(); // closes Usernames text file

    ofstream PasswordInput("Passwords.txt", ios::app); // opens Passwords text file to append user input


    do{ // do-while loop for password criteria
        bool Capital = false, Number = false, WhiteSpace = false;

        cout << "Register Password: ";
        getline(cin, RegisterPassword);

        for (int i = 0; i < RegisterPassword.length(); i++) { 
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
            PasswordInput << RegisterPassword <<'\n';
            system("Color 03");
            cout << "\nSuccessfully registered " << Register_Username <<'!'<<endl;
            valid = true;
            break;
        }
        else{ // repeats loop if password is invalid
            system("Color 04"); // changes system terminal color
            cout << "Ensure that your password contains a capital letter, atleast one number, and no white spaces;\n";
        }
    }while(!valid);
    PasswordInput.close();
    register_profile();
}

void login(){ // Log-in Function
    system("cls");
    system("color 03");
    string UserName, UserPassword, UserComparison, PasswordComparison, UserData, PasswordData;
    bool found = false;
    profile_count = 0;

    ifstream users("Usernames.txt"), passwords("Passwords.txt"); // opens "Usernames" and "Passwords" text file for reading
    cin.ignore (1, '\n');
    cout << "\nUsername: ";
    getline(cin, UserName);

    cout << "Password: ";
    getline(cin, UserPassword);
    
    while(getline(users, UserData) && getline(passwords, PasswordData)){ // retrieves line from text file
        profile_count++;
        istringstream issUser(UserData), issPass(PasswordData); 
        while(issUser >> UserComparison && issPass >> PasswordComparison){ 
            if (UserName == UserComparison && UserPassword == PasswordComparison){ // Compares user input with text file data base
                system("cls");
                cout << "Welcome " << UserName <<"!"<<endl;
                found = true;
            }
        }
        if (found){
            break;
        }
    }  
    if(!found){
        system("cls");
        system("color 04");
        cout << "\nUsername/Password not found!";
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
            system("cls");
            system("color 04");
            cout << "\nPlease enter a valid option!\n";
            IncorrectLogin();
    }
}
bool ValidSalary(string input) //This function checks if the input is a valid number
{   
    if (input.empty())
    {
        return false;
    }

    for (int i = 0; i < input.length(); i++){
        if(ispunct(input[i]) || isspace(input[i]) || isalpha(input[i])){
            return false;
        }
        else{
            return true;
        }
    }
}
void register_profile(){
	Profile profile;
	string user_Input;
	ofstream profile_input("profiles.txt", ios::app);

    while(profile.name.find_first_not_of(' ') == string::npos){
        system("cls");
        cout <<'\n';
        cout << "Enter Your name(Must not be empty): ";
	    getline(cin, profile.name);
    }
    while(profile.address.find_first_not_of(' ') == string::npos){
        system("cls");
        cout <<'\n';
        cout << "Enter Address(Must not be empty): ";
	    getline(cin, profile.address);
        
    }	

	while(profile.phone_number.find_first_not_of(' ') == string::npos){
        system("cls");
        cout <<'\n';
        cout << "Enter Phone Number(Must not be empty): ";
	    getline(cin, profile.phone_number);
        
    }

    do {
        cout << "Enter your Monthly Salary: ";
        getline(cin, user_Input);

        if (!ValidSalary(user_Input))
        {
            cout << "Invalid input! Please enter a valid number!" << endl;
        }
        else
        {
            istringstream(user_Input) >> profile.monthly1salary;
            break;
        }

    } while (true);
    
	profile_input << profile.name <<endl<< profile.address <<endl<< profile.phone_number <<endl<< profile.monthly1salary<<endl;
	profile_input.close();
    Start_Menu();
}

void View_Profile(){
    system("cls");
	string output, tempfile2;
    int count = 0;
	ifstream profile_output("profiles.txt");
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
        }
        cout << output << endl;
        count ++;
	    }
    }
	profile_output.close();    
}

void TIN () //This function will display the TIN number and the details of the user
{
	int tin;
    srand(time(0));
	int tin1 = rand() % 1000 + 1; //Generates a random number for the TIN number
	int tin2 = rand() % 1000 + 1;
	int tin3 = rand() % 1000 + 1;

	cout << "Your TIN number is: " << tin1 << "-" << tin2 << "-" << tin3 << "-" << "00000" << endl;
	cout << "Please proceed to your nearest BIR office for further instructions." << endl;	
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
            cout<<"Your annual tax is: " << endl;
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
    return 0;
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
    tempint = profile_count * 4;
    ifstream MonthlySalaryOutput("profiles.txt");
    while(getline(MonthlySalaryOutput, line)){
        count++;
        if (count == tempint){
            monthly1Salary = stod(line);            
        }
    }

tmp = thirteenmonthpay(monthly1Salary);
                
AS = annual_salary(monthly1Salary);      
cout << "\n"; //Displays output of the entire program
cout << "Monthly Salary: " << monthly1Salary << endl;
cout << "Your annual salary: " << AS << endl;
cout << tax_incomeTable(choice, monthly1Salary, tmp) << endl;
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