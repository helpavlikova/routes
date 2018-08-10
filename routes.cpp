#ifndef __PROGTEST__
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <list>
#include <algorithm>

#if defined ( __cplusplus ) && __cplusplus > 199711L	/* C++ 11 */
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#endif /* C++ 11 */

using namespace std;
#endif /* __PROGTEST__ */

class NoRouteException
{
};

template < typename _T, typename _E > 
class CRoute {
public:
  // default constructor
    CRoute(){};
  // destructor meh
  // Add 
    CRoute& Add(_T node1, _T node2, _E route);
  // Find (with optional filter)
 list < _T > Find(const _T & start, const _T& goal);
 list < _T > Find(const _T & start, const _T& goal, const function<bool(const _E & )> func);
    void Print() const;
    
private:
    map <_T, list<pair<_T,_E> > > routeMap;
};


template < typename _T, typename _E > 
CRoute< _T, _E>& CRoute< _T, _E>::Add(_T node1, _T node2, _E route){
    
    list<pair<_T,_E> >tmp, tmp1;
    
    
    if(routeMap.find(node1) == routeMap.end())
        routeMap.insert({node1, tmp});
    if(routeMap.find(node2) == routeMap.end())
        routeMap.insert({node2, tmp1});
    
    routeMap.at(node1).push_back({node2, route});
    routeMap.at(node2).push_back({node1, route});
    
    return *this;
}

template < typename _T, typename _E > 
list < _T > CRoute< _T, _E>::Find(const _T & start, const _T& goal, const function<bool(const _E & )> func){
    //cout << "Finding " << start << "-" << goal << endl;
    
    pair<_T,int> first = {start, -1};
    if(start == goal){
        list<_T> single;
        single.push_back(start);
        return single;
    
    }
    if(routeMap.find(start) == routeMap.end())
            throw NoRouteException();
    
    queue<pair<_T,int> > stopsQueue;
    set<_T> visited;
    stopsQueue.push(first);
    visited.insert(start);
    vector<pair<_T,int> > parents;
    parents.push_back(first);
    int ind = -1;
    
    while(! stopsQueue.empty()){
        pair<_T,int> previous = stopsQueue.front();
        stopsQueue.pop();
        ind++;
        
        for(auto i: routeMap.at(previous.first) ){
            if(visited.find(i.first) == visited.end() && func(i.second)){
                pair<_T,int> current = {i.first, ind};
                visited.insert(i.first);
                //cout << "adding " << i.first << " " << endl;
               
                stopsQueue.push(current);
                parents.push_back(current);
                
            if(current.first == goal){
                list<_T> result;
                result.push_front(current.first);
                int k = current.second;

                while(k >= 0){
                    result.push_front( parents[k].first );
                    k = parents[k].second;
                    //cout << k << endl;
                }
                return result;       
            }
            }
        }
        
    }
    throw NoRouteException();
}

template < typename _T, typename _E > 
list < _T > CRoute< _T, _E>::Find(const _T & start, const _T& goal){
    //cout << "Finding " << start << "-" << goal << endl;
    
    pair<_T,int> first = {start, -1};
    if(start == goal){
        list<_T> single;
        single.push_back(start);
        return single;
    
    }
    if(routeMap.find(start) == routeMap.end())
            throw NoRouteException();
    
    queue<pair<_T,int> > stopsQueue;
    set<_T> visited;
    stopsQueue.push(first);
    visited.insert(start);
    vector<pair<_T,int> > parents;
    parents.push_back(first);
    int ind = -1;
    
    while(! stopsQueue.empty()){
        pair<_T,int> previous = stopsQueue.front();
        stopsQueue.pop();
        ind++;
        
        for(auto i: routeMap.at(previous.first) ){
            if(visited.find(i.first) == visited.end() ){
                pair<_T,int> current = {i.first, ind};
                visited.insert(i.first);
                //cout << "adding " << i.first << " " << endl;
               
                stopsQueue.push(current);
                parents.push_back(current);
                
            if(current.first == goal){
                list<_T> result;
                result.push_front(current.first);
                int k = current.second;

                while(k >= 0){
                    result.push_front( parents[k].first );
                    k = parents[k].second;
                    //cout << k << endl;
                }
                return result;       
            }
            }
        }
        
    }
    throw NoRouteException();
}

template < typename _T, typename _E > 
void CRoute< _T, _E>::Print() const{
    cout << "------Map-------" << endl;
    
    for(auto elem : routeMap) {
    cout << elem.first << ": "; 
        for(auto it : elem.second){
            cout << it.first << "(" << it.second << ")" << " | ";
        }
    cout << endl;
  }
    cout << "-----------" << endl;
}

#ifndef __PROGTEST__
//=================================================================================================
class CTrain {
public:
  CTrain (const string & company,
	  int speed):m_Company (company), m_Speed (speed)
  {
  }
  //friend ostream& operator<<(ostream&, const CTrain&); //for debugging
  //---------------------------------------------------------------------------------------------
  string m_Company;
  int m_Speed;
};
ostream& operator<<(ostream& os, const CTrain& train){
    os << train.m_Company << ", " << train.m_Speed;
    return os;
}

