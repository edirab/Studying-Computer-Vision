#pragma once

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <vector>
#include <string>
#include "Missions.h"

bool check_tasks(vector<Mission*> tasks);

void printTasks(vector<Mission*> mission);

void writeToFile(vector<Mission*> &mission);

void edit_task(vector<Mission*>& Missions, int id);

void delete_task(vector<Mission*>& Missions, int id);

void insert_task(vector<Mission*>& Missions, int id);

void exchange_tasks(vector<Mission*>& Missions, int id1, int id2);

void read_from_file(vector<Mission*>& Missions, string path);

void print_help();

#endif