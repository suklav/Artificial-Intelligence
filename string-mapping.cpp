
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <random>
#include <utility>
#include <iterator>
#include <ctime>




using namespace std;


#define nlc 10 // number of longer children
#define nsc 10 // number of shorter children
#define prob 200	// probability of accepting a bad Move == 1/1000
#define pmoves 20 //plateauMoves
#define TOLERANCE 10


double t;
clock_t startClock;
vector<string> bestSofar;
int buf = 15;

using namespace std;

class MatchingCost{
private:
    vector<vector<int> > cmatx; //cost matrix
    map<char,int> charMap;

public:
    int CC;
    //copy assignments
    void initialize(const vector<vector<int> > & a, const map<char,int>& b,int c);
    MatchingCost() {}
    MatchingCost& operator=(const MatchingCost& rhs);
    MatchingCost(const MatchingCost& rhs);
    /* given 2 chars a and b, gives the cost of matching them */
    int operator()(char a, char b) const;
    
    
};



void MatchingCost::initialize(const vector<vector<int> > & a, const map<char,int>& b, int x){ cmatx = a; charMap = b; CC = x;}

int MatchingCost::operator()(char a, char b) const
{
    int x = charMap.at(a), y = charMap.at(b);
    return cmatx[y][x];
}

MatchingCost::MatchingCost(const MatchingCost& rhs)
{
    cmatx = rhs.cmatx;
    charMap = rhs.charMap;
}

MatchingCost& MatchingCost::operator=(const MatchingCost& rhs)
{
    if (this == &rhs)
        return *this;
    cmatx = rhs.cmatx;
    charMap = rhs.charMap;
    return *this;
}

MatchingCost m;

int colCost(const vector<string>& s, int row,int col, char currChar)
{
    vector<string> b = s;
    b[row][col] = currChar;
    int cost = 0;
    for (int i = 0; i < b.size(); i++){
        if (b[i][col] == '-') cost += m.CC;
        for (int j = i+1; j < b.size(); j++){
            cost += m(b[i][col], b[j][col]);
        }
    }
    return cost;
}

int cost(const vector<string>& s) {
    int cost = 0;
    for (int i =0; i < s[0].length(); i++)
        cost+= colCost(s,0, i, s[0][i]);
    return cost;
}

bool operator<(const vector<string>& a, const vector<string>& b)
{
    return cost(a) < cost(b);
}

bool operator>(const vector<string>& a, const vector<string>& b)
{
    return cost(a) > cost(b);
}

class Move{  
public:
    int row; // the row
    pair<int,int> deltaColumn; // Move from column first to column second
    int MoveCost;
    Move(int r, int c1,int c2, int m): row(r){
        deltaColumn = make_pair(c1,c2);
        MoveCost = m;
    }
    Move() {MoveCost = 1<<16;}
    void setCost(int c) { MoveCost = c;}
    
    bool operator<(const Move& rhs) const
    {
        return MoveCost < rhs.MoveCost;
    }
    bool operator==(const Move& rhs) const
    {
        return row == rhs.row && MoveCost == rhs.MoveCost && deltaColumn == rhs.deltaColumn;
    }
};

void debug(multiset<Move>& dashMoves, const vector<string>& curr){
    typedef multiset<Move>::iterator itr;
    
    cout << "********************************************" << '\n';
    for (itr it = dashMoves.begin(); it != dashMoves.end(); it++)
        cout << curr[it->row][it->deltaColumn.first] << " " << curr[it->row][it->deltaColumn.second] << '\n';
    cout << "*********************************************" << '\n';
};

bool sameSize(const vector<string>& a)
{
    
    for (int i = 0; i < (int)a.size(); i++)
    {
        if (a[i].length() != a[0].length()) 
          return false;
    }
    return true;
}

void removeDash(vector<string>& a, int column)
{
    for (int i = 0; i < a.size(); i++)
        a[i].erase(column, 1);
    
}
void eliminateDashes(vector<string>& a)
{
    for (int i = 0; i < a[0].size(); i++)
    {
        for (int j = 0; j  < a.size(); j++)
        {if (a[j][i] != '-') break; if (j == a.size() -1) removeDash(a, i);}
        
    }
    
    
}

