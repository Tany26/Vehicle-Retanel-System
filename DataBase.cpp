#ifndef database_cpp



#define database_cpp

#include "DataBase.h"
#include "Vehicle.h"
#include "STRING_HELPER.h"

#include<iostream>
using namespace std;

const char DELIMETER =';';

Database::Database() throw(IOError,MemoryError)
{


    try
    {

        this->vehicleTable = new Table<Vehicle> ("vehicle.txt");

        this->userTable = new Table<User> ("User.txt");

        this->tripTable = new Table<Trip> ("tripe.txt");




        this->fetchAllTrip();




    }
    catch(...)
    {

        throw;
    }
}
void Database::fetchAllVehicle() throw(IOError,MemoryError)
{

    this->vehicleTable->fileStream.open(this->vehicleTable->fileName);




    if(!this->vehicleTable->fileStream)
    {

        throw IOError();
    }



    for(string line; getline(this->vehicleTable->fileStream,line);)
    {


        vector<string> components = split(line,DELIMETER);

        auto recordId = stol(components[0]);

         auto regNo = components[1];

         auto type = VehicleType(stoi(components[2]));

         auto seats = stoi(components[3]);

        auto companyName = components[4];

        auto pricePerKm = stod(components[5]);

        Date PUCExp = Date(components[6]);


        Storable * record = new Vehicle(regNo,type,seats,companyName,pricePerKm,PUCExp,recordId);



        if(!record)
        {
            throw MemoryError();
        }
        this->vehicleTable->records->push_back(record);

    }

    this->vehicleTable->fileStream.close();


}



void Database::fetchAllUser() throw(IOError,MemoryError)
{

    this->userTable->fileStream.open(this->userTable->fileName);

    if(!this->userTable->fileStream)
    {

        throw IOError();
    }



    for(string line; getline(this->userTable->fileStream,line);)
    {


        vector<string> components = split(line,DELIMETER);
        auto recordId = stoi(components[0]);
        auto name = components[1];
        auto cont = components[2];
        auto email = components[3];






        Storable * record = new User(name,cont,email,recordId);


        if(!record)
        {
            throw MemoryError();
        }
        this->userTable->records->push_back(record);

    }

    this->userTable->fileStream.close();




}


void Database::fetchAllTrip() throw (IOError,MemoryError)
{


    this->tripTable->fileStream.open(this->tripTable->fileName);

    if(!this->tripTable->fileStream)
    {
        throw IOError();
    }

    for(string line; getline(this->tripTable->fileStream,line);)
    {


        vector<string> components = split(line,DELIMETER);

        try
        {
            auto recordId = stoi (components[0]);

            auto vehiclePtr = this->vehicleTable->getRefOfRecord(stoi(components[1]));

            auto UserPtr = this->userTable->getRefOfRecord(stoi(components[2]));

            auto stDate = Date(components[3]);

            auto enDate = Date(components[4]);

            auto stReading = stol(components[5]);

            auto enReading = stol(components[6]);

            auto fare = stod(components[7]);

            auto iscmp =  components[8]=="0"? false: true;

            Storable * rec= new Trip(vehiclePtr,UserPtr,stDate,enDate,recordId,stReading,enReading,fare,iscmp);

            if(!rec)
            {

                throw MemoryError();
            }

            this->tripTable->records->push_back(rec);



        }
        catch(...)
        {

        }

        }
        this->tripTable->fileStream.close();

}

    const Vehicle *const Database::getVehicle(string registrationNo) const throw (IOError)
    {



        for(auto & rec: *this->vehicleTable->records)

            {

                Vehicle *vehicle = dynamic_cast<Vehicle*>(rec);
                if(vehicle)
                {

                    if(vehicle->getregistrationnumber()== registrationNo)
                    {

                        return vehicle;
                    }
                }
            }
            throw IOError();
        }

        const User *const Database::getUser(string contact) const throw (IOError)
        {

            for(auto & rec: *this->userTable->records)
            {

                User * user = dynamic_cast<User *> (rec);
                if(user)
                {
                    if(user->getcontact()== contact)
                        return user;
                }
            }
            throw IOError();
        }


        const vector<const Vehicle *> Database ::getVehicle(Date stDate,Date enDate,VehicleType type) const throw(IOError)
        {

            vector<const Vehicle *> vehicle = vector<const Vehicle *>();

            for(auto &vrec : *this->vehicleTable->records)
            {

                Vehicle *vec = dynamic_cast<Vehicle*>(vrec);
                if(vec && vec->getVehicleType() == type)
                {
                    bool tripFound = false;
                    for(auto &trec : *this->tripTable->records)
                    {

                        Trip *t = dynamic_cast<Trip*> (trec);
                        if(
                           t &&
                           !t->isCmp()&&
                           t->getVehicle().getRecordID()==vec->getRecordID()
                           && !(t->getstDate()>= enDate && t->getenDate()>= enDate)
                           &&  !(t->getstDate()<=stDate&& t->getenDate()<=stDate))
                        {

                            tripFound=true;
                            break;
                        }
                    }
                    if(!tripFound)
                    {

                        vehicle.push_back(vec);
                    }
                }
            }
            return vehicle;
        }


        void Database::cleanUp()
        {

            delete this->vehicleTable;
            delete this->userTable;
            delete this->tripTable;
        }

        Database::~Database()
        {

            this->cleanUp();
        }

        const Table<Vehicle> * const Database::getVehicleRef() const
        {

            return this->vehicleTable;
        }
         const Table<User> * const Database::getUserRef() const
        {

            return this->userTable;
        }
         const Table<Trip> * const Database::getTripRef() const
        {

            return this->tripTable;
        }
#endif // database_cpp
