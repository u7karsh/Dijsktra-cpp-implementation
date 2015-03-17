#include "dijkstra.h"

int main(){
	std::vector<std::vector<char>> grid;
	std::vector<std::vector<int>> output;
	parseFile("input.txt", grid);
	printgrid(grid);
	int i;

	dijkstra(grid, output, 0, 2, 5, 5);
	printf("complete %d\n", output.size());
	for (i = output.size() - 1; i >= 0; i--){
		printf("%d   %d", output[i][0], output[i][1]);
		printf("\n");
	}
	while (1);
	return 0;
}