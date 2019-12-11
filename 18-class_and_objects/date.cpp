#include <iomanip>

class Date {
	public:
		Date(){
			m = 0;
			d = 0;
		}
		
		Date(int month, int day){
			m = month;
			d = day;
		}
		
		int daysInMonth(){
			switch (m) {
			case 2:
				return 28;
			case 4:
			case 6:
			case 9:
			case 11:
				return 30;
			default:
				return 31;
			}
		}
		
		int getDay(){
			return d;
		}
		
		int getMonth(){
			return m;
		}
		
		void nextDay(){
			int nDaysInMonth = daysInMonth();
			
			if(d < nDaysInMonth) {
				d++;
			
			// wrapping to next month
			} else {
				d = 1;
				
				if(m != 12) {
					m++;
				
				// wrapping to next year
				} else {
					m = 1;
				}
			}
		}
		
		string toString(){
			std::ostringstream date_oss;
			date_oss << setw(2) << setfill('0') << m << "/" << setw(2) << setfill('0') << d ;
			std::string date_str = date_oss.str();
			return date_str;
		}
	
	private:
		int m, d;
};