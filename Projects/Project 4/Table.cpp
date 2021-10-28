

#include "Table.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <functional>
#include <cstdlib>
using namespace std;


bool stringToDouble(string s, double& d)
{
    char* end;
    d = std::strtof(s.c_str(), &end);
    return end == s.c_str() + s.size()  &&  !s.empty();
}

HashTable::HashTable() {
    // Create an empty hashtable
    list<Node> nodes;
    for (int i = 0; i < 999; i++) {
        buckets.push_back(nodes);
    }
}

vector<vector<string>> HashTable::search(const string& key) const {
    
    // Create an empty result vector
    vector<vector<string>> res;

    // Visit every bucket in the table
    for (int i = 0; i < 999; i++) {
        list<Node> curr = buckets[i];
        
        // If the bucket is empty, skip to the next bucket
        if (curr.empty()) continue;
        
        // Loop through the list of vectors in each bucket
        for (list<Node>::iterator it = curr.begin(); it != curr.end(); it++) {
            
            // Loop through every element in the vector
            for (int j = 0; j < it->m_row.size(); j++) {
                
                // If the vector contains the key, add the vector to the result
                if (it->m_row[j] == key) {
                    res.push_back(it->m_row);
                    break;
                }
            }
        }
    }
    
    return res;
    
}

void HashTable::add(const vector<string>& s) {

    // Find the correct bucket to put the vector into
    list<Node> curr = buckets[hashFunc(s)];
    
    // Create a new node
    Node addNode;
    
    // Set the new node to the vector we are inserting
    addNode.m_row = s;
    
    // Add the new node to end of the list
    curr.push_back(addNode);
    
    // Replace the old bucket with new one that has the added node
    buckets[hashFunc(s)] = curr;
    
}

unsigned int HashTable::hashFunc(const vector<string>& hash) const {
    
    // Hash the first element in the vector
    unsigned int value = std::hash<string>()(hash[0]);;
    
    // Loop through every element in the vector and XOR the hashed values
    for (int i = 1; i < hash.size(); i++) {
        value = value^std::hash<string>()(hash[i]);
    }
    
    // Find the corresponding bucket
    unsigned int bucket = value % 999;
    
    return bucket;
}


vector<vector<string>> HashTable::querySearch(const int& index, const string& op, const string& token) const {
    
    // Create an empty result vector
    vector<vector<string>> res;
    
    // Visit every bucket in the table
    for (int i = 0; i < 999; i++) {
        list<Node> curr = buckets[i];
        
        // If the bucket is empty, skip to the next bucket
        if (curr.empty()) continue;
        
        // Loop through the list of vectors in each bucket
        for (list<Node>::iterator it = curr.begin(); it != curr.end(); it++) {
            
            // Loop through every element in the vector
            for (int j = 0; j < it->m_row.size(); j++) {
                
                // Check the element that is at the index we are searching for
                if (j == index) {
                    
                    // Push the vector into the result if it passes the operation
                    if (op == "<")
                        if (it->m_row[j] < token) res.push_back(it->m_row);
                    if (op == "<=")
                        if (it->m_row[j] <= token) res.push_back(it->m_row);
                    if (op == ">")
                        if (it->m_row[j] > token) res.push_back(it->m_row);
                    if (op == ">=")
                        if (it->m_row[j] >= token) res.push_back(it->m_row);
                    if (op == "!=")
                        if (it->m_row[j] != token) res.push_back(it->m_row);
                    if (op == "==")
                        if (it->m_row[j] == token) res.push_back(it->m_row);
                    if (op == "=")
                        if (it->m_row[j] == token) res.push_back(it->m_row);
                    
                }
            }
        }
    }
    
    return res;

}

vector<vector<string>> HashTable::querySearch(const int& index, const string& op, const double& token) const {
    
    // Create an empty result vector
    vector<vector<string>> res;
    
    // Visit every bucket in the table
    for (int i = 0; i < 999; i++) {
        list<Node> curr = buckets[i];
        
        // If the bucket is empty, skip to the next bucket
        if (curr.empty()) continue;
        
        // Loop through the list of vectors in each bucket
        for (list<Node>::iterator it = curr.begin(); it != curr.end(); it++) {
            
            // Loop through every element in the vector
            for (int j = 0; j < it->m_row.size(); j++) {
                double d;
                
                // Check the element that is at the index we are searching for and if it can be converted into a double
                if (j == index && stringToDouble(it->m_row[j], d))  {
                    
                    // Push the vector into the result if it passes the operation
                    if (op == "lt")
                        if (d < token) res.push_back(it->m_row);
                    if (op == "le")
                        if (d <= token) res.push_back(it->m_row);
                    if (op == "gt")
                        if (d > token) res.push_back(it->m_row);
                    if (op == "ge")
                        if (d >= token) res.push_back(it->m_row);
                    if (op == "ne")
                        if (d != token) res.push_back(it->m_row);
                    if (op == "eq")
                        if (d == token) res.push_back(it->m_row);
                    
                }
                
                // If the element is at the index we are searching for but it can't be converted into a double
                else if (j == index && !stringToDouble(it->m_row[j], d)){
                    
                    // Push an empty vector to signify a failure
                    vector<string> empty;
                    res.push_back(empty);
                }
            }
        }
    }
    
    return res;

}

