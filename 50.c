//1 maior elemento
int maxElement(){
    int n,max=0;
    while(n != 0){
        scanf("%d", &n);
        if(n > max) max = n;
    }
    return max;
}

//2 media da sequencia
float mediaSeq(){
    int n=1, i=0;
    float media=0;
    while(n != 0){
        scanf("%d", &n);
        media += n;
        i++;
    }
    media = media/i;
    return media;
}

//3 segundoMaior
int segundoMaior(){
    int n=1, max=0,max2=0;
    while(n != 0){
        scanf("%d", &n);
        if(n >= max){
            max2 = max;
            max = n;
        }
        else if(n > max2 && n < max){
            max2 = n;
        }
    }
    return max2;
}

//4 quantos bits 'um' têm o valor decimal
int bitsUm(unsigned int n){
    int uns=0;
    while(n > 0){
        if(n % 2 == 1) uns++;
        n = n/2;
    }
}

//5 quantos bits 'zero' têm o valor decimal
int trailingZ(unsigned int n){
    int zeros = 0;
     while(n > 0){
        if(n % 2 == 0) zeros++;
        n = n/2;
    }   
}


//6 calcula quantos digitos são necessários para por um número em decimal < 1
int qDig(unsigned int n){
  int x = 10,i=0;
  for(i; n > 1; i++){
      n = n / 10;
  }
  printf("%d\n", i);
  return i;
}


//7 adicionar a segunda string ao fim da primeira
char *strcat(char s1[], char s2[]){
    int i,j;
    for(i=0; s1[i] != '\0'; i++);
    for(j=i; s2[i] != '\0'; j++,i++){
        s1[i] = s2[j];
    }
    return s1;
}

//8 copiar a segunda string para a primeira
char *strcpy(char *dest, char *source){
    int i;
    for( i=0; source[i] != '\0'; i++){
        dest[i] = source[i];
    }
    dest[i] = '\0';
}

//9 comparar 2 strings
int strcmp(char s1[], char s2[]){
    int i;
    for(i=0; s1[i] != '\0' && s2[i] != '\0'; i++){
        if(s1[i] != s2[i]) return s1[i] - s2[i];
    }
    return s1[i] - s2[i];
}

//10 que determina em que posição a string 2 ocorre na string 1
char *strstr(char s1[], char s2[]){
  int i,j,k;
  if (s2[0] == '\0') return s1;
  for(i=0; s1[i] != '\0'; i++){
    for(j=i,k=0; s2[k] != '\0' && s1[j] == s2[k]; j++,k++);
    if(k == strlen(s2)) return s1+i;
  }
    return NULL;
}

//11 reverter a string
void strrev(char s[]){
  int i,j;
  for(i=0,j=strlen(s)-1; i<j; i++,j--){
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
  }
}

//12 retira todas as vogais da string
void strnoV (char t[]){
    int i, pos;
    for (i = 0, pos = 0; t[i] != '\0';i++) {
        if (t[i] != 'a' && t[i] != 'e' && t[i] != 'i' && t[i] != 'o' && t[i] != 'u' && t[i] != 'A' && t[i] != 'E' &&t[i] != 'I' &&t[i] != 'O' &&t[i] != 'U') {
			t[pos++] = t[i];
		}
    }
    t[pos] = '\0';
}

//13 trunca as palavras, cada palavra só tem n caracteres
void truncW(char t[], int n){
  int i,j;
  for(i=0; t[i] != '\0'; i++){
    if(i >= n){
      t[i] = '\0';
      break;
    }
  }
}

//14 verificar o char mais frequente
char charMaisFreq(char s[]){
  int i,j,k,maisFreq=0,freq=0,pos=0;
  for(i=0; s[i] != '\0'; i++){
    for(j=i,k=0; s[j] != '\0'; j++,k++){
      if(s[i] == s[j]){
        freq++;
      }
    }
    if(freq > maisFreq){
      maisFreq = freq;
      pos = i;
    }
    freq = 0;
  }
  return s[pos];
}

