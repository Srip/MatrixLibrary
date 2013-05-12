// Project -- Matrix library implementation 

//Contains matrix class -- with constructor ,destructor,supporting input iterator,copy constructor

#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

template<typename T>
class Matrix
{
	//Data members
        private:

        int rows_;
        int cols_;
        T **mat;

        public:
        //constructor
        Matrix(int r, int c): rows_(r),cols_(c)
        {
            mat = new T*[rows_];
            for(int i=0; i<rows_; i++)
            {
                    mat[i] = new T[cols_];
            }
			set_value();

        }

        //destructor
        ~Matrix()
        {
                for(int i=0; i<rows_; i++)
                {
                        delete [] mat[i];
                }
                delete [] mat;
        }

        //copy constructor
        Matrix(const Matrix& m): rows_(m.rows_),cols_(m.cols_)
        {
				mat = new T*[rows_];
                for(int i=0; i<rows_; i++)
                {
                        mat[i] = new T[cols_];
                }

		
		
                for(int i=0;i<rows_;i++)
                {
                        for(int j=0;j<cols_;j++)
                        {
                                mat[i][j] = m.mat[i][j];
                        }
                }
        }

        //assignment operator
         Matrix& operator=(const Matrix& m)
        {
		
            rows_ = m.rows_;
            cols_ = m.cols_;
            mat = new T*[rows_];
                for(int k=0; k<rows_; k++)
                {
                        mat[k] = new T[cols_];
                }

                for(int i=0;i<rows_;i++)
                {
                        for(int j=0;j<cols_;j++)
                        {
                                mat[i][j] = m.mat[i][j]; 
                        }
                }

                return (*this);
        }

        //returns the number of rows 
		int getRows()
        {
            return rows_;
        }

        //returns the number of columns
        int getCols()
        {
            return cols_;
        }

        //set function -- Sets the elements of the matrix to default type
        void set_value()
        {
      
               T k=T();
                for(int i=0;i<rows_;i++)
                {
                        for(int j=0;j<cols_;j++)
                        {
                                mat[i][j] =  k; 
                              
                        }
                }
               
        }

        //Proxy class --- to support indexing
		class proxy
		{
			Matrix &m_;
			int index;
			
			public:
			proxy(Matrix &m, int ind): m_(m), index(ind){}

			T &operator[](int index2)
			{
				return m_.mat[index][index2];
			}
		};

		proxy operator[](int index)
		{
			return proxy(*this,index);
		}
	
		
		//function to find transpose of a matrix
		Matrix transpose()
        {
        	if((*this).isIdentity())
        	{
        		return *this;
        	}
            Matrix<T> temp(cols_,rows_);
            for(int i=0;i<rows_;i++)
                for(int j=0;j<cols_;j++)
                {
                    temp[j][i]=mat[i][j];
                   
                }
                return temp;
        }

		//function to add two matrics 
        Matrix operator+(const Matrix& rhs)
        {
            //differnt dimension matrices cannot be added.
            if(rows_ != rhs.rows_ || cols_ != rhs.cols_)
            {
                cout<<"the matrices are of different dimensions.Hence cannot be added\n";
                exit(1);
            }
               
            Matrix<T> temp(rows_,cols_);
          
              for(int i=0;i<cols_;i++)
                {
                        for(int j=0;j<rows_;j++)
                        {
                             temp.mat[i][j] = mat[i][j]+rhs.mat[i][j]; 
                              
                        }
                }
                return (temp);
        }

        //function to support matrix subtraction 
        Matrix operator-(const Matrix& rhs)
        {
            //differnt dimension matrices cannot be added.
            if(rows_ != rhs.rows_ || cols_ != rhs.cols_)
            {
                cout<<"the matrices are of different dimensions.Hence cannot be added\n";
                exit(1);
            }
                //create a temporary storage for the resultant matrix;
            Matrix<T> temp(rows_,cols_);
          
              for(int i=0;i<cols_;i++)
                {
                        for(int j=0;j<rows_;j++)
                        {
                             temp.mat[i][j] = mat[i][j]-rhs.mat[i][j];
                              
                        }
                }
                return (temp);
        }

