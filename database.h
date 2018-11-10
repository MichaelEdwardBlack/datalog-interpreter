#include <map>
#include <sstream>
#include "relation.h"
#include "parser.h"

using namespace std;

class Database {
public:
  Database();
  void doSchemes(vector<Predicate> schemes);
  void doFacts(vector<Predicate> facts);
  void doQueries(vector<Predicate> queries);
  bool match(string parameter);
  string printQueryResults();
  string printTables(); //for testing purposes
private:
  map<string, Relation> tables;
  vector<Relation> queryResults;
  vector<Predicate> queries;
  vector<string> parameterCheck;
  int matchIndex;
};