//14
char charMaisFreq(char s[])
{
    char a, mf;
    int count,max=0;
    for(int i=0; s[i] != '\0';i++){
        count = 0;
        a = s[i];
        for(int j=i+1; s[j] != '\0'; j++){
            if(a == s[j]){
                count++;
            }
        }
        if (max < count){
            mf = a;
            max = count;
        }
    }
    return mf;
}

//15 quantos digitos iguais consecutivos existem
int iguaisConsecutivos(char s[])
{
    char a, mf;
    int count,max=0;
    for(int i=0; s[i] != '\0';i++){
        count = 0;
        a = s[i];
        for(int j=i+1; s[j] != '\0'; j++){
            if(a == s[j]){
                count++;
            }
            else {
                j = strlen(s);
            }
        }
        if (max < count){
            mf = a;
            max = count;
        }
    }
    return max;
}


//16 (hard) (Sofia solution) qual é o máximo de chars diferentes consecutivos
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

//17 maior prefixo entre 2 strings da frente pra trás
int maiorPrefixo(char s1[],char s2[]){
    int i,j,k;
    for(i=0;s1[i]!='\0';i++);
    for(j=0;s2[j]!='\0';j++);
    for(k=0;s1[k]==s2[k]&&k < i;k++);
    return k;
}

//18 maior sufixo entre 2 strings , de trás pra frente
int maiorSufixo(char s1[],char s2[]){
    int i, j, ans = -1;
    for(i = 0; s1[i]; i++);
    for(j = 0; s2[j]; j++);
    while(s1[i--] == s2[j--]) ans++;
    return ans;
}

//19 maior sufixo de s1 que é prefixo de s2
int sufPref(char s1[], char s2[]){
    int ans = 0, i, j = 0;
    for(i = 0; s1[i]; i++) {
        if(s1[i] == s2[j++]) ans++;
        else ans = j = 0;
    }
    return ans;
}

//20 conta as palavras de uma string
int contaPal(char s[]){
    int word = 0, total = 0;
    for(int i = 0; s[i]; i++) {
        if(s[i] == ' ' || s[i] == '\n') {
            if(word) total++;
            word = 0;
        }
        else word = 1;
    }
    if(word) total++;
    return total;
}

//21 conta vogais de uma string
int contaVogais(char s[]){
    int i,count = 0;
    for(i =0 ; s[i] != '\0'; i++){
        if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U'){
            count++;
        }
    }
    return count;
}

//22 testa se todos os chars da 1 string aparecem na 2 string
int contida(char s1[],char s2[]){
    int i,j;
    for(i=0;s1[i]!='\0';i++){
        for(j=0;s2[j]!='\0';j++){
            if(s1[i]==s2[j]){
                break;
            }
        }
        if(s2[j]=='\0'){
            return 0;
        }
    }
    return 1;
}

//23 ver se é palindrome word , ou seja se dá para ler de trás pra frente
int palindrome(char s[]){
    int i, j;
    for(i = 0, j = strlen(s)-1; i < j; i++, j--)
        if(s[i] != s[j]) return 0;
    return 1;
}

//24 elimina da string todos os chars repetidos
int remRep(char x[]){
    int i, j;
    for (i = 0, j = 0; x[i] != '\0'; i++) {
        if (x[i] != x[i+1]) {
        x[j] = x[i];
        j++;
        }
    }
    x[j] = '\0';
    return j;
}

//25 retira os espaços de uma string
int limpaEspacos(char t[]){
    int i, j;
    for(i = 0, j = 0; t[i] != '\0'; i++){
        if(t[i] != ' ' || (t[i] == ' ' && t[i+1] != ' ')){
        t[j] = t[i];
        j++;
        }
    }
    t[j] = '\0';
    return j;
}

