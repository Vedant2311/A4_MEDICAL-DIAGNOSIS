#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

string remove_quotes(string s){
    int n = s.size();
    return(s.substr(1,n-1));
}

vector<vector<string> > read_file(string filename){
    fstream file;
    string word = "";
    string line = "";
    file.open(filename.c_str()); 
    vector<vector<string> > patient_list;
    // extracting words from the file 
    while (getline(file,line)) 
    { 
        // displaying content
        vector<string> p;
        istringstream iss(line);

        while(iss>>word){
            p.push_back(remove_quotes(word));
        }
        
        patient_list.push_back(p);
    } 
    return patient_list;
}



int main()
{
    string filename = "records.dat";
    vector<vector<string> > patient_list = read_file(filename);
    cout<<patient_list.size()<<"  "<<patient_list[0].size()<<endl;
    return 0;
}
