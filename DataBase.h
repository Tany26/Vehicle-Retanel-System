#ifndef database_h



#define database_h

#include "Vehicle.h"
#include "USER.h"
#include "TRIP.h"
#include "Table.cpp"
#include "error.cpp"



using namespace std;

class Database
{

private:
    Table<Vehicle> *vehicleTable;

    Table<User> *userTable;

    Table<Trip> *tripTable;


    void fetchAllVehicle() throw (IOError,MemoryError);

    void fetchAllUser() throw (IOError,MemoryError);

    void fetchAllTrip() throw (IOError,MemoryError);


    void cleanUp();
public:
    Database() throw(IOError,MemoryError);

    ~Database();

    const Table<Vehicle> *const getVehicleRef() const;

    const Table<User> *const getUserRef() const;

    const Table<Trip> *const getTripRef() const;


     const Vehicle * const getVehicle(string RegistrationNo) const throw (IOError);

    const User * const getUser(string contact) const throw (IOError);

    const vector<const Vehicle *>  getVehicle(Date stDate,Date enDate,VehicleType type) const throw(IOError);

    template <class T> void addNewRecord(T* record) throw (IOError,MemoryError);

    template <class T> void updateRecord(T* record) throw(IOError,MemoryError);


};
#endif // database_h