        //function for matrix multiplication
        Matrix operator*(const Matrix& m1)
        {
            if(cols_ != m1.rows_)
            {
                cout<<"invalid multiplication- The dimensions of the matrix are not apt for multiplication"<<endl;
                exit(1);
            }
            Matrix<T> temp(rows_,m1.cols_);
     
            for(int i =0;i<rows_ ;i++)
            {
                for(int j=0;j<m1.cols_;j++)
                {
                    for(int k=0;k<m1.rows_;k++)
                        temp.mat[i][j] += mat[i][k] * m1.mat[k][j];

                }
            }
            return temp;
        }

		//trace of the matrix 
        T trace()
        {
            if(!isSquare())
            {
                cout<<"Invalid arguments-- requires a square matrix\n";
                 exit(1);
            }
            
            T temp = T();
            for(int i =0;i<rows_;i++)
                temp += mat[i][i];
            return temp;

        }

        //gives the respective power of the matrix using multiplication
		Matrix pow(int pwr)
		{
			if((*this).isIdentity()||(*this).isZero())
				return *this;
			Matrix<T> temp(rows_,cols_);
			temp=*this;
			for(int i=1;i<pwr;i++)
			{
				temp=temp * (*this);
			}
			return temp;
		}

		

		/*For calculating Determinant of the Matrix -takes in the number of rows*/
		T determinant(int temp)
		{

		  if(temp>rows_)
		  {
			  cout<<"Please provide the proper number of rows for calculating the determinant.\n"<<endl;
			  exit(1);
		  }
		   if(!isSquare())
		  {
			  cout<<"Please provide a square matrix for the calculation of determinant matrix\n";
			  exit(1);
		  }
		  if(isIdentity())
		  	return 1;
		  if(isZero())
		  	return 0;
		int i,j,m,n,c;
		double s=1,det=0;
		Matrix<T> b(rows_,cols_);
		if (temp==1)
		{
			return (mat[0][0]);
		}
		  else
			{
			 det=0;
			 for (c=0;c<temp;c++)
			   {
				m=0;
				n=0;
				for (i=0;i<temp;i++)
				  {
					for (j=0;j<temp;j++)
					  {
						b.mat[i][j]=0;
						if (i != 0 && j != c)
						 {
						   b.mat[m][n]=mat[i][j];
						   if (n<(temp-2))
							n++;
						   else
							{
							 n=0;
							 m++;
							 }
						   }
					   }
					 }
				  det=det + s * (mat[0][c] * b.determinant(temp-1));
				  s=-1 * s;
				  }
			}
 
			return (det);
		}

		//checks if the matrix is square matrix
		bool isSquare()
		{
			return (rows_==cols_);
		}

		//checks if the matrix is diagonal matrix
		bool isDiagonal()
		{
			if(!isSquare())
			{
				cout<<"Provide a square matrix.\n"<<endl;
				exit(1);
			}
			for(int i=0;i<rows_;i++)
				for(int j=0;j<cols_;j++)
				{
					if(i==j)
						continue;
					if(mat[i][j]!=0)
						return false;
				}
				return true;
		}

		//checks if the matrix is symmetric
		bool isSymmetric()
		{
			if(!isSquare())
			{
				cout<<"Provide a square matrix.\n";
				exit(1);
			}

			if(transpose()==*this)
				return true;
			return false;
		}

		//checks if the matrix is skew-symmetric matrix
		bool isSkewSymmetric()
		{
			if(!isSquare())
			{
				cout<<"Please provide a square matrix."<<endl;
				exit(0);
			}

			for(int i=0;i<rows_;i++)
				for(int j=0;j<rows_;j++)
					if(i!=j)
						if(mat[i][j]!= (-mat[j][i]))
							return false;
			return true;
		}

