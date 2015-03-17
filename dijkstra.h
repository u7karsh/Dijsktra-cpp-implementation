#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>

int inf;
int count;
#define wall '#'

//prototypes..
char* readNextLine(std::ifstream& fp);
void parseFile(char *file, std::vector<std::vector<char>> &grid);
void task(std::vector<std::vector<int>> &distance, std::vector<std::vector<std::vector<int>>> &previous, int x1, int y1, int x2, int y2);
int searchxy(std::vector<std::vector<int>> &q, int x, int y);
void rem(std::vector<std::vector<int>> &q, int x, int y);
void dijkstra(std::vector<std::vector<char>> &grid, std::vector<std::vector<int>> &output, int x, int y, int srcx, int srcy);
void printgrid(std::vector<std::vector<char>> &grid);