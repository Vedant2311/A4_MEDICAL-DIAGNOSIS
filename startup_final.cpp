#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <unordered_set>
#include <bits/stdc++.h> 
using namespace std;

struct unknowns{
    int row;
    int colm;
};

vector<unknowns> unknowns_list;
vector<string> visited;
vector<vector<string> > patient_list;

// Our graph consists of a list of nodes where each node is represented as follows:
class Graph_Node{

private:
    string Node_Name;  // Variable name 
    vector<int> Children; // Children of a particular node - these are index of nodes in graph.
    vector<string> Parents; // Parents of a particular node- note these are names of parents
    int nvalues;  // Number of categories a variable represented by this node can take
    vector<string> values; // Categories of possible values
    vector<float> CPT; // conditional probability table as a 1-d array . Look for BIF format to understand its meaning

public:
    // Constructor- a node is initialised with its name and its categories
    Graph_Node(string name,int n,vector<string> vals)       //n - size of value set
    {
        Node_Name=name;
    
        nvalues=n;
        values=vals;
        

    }
    string get_name()
    {
        return Node_Name;
    }
    vector<int> get_children()
    {
        return Children;
    }
    vector<string> get_Parents()
    {
        return Parents;
    }
    vector<float> get_CPT()
    {
        return CPT;
    }
    int get_nvalues()
    {
        return nvalues;
    }
    vector<string> get_values()
    {
        return values;
    }
    void set_CPT(vector<float> new_CPT)
    {
        CPT.clear();
        CPT=new_CPT;
    }
    void set_Parents(vector<string> Parent_Nodes)
    {
        Parents.clear();
        Parents=Parent_Nodes;
    }
    // add another node in a graph as a child of this node
    int add_child(int new_child_index )
    {
        for(int i=0;i<Children.size();i++)
        {
            if(Children[i]==new_child_index)
                return 0;
        }
        Children.push_back(new_child_index);
        return 1;
    }



};


 // The whole network represted as a list of nodes
class network{


    
public:

    list <Graph_Node> Pres_Graph;


    int addNode(Graph_Node node)
    {
        Pres_Graph.push_back(node);
        return 0;
    }
    
    
    int netSize()
    {
        return Pres_Graph.size();
    }
    // get the index of node with a given name
    int get_index(string val_name)
    {
        list<Graph_Node>::iterator listIt;
        int count=0;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            if(listIt->get_name().compare(val_name)==0)
                return count;
            count++;
        }
        return -1;
    }
// get the node at nth index
    list<Graph_Node>::iterator get_nth_node(int n)
    {
       list<Graph_Node>::iterator listIt;
        int count=0;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            if(count==n)
                return listIt;
            count++;
        }
        return listIt; 
    }
    //get the iterator of a node with a given name
    list<Graph_Node>::iterator search_node(string val_name)
    {
        list<Graph_Node>::iterator listIt;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            if(listIt->get_name().compare(val_name)==0)
                return listIt;
        }
    
            cout<<"node not found\n";
        return listIt;
    }

    int search_index(string val_name)
    {
        list<Graph_Node>::iterator listIt;
        int index=0;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            if(listIt->get_name().compare(val_name)==0)
                return index;
            index++;
        }
    
            cout<<"node not found\n";
        return -1;
    }

    vector<float> find_all_CPT(){

        vector<float> res;
        list<Graph_Node>::iterator listIt;
        for(listIt=Pres_Graph.begin();listIt!=Pres_Graph.end();listIt++)
        {
            std::vector<float> added = (*listIt).get_CPT();
            res.insert(res.end(),added.begin(), added.end()); 
        }
    
        return res;


    }


    

};

