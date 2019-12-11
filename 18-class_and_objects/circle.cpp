#include <sstream>

class Circle {
	const double PI = 3.14159;
	
	public:
		Circle(){
			r = 0.0;
		}
		
		Circle(double radius){
			r = radius;
		}
		
		double area(){
			return PI*r*r;
		}
		
		double circumference(){
			return 2*PI*r;
		}
		
		double getRadius(){
			return r;
		}
		
		string toString(){
			std::ostringstream r_oss;
			r_oss << r;
			std::string r_str = r_oss.str();
			return "Circle{radius=" + r_str + "}";
		}
	
	private:
		double r;
};