#include "interface.h"
#include "dados.h"

int main() {
    ESTADO *e = inicializar_estado();
    interpretador(e);
    return 0;
}
