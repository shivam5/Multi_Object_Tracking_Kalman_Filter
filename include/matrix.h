// Matrix library by Shivam Mittal (IIT Ropar)
// Visit - https://github.com/shivam5/Matrix_library

#ifndef _MATRIX_
#define _MATRIX_

#include <vector>
#include <iostream>
#include <complex.h>
#include <array>
#include <numeric>


template <class data_type>
class Matrix { 
	private: 
		typedef std::vector<data_type> row;
		typedef std::vector<row> matrix;
		matrix M;
		unsigned int row_size;
		unsigned int col_size;
		std :: vector <data_type> vals;

	public: 

		// Constructor with no parameters
		Matrix();

		// Constructor with predefined row size and column size
		Matrix(const unsigned int r_size, const unsigned int c_size);

		// Copy constructor
		template <class e_type>
		Matrix (const Matrix <e_type> &obj);

		// Helper functions
		void populate_vector() {}
		template <typename... Args>
		void populate_vector(data_type value, Args... args);

		template <typename... Args>
		bool set_matrix (data_type value, Args... args);

		template <typename... Args>
		bool set_row (const unsigned int row, data_type value, Args... args);

		template <typename... Args>
		bool set_col (const unsigned int col, data_type value, Args... args);

		void resize (const unsigned int r_size, const  unsigned int c_size);
		void display_matrix();
		void display_row(const unsigned int row);
		void display_col(const unsigned int col);

		void set_value(const unsigned int row, const unsigned int col, const data_type val);
		data_type get_value(const unsigned int row, const unsigned int col) const;

		unsigned int get_row_size() const;

		unsigned int get_col_size() const;


		data_type det ();
		// Helper functions
		data_type determinant (Matrix <data_type> &mat, int N);
		void cofactor_matrix (Matrix <data_type> &mat, Matrix <data_type> &cofactor, int p, int q, int N);

		Matrix <data_type> transpose ();

		template <typename d_type>
		Matrix <std::complex<double>>  inv (Matrix <std::complex<d_type>> &A, int a);
		// Helper functions
		template <typename d_type>		
		void  adjoint(Matrix <std::complex<d_type>> &A,Matrix <std::complex<d_type>> &adj);
		template <typename d_type>
		bool  inverse(Matrix <std::complex<d_type>> &A, Matrix <std::complex<double>> &inverse);

		Matrix <double> inv (Matrix <data_type> &A);
		// Helper functions
		void adjoint(Matrix <data_type> &A,Matrix <data_type> &adj);
		bool inverse(Matrix <data_type> &A, Matrix <double> &inverse);

		template <class d_type> friend 
		Matrix <d_type> operator + (const Matrix <d_type> &M1, const Matrix <d_type> &M2);

		template <class d_type>	friend 
		void operator += (Matrix <d_type> &M1, const Matrix <d_type> &M2);

		template <class d_type> friend 
		Matrix <d_type> operator - (const Matrix <d_type> &M1, const Matrix <d_type> &M2);

		template <class d_type>	friend 
		void operator -= (Matrix <d_type> &M1, const Matrix <d_type> &M2);

		template <class d_type>	friend 
		Matrix <d_type> operator * (const Matrix <d_type> &M1, const Matrix <d_type> &M2);

		template <class d_type>	friend 
		void operator *= (Matrix <d_type> &M1, const Matrix <d_type> &M2);

		template <class d_type> friend 
		Matrix <d_type> operator + (const Matrix <d_type> &M1, const d_type x);

		template <class d_type>	friend 
		void operator += (Matrix <d_type> &M1, const d_type x);

		template <class d_type> friend 
		Matrix <d_type> operator - (const Matrix <d_type> &M1, const d_type x);

		template <class d_type>	friend 
		void operator -= (Matrix <d_type> &M1, const d_type x);

		template <class d_type>	friend 
		Matrix <d_type> operator * (const Matrix <d_type> &M1, const d_type x);

		template <class d_type>	friend 
		void operator *= (Matrix <d_type> &M1, const d_type x);		

		template <class d_type>	friend 
		Matrix <d_type> operator / (const Matrix <d_type> &M1, const d_type x);

