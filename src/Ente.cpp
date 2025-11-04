#include "../include/Ente.h"

Gerenciadores::GerenciadorGrafico* Ent::pGG = Gerenciadores::GerenciadorGrafico::get_instance();

Ent::Ent() : id()
{

}

Ent::~Ent()
{
}