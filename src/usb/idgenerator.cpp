#include "idgenerator.h"

IdGenerator::IdGenerator() : id(0) { }

IdGenerator::~IdGenerator() { }

uint16_t IdGenerator::generate(){
    return id++;
}