//=================================================================================================
class TrainFilterCompany{
public:
  TrainFilterCompany (const set < string > &companies):m_Companies (companies)
  {
  }
  //---------------------------------------------------------------------------------------------
  bool operator  () (const CTrain & train) const
  {
    return m_Companies.find (train.m_Company) != m_Companies.end ();
  }
  //---------------------------------------------------------------------------------------------
private:
    set < string > m_Companies;
};

//=================================================================================================
class TrainFilterSpeed{
public:
  TrainFilterSpeed (int min, int max):m_Min (min), m_Max (max)
  {
  }
  //---------------------------------------------------------------------------------------------
  bool operator  () (const CTrain & train) const
  {
    return train.m_Speed >= m_Min && train.m_Speed <= m_Max;
  }
  //---------------------------------------------------------------------------------------------
private:
  int m_Min;
  int m_Max;
};

//=================================================================================================
bool NurSchnellzug (const CTrain & zug){
  return (zug.m_Company == "OBB" || zug.m_Company == "DB")
    && zug.m_Speed > 100;
}

//=================================================================================================
static string toText (const list < string > &l){
  ostringstream oss;

  auto it = l.cbegin ();
  oss << *it;
  for (++it; it != l.cend (); ++it)
    oss << " > " << *it;
  return oss.str ();
}

//=================================================================================================
int
main (void)
{
  CRoute < string, CTrain > lines;

  lines.Add ("Berlin", "Prague", CTrain ("DB", 120)).
        Add ("Berlin", "Prague",CTrain ("CD", 80)).
        Add ("Berlin", "Dresden", CTrain ("DB", 160)).
        Add ("Dresden", "Munchen", CTrain ("DB",160)).
        Add ("Munchen", "Prague", CTrain ("CD", 90)).
        Add ("Munchen", "Linz",CTrain ("DB",200)).
        Add ("Munchen", "Linz", CTrain ("OBB", 90)).
        Add ("Linz", "Prague",CTrain ("CD",50)).
        Add ("Prague", "Wien", CTrain ("CD", 100)).
        Add ("Linz", "Wien", CTrain ("OBB",160)).
        Add ("Paris", "Marseille", CTrain ("SNCF", 300)).
        Add ("Paris", "Dresden", CTrain ("SNCF", 250));
  
  lines.Print();

  list < string > r1 = lines.Find ("Berlin", "Linz");
  assert (toText (r1) == "Berlin > Prague > Linz");
  cout << "r1 nalezeno" << endl;

  list < string > r2 = lines.Find ("Linz", "Berlin");
  assert (toText (r2) == "Linz > Prague > Berlin");
  cout << "r2 nalezeno" << endl;

  list < string > r3 = lines.Find ("Wien", "Berlin");
  assert (toText (r3) == "Wien > Prague > Berlin");
  cout << "r3 nalezeno" << endl;

  list < string > r4 = lines.Find ("Wien", "Berlin", NurSchnellzug);
  assert (toText (r4) == "Wien > Linz > Munchen > Dresden > Berlin");
  cout << "r4 nalezeno" << endl;

  list < string > r5 = lines.Find ("Wien", "Munchen", TrainFilterCompany (set < string >{"CD", "DB"}));
  assert (toText (r5) == "Wien > Prague > Munchen");
  cout << "r5 nalezeno" << endl;

  list < string > r6 = lines.Find ("Wien", "Munchen", TrainFilterSpeed (120, 200));
  assert (toText (r6) == "Wien > Linz > Munchen");

  list < string > r7 = lines.Find ("Wien", "Munchen",[](const CTrain & x)
				   {
				   return x.m_Company == "CD";
				   }
  );
  assert (toText (r7) == "Wien > Prague > Munchen");

  list < string > r8 = lines.Find ("Munchen", "Munchen");
  assert (toText (r8) == "Munchen");

  list < string > r9 = lines.Find ("Marseille", "Prague");
  assert (toText (r9) == "Marseille > Paris > Dresden > Berlin > Prague"
	  || toText (r9) == "Marseille > Paris > Dresden > Munchen > Prague");

  try {
    list < string > r10 = lines.Find ("Marseille", "Prague", NurSchnellzug);
    assert ("Marseille > Prague connection does not exist!!" == NULL);
  }
  catch (const NoRouteException & e)
  {
  }

  list < string > r11 = lines.Find ("Salzburg", "Salzburg");
  assert (toText (r11) == "Salzburg");

  list < string > r12 =
    lines.Find ("Salzburg", "Salzburg",[](const CTrain & x)
		{
		return x.m_Company == "SNCF";
		}
  );
  assert (toText (r12) == "Salzburg");

  try{
    list < string > r13 = lines.Find ("London", "Oxford");
    assert ("London > Oxford connection does not exist!!" == NULL);
  } catch (const NoRouteException & e)
  {
  }

 
  return 0;
}
#endif /* __PROGTEST__ */
