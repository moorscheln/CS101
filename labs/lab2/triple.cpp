#include <string>
#include <iostream>
#include <sstream>

#include "triple.h"

using namespace std;

// all elements have value 0
// usage: Triple t;
Triple::Triple()
{
   a = 0;
   b = 0;
   c = 0;
}

// all elements have value k
// usage: Triple t(int);
Triple::Triple(int k)
{
   a = k;
   b = k;
   c = k;
}

// a has value x, b has value y, c has value z
// usage: Triple t(int, int, int);
Triple::Triple(int x, int y, int z)
{
   this->a = x;
   this->b = y;
   this->c = z;
}

// index 0 is a, 1 is b, 2 is c
// usage: int i = t.fetch(int);
int Triple::fetch(int index)
{
   if (index == 0)
   {
      return this->a;
   }
   else if (index == 1)
   {
      return this->b;
   }
   else if (index == 2)
   {
      return this->c;
   }
   else
   {

      return -1;
   }
}

// update chosen element to value k
// index 0 is a, 1 is b, 2 is c
// usage: t.assign(int, int);
void Triple::assign(int index, int k)
{
   if (index == 0)
   {
      this->a = k;
   }
   else if (index == 1)
   {
      this->b = k;
   }
   else if (index == 2)
   {
      this->c = k;
   }
}

// string representation is "(a,b,c)"
// write fromString() first and use it
// this method has already been written for you
// usage: Triple t("(1,2,3)");
Triple::Triple(string s)
{
   fromString(s);
}

// create a string representation of the vector: "(a,b,c)"
// use to_string(int) which returns the int as a string
// usage: string s = t.toString();
string Triple::toString()
{
   string string;
   string = "(" + to_string(this->a) + "," + to_string(this->b) + "," + to_string(this->c) + ")";
   return string;
}

// change the vector to equal the string representation: "(a,b,c)"
// this method has already been written for you
// usage: t.fromString("(1,2,3)");
void Triple::fromString(string s)
{
   istringstream ss(s); // c++ class version of sscanf() - ostringstream is like sprintf()
   char leftparen, comma1, comma2, rightparen;
   ss >> leftparen >> a >> comma1 >> b >> comma2 >> c >> rightparen;
}

// return the largest element value
// usage: int i = t.maxElement();
int Triple::maxElement()
{
   int max = 0;
   if (this->a >= this->b && this->a >= this->c)
   {
      max = this->a;
   }
   else if (this->b >= this->a && this->b >= this->c)
   {
      max = this->b;
   }
   else
   {
      max = this->c;
   }
   return max;
}

// return sum of the element values
// usage: int i = t.sum();
int Triple::sum()
{

   return this->a + this->b + this->c;
}

// return product of the element values
// usage: int i = t.product();
// example: int i = Triple(1,2,3).product(); // 1*2*3 = 6
int Triple::product()
{

   return this->a * this->b * this->c;
}

// add the vectors and return the new resulting vector
// usage: Triple t3 = t1 + t2;
// example: Triple t3 = Triple(1,2,3) + Triple(4,5,6); // t3 == (5,7,9)
Triple Triple::operator+(Triple t) const
{
   int val1 = this->a + t.a;
   int val2 = this->b + t.b;
   int val3 = this->c + t.c;
   return Triple(val1, val2, val3);
}

// add the "right hand side" vector to the local "left hand side" vector
// this function does not return anything because the left hand side is modified
// think about "int a = 1; a += 2;", nothing is returned from "+= 2", "a" is changed directly
// usage: t1 += t2;
void Triple::operator+=(Triple t)
{
   this->a += t.a;
   this->b += t.b;
   this->c += t.c;
}

// multiply vector elements by int value and return the new vector
// usage: Triple t2 = t1 * int;
// usage: Triple t2 = Triple(1,2,3) * 3; // t2 == (3,6,9)
Triple Triple::operator*(int k) const
{

   return Triple(a * k, b * k, c * k);
}

// multiply vector elements by int value
// this function does not return anything because the vector is modified
// usage: t *= int;
void Triple::operator*=(int k)
{
   this->a *= k;
   this->b *= k;
   this->c *= k;
}

// vector dot product
// usage: int i = t.dotProduct(t2);
// example int i = Triple(1,2,3).dotProduct( Triple(4,5,6) ); // i == (1*4 + 2*5 + 3*6) == 32
int Triple::dotProduct(Triple t)
{

   return (a * t.a + b * t.b + c * t.c);
}

// reverse the order of the vector elements and return the new vector
// usage: Triple t2 = t1.reverse();
// example: Triple t2 = Triple(1,2,3).reverse(); // t2 == (3,2,1)
Triple Triple::reverse() const
{

   return Triple(c, b, a);
}

// reverse the order of the vector elements
// usage: t.reverseInPlace();
void Triple::reverseInPlace()
{
   this->a = this->a + this->c;
   this->c = this->a - this->c;
   this->a = this->a - this->c;
}

// do both vectors contain the same values?
// usage: bool b = (t1 == t2);
bool Triple::operator==(Triple t)
{
   if ((t.a == this->a) && (t.b == this->b) && (t.c == this->c))
   {
      return true;
   }
   else
   {
      return false;
   }
}

// usage: bool b = (t1 != t2);
bool Triple::operator!=(Triple t)
{
   if ((t.a != this->a) || (t.b != this->b) || (t.c != this->c))
   {
      return true;
   }
   else
   {
      return false;
   }
}

// write the string representation of the vector to the stream
// the stream representation is "(a,b,c)"
// use toString()
// usage: cout << t << endl;
ostream &operator<<(ostream &os, Triple t)
{
   os << "(" << t.a << "," << t.b << "," << t.c << ")";
   return os;
}

// create a vector by reading from the stream
// the stream representation is "(a,b,c)"
// >> a char, then an int, then a ...
// usage: cin >> t;
istream &operator>>(istream &is, Triple &t)
{
   char c;
   is >> c >> t.a >> c >> t.b >> c >> t.c >> c;
   return is;
}