int deltaChange(const vector<string>& s, int i, int j, int k)
{
    assert(s[i][j] == '-');
    assert (s[i][k] != '-');
    int mI = colCost(s,i,j,'-'),lI = colCost(s,i,k, s[i][k]), mF = colCost(s,i,j,s[i][k]), lF = colCost(s,i,k,'-');
    int delta = (mF + lF) - (mI + lI);
    return delta;
}

void makeMove(vector<string>& s, const Move& m)
{
    int row = m.row;
    int initCol = m.deltaColumn.first;
    int finalCol = m.deltaColumn.second;
    assert (s[row][initCol] == '-');
    assert (s[row][finalCol] != '-');
    char temp = s[row][finalCol];
    s[row][finalCol] = '-';
    s[row][initCol] = temp;
}

void print(const vector<string>& s, ofstream& f)
{
    for (int i = 0; i < (int)s.size(); i++)
        f << s[i] << endl;
}

void update(vector<vector<int> >& v, const Move& m)
{
    int row = m.row;
    v[row].erase(remove(v[row].begin(), v[row].end(), m.deltaColumn.first), v[row].end());
    v[row].push_back(m.deltaColumn.second);

}

vector<string> input(ifstream& f)
{
    int vocab;
    f >> t;   
    f >> vocab;    
    string s;
    f.ignore();
    getline(f,s);
    stringstream inp(s);
    map<char,int> charMap;
    int i = 0;
    char letter;
    while (inp >> letter)
    {
        
        charMap[letter] = i;
        i++;
        if (inp.peek() == ' ' || inp.peek() == ',')
            inp.ignore();
        
        
    }
    
    charMap['-'] = i;
    int k;
    f >> k;
    vector<string> sequences;
    sequences.reserve(k);
    for (int i = 0; i < k; i++)
    {
        f >> s;
        
        sequences.push_back(s);
    }
    
    
   	int CC;
    f >> CC;

    int tempInt;
    vector<int> temp;
    vector<vector<int> > cmatx;
    for (int i = 0; i < vocab +1; i++)
    {
        
        temp.clear();
        for (int j = 0; j < vocab; j++)
        {
            f >> tempInt;
            
            temp.push_back(tempInt);
        }
        f >> tempInt;
        
        temp.push_back(tempInt);
        cmatx.push_back(temp);
        
    }
    char hash;
    f >> hash;
    m.initialize(cmatx,charMap, CC);
    
    
    return sequences;
}

void addNewMoves(multiset<Move>& currentMoves, const vector<pair<int,int> >& dashesAffected, vector<string>& s)
{
    if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - 10))
            {
                cout<<"TIME3\n";
                return;
            }

    for (int i = 0; i < dashesAffected.size(); i++)
    {
        int row = dashesAffected[i].first, col = dashesAffected[i].second;
        assert (s[row][col] == '-');
        bool transition = false;
        int l = col +1;
        if (l < s[row].size() && s[row][l] != '-') transition = true;
        if (transition)
        {
            assert (s[row][l] != '-');
            int cost = deltaChange(s, row, col, l);
            Move rightMove(row, col,l, cost);

            currentMoves.insert(rightMove);
        }
        
        if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - 10))
            {
                cout<<"TIME3\n";
                return;
            }
        transition = false;
        l = col -1;
        if (l >= 0 && s[row][l] != '-') transition = true;
        if (transition)
            
        {
            
            assert (s[row][l] != '-');
            int cost = deltaChange(s,row, col,l);
            Move leftMove(row, col, l, cost);
            currentMoves.insert(leftMove);
        }
    }
    
    
}

