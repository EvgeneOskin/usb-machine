#include "spline.h"

Spline::Spline() : mType(spline_cubic) {}
Spline::Spline(e_spline type) : mType(type) {}

Spline::~Spline(){
  for (spine_nodes_t::iterator i = this->mNodes.begin();
       i != this->nodes.end();
       ++i) {
    delete *i;
  }
}

spline_nodes_t Spline::get_nodes() {
  return this->mNodes;
}

void Spline::add_nodes(double x, double y) {
  this->mNodes.push(new spline_node_t(x, y));
}
