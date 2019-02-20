#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

vector<vector<char>> makePuzzle() {
    int ncols, nrows(0);
    ifstream import;
    import.open("C:\\Users\\Keoni\\Documents\\Computer Science\\cs61\\CS61_HW7\\puzzle.txt");

    if(import.fail()) {
        cout << "File open fail." << endl;
        exit(1);
    }

    string line;
    getline(import, line);

    ncols = line.size();
    ++nrows;
    while(getline(import,line)) ++nrows;

    import.close();
    vector<vector<char>> v(nrows, vector<char>(ncols/(2*line.length())));
    return v;

}

void fillPuzzle(vector<vector<char>> & v) {
    ifstream import;
    import.open("C:\\Users\\Keoni\\Documents\\Computer Science\\cs61\\CS61_HW7\\puzzle.txt");

    if(import.fail()) {
        cout << "File open fail." << endl;
        exit(1);
    }

    string line;
    int col = 0;

    while(getline(import,line)){
        for(int i = 0; i < line.length(); ++i) {
            if(line[i] >= 'a' && line[i] <= 'z') {
                v[col].push_back(line[i]);
            }
        }
        ++col;
    }
    import.close();
}

void loadDic(set<string> & d) {
    ifstream import;
    import.open("C:\\Users\\Keoni\\Documents\\Computer Science\\cs61\\CS61_HW7\\words.txt");

    if(import.fail()) {
        cout << "File open fail." << endl;
        exit(1);
    }
    string w;
    while(import>>w) d.insert(w);
    import.close();
}

void checkW(map<string,map<pair<int,int>,pair<int,int>>> & output, string word, set<string> const & dictionary, map<pair<int,int>,pair<int,int>> const & xy)
{
   if(word.length()>=6 && dictionary.find(word) != dictionary.end()) output[word]=xy;
   reverse(word.begin(),word.end());
   if(word.length()>=6 && dictionary.find(word)!= dictionary.end()) output[word]=xy;
}


map<string,map<pair<int,int>,pair<int,int>>> makeList(const vector<vector<char>> & puzzle, const set<string> & dictionary) {
    string word;
    map<string,map<pair<int,int>,pair<int,int>>> output;
    map<pair<int,int>,pair<int,int>> xy;
    for(unsigned i = 0; i < puzzle.size(); ++i){
        for(unsigned j = 0; j < puzzle[i].size(); ++j) {
            for(unsigned k = 0; k < puzzle[i].size()-j; ++k){
                    word+=puzzle[i][j+k];
                    xy[make_pair(i,j+k)] = make_pair(i,j);
                    checkW(output, word, dictionary, xy);
                    xy.clear();
                }
            word.clear();;
            for(unsigned k = 0; k < puzzle.size()-i; ++k) {
                word+=puzzle[i+k][j];
                xy[make_pair(i+k,j)] = make_pair(i,j);
                checkW(output, word, dictionary, xy);
                xy.clear();
            }
            word.clear();
            for(unsigned k = 0; k < puzzle[i].size()-j && k < puzzle.size()-i; ++k) {
                word+=puzzle[i+k][j+k];
                xy[make_pair(i+k,j+k)] = make_pair(i,j);
                checkW(output, word, dictionary, xy);
                xy.clear();
            }
            word.clear();
            for(unsigned k = 0; k+i > -1 && k+j >-1; --k) {
                word+=puzzle[i+k][j+k];
                xy[make_pair(i+k,j+k)] = make_pair(i,j);
                checkW(output, word, dictionary, xy);
                xy.clear();
            }
            word.clear();
        }


    }
    sort(output.begin(),output.end());
    return output;
}



int main()
{
    set<string> dictionary;
    loadDic(dictionary);
   vector<vector<char>>v = makePuzzle();
    fillPuzzle(v);

    map<string,map<pair<int,int>,pair<int,int>>> outputset = makeList(v,dictionary);

    for(auto e:outputset)
    {
        cout<<e.first<<" occurs from ";
        for(auto x:e.second)
        {
            cout << "(" << x.first.first << "," << x.first.second << ") to (" << x.second.first << "," << x.second.second << ")";
        }
        cout<<endl;
    }
}
