#ifndef SPLINE_H
#define SPLINE_H

#include <map>
#include <list>
#include <string>

typedef enum {
  spline_cubic
} e_spline;

typedef std::pair< double, double > * spline_node_t;
typedef std::list < spline_node_t > spline_nodes_t;

class Spline {

 public:
  Spline();
  Spline(e_spline type);

  void add_node(double x, double y);
  spline_nodes_t get_nodes();

 private:
  e_spline mType;
  spline_nodes_t mNodes ;

};

#endif // SPLINE_H
