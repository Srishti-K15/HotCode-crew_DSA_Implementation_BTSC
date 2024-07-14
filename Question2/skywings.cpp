#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class Seat {
public:
    int row;
    char type; // 'W' -window, 'A' -aisle, 'M' -middle

    Seat(int row, char type) : row(row), type(type) {}
};

// Class to represent a flight
class Flight {
private:
    int numRows;
    int count=0;
    vector<vector<Seat*>> seats;
    queue<int> waitingList;
    map<int, set<Seat*>> reservedSeats;

    //  initialize seats based on the provided layout
    void initializeSeats(const vector<vector<string>>& layout) {
        numRows = layout.size();
        for (int i = 0; i < numRows; ++i) {
            vector<Seat*> rowSeats;
            for (int j = 0; j < layout[i].size(); ++j) {
                rowSeats.push_back(new Seat(i + 1, layout[i][j][0]));
            }
            seats.push_back(rowSeats);
        }
    }

    // check if a seat is available
    bool isSeatAvailable(const Seat& seat) {
        return reservedSeats.find(seat.row) == reservedSeats.end(); 
            //   || reservedSeats[seat.row].find(&seat) == reservedSeats[seat.row].end();
    }

public:
    Flight(const vector<vector<string>>& layout) {
        initializeSeats(layout);
    }

    //1) Function to initialize flight seats
    void initializeFlight(const vector<vector<string>>& layout) {
        initializeSeats(layout);
    }

    //2) Function to reserve a seat
    bool reserveSeat(int row, char type, int passengerId) {
        Seat* seat = nullptr;
        for (auto& rowSeats : seats) {
            for (auto& s : rowSeats) {
                if (s->row == row && s->type == type && isSeatAvailable(*s)) {
                    seat = s;
                    break;
                }
            }
            if (seat) {
                break;
            }
        }

        if (seat) {
            reservedSeats[row].insert(seat);
            return true;
        } else {
           waitingList.push(passengerId);
            waitingLists(); // Check if there are available seats for waiting list passengers
        return false;
        }
    }

    //3) Function to check seat availability
    bool checkSeatAvailability(char type) {
        for (auto& rowSeats : seats) {
            for (auto& seat : rowSeats) {
                if (seat->type == type && isSeatAvailable(*seat)) {
                    return true;
                }
            }
        }
        return false;
    }

    //4) Function to suggest optimal seat
    Seat* suggestOptimalSeat(char preference) {
        if (preference == 'A') { // Aisle preference
            for (auto& rowSeats : seats) {
                for (auto& seat : rowSeats) {
                    if (seat->type == 'A' && isSeatAvailable(*seat)) {
                        return seat;
                    }
                }
            }
        } else if (preference == 'W') { // Window preference
            for (auto& rowSeats : seats) {
                for (auto& seat : rowSeats) {
                    if (seat->type == 'W' && isSeatAvailable(*seat)) {
                        return seat;
                    }
                }
            }
        } else { // Any preference
            for (auto& rowSeats : seats) {
                for (auto& seat : rowSeats) {
                    if (isSeatAvailable(*seat)) {
                        return seat;
                    }
                }
            }
        }

        return nullptr; // No available seats
    }

    //5) Function to handle waiting list
    void waitingLists() {
      int count=0;
    // Check if there are available seats
    for (auto& rowSeats : seats) {
        for (auto& seat : rowSeats) {
            count++;
            if (isSeatAvailable(*seat) && count==1) {
                
                // Check if there are passengers on the waiting list
                if (!waitingList.empty() ) {
                    int passengerId = waitingList.front();
                    waitingList.pop();
                    reserveSeat(seat->row, seat->type, passengerId);
                    cout << "Passenger " << passengerId << " has been assigned seat " << seat->row << seat->type << endl;
                }
                else{
                    cout<<"Waiting list is empty"<<endl;
                }
                
            }
            
        }
    }
}
    

    //6) Function to cancel reservation
    void cancelReservation(int row, char type, int passengerId) {
        Seat* seat = nullptr;
        for (auto& rowSeats : seats) {
            for (auto& s : rowSeats) {
                if (s->row == row && s->type == type) {
                    seat = s;
                    break;
                }
            }
            if (seat) {
                break;
            }
        }

        if (seat) {
            reservedSeats[row].erase(seat);
            // Update waiting list if necessary
            waitingLists();
        } else {
            // Handle case where reservation is not found
            cout<<"Reservation NOT found !"<<endl;
        }
    }

    // 7) Function to change reservation
    bool changeReservation(int oldRow, char oldType, int newRow, char newType, int passengerId) {
        Seat* oldSeat = nullptr;
        Seat* newSeat = nullptr;
        for (auto& rowSeats : seats) {
            for (auto& s : rowSeats) {
                if (s->row == oldRow && s->type == oldType) {
                    oldSeat = s;
                }
                if (s->row == newRow && s->type == newType) {
                    newSeat = s;
                }
            }
            if (oldSeat && newSeat) {
                break;
            }
        }

        if (oldSeat && newSeat && isSeatAvailable(*newSeat)) {
            reservedSeats[oldSeat->row].erase(oldSeat);
            reservedSeats[newSeat->row].insert(newSeat);
            return true;
        } else {
            
            return false;
        }
    }
};

int main() {
    // flight layout
    vector<vector<string>> layout = {
        {"W", "M", "A"},
        {"W", "M", "A"},
        {"W", "M", "A"},
        {"W", "M", "A"},
        {"W", "M", "A"},
        {"W", "M", "A"},
        {"W", "M", "A"}
    };

    Flight flight(layout);

    // Example 
    flight.initializeFlight(layout);

    if (flight.reserveSeat(3, 'W', 1)) {
        cout << "Seat reserved successfully!" << endl;
    } else {
        cout << "Seat is not available. Added to waiting list." << endl;
    }

  
    if (flight.checkSeatAvailability('A')) {
        cout << "Aisle seat available." << endl;
    } else {
        cout << "No aisle seats available." << endl;
    }

 
    Seat* suggestedSeat = flight.suggestOptimalSeat('W');
    if (suggestedSeat) {
        cout << "Suggested seat: Row " << suggestedSeat->row << ", Type: " << suggestedSeat->type << endl;
    } else {
        cout << "No suitable seat available." << endl;
    }

    flight.waitingLists();
    
    return 0;
}