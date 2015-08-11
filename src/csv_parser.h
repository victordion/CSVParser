// This file is part of CSVParser
// Copyright (C) 2015 Jianwei Cui <thucjw@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <fstream>
#include <vector>
using namespace std;

class CSVParser {
  public:
    CSVParser() {
    }

    CSVParser(std::string file) {
      m_input_file_stream.open(file.c_str(), std::ifstream::in);
    }

    void open(std::string file) {
      m_input_file_stream.open(file.c_str(), std::ifstream::in); 
    }


    void parse() {
      for(string line; getline(m_input_file_stream, line); ) {
        vector<string> tuple = parseLine(line);
        m_tuples.push_back(tuple);
      }
    }

    void printToConsole() {
      cout << "[" << endl;

      for (int i = 0; i < m_tuples.size(); ++i) {
        cout << "[";

        for (int j = 0; j < m_tuples[i].size(); ++j) {
          cout << "\"" <<  m_tuples[i][j] << "\"";
          if (j < m_tuples[i].size() - 1) {
            cout << ", ";
          }
        }
        cout << "]" << endl;
      }
    }

  protected:
    std::ifstream m_input_file_stream;
    std::ofstream m_output_file_stream;
    vector<vector<string> > m_tuples;
  
    inline vector<string> parseLine(string line) {
      vector<string> ret;
      string curr_ele = "";
      bool inQuote = false;
      int i = 0;

      while (i < line.length()) {
        if (line[i] == ',') {
          if (inQuote == false) {
            ret.push_back(curr_ele);
            curr_ele.clear();
            ++i;
          }
          else {
            curr_ele += line[i];
            ++i;
          }
        }
        else if (line[i] == '"') {
          if(isEscapeDoubleQuote(line, i)) {
            curr_ele += '"';
            i += 2;
          }
          else if (inQuote == false) {
            inQuote = true;
            ++i;
          }
          else {
            inQuote = false;
            ++i;
          }
        }
        else {
          curr_ele += line[i];
          ++i;
        }
      }

      ret.push_back(curr_ele);
      return ret;
    }

    // get the number of consecutive double quotes in a string starting at offset i
    inline bool isEscapeDoubleQuote(const string & line, const int pos) {
      return (pos + 1 < line.length()) && (line[pos + 1] == '"');
    }

};