void deletePreviousMoves(multiset<Move>& currentMoves, const vector<pair<int,int> >& d,const vector<string>& s,const Move& m)
{
    vector<pair<int,int> > dashesAffected = d;
    
    dashesAffected.push_back(make_pair(m.row, m.deltaColumn.first));

    currentMoves.erase(currentMoves.begin());
    
    typedef multiset<Move>::iterator itr;
    for (int i = 0; i < dashesAffected.size(); i++)
    {
        int row = dashesAffected[i].first, col = dashesAffected[i].second;
        assert (s[row][col] == '-');
        bool transition = false;
        int l = col +1;
      
        if (l < s[row].length() && s[row][l] != '-') transition = true;
     
        if (transition)
        {
            assert(s[row][l] != '-' );
            int cost = deltaChange(s,row,col, l);
            Move delMove(row, col, l,cost);
            pair<itr,itr> ret = currentMoves.equal_range(delMove);
            itr it = find(ret.first, ret.second, delMove);
            if (it != ret.second)
                currentMoves.erase(it);
            
            
        }
        
        transition = false;
        l = col -1;
       
        
        if (l >= 0 && s[row][l] != '-') transition = true;
        
        if (transition)
        {
            
            
            assert(s[row][l] != '-');
            int cost = deltaChange(s,row,col, l);
            Move delMove(row, col, l,cost);
            pair<itr,itr> ret = currentMoves.equal_range(delMove);
           
            itr it = find(ret.first, ret.second, delMove);
            if (it != ret.second)
                currentMoves.erase(it);
            
            
            
        }
    }
}

void neighbor(const vector<string>& s, vector<vector<int> > & dashCoordinates, multiset<Move>& dashMoves)
{
    int l = (int)s.size();
    
    for (int i = 0; i < l; ++i)
    {
        for (int j = 0; j < (int)dashCoordinates[i].size(); j++)
        {
            bool transition = false;
            assert (s[i][dashCoordinates[i][j]] == '-');
            int k = dashCoordinates[i][j] +1;
            
            if (k < s[0].size() && s[i][k] != '-')  transition = true;
            if (transition)
            {
                assert (s[i][k] != '-');
                int cost = deltaChange(s,(int)i,dashCoordinates[i][j], k);
                Move rightMove((int)i,dashCoordinates[i][j], k, cost);
                dashMoves.insert(rightMove);
            }
            
            if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - 10))
            {
                //cout<<"TIME3\n";
                return;
            }

            transition = false;
            k = dashCoordinates[i][j] -1;
           
            if (k >= 0 && s[i][k] != '-') transition = true;
            
            if (transition)
            {
                assert (s[i][k] != '-');
                int cost = deltaChange(s,(int)i,dashCoordinates[i][j], k);
                Move leftMove((int)i, dashCoordinates[i][j], k, cost);
                dashMoves.insert(leftMove);
            }
            
            
        }
    }
        
}

void updateCosts(const vector<string>& s, const Move& bestMove,const  vector<vector<int> >& dashCoordinates, multiset<Move>& currentMoves)
{
    
    int ro = bestMove.row;
  
    int initColumn = bestMove.deltaColumn.first;
    int finalColumn = bestMove.deltaColumn.second;
   
    assert (s[ro][initColumn] == '-' && s[ro][finalColumn] != '-');

    vector<pair<int,int> > dashesAffected;
    for (int r = 0; r < dashCoordinates.size(); r++)
        for (int i = 0; i < dashCoordinates[r].size(); i++)
            if (dashCoordinates[r][i] == initColumn - 1 || dashCoordinates[r][i] == initColumn + 1 || dashCoordinates[r][i] == finalColumn + 1 || dashCoordinates[r][i] == finalColumn - 1)
            {
                assert (s[r][dashCoordinates[r][i]] == '-');
                if (r == ro && dashCoordinates[r][i] == initColumn) continue;
                dashesAffected.push_back(make_pair(r, dashCoordinates[r][i]));
            }
    
    deletePreviousMoves(currentMoves, dashesAffected, s, bestMove);
 
    vector<string> a = s;

    makeMove(a, bestMove);
    dashesAffected.push_back(make_pair(ro, finalColumn));
    addNewMoves(currentMoves, dashesAffected, a);
    
}

vector<string> initialize(const vector<string>& s)
{
    vector<string> temp = s;
    int maxLength = 0;
    for (int i = 0; i < (int)temp.size(); i++)
        maxLength = max(maxLength, (int)temp[i].length());
    
    double lengthMod = ((double)rand() / (double)RAND_MAX);
    for (int i = 0; i < (int)temp.size(); i++)
    {
        int numDashes = ((1+lengthMod)*maxLength) - temp[i].length();
        for (int j = 0; j < numDashes; j++)
            temp[i].insert((rand() % (int)temp[i].length()), "-");
    }
 
    return temp;
    
}

