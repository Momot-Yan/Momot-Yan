#include <iostream>
#include <vector>
#include <locale.h>
using namespace std;
int main() {
	setlocale(LC_ALL, "Rus");
	size_t chet = 0, k = 1, j, m = 19, n =20;
	size_t mas[20][19];
	while(k<n){
		mas[k][1] = k;
		cout << "\n" << "mas[" << k <<"][" << 1 << "] = " << mas[k][1];
		cout << "\n" << "это число ";
		if((mas[k][1] %2) == 0) {
			cout << "четное";
			chet++;
		}
		else 
			cout << "нечетное";
		cout << "\n" << "четных элементов массива: " << chet << "\n" ;
		j = 2;
		cout << "\n" << "j = " << j; 
		while(j<m){
			mas[k][j] = k*j - mas[k][j-1];
			cout << "\n" << "mas[" << k <<"][" << j << "] = " << mas[k][j];
			cout << "\n" << "это число ";
			if(mas[k][j] %2 == 0) {
				cout << "четное";
				chet++;
			}
			else 
				cout << "нечетное";
			cout << "\n" << "четных элементов массива: " << chet << "\n" ;
			j = j+1;
			cout << "\n" << "j = " << j;
		}
		k++;
		cout << "\n" << "k = " << k; 

	}
	cout << "\n" << "четных элементов массива: " << chet << "\n" ;
	system("pause");

	return 0;
}