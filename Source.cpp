#include"Set.h"
#include<cassert>

int main() //ruleaza perfect in visual studio 2017
{
	Set s1; //s1 este vid, size = 0
	assert(s1.getSize() == 0);

	int a[] = { 5,3,7,1,1,3,5,7 };
	Set s2(a, 8); //s2 = { 1, 3, 5, 7}, size = 4
	assert(s2.getSize() == 4);
	assert(s2[0] == 1 && s2[1] == 3 && s2[2] == 5 && s2[3] == 7);

	Set s3(s2); //s3 = { 1, 3, 5, 7}, size = 4
	assert(s3.getSize() == s2.getSize());
	assert(s2[0] == s3[0] && s2[1] == s3[1] && s2[2] == s3[2] && s2[3] == s3[3]);

	assert(s3.search(3) == 1); //3 se gaseste pe pozitia 1 in s3
	assert(s3.search(2) < 0); //2 nu se gaseste in s3

	s3.insert(-2); //s3 = { -2, 1, 3, 5, 7}, size = 5
	s3.insert(-4); //s3 = { -4, -2, 1, 3, 5, 7}, size = 6
	s3.insert(1); //1 se afla deja in s3, deci nu este inserat 
	assert(s3.getSize() == 6);
	assert(s3[0] == -4 && s3[1] == -2);

	s3.erase(5); //s3 = { -4, -2, 1, 3, 7}, size = 5
	s3.erase(2); //2 nu se afla in s3, deci nu se intampla nimic
	assert(s3.getSize() == 5);
	assert(s3.search(5) < 0);

	assert(s2.sum() == 16); //s2 = { 1, 3, 5, 7}, deci s2.sum = 1+3+5+7 = 16

	s1 = s3.evenElements(); //s1 = { -4, -2}, size = 2
	s2 = s3.oddElements(); //s2 = { 1, 3, 7}, size = 3;
	assert(s1.getSize() == 2);
	assert(s1[0] == -4 && s1[1] == -2);
	assert(s2.getSize() == 3);
	assert(s2[0] == 1 && s2[1] == 3 && s2[2] == 7);

	Set s4(s1 + s2); //s4 = {-4, -2, 1, 3, 7}, size = 5
	assert(s4.getSize() == s3.getSize());
	assert(s4[0] == -4 && s4[1] == -2 && s4[2] == 1 && s4[3] == 3 && s4[4] == 7);

	s4 = s3 - s2; //s4 = { -4, -2}, size = 2;
	assert(s4.getSize() == s1.getSize());
	assert(s4[0] == -4 && s4[1] == -2);

	assert(s1 < s2);
	assert(s3 > s2);

	s4 = (-2) * s2; //s4 = { -14, -6, -2}, size = 3
	assert(s4.getSize() == s2.getSize());
	assert(s4[0] == -14 && s4[1] == -6 && s4[2] == -2);
	s4 = s3 * 0; //s4 = { 0 }, size = 1
	assert(s4.getSize() == 1);
	assert(s4[0] == 0);

	system("pause");
}