		//checks if the matrix is a zero matrix
		bool isZero()
		{
			if(!isDiagonal())
				return false;
			for(int i=0;i<rows_;i++)
			{
				if(mat[i][i]!=0)
					return false;
			}
			return true;
		}

		//cheks if the matrix is an identity matrix
		bool isIdentity()
		{
			if(!isDiagonal())
				return false;
			for(int i=0;i<rows_;i++)
			{
				if(mat[i][i]!=1)
					return false;
			}
			return true;
		}

		//cheks if the matrix is upper triangular
		bool isUpperTriangular()
		{
			if(isDiagonal())
				return true;
			for(int i=0;i<rows_;i++)
				for(int j=0;j<cols_;j++)
				{
					if(i>j)
					{
						if(mat[i][j]!=0)
							return false;
					}
				}
			return true;
		}

		//checks if the matrix is lower triangular
		bool isLowerTriangular()
		{
			if(isDiagonal())
				return true;
			for(int i=0;i<rows_;i++)
				for(int j=0;j<cols_;j++)
				{
					if(j>i)
					{
						if(mat[i][j]!=0)
							return false;
					}
				}
			return true;
		}	

	

	 	//function for scalar multiplication

	    Matrix<T> operator*(double scalar)
        {
		 	Matrix<T>temp(rows_,cols_);
		  	for(int i=0;i<rows_;i++)
		    	for(int j=0;j<cols_;j++)
		      		temp.mat[i][j] = scalar *mat[i][j];
		  	return temp;
	    }

		// function to find if a matrix is singular
       bool isSingular()
       {
			if(determinant(rows_) == 0)
			  return true;
			else
			  return false;
        }

				  // trying to find the cofactor of a matrix.

       Matrix<T> coFactor()
       {
	    //check if square matrix
	    if(rows_ != cols_)
	    {
	     cout<<"Invalid matrix -- The argument must be a square matrix."<<endl;
	     exit(1);
	    }
	    if(rows_ == 1)
	 	 return *this;
	    if((*this).isZero()||((*this).isIdentity()))
	 	 return *this;
	    Matrix<T> temp2(rows_,cols_);

	    //write a special case for 2*2  matrices as we do not have to do any kind of arithmetic operation or allocate extra memory.
	    if(rows_ == 2)
	    {
	    
	      temp2.mat[0][0] = mat[1][1];
	      temp2.mat[0][1] = -mat[1][0];
	      temp2.mat[1][0] = -mat[0][1];
	      temp2.mat[1][1] = mat[0][0];
	      return temp2;

	    }

	    
	    int temp;
	    Matrix<T> temp1(rows_-1,cols_-1);
	  	for(int i =0;i<rows_;i++)
	  		{
	    		for(int j =0;j<cols_;j++)
	    		{
	      		
	      		int m=0,n=0;
				for(int k =0;k<rows_;k++)
				{
		  		for(int l =0;l<cols_;l++)
 
			    if(k != i && l != j)
			    {
			      temp1.mat[m][n] = mat[k][l];
		    	  n++;
		      		if(n == cols_-1)
		      		{
		        		n =0;m++;
		      		}
		    	}

				}
		if((i+j) %2 == 0)
		    temp = 1;
		else 
		  temp = -1;
		if(temp1.determinant(rows_-1) == 0)
		  temp2.mat[i][j] = temp1.determinant(rows_-1);
		else
		temp2.mat[i][j] = temp*temp1.determinant(rows_-1);
	    }
	 }  

	    return temp2;
    }

       // function to find the adjoint of a matrix.
	   Matrix<T> adjoint()
       {
			return (coFactor().transpose());
       }

       //function to find the inverse of a matrix.
       Matrix<T> inverse()
       {
			//since determinent returns double... the division leads to double value
			if(isSingular())
			{
			  cout<<"The matrix is singular -- determinant is zero .Hence inverse doesnt exist\n";
			  exit(1);
			}
			if(isIdentity())
				return *this;

			double det = determinant(rows_);
			Matrix<T> temp(rows_,cols_);
			Matrix<T> temp1(rows_,cols_);
			temp1 = adjoint();
			if(!isSingular())
			{
			for(int i =0;i<rows_;i++)
			  for(int j=0;j<cols_;j++)
			    temp.mat[i][j] = temp1.mat[i][j] / det;
			}

			return temp;

       }