		template <class d_type>	friend 
		void operator /= (Matrix <d_type> &M1, const d_type x);		
		
}; 


template <class data_type> 
Matrix <data_type> :: Matrix(){	
	row_size = col_size = 0;
}

template <class data_type> 
Matrix <data_type> :: Matrix(const unsigned int r_size, const unsigned int c_size){
	row_size = r_size;
	col_size = c_size;
	
	M.resize(row_size);
	for (int i=0; i<row_size; i++)
		M[i].resize(col_size);
}

template <class data_type>
template <class e_type> 
Matrix <data_type> :: Matrix(const Matrix <e_type> &obj){
	row_size = obj.get_row_size();
	if (row_size > 0)
		col_size = obj.get_col_size();
	else
		col_size = 0;
	
	M.resize(row_size);

	for (int i=0; i<row_size; i++){
		M[i].resize(col_size);
		for (int j=0; j<col_size; j++)
			M[i][j] = obj.get_value(i, j);
	}
}

template <class data_type>
template <typename... Args>
void Matrix <data_type> :: populate_vector (data_type value, Args... args){
	vals.push_back(value);
	if( sizeof...(args)>0 )
		populate_vector (args... );
}

template <class data_type>
template <typename... Args>
bool Matrix <data_type> :: set_matrix (data_type value, Args... args){
	int n = sizeof...(args)+1;
	if ( n != (row_size*col_size) ){
		std :: cerr << "The number of arguments do not match with the dimensions of the matrix."<<std :: endl;
		return false;
	}

	vals.clear();
	populate_vector (value, args...);

	for (int i=0; i<row_size; i++){
		for (int j=0; j<col_size; j++)
			M[i][j] = vals[i*row_size+j];
	}
	return true;
}

template <class data_type>
template <typename... Args>
bool Matrix <data_type> :: set_row (const unsigned int row, data_type value, Args... args){
	int n = sizeof...(args)+1;
	if ( n != (row_size) ){
		std :: cerr << "The number of arguments do not match with the row size."<<std :: endl;
		return false;
	}

	if ( row >= col_size ){
		std :: cerr << "The column specified is out of bounds"<<std :: endl;
		return false;
	}

	vals.clear();
	populate_vector (value, args...);

	for (int i=0; i<row_size; i++)
		M[row][i] = vals[i];

	return true;
}

template <class data_type>
template <typename... Args>
bool Matrix <data_type> :: set_col (const unsigned int col, data_type value, Args... args){
	int n = sizeof...(args)+1;

	if ( n != (col_size) ){
		std :: cerr << "The number of arguments do not match with the column size."<<std :: endl;
		return false;
	}

	if ( col >= row_size ){
		std :: cerr << "The column specified is out of bounds"<<std :: endl;
		return false;
	}

	vals.clear();
	populate_vector (value, args...);

	for (int i=0; i<row_size; i++)
		M[i][col] = vals[i];
	return true;
}

template <class data_type> 
void Matrix <data_type> :: resize(const unsigned int r_size, const unsigned int c_size){
	row_size = r_size;
	col_size = c_size;
	
	M.resize(row_size);
	for (int i=0; i<row_size; i++)
		M[i].resize(col_size);
}

template <class data_type> 
void Matrix <data_type> :: display_matrix(){
	for (int i=0; i<row_size; i++){
		for (int j=0; j<col_size; j++)
			std :: cout<<M[i][j]<<" ";
		std :: cout<<std :: endl;
	}	
	std :: cout<<std :: endl;
}

template <class data_type> 
void Matrix <data_type> :: display_row(const unsigned int row){
	for (int j=0; j<col_size; j++)
		std :: cout<<M[row][j]<<" ";
	std :: cout<<std :: endl<<std :: endl;
}

template <class data_type> 
void Matrix <data_type> :: display_col(const unsigned int col){
	for (int i=0; i<row_size; i++)
		std :: cout<<M[i][col]<<std :: endl;
	std :: cout<<std :: endl;
}

template <class data_type> 
void Matrix <data_type> :: set_value(const unsigned int row, const unsigned int col, const data_type val){
	M[row][col] = val;
}

template <class data_type> 
data_type Matrix <data_type> :: get_value(const unsigned int row, const unsigned int col) const{
	return M[row][col];
}

