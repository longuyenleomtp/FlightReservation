#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <sstream>

using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "PhamLongUyen@1";
const char* DB = "flightreservation";

class Flight{
	private:
		string flightID, airline, flightType, time, depart, desti;
		int seatNum;
	public:
		Flight(){
			this->flightID = "";
			this->airline = "";
			this->flightType = "";
			this->time = "";
			this->depart = "";
			this->desti = "";
			this->seatNum = 0;
		}
		Flight(string flightID, string airline, string flightType, string time, string depart, string desti, int seatNum){
			this->flightID = flightID;
			this->airline = airline;
			this->flightType = flightType;
			this->time = time;
			this->depart = depart;
			this->desti = desti;
			this->seatNum = seatNum;
		}
		string getFlightID() {
			return flightID;
		}
		string getAirLine(){
			return airline;
		}
		string getFlightType(){
			return flightType;
		}
		string getTime() {
			return time;
		}
		string getDepart(){
			return depart;
		}
		string getDesti(){
			return desti;
		}
		int getSeatNum(){
			return seatNum;
		}
		void setFlightID(string flightID){
			this->flightID = flightID;
		}
		void setAirLine(string airline){
			this->airline = airline;
		}
		void setFlightType(string flightType){
			this->flightType = flightType;
		}
		void setTime(string time){
			this->time = time;
		}
		void setDepart(string depart){
			this->depart = depart;
		}
		void setDesti(string desti){
			this->desti = desti;
		}
		void setSeatNum(int seatNum){
			this->seatNum = seatNum;
		}
};

void display(MYSQL* conn) {
	string dis = "SELECT * FROM airline";
	if(mysql_query(conn,dis.c_str())){
		cout << "Error: " << mysql_error(conn);
	} else {
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		if(res){
			int num = mysql_num_fields(res);
			MYSQL_ROW row;
			while(row = mysql_fetch_row(res)){
				for(int i = 0; i< num; i++){
					cout << " " << row[i]; 
				}
				cout << endl;
			}
		}
	}
}


int main() {
	
	MYSQL* conn;
	conn = mysql_init(NULL);
	
	if(!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)){
		cout << "Error: " << mysql_error(conn);
	} else {
		cout << "Logged in Successfully!" << endl;
	}
	
	Flight f1("VJ1902", "Vietjet Air", "A320", "19:00 12/03/2024", "Da Nang (DAD)", "Ha Noi (HAN)", 170);
	Flight f2("VJ1502", "Vietjet Air", "A320", "14:00 13/03/2024", "Da Nang (DAD)", "TP HCM (SGN)", 126);
	Flight f3("VN7211", "Vietnam Airlines", "Boeing 787", "7:00 13/03/2024", "Da Nang (DAD)", "Da Lat (DLI)", 210);
	Flight f4("VU753", "Viettralvel Airlines", "A321 Neo", "18:00 13/03/2024", "Da Nang (DAD)", "Dong Hoi (VDH)", 170);
	Flight f5("QH1201", "Bamboo Airways", "A350", "19:00 14/03/2024", "Da Nang (DAD)", "Nha Trang (CXR)", 170);
	
	string insert1 = "INSERT INTO airline (flightID, airline, flightType, time, depart, desti, seatNum) VALUES('"+f1.getFlightID()+"', '"+f1.getAirLine()+"', '"+f1.getFlightType()+"', '"+f1.getTime()+"', '"+f1.getDepart()+"', '"+f1.getDesti()+"', '"+to_string(f1.getSeatNum())+"')";      
	string insert2 = "INSERT INTO airline (flightID, airline, flightType, time, depart, desti, seatNum) VALUES('"+f2.getFlightID()+"', '"+f2.getAirLine()+"', '"+f2.getFlightType()+"', '"+f2.getTime()+"', '"+f2.getDepart()+"', '"+f2.getDesti()+"', '"+to_string(f2.getSeatNum())+"')";  
	string insert3 = "INSERT INTO airline (flightID, airline, flightType, time, depart, desti, seatNum) VALUES('"+f3.getFlightID()+"', '"+f3.getAirLine()+"', '"+f3.getFlightType()+"', '"+f3.getTime()+"', '"+f3.getDepart()+"', '"+f3.getDesti()+"', '"+to_string(f3.getSeatNum())+"')";  
	string insert4 = "INSERT INTO airline (flightID, airline, flightType, time, depart, desti, seatNum) VALUES('"+f4.getFlightID()+"', '"+f4.getAirLine()+"', '"+f4.getFlightType()+"', '"+f4.getTime()+"', '"+f4.getDepart()+"', '"+f4.getDesti()+"', '"+to_string(f4.getSeatNum())+"')";  
	string insert5 = "INSERT INTO airline (flightID, airline, flightType, time, depart, desti, seatNum) VALUES('"+f5.getFlightID()+"', '"+f5.getAirLine()+"', '"+f5.getFlightType()+"', '"+f5.getTime()+"', '"+f5.getDepart()+"', '"+f5.getDesti()+"', '"+to_string(f5.getSeatNum())+"')";  
	
	if(mysql_query(conn, insert1.c_str()) || mysql_query(conn, insert2.c_str()) || mysql_query(conn, insert3.c_str()) || mysql_query(conn, insert4.c_str()) || mysql_query(conn, insert5.c_str())) {
		cout << "Error: " << mysql_error(conn);
	} else {
		cout << "Inserted Successfully!" << endl;
	}
	
	
	bool exit = false;
	while(!exit){
		cout << endl;
		display(conn);
		cout << endl;
		cout << "Welcome to Danang International Airport!" << endl;
		cout << "========================================" << endl;
		cout << "1. Reserve a seat." << endl;
		cout << "2. Exit." << endl;
		
		int option;
		cout << "Enter your option: ";
		cin >> option;
		
		if(option == 1){
			string flightID;
			int numberTicket;
			cout << endl;
			cout << "Enter Flight ID: ";
			cin >> flightID;
			cin.ignore();
			cout << "Enter number of tickets: ";
			cin >> numberTicket;
			
			int total;
			
			string check = "SELECT seatNum from airline WHERE flightID = '"+flightID+"' ";
			if(mysql_query(conn, check.c_str())){
				cout << "Error: " << mysql_error(conn);
			} else {
				MYSQL_RES* res;
				res = mysql_store_result(conn);
				if(res){
					MYSQL_ROW row = mysql_fetch_row(res);
					total = atoi(row[0]);
				}
			}
			
			if(total-numberTicket>=0){
				total-=numberTicket;
				string update = "UPDATE airline SET seatNum = '"+to_string(total)+"' WHERE flightID = '"+flightID+"' ";
				if(mysql_query(conn, update.c_str())){
					cout << "Error: " << mysql_error(conn);
				} else {
					cout << "Reserved Seat Successfully in flight " << flightID << endl;
				}
				if(total == 0){
					cout << "Sorry! No Enought Seat available!" << endl;
				}
			} else {
				cout << "Not enough " << numberTicket << " tickets! We only have " << total << " tickets! Try again!";
			}
			
		} else if(option == 2){
			exit = true;
			cout << "See you again!" << endl;
		}
	}
	
	return 0;
}














