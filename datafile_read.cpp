#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Patient{
    int index;
    vector<string> var;
};


string remove_quotes(string s){
    int n = s.size();
    return(s.substr(1,n-1));
}

void read_file(string filename){
    fstream file;
    string word = "";
    string line = "";
    file.open(filename.c_str()); 
    int count=0;
    int i=0;
    vector<Patient> Patient_list;
    // extracting words from the file 
    while (getline(file,line)) 
    { 
        // displaying content
        count=0;
        Patient p;
        p.index = i;
        istringstream iss(line);

        // p.var.push_back(remove_quotes(word));
        while(iss>>word){
            if(count==0)
                cout<<word<<endl;
            p.var.push_back(remove_quotes(word));
            count++;
        }
        
        Patient_list.push_back(p);
        cout <<i<<"size: "<<count<<endl;;
        i++;
    } 
    return;
}



int main()
{
    string filename = "records.dat";
    read_file(filename);
    return 0;
}