template <class data_type> 
unsigned int Matrix <data_type> :: get_row_size() const{
	return row_size;
}

template <class data_type> 
unsigned int Matrix <data_type> :: get_col_size() const{
	return col_size;
}


template <class data_type> 
data_type Matrix <data_type> :: det (){
	if ( row_size != col_size ){
		std :: cerr << "Square matrix required for calculating determinant. Returning 0."<<std::endl;
		return 0;
	}

	Matrix <data_type> mat( row_size, col_size);

	for (int i=0; i< row_size; i++){
		for (int j=0; j< col_size; j++)
			mat.set_value(i, j, M[i][j]);
	}	

	return determinant (mat, row_size);

}

template <class data_type> 
data_type Matrix <data_type> :: determinant (Matrix <data_type> &mat, int N){
    
    if (N == 1)
        return mat.get_value(0, 0);
    
    data_type det = 0;

	Matrix <data_type> cofactor(N, N);

    int sign_multiplier = 1;

    for (int i = 0; i < N; i++){
        cofactor_matrix(mat, cofactor, 0, i, N);
        det += (sign_multiplier * mat.get_value(0, i) * determinant(cofactor, N-1));
        sign_multiplier = -sign_multiplier;
    }
 
    return det;
}

template <class data_type> 
void Matrix <data_type> :: cofactor_matrix (Matrix <data_type> &mat, Matrix <data_type> &cofactor, int p, int q, int N){
	int i = 0, j = 0;
 
    for (int row = 0; row < N; row++){
        for (int col = 0; col < N; col++){

            if (row != p && col != q){
            	cofactor.set_value(i, j, mat.get_value(row, col));
            	j++;
 
                if (j == N - 1){
                    j = 0;
                    i++;
                }
            }
        }
    }	

}


template <class data_type> 
Matrix <data_type> Matrix <data_type> :: transpose (){
	Matrix <double> tr(get_col_size(), get_row_size());

	for (int i=0; i<get_row_size(); i++){
		for (int j=0; j<get_col_size(); j++){
			tr.set_value(j,i,get_value(i,j));
		}
	}

	return tr;
}


template <class data_type> 
template <typename d_type>
Matrix <std::complex<double>> Matrix <data_type> :: inv (Matrix <std::complex<d_type>> &A, int a){
	Matrix <std::complex<double>> inv(row_size, col_size);

	if ( A.get_col_size() != A.get_row_size() ){
		std :: cerr << "Square matrix required for calculating inverse. Returning 0 matrix."<<std::endl;
		return inv;
	}

	if (inverse(A, inv))
		return inv;

	Matrix <std::complex<double>> x(row_size, col_size);
	return x;

}

template <class data_type> 
template <typename d_type>
void Matrix <data_type> :: adjoint(Matrix <std::complex<d_type>> &A,Matrix <std::complex<d_type>> &adj){
	int N = adj.row_size;
    if (N == 1)
    {
        adj.set_value(0, 0, std::complex<int>(1, 0));
        return;
    }
 
    int sign = 1;
    Matrix <std::complex<d_type>> temp(N, N);
 
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            cofactor_matrix(A, temp, i, j, N);
            sign = ((i+j)%2==0)? 1: -1;
            adj.set_value(j, i, (sign)*(determinant(temp, N-1)));
        }
    }
}

template <class data_type> 
template <typename d_type>
bool Matrix <data_type> :: inverse(Matrix <std::complex<d_type>> &A, Matrix <std::complex<double>> &inverse){
	int N = A.row_size;
    data_type det = determinant(A, N);
    if (det == 0)
    {
        std::cout << "Singular matrix, can't find its inverse"<<std::endl;
        return false;
    }
 
    Matrix <std::complex<d_type>> adj(N, N);
    adjoint(A, adj);

    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
        	double real = adj.get_value(i,j).real();
        	double imag = adj.get_value(i,j).imag();
        	std::complex<double> x = std::complex<double>(real, imag) ;

        	real = det.real();
        	imag = det.imag();
        	std::complex<double> y = std::complex<double>(real, imag) ;

        	x = x / y;
            inverse.set_value(i, j, x);
        }
    }
 
    return true;
}




