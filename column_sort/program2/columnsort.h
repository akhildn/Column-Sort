#include "utility.h"
#define r 4000
#define s 25


bool SortCheck(int a[], int  n) {
	for (int i = 1; i < n; i++)
	{
		if (a[i - 1] > a[i])
		{
			return false;
		}
	}
	return true;
}
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void quickSort(short int **arr, int columnIndex, int left, int right) {
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2][columnIndex];

	/* partition */
	while (i <= j) {
		while (arr[i][columnIndex] < pivot)
			i++;
		while (arr[j][columnIndex] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i][columnIndex];
			arr[i][columnIndex] = arr[j][columnIndex];
			arr[j][columnIndex] = tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		quickSort(arr, columnIndex, left, j);
	if (i < right)
		quickSort(arr, columnIndex, i, right);
}


void Columnsort(string file_name, int n) {


	short int **b;
	b = new short int*[r];
	short int *a = new short int[n];

	//from file to 1-D array     
	ifstream file(file_name);
	int nl = 0;
	if (file.is_open()) {
		while (!file.eof())
		{
			file >> a[nl];
			++nl;
		}
	}

	// 1-D to 2-D array
	int k = 0;
	for (int i = 0; i < r; i++) {
		b[i] = new short int[s];
		for (int j = 0; j < s; j++) {
			if (k < n) {
				b[i][j] = a[k];
				k++;
			}
		}
	}

	
	ofstream inMatfile;
	inMatfile.open("part"+file_name+"data.txt");
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < s; j++) {
			inMatfile << b[i][j]<< "\t";
		}
		inMatfile << "\n";
	}


	Timer t;
	t.reset();
	
	//step 1
	for (int columnIndex = 0; columnIndex < s; columnIndex++)
		quickSort(b, columnIndex, 0,r-1);

	//step 2
	int columnTranspose[r][s];
	int tRowindex = 0, tColumnindex = 0;

	for (int columnIndex = 0; columnIndex < s; columnIndex++) {
		for (int rowIndex = 0; rowIndex < r; rowIndex++) {
			columnTranspose[tRowindex][tColumnindex % s] = b[rowIndex][columnIndex];
			tColumnindex++;
			if (tColumnindex % s == 0)
				tRowindex++;
		}
	}

	double time1 = t.elapsed_time();
	//moving back to original 2-D
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < s; j++) {
			b[i][j] = columnTranspose[i][j];
		}
	}


	t.reset();
	// step 3
	for (int columnIndex = 0; columnIndex < s; columnIndex++)
		quickSort(b, columnIndex, 0,r-1);


	//step 4
	int rowTranspose[r][s];
	tRowindex = 0, tColumnindex = 0;

	for (int rowIndex = 0; rowIndex < r; rowIndex++) {
		for (int columnIndex = 0; columnIndex < s; columnIndex++) {
			rowTranspose[tRowindex % r][tColumnindex] = b[rowIndex][columnIndex];
			tRowindex++;
			if (tRowindex % r == 0)
				tColumnindex++;
		}
	}
	double time2 = t.elapsed_time();

	//moving back to original 2-D
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < s; j++) {
			b[i][j] = rowTranspose[i][j];
		}
	}

	t.reset();
	//step 5
	for (int columnIndex = 0; columnIndex < s; columnIndex++)
		quickSort(b, columnIndex, 0, r - 1);


	//step 6
	short int **shiftMatrix;
	shiftMatrix = new short int*[r];
	for (int i = 0; i < r; i++)
		shiftMatrix[i] = new short int[s + 1];

	int flagRange = r / 2;
	int sRowIndex = flagRange, sColumnIndex = 0;
	for (int columnIndex = 0; columnIndex < s; columnIndex++) {
		for (int rowIndex = 0; rowIndex < r; rowIndex++) {
			shiftMatrix[sRowIndex][sColumnIndex] = b[rowIndex][columnIndex];
			if (sColumnIndex == 0 && rowIndex < flagRange) {
				shiftMatrix[rowIndex][sColumnIndex] = -32766;
			}
			if (columnIndex == s - 1 && rowIndex >= flagRange) {
				shiftMatrix[rowIndex][s] = 32767;
			}

			sRowIndex = sRowIndex + 1;
			if ((sRowIndex%r) == 0) {
				sColumnIndex = sColumnIndex + 1;
				sRowIndex = 0;
			}
		}
	}


	//step 7
	for (int columnIndex = 0; columnIndex <= s; columnIndex++)
		quickSort(shiftMatrix, columnIndex, 0,r-1);

	//step 8
	int *sortedArray = new int[n]; int sortedIndex = 0;
	int finalRowIndex = 0, finalColumnIndex = 0;
	for (int columnIndex = 0; columnIndex <= s; columnIndex++) {

		for (int rowIndex = 0; rowIndex < r; rowIndex++) {
			if (columnIndex == 0 && rowIndex < flagRange)
				continue;
			if (columnIndex == s && rowIndex >= flagRange)
				continue;
			b[finalRowIndex][finalColumnIndex] = shiftMatrix[rowIndex][columnIndex];
			sortedArray[sortedIndex] = b[finalRowIndex][finalColumnIndex];
			sortedIndex++;
			finalRowIndex++;
			if (finalRowIndex%r == 0) {
				finalColumnIndex++;
				finalRowIndex = 0;
			}
		}
	}

	double time3=t.elapsed_time();
	double time = time1 + time2 + time3;
	cout << "Time taken for coulmn-sort file-" <<file_name<<" is:"<<time <<endl;

	if (SortCheck(sortedArray, n)) {
		cout << "file is sorted" << endl;
	}

	ofstream infile;
	infile.open(file_name+"Results.txt");
	for (int i = 0; i < n; i++) {
		infile << sortedArray[i] << "\n";
	}

}