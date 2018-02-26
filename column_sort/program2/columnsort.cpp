#include "utility.h"
#include "filer.h"
#include "timer.h"
#include "columnsort.h"

void partTwo(int n, int range, string file_name);
void quickSort(short int arr[], int left, int right);
bool SortCheck(short int a[], int  n);


int main() {
	//part 1 call
	Filer f;
	int n, range;
	string file_name[3];
	for (int i = 1; i < 4; i++) {
		cout << "enter number of numbers you want in file" << i << ":";
		cin >> n;
		cout << "enter upper limit of size of numbers for file" << i << ":";
		cin >> range;
		cout << " enter file name for file" << i << ":";
		cin >> file_name[i - 1];
		f.makefile(n, range, file_name[i - 1]);
	}
	

	//part2 call
	for (int i = 0; i < 3; i++) {
		string a = file_name[i];
		partTwo(n, range, a);
	}

	//part 3 call
	for (int i = 0; i < 3; i++) {
		Columnsort(file_name[i], n);
	}

	int a;
	cin >> a;
}


//part 2
void partTwo(int n,int range, string file_name) {
	
	short int *a=new short int[n];
	ifstream file(file_name);
	int nl = 0;

	if (file.is_open()) {
		while (!file.eof())
		{
			file >> a[nl];
			++nl;
		}
	}

	Timer tr;
	tr.reset(); // start of time
	quickSort(a, 0, n-1);
	double time = tr.elapsed_time(); // end time

	// checking is array is sorted before writing to file
	if (SortCheck(a,n-1)) {
		ofstream infile;
		infile.open(file_name + "-sorted");
		for (int i = 0; i < n; i++) {
			infile << a[i] << "\n";
		}

		cout.setf(ios::fixed);
		cout.setf(ios::showpoint);
		cout.precision(3);
		cout << " Time taken to sort for " << file_name<<" is:" << time <<endl;
		
	}
	delete[] a; 

	}

void quickSort(short int arr[], int left, int right) {
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];

	// partition 
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	// recursion 
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

// sort check method
bool SortCheck(short int a[],int  n) {
	for (int i = 1; i < n; i++)
	{
		if (a[i - 1] > a[i])
		{
			return false;
		}
	}
	return true;
}