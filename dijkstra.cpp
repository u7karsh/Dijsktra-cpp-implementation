#include "dijkstra.h"

char* readNextLine(std::ifstream& fp){
	std::string line;
	if (fp.is_open() && fp.good())
	{
		getline(fp, line);
		char *cstr = new char[line.length() + 1];
		strcpy(cstr, line.c_str());
		return cstr;
	}
	else return NULL;
}

void parseFile(char *file, std::vector<std::vector<char>> &grid){
	//open file
	std::ifstream fp(file);
	int grid_rows = 0;
	char* line;
	if (fp.is_open()){
		while (fp.good()){
			//line by line parser
			line = readNextLine(fp);
			grid.resize(++grid_rows);
			int length = strlen(line);
			//char by char parse
			for(int i=0;i<length;i++){
				grid.at(grid_rows - 1).push_back(*(line + i));
			}
		}
	}
}

void task(std::vector<std::vector<int>> &distance, std::vector<std::vector<std::vector<int>>> &previous, int x1, int y1, int x2, int y2){
	if (distance[x1][y1] + 1 < distance[x2][y2]){
		distance[x2][y2] = distance[x1][y1] + 1;
		previous[x2][y2][0] = x1;
		previous[x2][y2][1] = y1;
	}
}

int searchxy(std::vector<std::vector<int>> &q, int x, int y){
	int i;
	for (i = 0; i<q.size(); i++){
		if (q[i][0] == x && q[i][1] == y)
			return(1);
	}
	return(0);
}

void rem(std::vector<std::vector<int>> &q, int x, int y){
	int i;
	for (i = 0; i<count; i++){
		if (q[i][0] == x && q[i][1] == y)
			break;
	}
	for (int j = i; j<count - 1; j++){
		int tem = q[j][0];
		q[j][0] = q[j + 1][0];
		q[j + 1][0] = tem;
		tem = q[j][1];
		q[j][1] = q[j + 1][1];
		q[j + 1][1] = tem;
	}
	count--;
}

void dijkstra(std::vector<std::vector<char>> &grid, std::vector<std::vector<int>> &output, int x, int y, int srcx, int srcy){
	//distance and previous vec init
	std::vector<std::vector<int>> distance;
	std::vector<std::vector<std::vector<int>>> previous;
	std::vector<std::vector<int>> q;

	int min = inf, out_count;

	//size computation
	int sizey = grid.size();
	int sizex = grid.at(0).size();

	//resize vectors vertically
	distance.resize(sizey);
	previous.resize(sizey);

	for (int i = 0; i<sizey; i++){
		//resize vectors horizontally
		distance[i].resize(sizex);
		previous[i].resize(sizex);
		for (int j = 0; j<sizex; j++){
			//init vals
			previous[i][j].resize(2);
			distance[i][j] = inf;
			previous[i][j][0] = -1;
			previous[i][j][1] = -1;
			if (grid[i][j] != wall){
				//resize and init val
				q.resize(++count);
				q.at(count - 1).resize(2);
				q.at(count - 1)[1] = j;
				q.at(count - 1)[0] = i;
			}
		}
	}

	//declare inf value or maximum possible path length + 1
	inf = (sizex * sizey) + 1;
	distance[x][y] = 0;
	while (count != 1){
		min = inf;
		for (int i = 0; i<count; i++){
			if (distance[q[i][0]][q[i][1]] < min){
				min = distance[q[i][0]][q[i][1]];
				x = q[i][0];
				y = q[i][1];
			}
		}
		rem(q, x, y);
		if (distance[x][y] == inf)
			break;
		if (x - 1 >= 0 && searchxy(q, x - 1, y) == 1)	
			task(distance, previous, x, y, x - 1, y);
		if (x + 1 <= sizex && searchxy(q, x + 1, y) == 1)	
			task(distance, previous, x, y, x + 1, y);
		if (y + 1 <= sizey && searchxy(q, x, y + 1) == 1)	
			task(distance, previous, x, y, x, y + 1);
		if (y - 1 >= 0 && searchxy(q, x, y - 1) == 1)	
			task(distance, previous, x, y, x, y - 1);
	}
	out_count = 0;
	x = srcx;
	y = srcy;
	while (previous[x][y][0] != -1 && previous[x][y][1] != -1){
		//resize and init
		output.resize(++out_count);
		output.at(out_count - 1).resize(2);
		output[out_count - 1][0] = x;
		output[out_count - 1][1] = y;

		int i = previous[x][y][0];
		int j = previous[x][y][1];
		x = i;
		y = j;
	}
}

void printgrid(std::vector<std::vector<char>> &grid){
	int i, j;
	for (i = 0; i<grid.size(); i++){
		for (j = 0; j<grid.at(i).size(); j++){
			printf("%c ", grid.at(i).at(j));
		}
		printf("\n");
	}
}