#include <iostream>
#include <fstream>
using namespace std;

/*
*Funkcja otwieraj¹ca plik + sprawdza czy uda³o siê go otworzyæ
*@param_in: nazwa pliku, fstream
*/
void otworzPlik(string nazwa, fstream &plik) {
	plik.open(nazwa);
	if (plik.good() == 0) {
		cout << "Nie udalo sie otworzyc pliku!" << endl;
		getchar();
		exit(0);
	}
}

/*
*Funkcja zamykajaca plik
*@param_in: fstream
*/
void zamknijPlik(fstream &plik) {
	plik.close();
}

/*
*Funkcja tworzaca tablice dwuwym dynamiczna
*@param_in: kolumny, wiersze
*@return: tablica dwuwym
*/
int **stworzTablice(int w, int k){
	int **t = NULL;
	try 
	{
		t = new int*[w];
	}
	catch (bad_alloc)
	{
		cout << "Brak miejsca na utworzenie tablicy. Koncze program";
		getchar();
		cin.ignore();
		exit(0);
	}
		for (int i = 0; i<w; i++)
			try
		{
			t[i] = new int[k];
		}
	catch (bad_alloc)
	{
		cout << "Brak miejsca na utworzenie tablicy. Koncze program";
		getchar();
		cin.ignore();
		exit(0);
	}
	return t;
}/**Funkcja zwalniajaca pamiec alokowana na tab dynam dwuwym*@param_in: kolumny, tablica*/void usunTablice(int w, int **t)
{
	for (int i = 0; i<w; i++)
		delete[] t[i];
	delete[] t;
}

/*
*Fkcja wypelniajaca dwuwym tablice zerami
*@param_in: tablica, wiersze, kolumny
*/
void wypelnijZerami(int **t, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) 
			t[i][j] = 0;
	}
}

/*
*Fkcja tworzaca macierz incydencji i wyswietlajaca ja
*@param_in: tablica, kolumny, wiersze, fstream
*/
void macierzIncydencji(int **t, int m, int n, fstream &plik) {
	int a, b, krawedz;
	for (int i = 0; i < m; i++) {
		plik >> a >> b;
		krawedz = i;
		t[a - 1][krawedz] = 1;
		t[b - 1][krawedz] = -1;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << t[i][j] << "  ";
		}
		cout << endl;
	}
}

/*
*Fkcja wypisujaca sasiadow kazdego wierzcholka
*@param_in: wiersze, kolumny, fstream
*/
void sasiedzi(int n, int m, fstream &plik) {
	int wmax, x, y, **t2 = stworzTablice(n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) t2[i][j] = 0;
	wmax = 0;
	plik >> m;
	plik >> n;
	for (int i = 0; i < m; i++)
	{
		plik >> x >> y; // odczytujemy krawêdŸ
		wmax = (x > wmax) ? x : wmax;
		wmax = (y > wmax) ? y : wmax;
		t2[x - 1][y - 1] = 1;
		t2[y - 1][x - 1] = 1;
	}
	for (int i = 0; i < n; i++) {
		cout << i + 1 << ": ";
		for (int j = 0; j < n; j++) {
			if (t2[i][j] == 1) cout << j + 1 << ' ';
		}
		cout << endl;
	}
	usunTablice(n, t2);
}


int main() {
	int m, n, krawedz; fstream plik;
	otworzPlik("plik.txt", plik);
	plik >> m >> n;
	int **t = stworzTablice(m, n);
	wypelnijZerami(t, n, m);
	macierzIncydencji(t, m, n, plik);
	usunTablice(m, t);
	zamknijPlik(plik);
	otworzPlik("plik.txt", plik);
	sasiedzi(n, m, plik);
	system("pause");
}