      //projection of a matrix is given as A(Atranspose A)inverse *A transpose 
       Matrix<T> projection ()
       {
	       	Matrix<T> temp(rows_,cols_); 

	       	temp = transpose() * (*(this))  ;
	       	temp = temp.inverse();
	       	temp = (*this) * temp;
	       	temp = temp * transpose() ;
	       	return temp;
       }
        
       //finding norm of a matrix --- square root of the sum of the squares of the diagonal elements
       double norm()
       {
	       	if(!isSquare())
	       	{
	       		cout<<"Invalid input -- enter a square matrix\n";
	       		exit(0);
	       	}
	       	int sum=0;
	       	for(int i =0;i<rows_;i++)
	       	{
	       		sum +=mat[i][i] * mat[i][i];
	       	}
	       	return (sqrt(sum));
       }


       // slicing by taking range of rows and cols  -- parameters : row_start row_end col_start col_end

       Matrix<T> slice(int row_start , int row_end , int col_start , int col_end)
       {

       	   if( row_end < row_start || col_end < col_start || row_start < 0 || col_start < 0 || row_end > rows_ || col_end > cols_ ||row_end<0||col_end<0)
       	   {
       	   	cout<<"Enter valid values of rows and cols with row and col range greater than zero"<<"\n";
       	   	exit(0);
       	   }
       	   	Matrix<T> temp(row_end-row_start+1 , col_end-col_start+1);
       	   	
       	   	int l = 0 ;
       	   	int k =0; 
       	   for( int i = row_start ;i<= row_end ;i++)
       	   {
       	   	    k= 0;
       	   		for ( int j = col_start ; j<= col_end ; j++)
       	   		{
       	   				temp.mat[l][k] = mat[i][j];
       	   				k++;
       	   		}
       	   		l++;
       	   }
    
       	   return temp;

       }

       //diagonal slicing of the matrix 
	   Matrix<T> diagonalSlice(int diagonalIndex, int startRow,int endRow)
	   {
		   if(diagonalIndex<0 || diagonalIndex>rows_ ||(endRow-startRow)>rows_)
		   {
			   cout<<"Please provide the correct index and the number of elements."<<endl;
		   }
		   	int count=endRow-startRow+1;
		   	Matrix<T> temp(1,count);
			int j=startRow;
			int k=startRow+diagonalIndex;
			count=endRow-startRow;
		   for(int i=0 ; i<=count ; i++ )
		   {
			   	temp.mat[0][i]=mat[j][k];
				j++;
				k++;
			   
		   }
		   cout<<temp;
		   return temp;
	   }

	//friend funxtions   
	template<typename V>
	friend ostream &operator<<( ostream &cout, const Matrix<V> m );
	template<typename U>
	friend Matrix<U> GaussianElimination(Matrix<U>& , Matrix<U>&);
	//overloading equals operator - to check equality of matrices
	template<typename U>
	friend bool operator==(const Matrix lhs,const Matrix rhs);
	template<typename U>
	friend bool operator!=(Matrix<U> lhs, Matrix<U> rhs);
	 
      //Iterator class  
	class Iterator{
	public:
			Matrix<T> m_obj;
			int currow;
			int curcol;
			
		//constructor
		explicit Iterator(Matrix<T> m, int r=0, int c=0)
				: m_obj(m), currow(r), curcol(c){}

		Iterator(const Iterator& obj)
			: m_obj(obj.m_obj), currow(obj.currow), curcol(obj.curcol)
		{
		}
	                T operator*()
	                {
	                    return (m_obj[currow][curcol]);
	                }