template <class data_type> 
Matrix <double> Matrix <data_type> :: inv (Matrix <data_type> &A){
	Matrix <double> inv(row_size, col_size);

	if ( A.get_row_size() != A.get_col_size() ){
		std :: cerr << "Square matrix required for calculating inverse. Returning 0 matrix."<<std::endl;
		return inv;
	}

	if (inverse(A, inv))
		return inv;

	Matrix <double> x(row_size, col_size);
	return x;

}

template <class data_type> 
void Matrix <data_type> :: adjoint(Matrix <data_type> &A,Matrix <data_type> &adj){
	int N = adj.row_size;
    if (N == 1)
    {
        adj.set_value(0, 0, 1);
        return;
    }
 
    int sign = 1;
    Matrix <data_type> temp(N, N);
 
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            cofactor_matrix(A, temp, i, j, N);
            sign = ((i+j)%2==0)? 1: -1;
            adj.set_value(j, i, (sign)*(determinant(temp, N-1)));
        }
    }
}

template <class data_type> 
bool Matrix <data_type> :: inverse(Matrix <data_type> &A, Matrix <double> &inverse){
	int N = A.row_size;
    data_type det = determinant(A, N);
    if (det == 0)
    {
        std::cout << "Singular matrix, can't find its inverse"<<std::endl;
        return false;
    }
 
    Matrix <data_type> adj(N, N);
    adjoint(A, adj);

    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++)
            inverse.set_value(i, j, adj.get_value(i,j) / (double) det);
    }
 
    return true;
}






template <class data_type>
Matrix <data_type> operator+ (const Matrix <data_type> &M1, const Matrix <data_type> &M2) {

	if ( M1.row_size!=M2.row_size || M1.col_size!=M2.col_size ){
		std :: cerr << "Dimensions of the two matrices are not same for matrix addition. Resultant = First_matrix."<<std::endl;
		return M1;
	}

		
	Matrix <data_type> M3(M1.row_size, M1.col_size);

	for (int i=0; i<M3.row_size; i++){
		for (int j=0; j<M3.col_size; j++)
			M3.set_value(i, j, M1.get_value(i, j) + M2.get_value(i, j));
	}

	return M3;

}


template <class data_type>
void operator+= (Matrix <data_type> &M1, const Matrix <data_type> &M2) {

	if ( M1.row_size!=M2.row_size || M1.col_size!=M2.col_size ){
		std :: cerr << "Dimensions of the two matrices are not same for matrix addition. Resultant = First_matrix."<<std::endl;
		return;
	}

	for (int i=0; i<M1.row_size; i++){
		for (int j=0; j<M1.col_size; j++)
			M1.set_value(i, j, M1.get_value(i, j) + M2.get_value(i, j));
	}

}

template <class data_type>
Matrix <data_type> operator- (const Matrix <data_type> &M1, const Matrix <data_type> &M2) {

	if ( M1.row_size!=M2.row_size || M1.col_size!=M2.col_size ){
		std :: cerr << "Dimensions of the two matrices are not same for matrix subtraction. Resultant = First_matrix."<<std::endl;
		return M1;
	}

		
	Matrix <data_type> M3(M1.row_size, M1.col_size);

	for (int i=0; i<M3.row_size; i++){
		for (int j=0; j<M3.col_size; j++)
			M3.set_value(i, j, M1.get_value(i, j) - M2.get_value(i, j));
	}

	return M3;

}


template <class data_type>
void operator-= (Matrix <data_type> &M1, const Matrix <data_type> &M2) {

	if ( M1.row_size!=M2.row_size || M1.col_size!=M2.col_size ){
		std :: cerr << "Dimensions of the two matrices are not same for matrix subtraction. Resultant = First_matrix."<<std::endl;
		return;
	}

	for (int i=0; i<M1.row_size; i++){
		for (int j=0; j<M1.col_size; j++)
			M1.set_value(i, j, M1.get_value(i, j) - M2.get_value(i, j));
	}

}


