#include "./../include/main.h"

// The text file which contains the location of all the images
string image_files = "/home/madan/new_darknet/kalman/kalman_c_code/example/test_video.txt";
// The folder location which contains the yolo predictions
string yolo_labels_folder = "/home/madan/new_darknet/kalman/kalman_c_code/example/yolo_predictions/";
// The folder location where our filtered predictions with track_id would be saved.
string filtered_labels_folder = "/home/madan/new_darknet/kalman/kalman_c_code/example/yolo_predictions_filtered/";

int new_object_iterator = 0; //Counter to maintain the track_id to be assigned to new variables
// bool flag = false; //Flag to read image and store w,h initially
int w = 1080; //Width of the image files
int h = 1080; //Height of the image files

int main(){
	// Creating dictionaries for keeping track of states and observations (upto previous 5)
	map <int, Matrix <float> > current_state;
	map <int, Matrix <float> > previous_state;
	map <int, Matrix <float> > current_state_covariance;
	map <int, Matrix <float> > previous_state_covariance;
	map <int, Matrix <float> > observations[5];
	
	// Set matrices for the kalman filter
	Matrix <float> transition_matrix(state_size, state_size), observation_matrix(observation_size, state_size);
	Matrix <float> initial_state(state_size, 1), initial_covariance(state_size, state_size);
	Matrix <float> transition_covar(state_size, state_size), observation_covar(observation_size, observation_size);
	Matrix <float> transition_offsets(state_size, 1), observation_offsets(observation_size, 1);
	transition_matrix.set_row(0, 2,0,-1,0,0,0,0,0);  
	transition_matrix.set_row(1, 0,2,0,-1,0,0,0,0);
	transition_matrix.set_row(2, 1,0,0,0,0,0,0,0 );
	transition_matrix.set_row(3, 0,1,0,0,0,0,0,0);
	transition_matrix.set_row(4, 0,0,0,0,2,0,-1,0); 
	transition_matrix.set_row(5, 0,0,0,0,0,2,0,-1);
	transition_matrix.set_row(6, 0,0,0,0,1,0,0,0);
	transition_matrix.set_row(7, 0,0,0,0,0,1,0,0);

	for (int i=0; i<observation_matrix.get_row_size(); i++){
		for (int j=0; j<observation_matrix.get_col_size(); j++)
			observation_matrix.set_value(i,j,0);
	}
	observation_matrix.set_value(0,0,1);
	observation_matrix.set_value(1,1,1);
	observation_matrix.set_value(2,4,1);
	observation_matrix.set_value(3,5,1);

	for (int i=0; i<initial_state.get_row_size(); i++){
		for (int j=0; j<initial_state.get_col_size(); j++)
			initial_state.set_value(i,j,0);
	}

	for (int i=0; i<transition_offsets.get_row_size(); i++){
		for (int j=0; j<transition_offsets.get_col_size(); j++)
			transition_offsets.set_value(i,j,0);
	}
	
	for (int i=0; i<observation_offsets.get_row_size(); i++){
		for (int j=0; j<observation_offsets.get_col_size(); j++)
			observation_offsets.set_value(i,j,0);
	}

	for (int i=0; i<state_size; i++){
		for (int j=0; j<state_size; j++){
			if (i==j)
				initial_covariance.set_value(i, j, 0.01);
			else
				initial_covariance.set_value(i, j, 0);
		}
	}
	for (int i=0; i<state_size; i++){
		for (int j=0; j<state_size; j++){
			if (i==j)
				transition_covar.set_value(i, j, 0.001);
			else
				transition_covar.set_value(i, j, 0);
		}
	}
	for (int i=0; i<observation_size; i++){
		for (int j=0; j<observation_size; j++){
			if (i==j)
				observation_covar.set_value(i, j, 1);
			else
				observation_covar.set_value(i, j, 0);
		}
	}

	// Intitialize the kalman object
	kalman kf(transition_matrix, observation_matrix, transition_covar,
			  observation_covar, transition_offsets, observation_offsets, 
			  initial_state, initial_covariance);
	string line;

	// Creating filtered_labels_folder
	system(("mkdir -p "+filtered_labels_folder).c_str());
	// Open the file image_files which contains the paths to all the different images 
	ifstream fin;
	fin.open(image_files.c_str());
	while(getline(fin, line)){

		// if (flag){
		// 	// Intially open an image file and store the width and height in global variable w,h
		// 	Mat image;
		//     image = imread(line, CV_LOAD_IMAGE_COLOR);   // Read the file
		//     w = image.cols;
		//     h = image.rows;
  //   		flag = false;
		// }

		// Extract appropriate label names from the line
		string label_name = split(path_leaf(line), '.')[0]+".txt";
		string yolo_label_file = yolo_labels_folder + label_name;
		string filtered_label_file = filtered_labels_folder + label_name;

		// Opening file to write the filtered predictions
		ofstream filtered_file;
		filtered_file.open(filtered_label_file);

		// readframe would read the yolo label file, and using the previous state, associate 
		// predictions and return the current observations
		observations[0] = readframe(yolo_label_file, previous_state);

		vector <int> current_observations_keys = get_keys(observations[0]);
		vector <int> previous_state_keys = get_keys(previous_state);
		vector <int> unionv = vector_union(current_observations_keys, previous_state_keys);

		for (int i=0; i<current_observations_keys.size(); i++){
			int j = current_observations_keys[i];
		}

		for (int i=0; i<unionv.size(); i++){
			int track_id = unionv[i];
			bool is_occupied_state = (find(previous_state_keys.begin(), previous_state_keys.end(), track_id) != previous_state_keys.end());		
			bool is_occupied_observation = (find(current_observations_keys.begin(), current_observations_keys.end(), track_id) != current_observations_keys.end());		

			if (!is_occupied_state){
				initial_state.set_value(0,0,observations[0][track_id].get_value(0,0));
				initial_state.set_value(1,0,observations[0][track_id].get_value(1,0));
				initial_state.set_value(2,0,observations[0][track_id].get_value(0,0));
				initial_state.set_value(3,0,observations[0][track_id].get_value(1,0));
				initial_state.set_value(4,0,observations[0][track_id].get_value(2,0));
				initial_state.set_value(5,0,observations[0][track_id].get_value(3,0));
				initial_state.set_value(6,0,observations[0][track_id].get_value(2,0));
				initial_state.set_value(7,0,observations[0][track_id].get_value(3,0));
				previous_state[track_id] = initial_state;
				previous_state_covariance[track_id] = initial_covariance;
			}

			vector <int> observations_keys1 = get_keys(observations[1]);
			vector <int> observations_keys2 = get_keys(observations[2]);
			vector <int> observations_keys3 = get_keys(observations[3]);
			vector <int> observations_keys4 = get_keys(observations[4]);
			bool is_occupied_observation1 = (find(observations_keys1.begin(), observations_keys1.end(), track_id) != observations_keys1.end());		
			bool is_occupied_observation2 = (find(observations_keys2.begin(), observations_keys2.end(), track_id) != observations_keys2.end());		
			bool is_occupied_observation3 = (find(observations_keys3.begin(), observations_keys3.end(), track_id) != observations_keys3.end());		
			bool is_occupied_observation4 = (find(observations_keys4.begin(), observations_keys4.end(), track_id) != observations_keys4.end());		

			if (is_occupied_observation){
				Matrix <float> current_observation(observation_size,1);
				current_observation.set_value(0,0, observations[0][track_id].get_value(0,0));
				current_observation.set_value(1,0, observations[0][track_id].get_value(1,0));
				current_observation.set_value(2,0, observations[0][track_id].get_value(2,0));
				current_observation.set_value(3,0, observations[0][track_id].get_value(3,0));
				
				Matrix <float> temp(state_size, 1);
				Matrix <float> temp1(state_size, state_size);
				current_state[track_id] = temp;
				current_state_covariance[track_id] = temp1;

				kf.filter_update(current_state[track_id], current_state_covariance[track_id], previous_state[track_id], previous_state_covariance[track_id], current_observation);
				
			}


			else if ( is_occupied_observation1 || is_occupied_observation2 || is_occupied_observation3 || is_occupied_observation4 ){
				Matrix <float> temp(state_size, 1);
				Matrix <float> temp1(state_size, state_size);
				current_state[track_id] = temp;
				current_state_covariance[track_id] = temp1;
				
				kf.filter_predict(current_state[track_id], current_state_covariance[track_id],
					previous_state[track_id], previous_state_covariance[track_id]);
			}
			else{
				Matrix <float> temp(state_size, 1);
				Matrix <float> temp1(state_size, state_size);
				current_state[track_id] = temp;
				current_state_covariance[track_id] = temp1;
			}

			filtered_file<<track_id<<" "<<current_state[track_id].get_value(0,0)<<" "<<current_state[track_id].get_value(1,0)<<" "<<current_state[track_id].get_value(4,0)<<" "<<current_state[track_id].get_value(5,0)<<"\n";

		}
		previous_state = current_state;
		previous_state_covariance = current_state_covariance;
		observations[4] = observations[3];
		observations[3] = observations[2];
		observations[2] = observations[1];
		observations[1] = observations[0];
	}

    fin.close();

	return 0;
}