	                bool operator==(const Iterator& rhs) const
	                {
	                    return (m_obj==rhs.m_obj && currow==rhs.currow && curcol==rhs.curcol);
	                }

	                bool operator!=(const Iterator& rhs) const
	                {
	                
	                    return !(*this == rhs);
	                }

	                Iterator& operator++() // pre
	                {
	                	
						curcol++;
						if(curcol==m_obj.cols_)
						{
							curcol=0;
							currow++;
						}
		
	                    return *this;
	                }

	                Iterator operator++(int) // post
	                {
				
	                     Iterator temp(*this);
			     ++*this;
	                     return temp;

	                }
	
	};

    Iterator begin()
    {
        return (Iterator(*this,0,0));
    }
    Iterator end()
    {
        return ( Iterator( *this ,rows_, 0) );
    }


      //rowwise iterator class  
	class Row_Iterator
	{
		public:
			Matrix<T> 	m_obj;
			int currow;
			int curcol;
			
		//ctor
		explicit Row_Iterator(Matrix<T> m, int r=0, int c=0)
				: m_obj(m), currow(r), curcol(c)
		{
			//cout<<"iterator ctor"<<endl; 
			
		}
		Row_Iterator(const Row_Iterator& obj)
			: m_obj(obj.m_obj), currow(obj.currow), curcol(obj.curcol)
		{
		}
	                T operator*()
	                {
	                    return (m_obj[currow][curcol]);
	                }

	                bool operator==(const Row_Iterator& rhs) const
	                {
	                    return (m_obj==rhs.m_obj && currow==rhs.currow && curcol==rhs.curcol);
	                }

	                bool operator!=(const Row_Iterator& rhs) const
	                {
	                
	                    return !(*this == rhs);
	                }

	                Row_Iterator& operator++() // pre
	                {
	                	
				curcol++;
				if(curcol==m_obj.cols_)
				{
					curcol=0;
					currow++;
				}
		
	                    	return *this;
	                }

	                Row_Iterator operator++(int) // post
	                {
				
	                     Row_Iterator temp(*this);
			     ++*this;
	                     return temp;

	                }
		
	};


	Row_Iterator rowwise_begin(int row)//row specified as 0,1,2,3,4,...
	{
		if(row<0 || row>=rows_)
		{
			cout<<"Invalid row given\n";
			exit(1);
		}
		return (Row_Iterator(*this,row,0));
	}

	Row_Iterator rowwise_end(int row)
	{
		if(row<0 || row>=rows_)
		{
			cout<<"Invalid row given\n";
			exit(1);
		}
		return (Row_Iterator(*this,row+1,0));
	}


    //column wise iterator class  
	class Col_Iterator
	{
	public:
		Matrix<T> m_obj;
		int currow;
		int curcol;
		
	//ctor
	explicit Col_Iterator(Matrix<T> m, int r=0, int c=0)
			: m_obj(m), currow(r), curcol(c)
	{
	
	}
	Col_Iterator(const Col_Iterator& obj)
		: m_obj(obj.m_obj), currow(obj.currow), curcol(obj.curcol)
	{
	}
                T operator*()
                {
                    return (m_obj[currow][curcol]);
                }

                bool operator==(const Col_Iterator& rhs) const
                {
                    return (m_obj==rhs.m_obj && currow==rhs.currow && curcol==rhs.curcol);
                }

                bool operator!=(const Col_Iterator& rhs) const
                {
                
                    return !(*this == rhs);
                }

                Col_Iterator& operator++() // pre
                {
                	
			currow++;
			if(currow==m_obj.rows_)
			{
				currow=0;
				curcol++;
			}
	
                    	return *this;
                }

                Col_Iterator operator++(int) // post
                {
			
                     Col_Iterator temp(*this);
		     ++*this;
                     return temp;

                }
	
	};


	Col_Iterator colwise_begin(int col)
	{
		if(col<0 || col>=cols_)
		{
			cout<<"Invalid col given\n";
			exit(1);
		}
		return (Col_Iterator(*this,0,col));
	}
	Col_Iterator colwise_end(int col)
	{
		if(col>cols_||col<0)
		{
			cout<<"Invalid col given\n";
			exit(1);
		}
		return (Col_Iterator(*this,0,col+1));
	}