//26 inserir um elemento x num array ordenado
void insert(int v[],int N, int x){
    for(int i = 0; i < N; i++) {
        if(v[i] > x) {
            for(int j = N; j > i; j--) {
                v[j] = v[j - 1];
            }
            v[i] = x;
            break;
        }
        if(i == N - 1) {
            v[N] = x;
        }
    }
}

//27 dá 2 vetores ordenados e temos que preencher um vetor r ordenado com 'a' e 'b'
void merge (int r [], int a[], int b[], int na, int nb) {
    int i = 0, j = 0, k = 0;
    while(k < na + nb) {
        if((a[i] < b[j] && i < na) || j >= nb)
            r[k++] = a[i++];
        else
            r[k++] = b[j++];
    }
}

//28 testa se tá ordenado
int crescente(int a[],int i,int j){
    for(int k = i; k < j; k++) {
        if(a[k] > a[k+1]) {
            return 0;
        }
    }
    return 1;
}

//29 retira os valores negativos do array
int retiraNeg (int v[],int N){
    int i, j;
    for(i = 0, j = 0; i < N; i++) {
        if(v[i] >= 0) {
            v[j] = v[i];
            j++;
        }
    }
    return j;
}


//30  que verifica o char menos frequente
int menosFreq (int v[], int N) {
    int freq = 1, minFreq = N, ans = v[0], i;
    for(i = 1; i < N; i++) {
        if(v[i] == v[i - 1]) freq++;
        if(v[i] != v[i - 1]) {
            if(freq < minFreq) {
                minFreq = freq;
                ans = v[i - 1];
            }
            freq = 1;
        }
    }
    if(freq < minFreq) {
        minFreq = freq;
        ans = v[i - 1];
    }
    return ans;
}

//31 que verifica o char mais frequente
int maisFreq (int v[], int N){
    int i, j, maior = 0, freq = 0, aux = 0;
    for(i = 0; i < N; i++){
        for(j = i; j < N; j++){
        if(v[i] == v[j]){
            aux++;
        }
        }
        if(aux > freq){
        freq = aux;
        maior = v[i];
        }
        aux = 0;
    }
    return maior;
}


//32 maior sequência ordenada seguida
int maxCresc (int v[], int N){
    int i, j, max = 0, aux = 0;
    for(i=0; i < N; i++){
        aux =0;
        for(j=i; j < N; j++){
            if(v[j] < v[j+1]){
                aux++;
            }
        }
        if (max < aux){
            max = aux;
        }
    }
    return max;
}



//33 elimina os inteiros repetidos do array
int elimRep(int v[],int n){
    int i,j,k;
    for(i=0; i<n; i++){
        for(j=i+1; j<n; j++){
        if(v[i] == v[j]){
            for(k=j; k<n; k++){
            v[k] = v[k+1];
            }
            n--;
            j--;
        }
        }
    }
    return n;
}

//34 mesma coisa que o de cima
int elimRepOrd (int v[], int n){
    int i,j,k;
    for(i=0; i<n; i++){
        for(j=i+1; j<n; j++){
        if(v[i] == v[j]){
            for(k=j; k<n; k++){
            v[k] = v[k+1];
            }
            n--;
            j--;
        }
        }
    }
    return n;
}

//35 calcula quantos elementos a e b têm em comum
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

//36 mesma coisa que o 35 só que não tá ordenado
int comuns (int a[], int na, int b[], int nb) {
    int ans = 0;
    for(int i = 0; i < na; i++) {
        for(int j = 0; j < nb; j++) {
            if(a[i] == b[j]){
                ans++;
            }
        }
    }
    return ans;
}

//37 retorna o menor indice 
int minInd(int v[],int n){
    int min=v[0];
    int ind=0;
    for(int i=1; i < n;i++){
        if(v[i] < min){
            min = v[i];
            ind = i;
        }
    }
    return ind;
}