network read_network(string s_name)
{
    network Alarm;
    string line;
    int find=0;
    ifstream myfile(s_name); 
    string temp;
    string name;
    vector<string> values;
    
    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            stringstream ss;
            getline (myfile,line);
            
            
            ss.str(line);
            ss>>temp;
            
            
            if(temp.compare("variable")==0)
            {
                    
                    ss>>name;
                    getline (myfile,line);
                   
                    stringstream ss2;
                    ss2.str(line);
                    for(int i=0;i<4;i++)
                    {
                        
                        ss2>>temp;
                        
                        
                    }
                    values.clear();
                    while(temp.compare("};")!=0)
                    {
                        values.push_back(temp);
                        
                        ss2>>temp;
                    }
                    Graph_Node new_node(name,values.size(),values);
                    int pos=Alarm.addNode(new_node);

                    
            }
            else if(temp.compare("probability")==0)
            {
                    
                    ss>>temp;
                    ss>>temp;
                    
                    list<Graph_Node>::iterator listIt;
                    list<Graph_Node>::iterator listIt1;
                    listIt=Alarm.search_node(temp);
                    int index=Alarm.get_index(temp);
                    ss>>temp;
                    values.clear();
                    while(temp.compare(")")!=0)
                    {
                        listIt1=Alarm.search_node(temp);
                        listIt1->add_child(index);
                        values.push_back(temp);
                        
                        ss>>temp;

                    }
                    listIt->set_Parents(values);
                    getline (myfile,line);
                    stringstream ss2;
                    
                    ss2.str(line);
                    ss2>> temp;
                    
                    ss2>> temp;
                    
                    vector<float> curr_CPT;
                    string::size_type sz;
                    while(temp.compare(";")!=0)
                    {
                        
                        curr_CPT.push_back(atof(temp.c_str()));
                        
                        ss2>>temp;
                       
                        

                    }
                    
                    listIt->set_CPT(curr_CPT);


            }
            else
            {
                
            }   
            
        }
        
        if(find==1)
        myfile.close();
    }
    
    return Alarm;
}

vector<int> get_roots(network Alarm){

    vector<int> roots;
    
    list<Graph_Node>::iterator listIt;
    int count=0;
    for(listIt=Alarm.Pres_Graph.begin();listIt!=Alarm.Pres_Graph.end();listIt++)
    {
        if(listIt->get_Parents().size()==0) roots.push_back(count);
          count ++;
    }

    return roots;
}

int get_index_val(vector<string> v, string s){
    for(int i=0 ;i<v.size(); i++){
        if(s.compare(v[i])==0)
            return i;
    }
    return -1;
}

bool has_space(string str){
    for (int i=0; i<str.size(); i++) 
   { 
       if (str[i] == ' ') 
        return true;
   }
   return false;
}

int check_prob_val(vector<string> values, vector<int> index){
    for(int i=0; i<index.size(); i++){
        if(has_space(values[index[i]])){
            return i;
        }
    }
    return -1;
    //returns the index of parent in this node's list who prev had a "?"
}

int find_row(vector<int> entry, vector<Graph_Node> parents){
    int row = 0;
    int temp = 0;
       
    for(int i=0; i<entry.size(); i++){
        temp = entry[i];
        for(int j=i+1; j<entry.size(); j++){
            temp = temp*(parents[j].get_nvalues());
        }
        row = row + temp;
    }
    return row;
}

void get_var_val(string s, vector<string> &var, vector<float> &val){
    string temp = "";
    float value=0.0;
    int start=0;
    vector<string> result; 
    stringstream check1(s); 
      
    string intermediate; 
      
    while(getline(check1, intermediate, ' ')) 
    { 
        result.push_back(intermediate); 
    } 
    for(int i=0; i<result.size(); i+=3){
        var.push_back(result[i]);
        val.push_back(stof(result[i+2]));
    }
    return;
}

bool diff_list(vector<float> v1, vector<float> v2){
    for(int i=0; i<v1.size(); i++){
        if(v1[i]!=v2[i])
            return true;
    }
    return false;
}


