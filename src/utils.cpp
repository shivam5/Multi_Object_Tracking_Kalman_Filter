#include "./../include/utils.h"

// Function to extract the filename out of a path
string path_leaf(string const & path){
  return path.substr(path.find_last_of("/\\") + 1);
}

float overlap(float x1, float w1, float x2, float w2){
    float l1 = x1 - w1/2;
    float l2 = x2 - w2/2;
    float left = l1 > l2 ? l1 : l2;
    float r1 = x1 + w1/2;
    float r2 = x2 + w2/2;
    float right = r1 < r2 ? r1 : r2;
    return right - left;
}

float box_intersection(float a[4], float b[4]){
    float w = overlap(a[0], a[2], b[0], b[2]);
    float h = overlap(a[1], a[3], b[1], b[3]);
    if(w < 0 || h < 0) return 0;
    float area = w*h;
    return area;
}

float box_union(float a[4], float b[4]){
    float i = box_intersection(a, b);
    float u = a[2]*a[3] + b[2]*b[3] - i;
    return u;
}

// Function to return the iou of two boxes (int [x,y,w,h])
float box_iou(float a[4], float b[4]){
    return box_intersection(a, b)/box_union(a, b);
}

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

bool exists (string name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

vector <int> get_keys(map <int, Matrix <float> > m){
    vector<int> v;
    for(map <int, Matrix <float> >::iterator it = m.begin(); it != m.end(); ++it) {
      v.push_back(it->first);
    }
    return v;    
}

vector<int> vector_union (vector <int> a, vector <int> b){
    vector <int> c;
    sort( a.begin(), a.end());
    sort( b.begin(), b.end());
    int i = 0, j = 0;
    while( i < a.size() && j < b.size())
    if( a[ i ] == b[ j ] )
    {
       c.push_back( a[ i ] );
       ++i, ++j;
    }
    else if( a[ i ] < b[ j ] )
       c.push_back( a[ i++ ] );
    else 
       c.push_back( b[ j++ ] );

    while( i < a.size()) c.push_back( a[ i++ ] );
    while( j < b.size()) c.push_back( b[ j++ ] );
    return c;
}

// // If file exists remove it, and then open it in append mode
// if (exists(filtered_label_file)){
//  system(("rm "+filtered_label_file).c_str());
// }