bool StringParser::getNextField(std::string& fieldText)
{
    m_start = m_text.find_first_not_of(" \t\r\n", m_start);
    if (m_start == std::string::npos)
    {
        m_start = m_text.size();
        fieldText = "";
        return false;
    }
    if (m_text[m_start] != '\'')
    {
        size_t end = m_text.find_first_of(" \t\r\n", m_start+1);
        fieldText = m_text.substr(m_start, end-m_start);
        m_start = end;
        return true;
    }
    fieldText = "";
    for (;;)
    {
        m_start++;
        size_t end = m_text.find('\'', m_start);
        fieldText += m_text.substr(m_start, end-m_start);
        m_start = (end != std::string::npos ? end+1 : m_text.size());
        if (m_start == m_text.size()  ||  m_text[m_start] != '\'')
            break;
        fieldText += '\'';
    }
    return true;
}



Table::~Table() {
    
}

Table::Table(std::string keyColumn, const std::vector<std::string>& columns) {
    m_key = keyColumn;
    m_cols = columns;
    
    // Find the index where the key is located
    for (int i = 0; i < m_cols.size(); i++) {
        if (m_cols[i] == m_key) {m_keyIndex = i; break;}
    }
}

bool Table::good() const {
    
    
    bool found = false;
    
    // If the column vector is empty, return false
    if (m_cols.empty()) return false;
    
    // If the key is the empty string, return false
    if (m_key == "") return false;
    
    // If any element in the column vector is the empty string, return false
    for (int i = 0; i < m_cols.size(); i++) {
        if (m_cols[i] == "") return false;
        if (m_key == m_cols[i]) found = true;
        
    }
    // If the key is not in the column vector, return false
    if (!found) return false;
    
    // If there is a duplicate in the column vector, return false
    for (int i = 0; i < m_cols.size(); i++) {
        for (int j = i + 1; j < m_cols.size(); j++) {
            if (m_cols[i] == m_cols[j]) return false;
        }
    }
    
    
    return true;
}

bool Table::insert(const std::string &recordString) {
    
    if (!good()) return false;
    
    StringParser parser(recordString);
    vector<string> row;
    string s;
    
    // Create a vector where each element is one of the parsed strings
    while (parser.getNextField(s)) {
        row.push_back(s);
    }
    
    // If there is a different number of parsed strings than columns, return false
    if (row.size() != m_cols.size()) return false;
    
    // Insert the vector into the hashtable
    m_hash.add(row);
    
    return true;
}

void Table::find(std::string key, std::vector<std::vector<std::string>>& records) const {
    
    // Clear the final vector
    records.clear();
    
    // Create an empty result vector
    vector<vector<string>> result;
    
    // Add every record that contains the key in the list
    result = m_hash.search(key);
    
    // Loop through every vector in the result
    for (int i = 0; i < result.size(); i++) {
        
        // Loop through every element in each vector
        for (int j = 0; j < result[i].size(); j++) {
            
            // Only add the vector to records if the key is in the correct index
            if (j == m_keyIndex && result[i][j] == key) records.push_back(result[i]);
        }
    }

}

int Table::select(std::string query, std::vector<std::vector<std::string>>& records) const {
    
    // Clear the final vector
    records.clear();
    
    // Convert the query string into a vector with 3 elements
    StringParser parser(query);
    vector<string> parsedQuery;
    string s;
    while (parser.getNextField(s)) {
        parsedQuery.push_back(s);
    }
    
    // If there is not exactly 3 elements, the query is invalid
    if (parsedQuery.size() != 3) return -1;
    
    // If any of the elemeents are the empty string, the query is invalid
    for (int i = 0; i < parsedQuery.size(); i++) {
        if (parsedQuery[i] == "") return -1;
    }

    
    int counter = 0;
    int colIndex = -1;
    
    // If there are duplicate values, the query is invalid
    for (int i = 0; i < m_cols.size(); i++) {
        if (parsedQuery[0] == m_cols[i]) {
            counter++;
            // Store the index of the correct column
            colIndex = i;
        }
    }
    if (counter != 1) return -1;

    // Convert the operator to lowercase
    for (auto & c : parsedQuery[1]) {
        c = tolower(c);
    }

    // If the second element isn't a valid operator, the query is invalid
    if (parsedQuery[1] != "<" && parsedQuery[1] != "<=" && parsedQuery[1] != ">" && parsedQuery[1] != ">=" && parsedQuery[1] != "!=" && parsedQuery[1] != "==" && parsedQuery[1] != "=" && parsedQuery[1] != "lt" && parsedQuery[1] != "le" && parsedQuery[1] != "gt" && parsedQuery[1] != "ge" && parsedQuery[1] != "ne" && parsedQuery[1] != "eq") return -1;
    
    double d;
    vector<vector<string>> result;
    
    if (parsedQuery[1] == "lt" || parsedQuery[1] == "le" || parsedQuery[1] == "gt" || parsedQuery[1] == "ge" || parsedQuery[1] == "ne" || parsedQuery[1] == "eq") {
        // If the operator is for numerical comparisons, the third element in the query must be a number
        if (!stringToDouble(parsedQuery[2], d)) return -1;
        
        // Execute the query search
        result = m_hash.querySearch(colIndex, parsedQuery[1], d);
    }
    // Otherwise if we are doing string comparisons, do the query search for strings
    else result = m_hash.querySearch(colIndex, parsedQuery[1], parsedQuery[2]);
    
    
    int resCounter = 0;
    
    // Loop through every vector in the result
    for (int i = 0; i < result.size(); i++) {
        
        // If the result contains an empty string, this means there was a failure in the numerical comparison query search
        if (result[i].empty()) {resCounter++;
         //   continue;
            
        }
        
        // Otherwise if it isn't the empty string, push the vector into the records
        else records.push_back(result[i]);
    }
    
    
    return resCounter;
}
