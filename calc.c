#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

int elem;
double element;

int next() {
	for (;;) {
		int c = getchar();
		if (c == EOF || strchr("+-*/^()\n", c) != NULL)
            return elem = c;
		if (isspace(c))
            continue;
		if (isdigit(c) || c == '.') {
			ungetc(c, stdin);
			scanf(" %lf", &element);
			return elem = 'n';
		}
		fprintf(stderr, "Incorrect enter, string contains: %c\n", c); abort();
	}
}

void skip(int t) { assert(elem == t); next(); }

double expr();

// numpar ::= number | '(' expr ')'
double numpar() {
	if (elem == 'n') { double x = element; skip('n'); return x; }
	skip('('); double x = expr(); skip(')'); return x;
}

// factor ::= numpar | numpar '^' factor
double factor() {
	double x = numpar();
	if (elem == '^') { skip('^'); x = pow(x, factor()); }
	return x;
}

// term ::= factor | term '*' factor | term '/' factor
double term() {
	double x = factor();
	for (;;) {
		if (elem == '*') { skip('*'); x *= factor(); }
		else if (elem == '/') { skip('/'); x /= factor(); }
		else return x;
	}
}

// expr ::= term | expr '+' term | expr '-' term
double expr() {
	double x = term();
	for (;;) {
		if (elem == '+') { skip('+'); x += term(); }
		else if (elem == '-') { skip('-'); x -= term(); }
		else return x;
	}
}

int main() {
   	next();
	while (elem != EOF) {
		if (elem == '\n') { skip('\n'); continue; }
		printf("%.9g\n", expr());
	}
	return 0;
}
