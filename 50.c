int ex1() {
	int p;
	scanf("%d", &p);
	int max = p;
	while(p != 0) {
		scanf("%d", &p);
		if (p > max)
			max = p;
	}
	printf("%d", max);
	return max;
}

int ex2() { //Vou imprimir a média em int porque não especifica
	int numElementos = 1, x, soma;
	scanf("%d", &soma);
	x = soma;
	while(x != 0) {
		scanf("%d", &x);
		if (x != 0) {
			soma += x;
			numElementos++;
		}
	}
	int media = soma/numElementos;
	printf("%d", media);
	return media;
}

int ex3() {
	int maior, sMaior;
	int x;
	scanf("%d", &x);
	maior = x;
	scanf("%d", &x);
	if (x > maior) {
		sMaior = maior;
		maior = x;
	} else sMaior = x;
	while(x != 0) {
		scanf("%d", &x);
		if (x!= 0 && x > sMaior) {
			if (x > maior) {
				sMaior = maior;
				maior = x;
			} else sMaior = x;
		}
	}
	printf("%d", sMaior);
	return sMaior;
}

// Ex 4
int bitsUm(unsigned int n) {
	int i, uns = 0;
	for(i = n; i > 0; i/=2) {
		if (i % 2 == 1) uns++;
	}
	return uns;
}

//Ex 5
//unsigned int mas o codeboard use valores negativos para testar lol
int trailingZ(unsigned int n) {
	int i, zeros = 0;
	for(i = n; i > 0; i/=2)
		if (i % 2 == 0) zeros++;
	return zeros;
}

//Ex 6
int qDig(unsigned int n) {
	int i,x = 0, resto = 1;
	for(i = 1; resto != n; i*=10) {
		resto = n % i;
		if (resto != n)
			x++;
	}
	return x;
}

//Ex 7
char *mystrcat(char s1[], char s2[]) {
	int p,i;
	for(p = 0; s1[p] != '\0'; p++); //p final tem s1[p] == '\0'
	for (i = 0; s2[i] != '\0';i++,p++)
		s1[p] = s2[i];
	s1[p] = '\0';
	return s1;
}

//Ex 8
char *mystrcpy(char *dest, char source[]) {
	int i = 0;
	for(i = 0; source[i] != '\0'; i++)
		dest[i] = source[i];
	dest[i] = '\0';
	return dest;
}

//Ex 9
int mystrcmp(char s1[], char s2[]) {
	int i;
	for(i = 0; s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]; i++);
	return s1[i]-s2[i];
}

//Ex 10
char *mystrstr(char s1[], char s2[]) {
    char *res = NULL;
    int i,p;
    if (s2[0] == '\0') return s1;
    for(i = 0; s1[i] != '\0' && res == NULL; i++) {
        for(p = 0; s2[p] != '\0' && s2[p] == s1[i+p];p++);
        if (s2[p] == '\0')
            res = s1 + i;
    }
    return res;
}