map <int, Matrix <float> > readframe (string input_file, map <int, Matrix <float> > previous_state){
	map <int, Matrix <float> > current_observations;

	// Opening yolo predictions file
	ifstream file;
	file.open(input_file.c_str());

	// Getting the keys of previous_state
	vector <int> previous_objects = get_keys(previous_state);

	// Updating the new_object_iterator
	if (previous_objects.size() > 0){
		int max = *max_element(previous_objects.begin(), previous_objects.end());
		if (new_object_iterator < max){
			new_object_iterator = max + 1;
		}
	}

	string line;
	// Reading yolo predictions line by line
	while(getline(file, line)){
		vector <string> line_split = split(line, ' ');
		float centerx = atof(string(line_split[1]).c_str());
		float centery = atof(string(line_split[2]).c_str());
		float wid = atof(string(line_split[3]).c_str());
		float hei = atof(string(line_split[4]).c_str());

		// Associating correct track id, by comparing and choosing the minimum euclidean distance
		float min_dist = 100000;
		int correct_track_id = -1;
		for (int i=0; i<previous_objects.size(); i++){
			int j = previous_objects[i];
			Matrix <float> prev_box(state_size, 1);
			prev_box = previous_state[j];
			float centerx_prev = prev_box.get_value(0,0);
			float centery_prev = prev_box.get_value(1,0);
			float dist = (centerx_prev - centerx)*(centerx_prev - centerx) + (centery_prev - centery)*(centery_prev - centery);
			if (dist < min_dist){
				correct_track_id = j;
				min_dist = dist;
			}
		}
		
		// Extract the keys of the current_observations map
		vector <int> observations_keys = get_keys(current_observations);
		bool is_occupied = (find(observations_keys.begin(), observations_keys.end(), correct_track_id) != observations_keys.end());		

		if (min_dist >= euc_threshold && min_dist != 100000){
			Matrix <float> prev_box = previous_state[correct_track_id];
			float centerx_prev = prev_box.get_value(0,0);
			float centery_prev = prev_box.get_value(1,0);
			float width_prev = prev_box.get_value(4,0);
			float height_prev = prev_box.get_value(5,0);
			float box1[4] = {(centerx_prev*w),(centery_prev*h),(width_prev*w),(height_prev*h)};
			float box2[4] = {(centerx*w),(centery*h),(wid*w),(hei*h)};
			float iou = box_iou (box1, box2);

			// Find whether the correc_track_id is already taken in the current observation
			// If IOU is greater than safe threshold, then its safe to associate
			if (iou > safe_IOU_threshold &&  (!is_occupied) ){
				Matrix <float> temp(observation_size+1, 1);
				current_observations[correct_track_id] = temp;
				current_observations[correct_track_id].set_value(0,0,centerx) ;
				current_observations[correct_track_id].set_value(1,0,centery);
				current_observations[correct_track_id].set_value(2,0,wid);
				current_observations[correct_track_id].set_value(3,0,hei);
				current_observations[correct_track_id].set_value(4,0,min_dist);
			}
			// If the object is occupied, check whose distance is lesser and associate accordingly
			else if ( (iou > safe_IOU_threshold) && is_occupied && (min_dist<current_observations[correct_track_id].get_value(4,0)) ){
				Matrix <float> temp(observation_size+1, 1);
				current_observations[new_object_iterator] = temp;
				current_observations[new_object_iterator].set_value(0,0, current_observations[correct_track_id].get_value(0,0));
				current_observations[new_object_iterator].set_value(1,0, current_observations[correct_track_id].get_value(1,0));
				current_observations[new_object_iterator].set_value(2,0, current_observations[correct_track_id].get_value(2,0));
				current_observations[new_object_iterator].set_value(3,0, current_observations[correct_track_id].get_value(3,0));
				current_observations[new_object_iterator].set_value(4,0, current_observations[correct_track_id].get_value(4,0));
				new_object_iterator += 1;

				current_observations[correct_track_id].set_value(0,0,centerx);
				current_observations[correct_track_id].set_value(1,0,centery);
				current_observations[correct_track_id].set_value(2,0,wid);
				current_observations[correct_track_id].set_value(3,0,hei);
				current_observations[correct_track_id].set_value(4,0,min_dist);
			}
			else{
				Matrix <float> temp(observation_size+1, 1);
				current_observations[new_object_iterator] = temp;
				current_observations[new_object_iterator].set_value(0,0,centerx);
				current_observations[new_object_iterator].set_value(1,0,centery);
				current_observations[new_object_iterator].set_value(2,0,wid);
				current_observations[new_object_iterator].set_value(3,0,hei);
				current_observations[new_object_iterator].set_value(4,0,min_dist);
				new_object_iterator += 1;
			}
		}

		// If that trackid is not taken by any object in current frame
		else if (correct_track_id!=-1 && (!is_occupied)){
			Matrix <float> temp(observation_size+1, 1);
			current_observations[correct_track_id] = temp;
			current_observations[correct_track_id].set_value(0,0,centerx);
			current_observations[correct_track_id].set_value(1,0,centery);
			current_observations[correct_track_id].set_value(2,0,wid);
			current_observations[correct_track_id].set_value(3,0,hei);
			current_observations[correct_track_id].set_value(4,0,min_dist);
		}

		// If that object_id is already taken, compare whose euclidean distance is less, also given the condition of minimum threshold
		else if (correct_track_id!=-1 && min_dist<current_observations[correct_track_id].get_value(4,0)){
			Matrix <float> temp(observation_size+1, 1);
			current_observations[new_object_iterator] = temp;
			current_observations[new_object_iterator].set_value(0,0, current_observations[correct_track_id].get_value(0,0));
			current_observations[new_object_iterator].set_value(1,0, current_observations[correct_track_id].get_value(1,0));
			current_observations[new_object_iterator].set_value(2,0, current_observations[correct_track_id].get_value(2,0));
			current_observations[new_object_iterator].set_value(3,0, current_observations[correct_track_id].get_value(3,0));
			current_observations[new_object_iterator].set_value(4,0, current_observations[correct_track_id].get_value(4,0));
			new_object_iterator += 1;

			current_observations[correct_track_id].set_value(0,0,centerx);
			current_observations[correct_track_id].set_value(1,0,centery);
			current_observations[correct_track_id].set_value(2,0,wid);
			current_observations[correct_track_id].set_value(3,0,hei);
			current_observations[correct_track_id].set_value(4,0,min_dist);
		}

		// If above conditions not satisfied, assign a new track_id. Also id threshold not crossed
		else{
			Matrix <float> temp(observation_size+1, 1);
			current_observations[new_object_iterator] = temp;
			current_observations[new_object_iterator].set_value(0,0,centerx);
			current_observations[new_object_iterator].set_value(1,0,centery);
			current_observations[new_object_iterator].set_value(2,0,wid);
			current_observations[new_object_iterator].set_value(3,0,hei);
			current_observations[new_object_iterator].set_value(4,0,min_dist);
			new_object_iterator += 1;
		}

	}
		
	return current_observations;
}