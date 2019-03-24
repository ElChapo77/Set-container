#include"Set.h"

Set::Set() //constuctor ce initializeaza size-ul cu 0
	: size(0)
{}

Set::Set(int *a, int n) //constructor ce primeste ca parametri un array si initializeaza set-ul cu elementele array-ului pastrand proprietatea de set
{
	for (int i = 0; i < n; i++)
		insert(a[i]);
}

Set::Set(const Set&ob) //constructor de copiere
	: size(ob.size)
{
	store = new int[size];
	for (int i = 0; i < size; i++)
		store[i] = ob.store[i];
}

Set::~Set() //destructor ce elibereaza memoria ocupata de set
{
	clear();
}

int Set::getSize() const { return size; } //returneaza numarul de elemente al set-ului

void Set::resize(bool IorD, int pos) //modifica marimea set-ului in functie de parametrul IorD (inserare sau stergere) si de pozitia pos
{ //IorD este true pentru inserare si false pentru stergere
	int *p;
	if (IorD == true) //daca urmeaza inserarea unui element
	{ //creste marimea set-ului cu o pozitie, si se lasa libera pozitia pos, deoarece acolo va urma inserarea unui element
		p = new int[++size];
		for (int i = 0; i < pos; i++)
			p[i] = store[i];
		for (int i = pos; i < size - 1; i++)
			p[i + 1] = store[i];
	}
	else //daca urmeaza stergerea unui element
	{ //scade marimea set-ului iar elementul de pe pozitia pos nu mai este retinut in set
		p = new int[--size];
		for (int i = 0; i < pos; i++)
			p[i] = store[i];
		for (int i = pos + 1; i < size + 1; i++)
			p[i - 1] = store[i];
	}
	delete[] store;
	store = p;
}

void Set::clear() //goleste set-ul
{
	delete[] store;
	size = 0;
}

int Set::search(int x) const //returneaza pozitia pe care se gaseste x, daca x nu se gaseste returneaza pozitia pe care acesta s-ar afla daca ar fi inserat
{ //se foloseste cautarea binara pentru a-l cauta pe x
	int ls, li;
	li = 0;
	ls = size - 1;
	do
	{
		int m = ls - (ls - li) / 2;
		if (store[m] == x)
			return m;
		if (x > store[m])
			li = m + 1;
		else
			ls = m - 1;
	} while (li <= ls);
	return -li;
}

void Set::insert(int x) //insereaza x in set, pastrand proprietatile set-ului
{
	if (size == 0) //daca set-ul e vid
	{
		store = new int;
		store[size++] = x;
		return;
	}

	int position = search(x); //pozitia pe care se afla x sau pe care ar trebui inserat
	if (position > 0 || x == store [0]) //testeaza daca x se gaseste deja in set, iar daca este, nu il insereaza (am testat daca x == store[0] deoarece fie ca se gaseste, fie ca nu, va returna aceeasi valoare (0 sau -0))
		return;
	resize(true, -position); //mareste set-ul cu o pozitie si lasa libera pozitia pe care x va fi inserat
	store[-position] = x; //insereaza x pe pozitia corecta
}

void Set::erase(int x) //sterge x din set
{
	if (size == 0) //daca set-ul e vid atunci nu se intampla nimic
		return;
	int position = search(x); //pozitia pe care se afla x
	if (position < 0) //daca x nu apare in set atunci nu se intampla nimic
		return;
	resize(false, position); //micsoreaza set-ul cu o pozitie fara sa-l mai retina pe x (sterge pe x)
}

int Set::sum() const //returneaza suma elementelor din multime
{
	int x = 0;
	for (int i = 0; i < size; i++)
		x += store[i];
	return x;
}

Set Set::evenElements() const //returneaza un nou set ce contine elementele pare din set-ul curent
{
	Set temp;
	for (int i = 0; i < size; i++)
		if (store[i] >= 0)
		{
			if (store[i] % 2 == 0)
				temp.insert(store[i]);
		}
		else
			if ((-store[i]) % 2 == 0)
				temp.insert(store[i]);
	return temp;
}

