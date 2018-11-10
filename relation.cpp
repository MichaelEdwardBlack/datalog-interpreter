#include "relation.h"

Relation::Relation() { numRows = 0; name = ""; }

void Relation::addColumns(Schema s) {
  columns = s;
}

void Relation::addRow(Tuple t) {
  rows.insert(t);
  numRows++;
}

void Relation::addRows(set<Tuple> tupleSet) {
  rows = tupleSet;
  numRows = tupleSet.size();
}

Relation Relation::selectColumnValue(int columnPosition, string value) {
  Relation newTable;
  Schema newHeader = this->columns;
  newTable.setName(this->name);
  newTable.addColumns(newHeader);
  for (set<Tuple>::iterator it = rows.begin(); it != rows.end(); ++it) {
    if (it->at(columnPosition) == value) {
      newTable.addRow(*it);
    }
  }
  return newTable;
}

Relation Relation::selectColumnColumn(int column1, int column2) {
  Relation newTable;
  newTable.setName(this->name);
  newTable.addColumns(this->columns);
  for (set<Tuple>::iterator it = rows.begin(); it != rows.end(); ++it) {
      if (it->at(column1) == it->at(column2)) {
        newTable.addRow(*it);
      }
  }
  return newTable;
}

Relation Relation::project(vector<int> indexes) {
  Relation newTable;
  newTable.setName(this->name);
  Schema newColumns;
  Tuple newRow;
  int numColumns = indexes.size();
  // Make new headers for the columns
  for (int i = 0; i < numColumns; i++) {
    newColumns.addAttribute(this->columns.at(indexes.at(i)));
  }
  newTable.addColumns(newColumns);
  // Add rows to the new table
  for (set<Tuple>::iterator it = rows.begin(); it != rows.end(); ++it) {
    newRow.clear();
    for (int i = 0; i < numColumns; i++) {
      newRow.push_back(it->at(indexes.at(i)));
    }
    newTable.addRow(newRow);
  }

  return newTable;
}

Relation Relation::rename(int columnPosition, string columnName) {
  Relation tempTable;
  Schema tempColumns = this->columns;
  tempColumns.changeAttribute(columnPosition, columnName);
  set<Tuple> tempRows = rows;
  tempTable.setName(this->name);
  tempTable.addColumns(tempColumns);
  tempTable.addRows(tempRows);
  return tempTable;
}

void Relation::clear() {
  columns.clear();
  rows.clear();
  numRows = 0;
  name = "";
}

Schema Relation::getColumns() {
  return columns;
}

set<Tuple> Relation::getRows() {
  return this->rows;
}

int Relation::getNumRows() {
  return this->numRows;
}

void Relation::setName(string n) {
  this->name = n;
}

string Relation::getName() {
  return this->name;
}

string Relation::printColumns() {
    std::stringstream ss;
    ss << columns.toString();
    return ss.str();
}

string Relation::printRows() {
  std::stringstream ss;
  //problem here!!!
  int numColumns = this->columns.size();

  for (set<Tuple>::iterator it = this->rows.begin(); it != this->rows.end(); ++it) {
      ss << "  ";
      for (int i = 0; i < numColumns; i++) {
        ss << this->columns.at(i) << "=" << it->at(i);
        if (i < numColumns - 1) {
          ss << ", ";
        }
      }
      ss << "\n";
  }

  return ss.str();
}
