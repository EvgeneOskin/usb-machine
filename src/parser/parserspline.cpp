#include "parserspline.hpp"
#include <iostream>

Spline::Spline() : mType(spline_cubic) {}
Spline::Spline(e_spline type) : mType(type) {}

Spline::~Spline() {
  std::cout << "Called destructor\n";
  for (spline_nodes_t::iterator i = this->mNodes.begin();
       i != this->mNodes.end();
       ++i) {
    std::cout << "Destroy " << (*i)->first;
    delete *i;
  }
}

spline_nodes_t Spline::get_nodes() {
  return this->mNodes;
}

void Spline::add_node(double x, double y) {
  this->mNodes.push_back(new spline_node_t(x, y));
}

void Spline::add_node(int x, int y) {
  add_node((double) x, (double) y);
}

void Spline::add_node(int x, double y) {
  add_node((double) x, y);
}

void Spline::add_node(double x, int y) {
  add_node(x, (double) y);
}
