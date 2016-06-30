/*
 * QuickRank - A C++ suite of Learning to Rank algorithms
 * Webpage: http://quickrank.isti.cnr.it/
 * Contact: quickrank@isti.cnr.it
 *
 * Unless explicitly acquired and licensed from Licensor under another
 * license, the contents of this file are subject to the Reciprocal Public
 * License ("RPL") Version 1.5, or subsequent versions as allowed by the RPL,
 * and You may not copy or use this file in either source code or executable
 * form, except in compliance with the terms and conditions of the RPL.
 *
 * All software distributed under the RPL is provided strictly on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND
 * LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the RPL for specific
 * language governing rights and limitations under the RPL.
 *
 * Contributors:
 *  - Andrea Battistini (andreabattistini@hotmail.com)
 *  - Chiara Pierucci (chiarapierucci14@gmail.com)
 *  - Claudio Lucchese (claudio.lucchese@isti.cnr.it)
 */
#ifndef QUICKRANK_LEARNING_LINE_SEARCH_H_
#define QUICKRANK_LEARNING_LINE_SEARCH_H_

#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <memory>

#include "data/dataset.h"
#include "metric/ir/metric.h"
#include "learning/ltr_algorithm.h"

namespace quickrank {
namespace learning {
namespace linear {

/// This implements the Line Search algorithm.
class LineSearch : public LTR_Algorithm {

 public:

  LineSearch(size_t num_points, double window_size,
             double reduction_factor, size_t max_iterations,
             size_t max_failed_vali, bool adaptive);

  LineSearch(const boost::property_tree::ptree &info_ptree,
             const boost::property_tree::ptree &model_ptree);

  virtual ~LineSearch();

  /// Returns the name of the ranker.
  virtual std::string name() const {
    return NAME_;
  }

  static const std::string NAME_;

  /// Executes the learning process.
  ///
  /// \param training_dataset The training dataset.
  /// \param validation_dataset The validation training dataset.
  /// \param metric The metric to be optimized.
  /// \param partial_save Allows to save a partial model every given number of iterations.
  /// \param model_filename The file where the model, and the partial models, are saved.
  virtual void learn(std::shared_ptr<data::Dataset> training_dataset,
                     std::shared_ptr<data::Dataset> validation_dataset,
                     std::shared_ptr<metric::ir::Metric> metric,
                     size_t partial_save,
                     const std::string model_filename);

  /// Returns the score of a given document.
  virtual Score score_document(const Feature* d) const;

  /// Returns the learned weights
  virtual std::vector<double> get_weigths() {
    return best_weights_;
  }

 private:
  size_t num_points_;
  double window_size_;
  double reduction_factor_;
  size_t max_iterations_;
  size_t max_failed_vali_;
  bool adaptive_;

  std::vector<double> best_weights_;

  /// The output stream operator.
  friend std::ostream& operator<<(std::ostream& os, const LineSearch& a) {
    return a.put(os);
  }

  /// Prints the description of Algorithm, including its parameters
  virtual std::ostream& put(std::ostream& os) const;

  /// Save the current model in the given output file stream.
  virtual std::ofstream& save_model_to_file(std::ofstream& of) const;

  virtual void preCompute(Feature *training_dataset, unsigned int num_samples,
                          unsigned int num_features, Score *pre_sum, double *weights,
                          Score *training_score, unsigned int feature_exclude);

  virtual void score(Feature *dataset, unsigned int num_samples,
             unsigned int num_features, double *weights, Score *scores);
};

}  // namespace linear
}  // namespace learning
}  // namespace quickrank

#endif
