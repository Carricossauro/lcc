//1 (n é o número de elementos da lista)
int maiorSeq(int n){
    int lista[n];
    int max = 0, i;
    for (i=0; i < n; i++){
        int numero; printf("Número %d:",i); scanf("%d",&numero);
        lista[i] = numero;
        if (numero > max){
            max = numero;
        }
    }
    printf("%d\n",max);
    return max;
}
//2 (n é o número de elementos da lista)
int sMaiorSeq(int n){
   int lista[n];
   int valortotal = 0;
   float media;
   for (int i =0 ; i < n; i++){
       int numero; printf("Número %d:",i); scanf("%d",&numero);
       valortotal += numero;
       lista[i] = numero;
   }    
   media = valortotal / n + (valortotal % n)*0.1;
   return media;
}


// 3 (n é o número de elementos da lista)
int sMaiorSeq(int n){
   int lista[n];
   int max = 0, max2 = 0;
   for (int i =0 ; i < n; i++){
       int numero; printf("Número %d:",i); scanf("%d",&numero);
       if (numero > max2 && numero >= max){
           max2 = max;
           max = numero;
       }
       else if(numero > max2 && numero < max){
           max2 = numero;
       }
       lista[i] = numero;
   }    
   return max2;
}

//4
int bitsUm(unsigned int n){
    int um=0;
    for(int i = n; i > 0 ; i /= 2){
            if(i % 2 == 1) um++;
    }
    return um;
}

//5 
int trailingZ(unsigned int n){
    int zero=0;
    for(int i = n; i > 0 ; i /= 2){
            if(i % 2 == 0) zero++;
    }
    return zero;
}
/ 5

int trailingZ (unsigned int n) {
    if(n % 2) return 0;
    else return 1 + trailingZ(n >> 1);
}

// 6

int qDig (unsigned int n) {
    if(n / 10 < 1) return 1;
    else return 1 + qDig(n / 10);
}

// 7

char* mystrcat(char s1[], char s2[]) {
    char* cat = s1;
    while(*s1) s1++;
    while((*s1 = *s2)) {s1++; s2++;}
    *s1 = '\0';
    return cat;
}

// 8

char* mystrcpy(char* dest, char source[]) {
    char* result = dest;
    while((*dest = *source)) { source++; dest++; }
    return result;
}

// 9

int mystrcmp(char s1[], char s2[]) {
    while(*s1 == *s2 && *s1) { s1++; s2++; }
    return *s1 - *s2;
}
}

// 13

void truncW (char t[], int n) {
    int wordLen = 0;
    while(*t) {
        if(*t == ' ' || *t == '\n' || *t == '\t') {t++; wordLen = 0;}
        else {
            if(wordLen++ >= n) tail(t);
            else t++;
        }
    } 
}

// 14

int freqC(char ch, char s[]) {
    int freq = 0;
    for(int i = 0; s[i]; i++) {
        if(s[i] == ch) freq++;
    }
    return freq;
}

char charMaisFreq(char s[]) {
    char maisFreq = 0;
    int freqMax = 0, freq;
    for(int i = 0; s[i]; i++) {
        if((freq = freqC(s[i],s)) > freqMax) {
            freqMax = freq;
            maisFreq = s[i];
        }
    }
    return maisFreq;
}

// 15

int iguaisConsecutivos (char s[]) {
    int consec = 1, max = 0;
    for(int i = 0; s[i]; i++) {
        if(s[i] == s[i + 1]) consec++;
        else {
            if(consec > max) max = consec;
            consec = 1;
        }
    }
    return max;
}

int difConsecutivos(char s[]) {
    int ans = 0;
    for(size_t i = 0; s[i]; i++) {
        int consec = 0;
        for(size_t j = i; s[j]; j++) {
            if(not_in_prev(s,i,j)) consec++;
            else break;
        }
        if (consec > ans) ans = consec;
    }
    return ans;
}

// 17

int maiorPrefixo (char s1 [], char s2 []) {
    int i;
    for(i = 0; s1[i] == s2[i] && s1[i]; i++);
    return i;
}

// 18

int maiorSufixo (char s1 [], char s2 []) {
    int i, j, ans = -1;
    for(i = 0; s1[i]; i++);
    for(j = 0; s2[j]; j++);
    while(s1[i--] == s2[j--]) ans++;
    return ans;
}

// 19

int sufPref (char s1[], char s2[]) {
    int ans = 0, i, j = 0;
    for(i = 0; s1[i]; i++) {
        if(s1[i] == s2[j++]) ans++;
        else ans = j = 0;
    }
    return ans;
}

// 20

int contaPal (char s[]) {
    int inWord = 0, total = 0;
    for(int i = 0; s[i]; i++) {
        if(s[i] == ' ' || s[i] == '\n') {
            if(inWord) total++;
            inWord = 0;
        }
        else inWord = 1;
    }
    if(inWord) total++;
    return total;
}

//21

int contaVogais (char s[]) {
    int total = 0;
    for(int i = 0; s[i]; i++) {
        switch(s[i]) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
            case 'A': case 'E': case 'I': case 'O': case 'U':
                total++;
        }
    }
    return total;
}

// 34

int elimRepOrd (int v[], int n) {return elimRep(v,n);}

// 35

int comunsOrd (int a[], int na, int b[], int nb) {
    int i = 0, j = 0, ans = 0;
    while(i < na && j < nb) {
        if(a[i++] == b[j++]) {
            ans++;
            i++;
            j++;
        }
        else if(a[i] > b[j]) j++;
        else i++;
    }
    return ans;
}

// 36

int comuns (int a[], int na, int b[], int nb) {
    int ans = 0;
    for(int i = 0; i < na; i++) {
        int belongs = 0;
        for(int j = 0; j < nb; j++) if(a[i] == b[j]) belongs = 1;
        if(belongs) ans++;
    }
    return ans;
}

// 37

int minInd (int v[], int n) {
    int minIndex = 0;
    for(int i = 1; i < n; i++) 
        if(v[i] < v[minIndex]) 
            minIndex = i;
    return minIndex;
}

// 38

void somasAc (int v[], int Ac [], int N) {
    for(int i = 0; i < N; i++) {
        Ac[i] = 0;
        for(int j = 0; j <= i; j++) {
            Ac[i] += v[j];
        }
    }
}

// 39

int triSup (int N, float m [N][N]) {
    int x = 1;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < i; j++) {
            if(m[i][j]) x = 0;
        }
    }
    return x;
}

// 40

void transposta (int N, float m[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < i; j++) {
            float temp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = temp;
        }
    }
}