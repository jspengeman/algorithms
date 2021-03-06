#include <iostream>
#include <string>
#include "List.cpp"

using namespace std;

int main(){
	LinkedList<char> *list = new LinkedList<char>;
	// Invalid strings
	string a = "9ab";
	string b = "a9b"; 
	string c = "a=+b"; 
	string d = "a=123 456 + 12";
	string e = "a=2  ^  b";
	string f = "a= 12 + 1 B";

	// Valid strings
	string g = "a = 10002000 + 10001000";
	string h = "b = 1000";

	Calculator *calc = new Calculator;
	calc->viewEquations();
	// calc->validateEquation(a);
	// calc->validateEquation(b);
	// calc->validateEquation(c);
	// calc->validateEquation(d);
	// calc->validateEquation(e);
	// calc->validateEquation(f);

	// calc->validateEquation(g);
	calc->validateEquation(h);

	return 0;
}