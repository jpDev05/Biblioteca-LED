#include "LED.h"





Led::Led(uint8_t pin) : pino(pin),
                        estado(LOW),
                        apagarNoTempo(false),
                        apagarNoMomento(false),
                        estadoPiscar(false),
                        tempoEspera(0),
                        tempoAnteriorPisca(0),
                        repeticoes(0)
{
    pinMode(pino, OUTPUT);
}




void Led::acender()
{
    estado = HIGH;
    apagarNoTempo = false;
    estadoPiscar = false;
}

void Led::acender(uint32_t tempoLigado)
{
    estado = HIGH;
    apagarNoTempo = true;
    apagarNoMomento = millis() + tempoLigado;
    estadoPiscar = false;
}

void Led::apagar()
{
    estado = LOW;
    digitalWrite(pino, estado);
    apagarNoTempo = false;
    estadoPiscar = false;
}

void Led::piscar()
{
    estadoPiscar = true;
    tempoAnteriorPisca = millis(); // intervalo de 500ms
    estado = HIGH;
    tempoEspera = 500;
    apagarNoTempo = false;
    repeticoes = -1;
}

void Led::piscar(float freq)
{
    if(freq == 0)
    {
        return;
    }
    estadoPiscar = true;
    tempoAnteriorPisca = millis(); // intervalo de 500ms
    estado = HIGH;
    tempoEspera = (1000.0f / (2.0f * freq));
    apagarNoTempo = false;
    repeticoes = -1;
}

void Led::piscar(float freq, uint16_t repeticoes)
{
    if(freq == 0)
    {
        return;
    }
    estadoPiscar = true;
    tempoAnteriorPisca = millis(); // intervalo de 500ms
    estado = HIGH;
    tempoEspera = (1000.0f / (2.0f * freq));
    this->repeticoes = repeticoes * 2;
    apagarNoTempo = false;
}

void Led::alternar()
{
    estado = !estado;
    apagarNoTempo = false;
    estadoPiscar = false;
}

void Led::setEstado(bool estado)
{
    this->estado = estado;
    apagarNoTempo = false;
    estadoPiscar = false;
}

uint8_t Led::getPino()
{

    return pino;
    apagarNoTempo = false;
    estadoPiscar = false;
}

void Led::update()
{
    if (apagarNoTempo)
    {
        funcaoApagarNoTempo();
    }

    if (estadoPiscar)
    {
        funcaoPiscar();
    }

    digitalWrite(pino, estado);
}

void Led::funcaoApagarNoTempo()
{
    if (millis() >= apagarNoMomento)
    {
        estado = LOW; // alterna entre HIGH e LOW
        apagarNoTempo = false;
    }
}

void Led::funcaoPiscar()
{
    if (millis() - tempoAnteriorPisca >= tempoEspera)
    {
        estado = !estado;
        tempoAnteriorPisca = millis();
        if (repeticoes > 0)
        {
            repeticoes--;
            if (repeticoes == 0)
            {
                estadoPiscar = false;
                estado = LOW;
            }
        }
    }
}

//Author: João Pedro de Oliveira.
//Date: 2026-06-10
//Biblioteca led, que permite controlar um led de forma simples e intuitiva. A biblioteca oferece funcionalidades para acender, apagar, piscar e alternar o estado do led, além de permitir a configuração de tempo e frequência de piscar.