Set Set::oddElements() const //returneaza un nou set ce contine elementele impare din set-ul curent
{
	Set temp;
	for (int i = 0; i < size; i++)\
		if (store[i] >= 0)
		{
			if (store[i] % 2 == 1)
				temp.insert(store[i]);
		}
		else
			if ((-store[i]) % 2 == 1)
				temp.insert(store[i]);
	return temp;
}

Set Set::operator=(Set ob) //copiaza continutul altui set
{
	clear();
	for (int i = 0; i < ob.size; i++)
		insert(ob.store[i]);
	return *this;
}

int Set::operator[](int i) //aceseaza elementul de pe pozitia i
{
	return store[i];
}

Set Set::operator+(Set ob) //reuniunea cu alt set
{
	Set temp(ob);
	for (int i = 0; i < size; i++)
		temp.insert(store[i]);
	return temp;
}

Set Set::operator-(Set ob) //face operatia de diferenta ( A\B )
{
	Set temp(*this);
	for (int i = 0; i < ob.getSize(); i++)
		temp.erase(ob[i]);
	return temp;
}

bool Set::operator<(Set ob) //compara cardinalul
{
	return(size < ob.getSize());
}

bool Set::operator>(Set ob) //compara cardinalul
{
	return(size > ob.getSize());
}

Set operator*(Set ob, int x) //inmulteste set-ul cu un scalar (scalarul fiind la dreapta)
{
	Set temp(ob);
	if (x == 0) //in caz ca scalarul este 0 atunci set-ul este redus la un singur element, acela fiind 0
	{
		delete[] temp.store;
		temp.store = new int;
		temp.store[0] = 0;
		temp.size = 1;
	}
	else if (x > 0) //daca e mai mare decat 0, atunci se pastreaza ordinea
	{
		for (int i = 0; i < temp.size; i++)
			temp.store[i] *= x;
	}
	else //daca e mai mic decat 0, atunci se se inverseaza ordinea
	{
		for (int i = 0; i <= temp.size / 2 - 1; i++)
		{
			int aux = temp.store[i] * x;
			temp.store[i] = temp.store[temp.size - 1 - i] * x;
			temp.store[temp.size - 1 - i] = aux;
		}
		if (temp.size % 2 == 1)
			temp.store[temp.size / 2] *= x;
	}
	return temp;
}

Set operator*(int x, Set ob) //inmulteste set-ul cu un scalar (scalarul fiind la stanga)
{ //la fel ca cel de sus
	Set temp(ob);
	if (x == 0)
	{
		delete[] temp.store;
		temp.store = new int;
		temp.store[0] = 0;
		temp.size = 1;
	}
	else if (x > 0)
	{
		for (int i = 0; i < temp.size; i++)
			temp.store[i] *= x;
	}
	else
	{
		for (int i = 0; i <= temp.size / 2 - 1; i++)
		{
			int aux = temp.store[i] * x;
			temp.store[i] = temp.store[temp.size - 1 - i] * x;
			temp.store[temp.size - 1 - i] = aux;
		}
		if (temp.size % 2 == 1)
			temp.store[temp.size / 2] *= x;
	}
	return temp;
}

ostream &operator<<(ostream &out, const Set &ob) //scrie fiecare element al set-ului
{
	if (ob.size == 0) //pentru set-uri vide
	{
		cout << "Set-ul este vid" << endl << endl;
		return out;
	}
	cout << "Set-ul este: ";
	for (int i = 0; i < ob.size; i++)
		out << ob.store[i] << ' ';
	out << endl << endl;
	return out;
}

istream &operator>>(istream &in, Set &ob) //citeste set-ul de la tastatura
{
	ob.clear();
	int n;
	cout << "Enter number of values: ";
	cin >> n;
	cout << "Enter " << n << " values: ";
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		ob.insert(x);
	}
	return in;
}