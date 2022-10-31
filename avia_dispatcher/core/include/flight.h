//
// Created by igor on 31.10.22.
//

#ifndef AVIA_DISPATCHER_FLIGHT_H
#define AVIA_DISPATCHER_FLIGHT_H


#include <string>
#include <vector>

struct SeatData {
    int place_number;
    bool is_taken{false};
    std::string passenger_name;
    std::string passenger_surname;
};



class Flight {


public:
    Flight(int flight_number, int seats_amount) : flight_number_(flight_number), seats_amount_(seats_amount){};

    


private:
    int flight_number_;
    int seats_amount_;
    std::vector<SeatData> seats_data_;
};
#endif //AVIA_DISPATCHER_FLIGHT_H
