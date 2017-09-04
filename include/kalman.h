#ifndef __KALMAN_H__
#define __KALMAN_H__

#include "matrix.h"
#include "main.h"

using namespace std;

class kalman{
	public:
		kalman(Matrix <float> g_transition_matrices,
		 Matrix <float> g_observation_matrices,
         Matrix <float> g_transition_covariance, 
         Matrix <float> g_observation_covariance,
         Matrix <float> g_transition_offsets, 
         Matrix <float> g_observation_offsets,
         Matrix <float> g_initial_state_mean, 
         Matrix <float> g_initial_state_covariance);
		~kalman();

		void filter_predict(Matrix <float> & predicted_state_mean,
        		Matrix <float> & predicted_state_covariance,
                Matrix <float> current_state_mean,
                Matrix <float> current_state_covariance);

		void filter_correct(Matrix <float> & corrected_state_mean,
            	Matrix <float> & corrected_state_covariance, 
                Matrix <float> predicted_state_mean,
                Matrix <float> predicted_state_covariance, 
                Matrix <float> observation);

    	void filter_update(Matrix <float> &next_filtered_state_mean,
    					   Matrix <float> &next_filtered_state_covariance,
    					   Matrix <float> filtered_state_mean, 
    					   Matrix <float> filtered_state_covariance,
                      	   Matrix <float> observation);


	protected:
		Matrix <float> transition_matrices;
		Matrix <float> observation_matrices;
		Matrix <float> transition_covariance;
		Matrix <float> observation_covariance;
		Matrix <float> transition_offsets;
		Matrix <float> observation_offsets;
		Matrix <float> initial_state_mean;
		Matrix <float> initial_state_covariance;
	private:
};

#endif