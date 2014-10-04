#ifndef QUICKRANK_METRIC_METRICSCORER_H_
#define QUICKRANK_METRIC_METRICSCORER_H_

#include "learning/dpset.h"
#include "utils/symmatrix.h" // symetric matrix

#include "types.h"

#include <iostream>

typedef SymMatrix<double> fsymmatrix;

class DeprecatedMetric {
 protected:
  unsigned int k;

 public:
  virtual ~DeprecatedMetric() {}
  void set_k(const unsigned int _k) { k = _k; }
  unsigned int get_k() const { return k; }

  virtual const char *whoami() const = 0;

  virtual double compute_score(const qlist &ql) = 0;

  virtual fsymmatrix *swap_change(const qlist &ql) = 0;

  virtual void showme() { printf("\tscorer type = %s@%u\n", whoami(), k); };

  // Metric

};


#endif
