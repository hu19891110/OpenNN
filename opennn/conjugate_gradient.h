/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   C O N J U G A T E   G R A D I E N T   C L A S S   H E A D E R                                              */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __CONJUGATEGRADIENT_H__
#define __CONJUGATEGRADIENT_H__

// System inlcludes

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <climits>
#include <cmath>
#include <ctime>

// OpenNN includes

#include "performance_functional.h"

#include "training_algorithm.h"
#include "training_rate_algorithm.h"

// TinyXml includes

#include "../tinyxml2/tinyxml2.h"

namespace OpenNN
{

///
/// This concrete class represents a conjugate gradient training algorithm for a performance functional of a neural network. 
///

class ConjugateGradient : public TrainingAlgorithm
{

public:

   // ENUMERATIONS

   /// Enumeration of the available training operators for obtaining the training direction.

   enum TrainingDirectionMethod{PR, FR};

   // DEFAULT CONSTRUCTOR

   explicit ConjugateGradient(void); 


   // GENERAL CONSTRUCTOR

   explicit ConjugateGradient(PerformanceFunctional*);


   // XML CONSTRUCTOR

   explicit ConjugateGradient(const tinyxml2::XMLDocument&); 


   // DESTRUCTOR

   virtual ~ConjugateGradient(void);


   // STRUCTURES

   ///
   /// This structure contains the conjugate gradient results. 
   ///

   struct ConjugateGradientResults : public TrainingAlgorithm::TrainingAlgorithmResults
   {
       /// Default constructor.

       ConjugateGradientResults(void)
       {
           conjugate_gradient_pointer = NULL;
       }

       /// Conjugate gradient constructor.

       ConjugateGradientResults(ConjugateGradient* new_conjugate_gradient_pointer)
       {
           conjugate_gradient_pointer = new_conjugate_gradient_pointer;
       }

       /// Destructor.

       virtual ~ConjugateGradientResults(void)
       {
       }

       /// Pointer to the conjugate gradient object for which the training results are to be stored.

      ConjugateGradient* conjugate_gradient_pointer;

      // TRAINING HISTORY

      /// History of the neural network parameters over the training iterations. 

      Vector< Vector<double> > parameters_history;

      /// History of the parameters norm over the training iterations. 

      Vector<double> parameters_norm_history;

      /// History of the performance function performance over the training iterations. 

      Vector<double> performance_history;

      /// History of the selection performance over the training iterations. 

      Vector<double> selection_performance_history;

      /// History of the performance function gradient over the training iterations. 

      Vector< Vector<double> > gradient_history;

      /// History of the gradient norm over the training iterations. 

      Vector<double> gradient_norm_history;

      /// History of the conjugate gradient training direction over the training iterations. 

      Vector< Vector<double> > training_direction_history;

      /// History of the training rate over the training iterations. 

      Vector<double> training_rate_history;

      /// History of the elapsed time over the training iterations. 

      Vector<double> elapsed_time_history;

      // FINAL VALUES

      /// Final neural network parameters vector. 

      Vector<double> final_parameters;

      /// Final neural network parameters norm. 

      double final_parameters_norm;

      /// Final performance function evaluation.

      double final_performance;

      /// Final selection performance. 

      double final_selection_performance;

      /// Final performance function gradient. 

      Vector<double> final_gradient;

      /// Final gradient norm. 

      double final_gradient_norm;

      /// Final conjugate gradient training direction. 

      Vector<double> final_training_direction;

      /// Final conjugate gradient training rate. 

      double final_training_rate;

      /// Elapsed time of the training process. 

      double elapsed_time;

      /// Maximum number of training iterations.

      size_t iterations_number;

      void resize_training_history(const size_t&);
      std::string to_string(void) const;

      Matrix<std::string> write_final_results(const size_t& precision = 3) const;
   };


   // METHODS

   // Get methods

   const TrainingRateAlgorithm& get_training_rate_algorithm(void) const;
   TrainingRateAlgorithm* get_training_rate_algorithm_pointer(void);

   // Training operators

   const TrainingDirectionMethod& get_training_direction_method(void) const;
   std::string write_training_direction_method(void) const;

   // Training parameters

   const double& get_warning_parameters_norm(void) const;
   const double& get_warning_gradient_norm(void) const;
   const double& get_warning_training_rate(void) const;

   const double& get_error_parameters_norm(void) const;
   const double& get_error_gradient_norm(void) const;
   const double& get_error_training_rate(void) const;

   // Stopping criteria

   const double& get_minimum_parameters_increment_norm(void) const;

   const double& get_minimum_performance_increase(void) const;
   const double& get_performance_goal(void) const;
   const size_t& get_maximum_selection_performance_decreases(void) const;
   const double& get_gradient_norm_goal(void) const;

   const size_t& get_maximum_iterations_number(void) const;
   const double& get_maximum_time(void) const;

   // Reserve training history

   const bool& get_reserve_parameters_history(void) const;
   const bool& get_reserve_parameters_norm_history(void) const;

   const bool& get_reserve_performance_history(void) const;
   const bool& get_reserve_selection_performance_history(void) const;
   const bool& get_reserve_gradient_history(void) const;
   const bool& get_reserve_gradient_norm_history(void) const;

   const bool& get_reserve_training_direction_history(void) const;
   const bool& get_reserve_training_rate_history(void) const;
   const bool& get_reserve_elapsed_time_history(void) const;

