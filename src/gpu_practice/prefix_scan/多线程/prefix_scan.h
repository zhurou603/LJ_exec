#ifndef PREFIX_SCAN_H
#define PREFIX_SCAN_H

#include<thread>
#include<random>
#include<iostream>
#include<vector>

#include"barrier.h"

using namespace std;

void prefix_scan_thread(vector<Barrier*>& barriers, vector<int>& output, int id, int epochs, int num_threads, int size);

void multithread_prefix_scan(vector<int>& input, int num_threads);

#endif
