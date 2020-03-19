#include "logica.h"
#include "dados.h"

int jogar(ESTADO *e, COORDENADA c)
{
    if(casa_esta_livre(e, c))
    {
        mudar_casa(e, c);
        return 1;
    }
    else
    {
        return 0;
    }
}

