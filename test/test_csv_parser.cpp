// This file is part of CSVParser
// Copyright (C) 2015 Jianwei Cui <thucjw@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include "csv_parser.h"

using namespace std;

int main() {
  CSVParser csvparser;
  string file = "csv_1.csv";
  csvparser.open(file);

  csvparser.parse();
  csvparser.printToConsole();

  return 0;
}