vector<string> perturbSingleExchange(const vector<string>& s, int len)
{
    int a, j, n;
    vector<string> t = s;
    string temp, subseq;
    do{
        a = rand() % ((int)t[0].length() - len);
        j = rand() % (int)t.size();
        subseq = t[j].substr(a, len);
        temp.clear();
        // int k = 0;
        n = 0;
        for (int i = 0; i < (int)subseq.length(); i++)
        {
            if (subseq[i] == '-')
                n++;
            else
                temp.append(subseq, i, 1);
        }
    } while (n == 0 || temp == subseq);
    for (int i = 0; i < n; i++)
        temp.insert(rand() % (int)temp.length(), "-");
    
    t[j].replace(a, len, temp);
    return t;
}
vector<string> generateLargerChild(const vector<string> & b)
{
    vector<string> s = b;
    int a  = (int)s[0].length();
    for (int i = 0; i < s.size(); i++){
        int r = rand()%(a);
        s[i].insert(r,"-");
        
    }
    
    assert (sameSize(s));
    return s;
}

vector<string> generateSmallerChild(const vector<string>& b,const  vector<vector<int> >& dashCoordinates)
{
    
    int r;
    vector<string> s = b;    
      for (int i = 0; i < dashCoordinates.size(); i++)
      {
        int b = (int)dashCoordinates[i].size();
        r = dashCoordinates[i][rand() % b];
        s[i].erase(r,1);
      }
    return s;
}

vector<string> perturbBlockExchange2(vector<string>& s)
{
   
    int ind;
    vector<string> temp = s;
    vector<size_t> pos;
    
    size_t randind, a, b;
    
    do{
        ind = rand() % temp.size();
        size_t idx = 0;
        while (idx != string::npos && idx <temp[ind].length())
        {
            size_t first = temp[ind].find_first_of("-", idx);
            if (first == string::npos)
                break;
            pos.push_back(first);
            idx = temp[ind].find_first_not_of("-", first);
        }
        if(pos.empty()) continue;

    randind = pos.at(rand() % pos.size());
    a = randind;
    b = temp[ind].find_first_not_of("-", a);
    }while((b-a) == 1);
    
    if (b == string::npos)
        b = temp[ind].length();
    
    size_t randomPos = rand() % (temp[ind].length() - b + a);
    string sub = temp[ind].substr(a, b - a);
    temp[ind].erase(a, b - a);
    temp[ind].insert(randomPos, sub);
    
    
    return temp;
}

vector<string> perturbBlockExchange(vector<string>& s, int maxSize)
{
    int ind;
    vector<string> temp = s;
    vector<size_t> pos;

    if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - 10))
            {
                //cout<<"TIME13\n";
                return temp;
            }
    
    typedef vector<string> state;
    
    
    vector<state> newChildren;
    for (int i = 0; i < nlc; i++)
        newChildren.push_back(generateLargerChild(s));

    if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - 10))
            {
                //cout<<"TIME3\n";
                return temp;
            }
    
    vector<vector<int> > dashCoords(s.size(), vector<int>());
    for (int i = 0; i < s.size(); i++)
    {
        for (int j = 0; j < s[0].size(); j++)
            if (s[i][j] == '-') dashCoords[i].push_back(j);
    }
    
    if (s[0].size() > maxSize)
    {  for (int i = 0; i < nsc; i++)
        newChildren.push_back(generateSmallerChild(s, dashCoords));
    }
    
    do{
        ind = rand() % temp.size();
        
        size_t idx = 0;
        while (idx != string::npos && idx <temp[ind].length())
        {
            size_t first = temp[ind].find_first_of("-", idx);
            if (first == string::npos)
                break;
            pos.push_back(first);
            idx = temp[ind].find_first_not_of("-", first);
        }
    } while (pos.empty());
    
    size_t randind = pos.at(rand() % pos.size());
    
    size_t a = randind;
    size_t b = temp[ind].find_first_not_of("-", a);
    if (b == string::npos)
        b = temp[ind].length();
    
    size_t randomPos = rand() % (temp[ind].length() - b + a);
    string sub = temp[ind].substr(a, b - a);
    temp[ind].erase(a, b - a);
    temp[ind].insert(randomPos, sub);
    assert (sameSize(temp));

    if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - buf))
            {
                return bestSofar;
            }

    transform(newChildren.begin(), newChildren.end(), newChildren.begin(),perturbBlockExchange2);
    newChildren.push_back(temp);
    int min = -1;
    for (int i = 0; i < newChildren.size(); i++)
        if (min < 0 || newChildren[min] > newChildren[i])
            min = i;

    return newChildren[min];
}