//38 preenche o vetor Ac com a soma dos elementos no vetor v
// Ac[3] = v[3] + v[2] + v[1] + v[0]
void somasAc(int v[], int Ac[], int N){
    int i;
    for(int j=0; j < N; j++){
        Ac[j] = 0;
    }
    for(i=0; i < N; i++){
        for(int j=0; j <= i; j++){
            Ac[i] += v[j];
        }
    }
    for(int i=0; i < N; i++){
        printf("%d ", Ac[i]);
    }
}

//39 testa se uma matriz é triangulo superior
int triSup (int N, float m [N][N]){
    int i,j;
    for(i=0; i < N; i++){
        for(j=0; j < N; j++){
        if(i > j && m[i][j] != 0){
            return 0;
        }
        }
    }
    return 1;
}

//40 calcula a transposta
void transposta (int N, float m[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < i; j++) {
            float temp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = temp;
        }
    }
}

//41 (not sure)
void addTo(int N, int M, int A[N][M], int B[N][M]){
    for(int i=0; i< N ; i++){
        for(int j=0; j < M ; j++){
            A[i][j] += B[i][j];
        }
    }
}

// 42
int unionSet (int N, int v1[N], int v2[N], int r[N]) {
    int count = 0;
    for(int i = 0; i < N; i++) {
        r[i] = v1[i] || v2[i];
        count += r[i];
    }
    return count;
}

// 43
int intersectSet (int N, int v1[N], int v2[N],int r[N]) {
    int count = 0;
    for(int i = 0; i < N; i++) {
        r[i] = v1[i] && v2[i];
        count += r[i];
    }
    return count;
}

// 44
int intersectMSet (int N, int v1[N], int v2[N],int r[N]) {
    int count = 0;
    for(int i = 0; i < N; i++) {
        if( v1[i] < v2[i]){
            r[i] = v1[i];
        }
        else {
            r[i] = v2[i];
        }
        count += r[i]; 
    }
    return count;
}

// 45
int unionMSet (int N, int v1[N], int v2[N], int r[N]) {
    int count = 0;
    for(int i = 0; i < N; i++) {
        r[i] = v1[i] + v2[i];
        count += r[i]; 
    }
    return count;
}

// 46
int cardinalMSet (int N, int v[N]) {
    int count = 0;
    for(int i = 0; i < N; i++) {
        count += v[i];
    }
    return count;
}

// Definições para representar as posições e movimentos de um robot
typedef enum movimento {Norte, Oeste, Sul, Este} Movimento;
typedef struct posicao {
    int x, y;
} Posicao;

//47
Posicao posFinal (Posicao inicial, Movimento mov[], int N){
    int i= 0;
    for(; i< N; i++){
        if(mov[i]== Norte) inicial.y++;
        if(mov[i]== Sul) inicial.y--;
        if(mov[i]==Este) inicial.x++;
        if(mov[i]== Oeste) inicial.x--;
    }
    return inicial;
}

//48
int caminho (Posicao inicial, Posicao final, Movimento mov[], int N){
    int i= 0;
    for(; i< N; i++){
        if(final.y< inicial.y){
            mov[i]= Sul; inicial.y--;
        }
        else if(final.y> inicial.y){
            mov[i]= Norte; inicial.y++;
        }
        else break;
    }
    int j= i;
    for(; j< N; j++){
        if(final.x< inicial.x){
            mov[j]= Oeste;
            inicial.x--;
        }
        else if(final.x> inicial.x){
            mov[j]= Este;
            inicial.x++;
        }
        else break;
    }
    if(inicial.x!= final.x || inicial.y!= final.y) return -1;
    else return j;
}

//49 (em processo)



//50
int vizinhos (Posicao p, Posicao pos[], int N){
    int i= 0, count= 0;
    for(; i< N; i++){
        if((pos[i].x+1 == p.x && pos[i].y == p.y) || (pos[i].x-1 == p.x && pos[i].y== p.y) || (pos[i].y +1== p.y && pos[i].x== p.x) || (pos[i].y- 1== p.y && pos[i].x== p.x)) count++;
    }
    return count;
}
