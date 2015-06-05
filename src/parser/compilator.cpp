#include "grammar_yacc.h"
#include "compilator.h"

extern FILE* yyin;
extern void yyrestart(FILE*);

Compilator::Compilator(const char* filename) : QObject(), Parser() {
    inputFile = fopen(filename, "r");
    errorHappen = false;
}

Compilator::~Compilator() {
    if (inputFile != NULL){
        fclose(inputFile);
    }
}

void Compilator::compile() {
    if (inputFile == NULL){
        errorHappen = true;
        return;
    }

    errorHappen = false;
    flexrestart(inputFile);
    grammarparse(this);
    fclose(inputFile);
}

int Compilator::handleError(const char *msg,
                             int first_line, int first_column,
                             int last_line, int last_column) {
    errorHappen = true;
    emit parserError(QString(msg).append (" %1:%2 - %3:%4")
                .arg (first_line).arg(first_column)
                .arg(last_line).arg(last_column));
    return 0;
}

double safullyGetCoor(line_t *line, std::string coor, double *def) {
    double c = *def;
    line_t::iterator point_x = line->find(coor);
    if (point_x != line->end()) {
        if (point_x->second.getType() == value_types_number) {
            c = point_x->second.get_number();
        } else {
            spline_nodes_t::iterator it = point_x->second.get_spline()->get_nodes().end();
            it--;
            c = (*it)->second;
        }
        *def = c;
    }
    return c;
}

lines_t* Compilator::getLines() {
    double x = 0.0, y = 0.0, z = 0.0, f = 0.0, s = 0.0, p = 1.0;
    std::string key_x("x"), key_y("y"), key_z("z"), key_f("f"), key_s("s"),
            key_p("p");
    foreach(line_t *line, *result) {
        line->insert(variable(key_x, safullyGetCoor(line, key_x, &x)));
        line->insert(variable(key_y, safullyGetCoor(line, key_y, &y)));
        line->insert(variable(key_z, safullyGetCoor(line, key_z, &z)));
        line->insert(variable(key_f, safullyGetCoor(line, key_f, &f)));
        line->insert(variable(key_s, safullyGetCoor(line, key_s, &s)));
        line->insert(variable(key_p, safullyGetCoor(line, key_p, &p)));
    }

    return result;
}

bool Compilator::isErrorHappen() {
    return errorHappen;
}