	void addRow()
	{
		Matrix<T> temp(rows_+1,cols_);

                cout<<"add row"<<endl;

                for(int i=0;i<rows_;i++)
                {
                        for(int j=0;j<cols_;j++)
                        {
                                temp[i][j] = mat[i][j]; 
                        }
                }
		*this = temp;  //can be made more efficient using move semantics
	}

	void addCol()
	{
		Matrix<T> temp(rows_,cols_+1);

                cout<<"add col"<<endl;

                for(int i=0;i<rows_;i++)
                {
                    for(int j=0;j<cols_;j++)
                    {
                        temp[i][j] = mat[i][j]; 
                    }
                }
		*this = temp;  //can be made more efficient using move semantics
	}

};

template<typename V>
ostream &operator<<( ostream &cout, const Matrix<V> m )
{ 
	for(int i=0;i<m.rows_;i++)
    {
        for(int j=0;j<m.cols_;j++)
        {
                cout<<m.mat[i][j]<<"\t";
        } 
        cout<<"\n";
    }
    return cout;        
}

template<typename U>
bool operator==(Matrix<U> lhs, Matrix<U> rhs)
{
	int lhsRows=lhs.getRows();
	int lhsCols=lhs.getCols();
	int rhsRows=rhs.getRows();
	int rhsCols=rhs.getCols();
	if(lhsRows!=rhsRows||lhsCols!=rhsCols)
		return false;
	for(int i=0;i<lhsRows;i++)
		for(int j=0;j<lhsCols;j++)
		{
			if(lhs[i][j]!=rhs[i][j])
				return false;
		}
		return true;
}

     //scalar multiplication
  template<typename T>
  Matrix<T> operator*(double scalar ,  Matrix<T>& m)
       {
          return m * scalar;
       }

       //solve linear equations  using Gaussian elimination
       template<typename U>
       Matrix<U> GaussianElimination ( Matrix<U>& lhs,  Matrix<U>& rhs)
       {
       	//check for conditions
       	if(lhs.rows_ != rhs.rows_  || lhs.rows_ < lhs.cols_ || rhs.cols_ != 1)
       	{
       		cout<<"Invalid input --- the rhs and lhs matrices must have the same number of rows \n";
       		exit(0);
       	}
       	//augmented matrix.
       	int pivotrow=0;
       	lhs.addCol();
       	for(int i =0;i< lhs.rows_ ;i++)
       		lhs.mat[i][lhs.cols_-1] = rhs.mat[i][0];          
       	for(int i =0;i< lhs.rows_-1 ; i++)
       	{
       		pivotrow = i;
       		for(int j =i+1 ; j<lhs.rows_ ;j++)
       		{
       			if(fabs(lhs.mat[j][i]) > fabs(lhs.mat[pivotrow][i]))
       				pivotrow = j;
       		}
       		for(int k = i ; k<lhs.cols_ ; k++)
       		{
       			 U temp;
       			//swapping the two rows
       			for(int h =0;h<lhs.cols_;h++)
       			{
       				temp = lhs.mat[i][k];
       				lhs.mat[i][k] = lhs.mat[pivotrow][k];
       				lhs.mat[pivotrow][k] = temp;
       			}
       		}
       		for(int j = i+1;j < lhs.rows_;j++)
       		{
       			U temp;
       			temp = lhs.mat[j][i] / lhs.mat[i][i];
       			for(int k =i;k<lhs.cols_;k++)
       			{
       				lhs.mat[j][k] = lhs.mat[j][k] - lhs.mat[i][k] * temp;
       			}
       		}
       	}
       	return lhs;
       }

       template<typename U>
		bool operator!=(Matrix<U> lhs, Matrix<U> rhs)
		{
       			return !(lhs==rhs);
		}
#endif      

