#include "interface.h"
#include "dados.h"

int main() {
    ESTADO *e = inicializar_estado();
    while (interpretador(e));
    return 0;
}
