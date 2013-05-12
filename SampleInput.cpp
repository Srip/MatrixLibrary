	#include"matrix.h"
#include<iostream>
using namespace std;
int main()
{
	Matrix<int> zero(4,4);
	Matrix<int> identity(3,3);
	Matrix<int> upper(2,2);
	Matrix<double> lower(2,2);
	Matrix<int> temp(3,3);
	Matrix<int> a(3,3);
	Matrix<int> b(3,3);
	Matrix<int> diagonal(2,2);
	diagonal[0][0]=0;
	diagonal[1][1]=0;
	cout<<diagonal.isDiagonal();
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			temp[i][j]=i+j*2+1;
			a[i][j]=i*2+1;
			b[i][j]=i+j*2-1;
		}
	upper[0][1]=2;
	lower[1][0]=3;
	for(int i=0;i<3;i++)
		identity[i][i]=1;
	cout<<"a= \n"<<a<<endl;
	cout<<"b= \n"<<b<<endl;
	Matrix<int>temp1(temp);//copy ctor works
	cout<<(temp==temp1)<<endl;//Checked for unequal stuff too 
	//Matrix<double> temp=identity; -->assignment workin fine
	temp1=identity.transpose();
	cout<<"THE MATRIX IS \n"<<upper;
	cout<<"TRANSPOSE IS \n"<<temp1;
	a=a+b;
	cout<<a<<endl;
	a=a-b;
	cout<<"Difference"<<endl;
	cout<<a<<endl;
	cout<<"\n"<<b<<endl;
	a=a*b;
	cout<<a;
	cout<<"TRACE OF B IS"<<b.trace()<<"\n";
	cout<<b.pow(2)<<endl;
/*


	cout<<b.pow(80)<<endl;   not working as in it is getting converted to numbers larger than int so wont work ??


	*/
	cout<<"Determinant of b is"<<b.determinant(3);
	cout<<"\nIS skew symmetric??"<<zero.isSkewSymmetric()<<" "<<identity.isSkewSymmetric()<<" "<<upper.isSkewSymmetric()<<" "<<lower.isSkewSymmetric()<<" "<<temp.isSkewSymmetric()<<endl;
	cout<<a.isSingular();
	cout<<"IS upper triangular??"<<zero.isUpperTriangular()<<" "<<identity.isUpperTriangular()<<" "<<upper.isUpperTriangular()<<" "<<upper.isLowerTriangular()<<" "<<temp.isLowerTriangular()<<endl;
	cout<<"IS lower triangular??"<<zero.isLowerTriangular()<<" "<<identity.isLowerTriangular()<<" "<<upper.isLowerTriangular()<<" "<<lower.isLowerTriangular()<<" "<<temp.isLowerTriangular()<<endl;
	cout<<2*a;
	cout<<a*2;
	cout<<"B IS\n"<<b;
	cout<<"COFACTOR OF B"<<"\n"<<b.coFactor();
	cout<<"ADJOINT OF B"<<"\n"<<b.adjoint();
	//cout<<"INVERSE OF A"<<"\n"<<a.inverse();
	cout<<"INVERSE OF B"<<"\n"<<identity.inverse();
	for(Matrix<int>::Iterator it= a.begin();it!=a.end();++it)
		cout<<*it<<"\t";
	Matrix<int>::Iterator it1= a.begin();
	Matrix<int>::Iterator it2= b.begin();
	
	cout<<"\n"<<(it1==it2)<<endl;
	if(a != b)
		cout<<"false";

}