   // Set methods

   void set_default(void);

   void set_performance_functional_pointer(PerformanceFunctional*);

   // Training operators

   void set_training_direction_method(const TrainingDirectionMethod&);
   void set_training_direction_method(const std::string&);

   // Training parameters

   void set_warning_parameters_norm(const double&);
   void set_warning_gradient_norm(const double&);
   void set_warning_training_rate(const double&);

   void set_error_parameters_norm(const double&);
   void set_error_gradient_norm(const double&);
   void set_error_training_rate(const double&);

   // Stopping criteria

   void set_minimum_parameters_increment_norm(const double&);

   void set_performance_goal(const double&);
   void set_minimum_performance_increase(const double&);
   void set_maximum_selection_performance_decreases(const size_t&);
   void set_gradient_norm_goal(const double&);

   void set_maximum_iterations_number(const size_t&);
   void set_maximum_time(const double&);

   // Reserve training history

   void set_reserve_parameters_history(const bool&);
   void set_reserve_parameters_norm_history(const bool&);

   void set_reserve_performance_history(const bool&);
   void set_reserve_selection_performance_history(const bool&);
   void set_reserve_gradient_history(const bool&);
   void set_reserve_gradient_norm_history(const bool&);

   void set_reserve_training_direction_history(const bool&);
   void set_reserve_training_rate_history(const bool&);
   void set_reserve_elapsed_time_history(const bool&);

   void set_reserve_all_training_history(const bool&);

   // Utilities

   void set_display_period(const size_t&);
   void set_save_period(const size_t&);

   // Training direction methods

   double calculate_PR_parameter(const Vector<double>&, const Vector<double>&) const;
   double calculate_FR_parameter(const Vector<double>&, const Vector<double>&) const;

   Vector<double> calculate_PR_training_direction(const Vector<double>&, const Vector<double>&, const Vector<double>&) const;
   Vector<double> calculate_FR_training_direction(const Vector<double>&, const Vector<double>&, const Vector<double>&) const;

   Vector<double> calculate_gradient_descent_training_direction(const Vector<double>&) const;

   Vector<double> calculate_training_direction(const Vector<double>&, const Vector<double>&, const Vector<double>&) const;

   // Training methods

   ConjugateGradientResults* perform_training(void);

   std::string write_training_algorithm_type(void) const;

   // Serialization methods

   Matrix<std::string> to_string_matrix(void) const;

   tinyxml2::XMLDocument* to_XML(void) const;
   void from_XML(const tinyxml2::XMLDocument&);

   void write_XML(tinyxml2::XMLPrinter&) const;
   //void read_XML(   );

private:

   /// Applied method for calculating the conjugate gradient direction.

   TrainingDirectionMethod training_direction_method;

   /// Training rate algorithm object for one-dimensional minimization. 

   TrainingRateAlgorithm training_rate_algorithm;

   /// Value for the parameters norm at which a warning message is written to the screen. 

   double warning_parameters_norm;

   /// Value for the gradient norm at which a warning message is written to the screen. 

   double warning_gradient_norm;   

   /// Training rate value at wich a warning message is written to the screen.

   double warning_training_rate;

   /// Value for the parameters norm at which the training process is assumed to fail. 
   
   double error_parameters_norm;

   /// Value for the gradient norm at which the training process is assumed to fail. 

   double error_gradient_norm;

   /// Training rate at wich the line minimization algorithm is assumed to be unable to bracket a minimum.

   double error_training_rate;


   // STOPPING CRITERIA

   /// Norm of the parameters increment vector at which training stops.

   double minimum_parameters_increment_norm;

   /// Minimum performance improvement between two successive iterations. It is used as a stopping criterion.

   double minimum_performance_increase;

   /// Goal value for the performance. It is used as a stopping criterion.

   double performance_goal;

   /// Goal value for the norm of the objective function gradient. It is used as a stopping criterion.

   double gradient_norm_goal;

   /// Maximum number of iterations at which the selection performance decreases.
   /// This is an early stopping method for improving selection.

   size_t maximum_selection_performance_decreases;

   /// Maximum number of iterations to perform_training. It is used as a stopping criterion.

   size_t maximum_iterations_number;

   /// Maximum training time. It is used as a stopping criterion.

   double maximum_time;

   // TRAINING HISTORY

   /// True if the parameters history matrix is to be reserved, false otherwise.

   bool reserve_parameters_history;

   /// True if the parameters norm history vector is to be reserved, false otherwise.

   bool reserve_parameters_norm_history;

   /// True if the performance history vector is to be reserved, false otherwise.

   bool reserve_performance_history;

   /// True if the gradient history matrix is to be reserved, false otherwise.

   bool reserve_gradient_history;

   /// True if the gradient norm history vector is to be reserved, false otherwise.

   bool reserve_gradient_norm_history;

   /// True if the training direction history matrix is to be reserved, false otherwise.
   
   bool reserve_training_direction_history;

   /// True if the training rate history vector is to be reserved, false otherwise.

   bool reserve_training_rate_history;

   /// True if the elapsed time history vector is to be reserved, false otherwise.

   bool reserve_elapsed_time_history;

   /// True if the Selection performance history vector is to be reserved, false otherwise. 

   bool reserve_selection_performance_history;


};

}

#endif


// OpenNN: Open Neural Networks Library.
// Copyright (c) 2005-2016 Roberto Lopez.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

