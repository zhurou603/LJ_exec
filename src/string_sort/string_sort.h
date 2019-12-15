#ifndef STRING_SORT_H
#define STRING_SORT_H

#include<vector>
#include<string>

using namespace std;

bool is_small_equal(const string& a, const string& b);
void merge_string_sort(vector<string>* data);
void merge_string_sort(vector<string>* data, vector<string>* help, int low, int high);
void merge(vector<string>* data, vector<string>* help, int low, int mid, int high);

#endif
