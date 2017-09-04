#include "./../include/kalman.h"

using namespace std;


kalman::kalman(Matrix <float> g_transition_matrices,
		 Matrix <float> g_observation_matrices,
         Matrix <float> g_transition_covariance, 
         Matrix <float> g_observation_covariance,
         Matrix <float> g_transition_offsets, 
         Matrix <float> g_observation_offsets,
         Matrix <float> g_initial_state_mean, 
         Matrix <float> g_initial_state_covariance)
{
	transition_matrices = g_transition_matrices;
	observation_matrices = g_observation_matrices;
	transition_covariance = g_transition_covariance;
	observation_covariance = g_observation_covariance;
	transition_offsets = g_transition_offsets;
	observation_offsets = g_observation_offsets;
	initial_state_mean = g_initial_state_mean;
	initial_state_covariance = g_initial_state_covariance;
}

kalman::~kalman(){

}

void kalman::filter_predict(Matrix <float> & predicted_state_mean,
        Matrix <float> & predicted_state_covariance,
        Matrix <float> current_state_mean,
        Matrix <float> current_state_covariance)
{
	predicted_state_mean = transition_matrices * current_state_mean + transition_offsets;
    
    predicted_state_covariance = (transition_matrices*
    	(current_state_covariance* (transition_matrices.transpose()) ) )+ transition_covariance;
    
}

void kalman::filter_correct(Matrix <float> & corrected_state_mean,
    	Matrix <float> & corrected_state_covariance, 
        Matrix <float> predicted_state_mean,
        Matrix <float> predicted_state_covariance, 
        Matrix <float> observation)
{
        Matrix <float> predicted_observation_mean (observation_matrices.get_row_size(), predicted_state_mean.get_col_size());
        predicted_observation_mean = (observation_matrices * predicted_state_mean) + observation_offsets;

        Matrix <float> predicted_observation_covariance(observation_matrices.get_row_size(), observation_matrices.get_row_size());
        predicted_observation_covariance = (observation_matrices* 
        	(predicted_state_covariance* (observation_matrices.transpose()) )) + observation_covariance;

        Matrix <float> temp(predicted_observation_covariance.get_row_size(), predicted_observation_covariance.get_row_size());
        temp = (predicted_observation_covariance.inv(predicted_observation_covariance));
        Matrix <float> kalman_gain(predicted_state_covariance.get_row_size(), predicted_state_covariance.get_row_size());
        kalman_gain = (predicted_state_covariance * ((observation_matrices.transpose()) * temp));

        corrected_state_mean =  predicted_state_mean + (kalman_gain * (observation - predicted_observation_mean));

        corrected_state_covariance = predicted_state_covariance - (kalman_gain
                     * (observation_matrices * predicted_state_covariance));
}

void kalman::filter_update(Matrix <float> &next_filtered_state_mean,
				   Matrix <float> &next_filtered_state_covariance,
				   Matrix <float> filtered_state_mean, 
				   Matrix <float> filtered_state_covariance,
              	   Matrix <float> observation)
{
	Matrix <float> predicted_state_mean(state_size,1);
	Matrix <float> predicted_state_covariance(state_size, state_size);

	filter_predict(predicted_state_mean, predicted_state_covariance,
					filtered_state_mean, filtered_state_covariance);

	filter_correct(next_filtered_state_mean, next_filtered_state_covariance,
					predicted_state_mean, predicted_state_covariance, observation);
}
