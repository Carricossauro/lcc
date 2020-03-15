#include "logica.h"
#include "dados.h"

int jogar(ESTADO *e, COORDENADA c)
{
    if(obter_estado_casa(e, c))
    {
        mudar_casa(e, c);
        return 1;
    }
    else
    {
        return 0;
    }
}