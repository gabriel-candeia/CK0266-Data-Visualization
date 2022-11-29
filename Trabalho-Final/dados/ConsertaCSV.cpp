#include<bits/stdc++.h>
using namespace std;

string trim(string s){
    while(s.size() && s.back()==' '){
        s.pop_back();
    }
    reverse(s.begin(),s.end());
    while(s.size() && s.back()==' '){
        s.pop_back();
    }
    reverse(s.begin(),s.end());
    return s;
}

string parseInt(const string& x){
    string answ;
    for(auto c:x)
        if(c>='0' && c<='9')
            answ.push_back(c);
    return answ;
}

vector<string> split(string s){
    vector<string> answ = {""};
    bool block = false;
    for(auto c:s){
        if(c=='"'){
            block = !block;
            answ.back().push_back(c);
        }
        else{
            if(!block && c==','){
                answ.push_back("");
            }
            else{
                answ.back().push_back(c);
            }
        }
    }
    for(auto &s:answ){
        s = trim(s);
    }
    return answ;
}

void write(ofstream& out, vector<string> s){
    bool ok = true;
    for(auto c:s){
        if(!ok)out << ",";
        out << c;
        ok = false;
    }
    out <<"\n";
}

void fixSexDestination(string filename, string output){
    ifstream in(filename);
    ofstream out(output);
    vector<string> Sex = {"Both","Male","Female"};
    string line;
    int index = 0;

    getline(in,line);
    write(out,{"Index","Year","Location","Location Code","Sex","Age","Value"});
    
    while(getline(in,line)){
        auto s = split(line);
        int ptr = 6;
        for(auto sex:Sex){
            for(int age=0;age<=75;age+=5,ptr++){
                string lb = to_string(age);
                string ub = ((age==75) ? "" : to_string(age+4));
                write(out,{to_string(++index),s[1],s[2],parseInt(s[4]),sex,lb,parseInt(s[ptr])});
            }
            ptr++;
        }
    }
}

int main(){
    fixSexDestination("migratory-flows-sex-destination-brute.csv","migratory-flows-sex-destination-processed.csv");
    return 0;
}