void find_cpt(network &Alarm, int ind, vector<vector<string> > patient_list, bool print){

    list<Graph_Node>::iterator it = Alarm.get_nth_node(ind);
    Graph_Node gn = (*it);
    vector<string> parent_str = gn.get_Parents();
    vector<Graph_Node> parents;
    vector<int> parent_index;

    int m = gn.get_nvalues();
    int n = 1;

    for(int i=0; i<parent_str.size(); i++){
        list<Graph_Node>::iterator temp = Alarm.search_node(parent_str[i]);
        parents.push_back(*temp);
        parent_index.push_back(Alarm.search_index((*temp).get_name()));
        n = n*((*temp).get_nvalues());
    }
    float cpt_values[n][m+1];
    for(int i=0; i<n; i++){
        for(int j=0; j<m+1; j++)
            cpt_values[i][j] = 0.0;
    }
    vector<int> entry;
    int x=0; 
    int y=0;

    //main loop
    for(int i=0; i<patient_list.size(); i++){
        bool flag = false;
        entry.clear();
        
        if(patient_list[i][ind].compare("\"?\"")==0){
            unknowns u;
            u.row =i; u.colm = ind;
            unknowns_list.push_back(u);
            continue;
        }

        int prob_val = check_prob_val(patient_list[i], parent_index);
        //////////////////////////////////// case when one of the parent had an unknown value

        if(prob_val>=0){
            for(int j=0; j<parent_index.size(); j++){
                if(j==prob_val)
                    continue;
                vector<string> values_list = parents[j].get_values();
                int var_numb = get_index_val(values_list,patient_list[i][parent_index[j]]);
                if(var_numb<0){
                    break;
                } 
                entry.push_back(var_numb);
            }
            string s = patient_list[i][parent_index[prob_val]];
      
            vector<string> values_list = parents[prob_val].get_values(); 
            vector<string> var;
            vector<float> val;
            get_var_val(s, var, val);            
            for(int i=0; i<var.size(); i++){
                int var_numb = get_index_val(values_list,var[i]);
                if(var_numb<0){
                    break;
                } 
                std::vector<int>::iterator it = entry.begin();
                entry.insert(it+prob_val,var_numb);
                x = find_row(entry, parents);
                y = get_index_val(gn.get_values(),patient_list[i][ind]);
                cpt_values[x][y]+=val[i];
        
                it = entry.begin();
                entry.erase(it+prob_val); 

            }   
        }
        ////////////////////////////////////////// normal case where all variable values are known
        else{
            for(int j=0; j<parent_index.size(); j++){
                vector<string> values_list = parents[j].get_values();
                int var_numb = get_index_val(values_list,patient_list[i][parent_index[j]]);
                if(var_numb<0){
                    break;
                } 
                entry.push_back(var_numb);
            }
            x = find_row(entry, parents);
            y = get_index_val(gn.get_values(),patient_list[i][ind]);
            cpt_values[x][y]+=1.0;
        }
        
    }


    for(int i=0; i<n; i++){
        cpt_values[i][m]=0.0;
        for (int j=0; j<m; j++)
            cpt_values[i][m] = cpt_values[i][m] + cpt_values[i][j];
    }

    vector<float> cpt_list;
    float sum0=0;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            float d=0.0;
            if(cpt_values[j][m]>0)
                d = (cpt_values[j][i])/(cpt_values[j][m]);
            if(d>0.999){
                d = d-0.01;    
            }
            if(d<0.001){
                d = d+0.01;
            }
            cpt_list.push_back(d);

        }

    }
 
    (*Alarm.get_nth_node(ind)).set_CPT(cpt_list);
}

