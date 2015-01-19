#ifndef SPLINE_H
#define SPLINE_H

#include <map>
#include <list>
#include <string>

typedef enum {
  spline_cubic
} e_spline;

typedef std::pair< double, double >  spline_node_t;
typedef std::list < spline_node_t* > spline_nodes_t;

class Spline {

 public:
  Spline();
  Spline(e_spline type);
  ~Spline();

  void add_node(double x, double y);
  void add_node(int x, int y);
  void add_node(int x, double y);
  void add_node(double x, int y);
  spline_nodes_t get_nodes();

 private:
  e_spline mType;
  spline_nodes_t mNodes ;

};

#endif // SPLINE_H
