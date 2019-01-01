//
// Created by goforbroke on 20.11.18.
//

#ifndef CONSOLE_INTERACTION_TESTER_STRINGS_H
#define CONSOLE_INTERACTION_TESTER_STRINGS_H

#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

namespace strings {

    string Trim(string s, const string &cutset = "\n\t\r ") {
        for (long i = 0; i < cutset.length(); ++i) {

            const char &ch = cutset.at(i);

            if (s.at(0) == ch) {
                s = s.substr(1);
                i = -1;
                continue;
            }
            if (s.at(s.length() - 1) == ch) {
                s = s.substr(0, s.length() - 1);
                i = -1;
                continue;
            }
        }
        return s;
    }

    string Trim2(string str, list <string> search = {" ", "\t", "\r\n", "\n"}) {
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

    string Join(const vector<string> &a, const string &sep) {
        string res;
        for (auto it = a.begin(); it < std::prev(a.end()); ++it) {
            res += (*it) + sep;
        }
        res += (*std::prev(a.end()));
        return res;
    }

    vector<string> Split(const string &s, const string &sep) {
        vector<string> res;

        unsigned long start = 0;
        long next = 0;
        string token;
        for (;;) {
            next = s.find(sep, start);
            if (next < 0) {
                token = s.substr(start, s.length() - start);
                res.push_back(token);
                break;
            }

            token = s.substr(start, next - start);

            res.push_back(token);
            start = next + sep.length();
        }

        return res;
    }
}

#endif //CONSOLE_INTERACTION_TESTER_STRINGS_H