void replace_unknowns(network Alarm, int ind, Graph_Node gn, vector<vector<string> > &patient_list, vector<unknowns> unknowns_list){
    visited.push_back(gn.get_name());
    vector<float> cpt_list = gn.get_CPT();
    vector<string> parent_str = gn.get_Parents();

    vector<Graph_Node> parents;
    vector<int> parent_index;

    int m = gn.get_nvalues();
    int n = 1;

    for(int i=0; i<parent_str.size(); i++){
        list<Graph_Node>::iterator temp = Alarm.search_node(parent_str[i]);
        parents.push_back(*temp);
        parent_index.push_back(Alarm.search_index((*temp).get_name()));
        n = n*((*temp).get_nvalues());
    }
    vector<int> entry;

    int start = 0;
    while(start<unknowns_list.size()){
        if(unknowns_list[start].colm==ind){
            break;
        }
        else start++;
    }
    if(start==unknowns_list.size())
        return;

    while(start<unknowns_list.size()){
        if(unknowns_list[start].colm!=ind)
            break;
        entry.clear();
        int row = unknowns_list[start].row;
        for(int j=0; j<parent_index.size(); j++){
            vector<string> values_list = parents[j].get_values();
            int var_numb = get_index_val(values_list,patient_list[row][parent_index[j]]);
            if(var_numb<0){
                break;
            } 
            entry.push_back(var_numb);
        }
        int x = find_row(entry, parents);
        float max=0.0;
        int maxIndex=0;
        // for(int i=0; i<gn.get_nvalues(); i++){
        //     if(prob[i]>max){
                // max = prob[i];
                // maxIndex = i;
        //     }
        // }
       
        string input_s="";
        for(int k=0; k<gn.get_values().size(); k++){
            if(cpt_list[(k*n)+x]>max){
                max = cpt_list[(k*n)+x];
                maxIndex = k;
            }
            // input_s = input_s + gn.get_values()[k] + " = " + to_string(cpt_list[(k*n)+x]) + " ";
        }
        patient_list[row][ind] = gn.get_values()[maxIndex];
        start++;
    }
    return;
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
            p.push_back(word);
        }
        
        patient_list.push_back(p);
    } 
    return patient_list;
}

string find_CPTmarkov(network Alarm, vector<string> patient_val, Graph_Node gn, vector<Graph_Node> parents, vector<int> parent_index){
    float prob[gn.get_nvalues()];
    float temp=1.0;

    vector<int> child_index = gn.get_children();
    vector<Graph_Node> children;

    for(int i=0; i<child_index.size(); i++){
        children.push_back(*(Alarm.get_nth_node(child_index[i])));
    }

    for(int k=0; k<gn.get_nvalues(); k++){
        float p = 1.0;
         
        for(int i=0; i<children.size(); i++){
            vector<int> entry;
            vector<string> mate_str = children[i].get_Parents();
            vector<Graph_Node> mate;
            vector<int> mate_index;
            int n=1;
            for(int i=0; i<mate_str.size(); i++){
                list<Graph_Node>::iterator temp = Alarm.search_node(mate_str[i]);
                mate.push_back(*temp);
                mate_index.push_back(Alarm.search_index((*temp).get_name()));
                n = n*((*temp).get_nvalues());
            }
               
            for(int j=0; j<mate_index.size(); j++){
                vector<string> values_list = mate[j].get_values();
                int var_numb = -1;
                if(mate[j].get_name().compare(gn.get_name())==0){
                    var_numb = get_index_val(values_list,gn.get_values()[k]);
                }
                else var_numb = get_index_val(values_list,patient_val[mate_index[j]]);
                if(var_numb<0){
                    break;
                } 
                entry.push_back(var_numb);
            }
            int x = find_row(entry, mate);
            int y = get_index_val(children[i].get_values(),patient_val[child_index[i]]);
            int index_found = x + (y*n);
            p = p * children[i].get_CPT()[index_found];
        }
        vector<int> entry;
        int rows=1;
        for(int j=0; j<parent_index.size(); j++){
            rows = rows*(parents[j].get_nvalues());
            vector<string> values_list = parents[j].get_values();
            int var_numb = get_index_val(values_list,patient_val[parent_index[j]]);
            if(var_numb<0){
                break;
            } 
            entry.push_back(var_numb);
        }
        int x = find_row(entry, parents);
        int y = k;
        int index_found = x + (y*rows);
        p = p * gn.get_CPT()[index_found];

        prob[k] = p;
    }
    float sum = 0.0;
    for(int i=0; i<gn.get_nvalues(); i++)
        sum = sum+prob[i];

    for(int i=0; i<gn.get_nvalues(); i++)
        prob[i] = prob[i]/sum;

    float max=0.0;
    int maxIndex=0;
    for(int i=0; i<gn.get_nvalues(); i++){
        if(prob[i]>max){
            max = prob[i];
            maxIndex = i;
        }
    }
        

    // string input_s = "";
    // for(int k=0; k<gn.get_values().size(); k++){
    //     input_s = input_s + gn.get_values()[k] + " = " + to_string(prob[k]) + " ";
    // }
    return gn.get_values()[maxIndex];
}