vector<string> initializeToLength(const vector<string>& s, int length)
{
    vector<string> temp = s;
    for (int i = 0; i < (int)temp.size(); i++)
    {
        int numDashes = (length - (int)temp[i].length());
        for (int j = 0; j < numDashes; j++)
            temp[i].insert((rand() % (int)temp[i].length()), "-");
    }
    return temp;
}

vector<string> hillClimbingRecur(vector<string>& s,vector<string>& st,int pM)
{
    typedef vector<vector<int> > vvi;
    typedef vector<string> state;
    typedef multiset<Move> mm;
    mm dashMoves;
    state curr = st;
    int t = pM;
    if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - buf))
        return curr;
    Move bestMove;
    vector<vector<int> > dashCoordinates(st.size(), vector<int>());
    for (int i = 0; i < st.size(); i++)
    {
        if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - buf))
            return curr;

        for (int j = 0; j < st[0].length(); j++)
            if (st[i][j] == '-') dashCoordinates[i].push_back(j);
    }
    neighbor(curr, dashCoordinates, dashMoves);
    while (!dashMoves.empty()){
        bestMove = *dashMoves.begin();
        if (bestMove.MoveCost == 0){
            if (t == 0) return curr;
            t--;
          }
        
        if (bestMove.MoveCost > 0){
            int a = rand()% prob;
            if (a) return curr;
        }
 
        updateCosts(curr, bestMove, dashCoordinates, dashMoves);
        if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - buf))
         return curr;
        
        makeMove(curr, bestMove);
        if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - buf))
         return curr;
        
        update(dashCoordinates, bestMove);
        if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - buf))
         return curr;
        
    }
    
    return curr;
    
}
vector<string> hillClimbing(vector<string>& s,vector<string>& start, int iterations, int pM = pmoves)
{
    typedef vector<string> state;
    bestSofar = start;
    state randomStart = start;

    if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - buf))
            {
                
                return bestSofar;
            }

    int maxSize = -1;

    for (int i = 0; i < (int)start.size(); i++)
        maxSize = max(maxSize, (int)start[i].length());
    
    int numIterations = 0;
    for (int i = 0; i < iterations; ++i)
    {
        state localMinima = hillClimbingRecur(s,randomStart, pM);
        
        eliminateDashes(localMinima);
        if (localMinima < bestSofar)
        {bestSofar = localMinima; numIterations = 0;}
        if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - buf))
            {
                return bestSofar;
            }
        
        if (cost(localMinima) == cost(bestSofar))
            numIterations++;
        
        if (numIterations == TOLERANCE)
        {
            randomStart = initializeToLength(s,(int)localMinima[0].length());
            if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - buf))
            {
                
                return bestSofar;
            }
        }
        else
        {
            randomStart = perturbBlockExchange(localMinima, maxSize);
        }
        
        int ct = cost(bestSofar);
        if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - buf))
            {
                
                return bestSofar;
            }
        
    }
    
    return bestSofar;
}

int main(int argc, const char * argv[]) 
{
    startClock = clock();
    
    ifstream f;
    f.open(argv[1]);
    if (f.fail())
    {
        cout << "File not found " << '\n';
        return 0;
    }
    ofstream o;
    o.open(argv[2]);
    vector<string> s = input(f);
    srand((int)time(NULL));

    if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - buf))
        return 0;
    vector<string> T = initialize(s);
    if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - buf))
        return 0;

    vector<string> solution = hillClimbing(s,T,10000);
    print(solution, o);
    if((clock() - startClock)/(double)CLOCKS_PER_SEC >= (t*60 - buf))
    {
        return 0;
    }
    
    return 0;
}
