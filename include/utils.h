#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <string>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <sys/stat.h>
#include <unistd.h>
#include <map>
#include <iterator>
#include <algorithm>
#include "kalman.h"
using namespace std;

string path_leaf(string const & path);
float overlap(float x1, float w1, float x2, float w2);
float box_intersection(float a[4], float b[4]);
float box_union(float a[4], float b[4]);
float box_iou(float a[4], float b[4]);
template<typename Out> void split(const std::string &s, char delim, Out result);
std::vector<std::string> split(const std::string &s, char delim);
bool exists (string name);
vector <int> get_keys(map <int, Matrix <float> > m);
vector<int> vector_union (vector <int> a, vector <int> b);

#endif