void update_unknowns(network Alarm, int ind, Graph_Node gn, vector<vector<string> > &patient_list, vector<unknowns> unknowns_list){

    vector<string> parent_str = gn.get_Parents();
    vector<Graph_Node> parents;
    vector<int> parent_index;

    int m = gn.get_nvalues();
    int n = 1;

    for(int i=0; i<parent_str.size(); i++){
        list<Graph_Node>::iterator temp = Alarm.search_node(parent_str[i]);
        parents.push_back(*temp);
        parent_index.push_back(Alarm.search_index((*temp).get_name()));
        n = n*((*temp).get_nvalues());
    }

    // WORK: Your code seems too complicated to understand lol. That encoding to get the corresponding variable CPT values. I got a way of doing this. I will tell you when we meet tomorrow

    int start = 0;
    while(start<unknowns_list.size()){
        if(unknowns_list[start].colm==ind){
            break;
        }
        else start++;
    }
    if(start==unknowns_list.size())
        return;

    while(start<unknowns_list.size()){
        if(unknowns_list[start].colm!=ind)
            break;
        int rows = unknowns_list[start].row;
        string input_s = find_CPTmarkov(Alarm, patient_list[rows], gn, parents, parent_index);
        patient_list[rows][ind] = input_s;
        start++;
    }
    return;
}

void initialise_randCPT(network &Alarm, int ind, vector<vector<string> > patient_list){
    Graph_Node gn = *(Alarm.get_nth_node(ind));
    int n = gn.get_nvalues();
    vector<float> cpt_list = gn.get_CPT();
    int m = cpt_list.size()/n;
    float sum[m];

    for(int i=0 ;i<m; i++)
        sum[i] = 0.0;

    int count=0;
    for(int i=0; i<cpt_list.size(); i++){
        // cpt_list[i] = (rand() / double(RAND_MAX))*(1-sum[i%m]);
        cpt_list[i] = 1/n;
        // if(i%m==0) count++;
        // sum[i%m]+=cpt_list[i];
    }
    (*Alarm.get_nth_node(ind)).set_CPT(cpt_list);
}



void traverseIndex(network& Alarm, int index, vector<vector<string>> &patient_list){

    // initialise_randCPT(Alarm,index,patient_list);
    find_cpt(Alarm,index,patient_list,true);

    Graph_Node gn = *(Alarm.get_nth_node(index));
    // replace_unknowns(Alarm, index, gn, patient_list, unknowns_list);
 

}

void traverse(network& Alarm, vector<int> roots, vector<vector<string>> &patient_list){

    vector<int> newChild;
    
    for (int i=0; i<roots.size() ; i++){
        traverseIndex(Alarm,roots[i],patient_list);
   
        vector<int> added = (*(Alarm.get_nth_node(roots[i]))).get_children();
        newChild.insert(newChild.end(),added.begin(), added.end());
    }

    if (newChild.size() == 0) return;

    vector<int> newRoot;
    int flag;
    for(int i=0; i<newChild.size(); i++){
        flag = 0;
        std::vector<string> v = (*(Alarm.get_nth_node(newChild[i]))).get_Parents();

        for(int j=0; j<v.size() ; j++){

            std::vector<string>::iterator it1; 
            it1 = std::find (visited.begin(), visited.end(), v[j]);

            if (it1==visited.end()){

                flag = 1;
                break;
            } 

        }

        if (flag==0){

                std::vector<int>::iterator it1; 
                it1 = std::find (newRoot.begin(), newRoot.end(), newChild[i]);

                if (it1 == newRoot.end()){
                    newRoot.push_back(newChild[i]);
                }

        }

    }

     traverse(Alarm,newRoot,patient_list);
    


}


void traverseIndex_EM(network Alarm, int index, vector<vector<string>> &patient_list){


    Graph_Node gn = *(Alarm.get_nth_node(index));
    update_unknowns(Alarm, index, gn, patient_list, unknowns_list);

}

