#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <algorithm>
#include <conio.h>

using namespace std;
ifstream inputFile;
std::ofstream outputFile;
class Database{
public:
    int verificare(string licenseNr){
        inputFile.open("database.csv");
        string line="";
        while(getline(inputFile,line)){
            string nr, name, adress;
            stringstream inputString(line);
            getline(inputString, nr, ',');
            getline(inputString, name, ',');
            getline(inputString, adress);
            line="";
            size_t found = licenseNr.find(nr);
            if (found != string::npos){
                cout<<"Permission granted.\nUser information:\nName: "<<name<<"\nAddress: "<<adress<<endl;
                return 1;
            }
        }
        inputFile.close();
        return 0;
    }
};
class Admin{
public:
    void addUser(string nr, string name, string adress){
        outputFile<<nr<<','<<name<<','<<adress<<endl;
    }
    int login(string username, string password){
        inputFile.open("admins.csv");
        string line="";
        while(getline(inputFile,line)){
            string name, pass;
            stringstream inputString(line);
            getline(inputString, name, ',');
            getline(inputString, pass);
            line="";
            if(name==username)
                if(pass==password)return 1;
                else throw "Incorrect password";
        }
        inputFile.close();
        throw "Incorrect username";
    }
    void deleteUser(string license){
        ifstream in;
        ofstream out;
        int count=0;
        transform(license.begin(), license.end(), license.begin(), ::toupper);
        in.open("database.csv");
        out.open("databasenew.csv");
        string line="";
        while(getline(in,line)){
            string nr;
            string name;
            string adress;

            stringstream inputString(line);

            getline(inputString, nr, ',');
            getline(inputString, name, ',');
            getline(inputString, adress);

            line="";

            //check if we have to delete the record
            if(nr!=license){
                //add record to new csv
                out<<nr<<','<<name<<','<<adress<<endl;
            }
            else count=1;
        }
        in.close();
        out.close();
        remove("database.csv");
        rename("databasenew.csv","database.csv");
        if(count==0)throw "User not found";
    }
};
int main(){
    int aux;
    Database obj;
    Admin admin;
    ifstream f;

    string licenseNr;
    cout<<"1 for check, 2 for admin: \n";
    cin>>aux;
    switch(aux){
        case 1:{
            f.open("result.txt");
            while(getline(f, licenseNr)){
                transform(licenseNr.begin(), licenseNr.end(), licenseNr.begin(), ::toupper);
                if(obj.verificare(licenseNr)){
                    cout << endl << "Press any key to continue" << endl;
                    getch();
                    return 0;
                }
            }
            f.close();
            cout<<"No match";
            break;
        }
        case 2:{
            string username, password;
            char c;
            cout<<"username: ";
            cin>>username;
            cout<<"password: ";
            cin>>password;
            try{
                if(admin.login(username,password)){
                    cout<<"a to add, d to delete: \n";
                    char c;
                    cin>>c;
                    switch(c){
                        case 'a':{
                            string license, name, adress;
                            cout<<"Provide information for the database: "<<endl;
                            cout<<"License plate: ";
                            cin>>license;
                            cout<<"Name: ";
                            cin>>name;
                            cout<<"Adress: ";
                            cin>>adress;
                            outputFile.open("database.csv", std::ios::app);
                            admin.addUser(license, name, adress);
                            outputFile.close();
                            break;
                        }
                        case 'd':{
                            string license;
                            cout<<"Provide the license plate number that you want to delete.\n";
                            cin>>license;
                            try {
                                admin.deleteUser(license);
                                cout<<"User deleted succesfully";
                            }catch(const char *msg){
                                cout<<msg;
                            }
                            break;
                        }
                    }
                }
            }catch(const char *msg){
                cout<<msg;
            }
            break;
        }
    }
    cout << endl << "Press any key to continue" << endl;
    getch();
    return 0;
}
