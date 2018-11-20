//
// Created by goforbroke on 20.11.18.
//

#ifndef CONSOLE_INTERACTION_TESTER_STRINGS_H
#define CONSOLE_INTERACTION_TESTER_STRINGS_H

#include <string>
#include <list>
#include <algorithm>

using namespace std;

string trim(string str, list<string> search = {" ", "\r\n", "\n"}) {
    if (str.length() == 0) return str;

    list<string>::iterator match;

    string first;
    while (true) {
        first = str.substr(0, 1);
        match = std::find(search.begin(), search.end(), first);
        if (match == search.end())
            break;
        str = str.substr(1);
    }

    string last;
    while (true) {
        last = str.substr(str.length() - 1, 1);
        match = std::find(search.begin(), search.end(), last);
        if (match == search.end())
            break;
        str = str.substr(0, str.length() - 1);
    }

    return str;
}

#endif //CONSOLE_INTERACTION_TESTER_STRINGS_H