void traverse_EM(network Alarm, vector<int> roots, vector<vector<string>> &patient_list){

    vector<int> newChild;

    for (int i=0; i<roots.size() ; i++){
        traverseIndex_EM(Alarm,roots[i],patient_list);
        vector<int> added = (*(Alarm.get_nth_node(roots[i]))).get_children();
        newChild.insert(newChild.end(),added.begin(), added.end());
    }

    std::unordered_set<int> set;
    std::copy(newChild.begin(),
            newChild.end(),
            std::inserter(set, set.end()));


    std::vector<int> newRoot;
    newRoot.assign(set.begin(), set.end());


    if (newRoot.size() ==0) return;
    else{
        traverse_EM(Alarm,newRoot,patient_list);
    }


}

void traverseIndex_EM1(network &Alarm, int index, vector<vector<string>> patient_list){

  find_cpt(Alarm,index,patient_list,false);

}


void traverse_EM1(network &Alarm, vector<int> roots, vector<vector<string>> patient_list){

    vector<int> newChild;

    for (int i=0; i<roots.size() ; i++){
        traverseIndex_EM1(Alarm,roots[i],patient_list);
        vector<int> added = (*(Alarm.get_nth_node(roots[i]))).get_children();
        newChild.insert(newChild.end(),added.begin(), added.end());
    }


    std::unordered_set<int> set;
    std::copy(newChild.begin(),
            newChild.end(),
            std::inserter(set, set.end()));


    std::vector<int> newRoot;
    newRoot.assign(set.begin(), set.end());

    if (newRoot.size() ==0) return;
    else{
   
        traverse_EM1(Alarm,newRoot,patient_list);
    }

}

void write_file(string file_read, string file_write, network Alarm){
    fstream file;
    string word = "";
    string line = "";
    file.open(file_read.c_str()); 
    vector<vector<string> > patient_list;
    ofstream myfile;
    myfile.open (file_write);
    string out_str="";
    int count=0;
    // extracting words from the file 
    while (getline(file,line)) 
    { 
        // displaying content
        vector<string> p;
        istringstream iss(line);

        iss>>word;
        if(word.compare("table")==0){
            Graph_Node g = *(Alarm.get_nth_node(count));
            vector<float> cpt_val = g.get_CPT();
            out_str = "table ";
            for(int i=0 ; i<cpt_val.size(); i++){
                out_str = out_str+to_string(cpt_val[i])+" ";
            }
            out_str = out_str+";";
            myfile<<(out_str +"\n");
            count++;
        }
        else
            myfile<<(line + "\n");

    } 
    myfile.close();
    return;
}


void write_file_pat(string file_write, vector<vector<string> > l){
    ofstream myfile;
    myfile.open (file_write);
    string out_str="";
    int count=0;
    // extracting words from the file 
    for(int i=0; i<l.size(); i++){
        for(int j=0 ;j<l[0].size(); j++){
            myfile<<l[i][j]<<" ";
        }
        myfile<<"\n";
    }
    myfile.close();
    return;
}


int main(int argc, char *argv[])
{
    clock_t startt,endt;
    startt=clock();
    srand (time(NULL));

     if(argc<3){//##Make .sh files
    cout<<"Argumnents Missing"<<endl;
    return 0;
  }
  /*---------Vars--------*///##Make Gobal if needed
  string ifilename = argv[1];
  string ofilename = argv[2];
 
    patient_list = read_file(ofilename);
    
    network Alarm;
    Alarm=read_network(ifilename);
    
    vector<int> roots;

    roots = get_roots(Alarm);
    traverse(Alarm,roots,patient_list);
    write_file(ifilename, "solved_alarm.bif", Alarm);

    vector<float> old_CPT_list;
    vector<float> new_CPT_list;

    old_CPT_list = Alarm.find_all_CPT();
    int count = 0;
    float diff = 10.0;

    while(true){
        
        old_CPT_list = Alarm.find_all_CPT();
        
        count++;

        endt = clock();
        if ((((endt - startt)/1000)/1000) >= ((2 * 60) -1)){
        
            break;
        } 

        traverse_EM(Alarm,roots,patient_list);

        traverse_EM1(Alarm,roots,patient_list);

        new_CPT_list = Alarm.find_all_CPT();

        write_file(ifilename, "solved_alarm.bif", Alarm);


    }
    
    return 0;
}
 