template <class data_type>
Matrix <data_type> operator* (const Matrix <data_type> &M1, const Matrix <data_type> &M2) {

	if ( M1.col_size!=M2.row_size )
		std :: cerr << "Dimensions of the two matrices are not compatible for matrix multiplication."<<std::endl;

		
	Matrix <data_type> M3(M1.row_size, M2.col_size);

	for (int i=0; i<M1.row_size; i++){
		for (int j=0; j<M2.col_size; j++){
			data_type x=0;
			for (int k=0; k<M1.col_size; k++){
				x += M1.get_value(i,k) * M2.get_value(k,j);
			}
			M3.set_value(i, j, x);
		}
	}

	return M3;

}

template <class data_type>
void operator*= (Matrix <data_type> &M1, const Matrix <data_type> &M2) {

	if ( M1.col_size!=M2.row_size )
		std :: cerr << "Dimensions of the two matrices are not compatible for matrix multiplication."<<std::endl;
		
	Matrix <data_type> M3(M1.row_size, M2.col_size);

	for (int i=0; i<M1.row_size; i++){
		for (int j=0; j<M2.col_size; j++){
			data_type x=0;
			for (int k=0; k<M1.col_size; k++){
				x += M1.get_value(i,k) * M2.get_value(k,j);
			}
			M3.set_value(i, j, x);
		}
	}

	M1.resize(M1.row_size, M2.col_size);

	for (int i=0; i<M1.row_size; i++){
		for (int j=0; j<M1.col_size; j++){
			M1.set_value(i, j, M3.get_value(i,j));
		}
	}

}



template <class data_type>
Matrix <data_type> operator+ (const Matrix <data_type> &M1, const data_type x) {
		
	Matrix <data_type> M2(M1.row_size, M1.col_size);

	for (int i=0; i<M2.row_size; i++){
		for (int j=0; j<M2.col_size; j++)
			M2.set_value(i, j, M1.get_value(i,j)+x);
	}

	return M2;
}


template <class data_type>
void operator+= (Matrix <data_type> &M1, const data_type x) {

	for (int i=0; i<M1.row_size; i++){
		for (int j=0; j<M1.col_size; j++)
			M1.set_value(i, j, M1.get_value(i,j)+x);
	}

}

template <class data_type>
Matrix <data_type> operator- (const Matrix <data_type> &M1, const data_type x) {
		
	Matrix <data_type> M2(M1.row_size, M1.col_size);

	for (int i=0; i<M2.row_size; i++){
		for (int j=0; j<M2.col_size; j++)
			M2.set_value(i, j, M1.get_value(i,j)-x);
	}

	return M2;
}


template <class data_type>
void operator-= (Matrix <data_type> &M1, const data_type x) {

	for (int i=0; i<M1.row_size; i++){
		for (int j=0; j<M1.col_size; j++)
			M1.set_value(i, j, M1.get_value(i,j)-x);
	}

}


template <class data_type>
Matrix <data_type> operator* (const Matrix <data_type> &M1, const data_type x) {

	Matrix <data_type> M2(M1.row_size, M1.col_size);

	for (int i=0; i<M2.row_size; i++){
		for (int j=0; j<M2.col_size; j++)
			M2.set_value(i, j, M1.get_value(i,j)*x);
	}

	return M2;

}

template <class data_type>
void operator*= (Matrix <data_type> &M1, const data_type x) {

	for (int i=0; i<M1.row_size; i++){
		for (int j=0; j<M1.col_size; j++)
			M1.set_value(i, j, M1.get_value(i,j)*x);
	}

}

template <class data_type>
Matrix <data_type> operator/ (const Matrix <data_type> &M1, const data_type x) {

	if ( x==0 ){
		std :: cerr << "Division by 0 not allowed."<<std :: endl;
		return M1;
	}

	Matrix <data_type> M2(M1.row_size, M1.col_size);

	for (int i=0; i<M2.row_size; i++){
		for (int j=0; j<M2.col_size; j++)
			M2.set_value(i, j, M1.get_value(i,j)/x);
	}

	return M2;

}

template <class data_type>
void operator/= (Matrix <data_type> &M1, const data_type x) {

	if ( x==0 ){
		std :: cerr << "Division by 0 not allowed."<<std :: endl;
		return;
	}

	for (int i=0; i<M1.row_size; i++){
		for (int j=0; j<M1.col_size; j++)
			M1.set_value(i, j, M1.get_value(i,j)/x);
	}

}



#endif