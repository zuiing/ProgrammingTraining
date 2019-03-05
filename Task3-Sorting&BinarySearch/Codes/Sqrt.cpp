#include <iostream>
using namespace std;
double mySqrt(double x,double precision){
	double l = 0, r = x,mid;
	while ((r - l)>precision)
	{
		mid = (l + r) / 2;		
		if (mid > x / mid) r = mid;
		else l = mid;
	}
	return l;
}
//Å£¶Ùµü´ú
double mySqrt2(double x, double precision){
	double r = x;
	while ((r*r - x)>precision)
	{
		r = (r + x / r) / 2;
	}
	return r;
}
int main(){
	cout << mySqrt(2,1e-5);
	cout << endl;
	cout << mySqrt2(2, 1e-5);
	return 0;
}

