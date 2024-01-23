#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARTAS_TOTAL 52
#define CARTA_valors 13
#define MAX_BARAJA 10

// Representación de las__ cartas
char *valors[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *tipos[] = {"Corazones", "Diamantes", "Picas", "Treboles"};

// Estructura para una carta.
struct carta {
    char *valor;
    char *tipo;
    int valorNumerico;
};

struct carta baraja[CARTAS_TOTAL];
struct carta barajaJugador[MAX_BARAJA];
int numeroCartasJugador = 0;
int sumaJugador = 0;
char elegir;

//void inicializarbaraja() {

//}

//void mezclarbaraja() {
//
//}

void mostrarCarta(struct carta c) {
    printf("  %s de %s\n", c.valor, c.tipo);

}

int sumaBaraja(struct carta baraja[], int numeroCartas) {
    int sum = 0;
    for (int i = 0; i < numeroCartas; i++) {
        sum += baraja[i].valorNumerico;
    }
    return sum;
}

int main() {
    for (int i = 0; i < CARTAS_TOTAL; i++) {
    baraja[i].valor = valors[i % CARTA_valors];
    baraja[i].tipo = tipos[i / CARTA_valors];
    baraja[i].valorNumerico = (i % CARTA_valors) + 2;
    if (baraja[i].valorNumerico > 10) baraja[i].valorNumerico = 10;
    if (i % CARTA_valors == CARTA_valors - 1) baraja[i].valorNumerico = 11;
};
    srand(time(NULL));
    for (int i = 0; i < CARTAS_TOTAL; i++) {
        int j = rand() % CARTAS_TOTAL;
        struct carta temp = baraja[i];
        baraja[i] = baraja[j];
        baraja[j] = temp;
    }

    printf("Bienvenido al Blackjack!\n");

    barajaJugador[numeroCartasJugador++] = baraja[0];
    barajaJugador[numeroCartasJugador++] = baraja[1];
    sumaJugador = sumaBaraja(barajaJugador, numeroCartasJugador);

    printf("Tus cartas:\n");
    mostrarCarta(barajaJugador[0]);
    mostrarCarta(barajaJugador[1]);
    printf("Suma total: %d\n", sumaJugador);

    while (sumaJugador < 21) {
        printf("Quieres otra carta? (s/n): ");
        scanf(" %c", &elegir);

        if (elegir == 's' || elegir == 'S') {
             barajaJugador[numeroCartasJugador] = baraja[numeroCartasJugador + 1];
            sumaJugador = sumaBaraja(barajaJugador, ++numeroCartasJugador);

            printf("Nueva carta:\n");
            mostrarCarta(barajaJugador[numeroCartasJugador - 1]);
            printf("Suma total: %d\n", sumaJugador);
        } else {
            break;
        }
    }

    if (sumaJugador == 21) {
        printf("Blackjack! Has ganado.\n");
    } else if (sumaJugador > 21) {
        printf("Te has pasado. Fin del juego.\n");
    } else {
        printf("Te has plantado con %d. Fin del juego.\n", sumaJugador);
    }

    return 0;
}
