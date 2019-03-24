#pragma once
#include<iostream>
using namespace std;

class Set
{
	int *store; //pointer catre elementele set-ului
	int size; //numarul de elemente al set-ului
	void resize(bool, int); //folosit doar de functia de inserare si stergere
public:
	Set();
	Set(int*, int);
	Set(const Set&);
	~Set();

	int getSize() const;

	void clear();
	int search(int) const;
	void insert(int);
	void erase(int);
	int sum() const;
	Set evenElements() const;
	Set oddElements() const;

//supraincarcarea operatorilor
	Set operator=(Set);
	int operator[](int);
	Set operator+(Set);
	Set operator-(Set);
	bool operator<(Set);
	bool operator>(Set);
	friend Set operator*(Set, int);
	friend Set operator*(int, Set);
	friend ostream &operator<<(ostream&, const Set&);
	friend istream &operator>>(istream&, Set&);
};