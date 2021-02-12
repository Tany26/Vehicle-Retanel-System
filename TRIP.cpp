#include "TRIP.h"

#include "STRING_HELPER.h"

#include<iostream>


const char DELIMETER =';';

Trip::Trip(const Vehicle *vehicle,
    const User *user,
    Date stDate,
    Date enDate,
    long recordId,
    long stReading,
    long enReading,
    double fare,
    bool iscmp ) :Storable(recordId)
    {

        this->vehicle= vehicle;
        this->user = user;
        this->stDate= stDate;
        this->enDate= enDate;
        this->stReading= stReading;
        this->enReading = enReading;
        this->fare = fare;
        this->cmp = iscmp;


    }
    const User &Trip ::getUser() const
    {

        return *this->user;
    }
    const Vehicle &Trip::getVehicle() const
    {

        return *this->vehicle;
    }
    Date Trip ::getstDate() const
    {

        return this->stDate;
    }

    Date Trip ::getenDate() const
    {
        return this->enDate;
    }

   long Trip::getstReading() const
   {
       return this->stReading;

   }


   long Trip::getenReading() const
   {

       return this->enReading;
   }






    long Trip:: getFare() const
    {

        return this->fare;
    }

    bool Trip::isCmp() const
    {

        return this->cmp;
    }




    void Trip ::stTrip( long stReading)
    {

        this->stReading = stReading;
    }

    double Trip::cmpTrip (long enReading)
    {
        if(this->cmp)
            return this->fare;

        this->enReading= enReading;
        this->fare =(this->enReading - this->stReading) * this->vehicle->getPricePerKm();
        this->cmp = true;
        return this->fare;



    }

    void Trip::display () const
    {
        cout<< "Vehicle Details :"<<endl;

        cout<< "Registration Number :"<<this->vehicle->getregistrationnumber()<<endl;

        cout<< "Vehicle Type :"<< this->vehicle->getVehicleTypeName()<<endl;

        cout<< "Company Name:"<< this->vehicle->getcompanyName()<<endl;

        cout<< "Price Per km:"<< this->vehicle->getPricePerKm()<<endl;

        cout<<endl;

        cout<< "USER DETAILS :"<<endl;


        cout<< "NAME :"<< this->user->getname()<<endl;

        cout <<"Contact :"<< this->user->getcontact()<<endl;

        cout<<endl;

        cout<< "Trip Details :"<<endl;

        cout<< "start Date :"<< this->stDate.toString()<<endl;
        cout<< "End Date :"<< this->enDate.toString()<<endl;

        string tripst = "Not Start";

        if(this->stReading!=0)
        {

            tripst= "on going";
            cout<< " Start Reading :"<<this->stReading<<endl;

        }
        if(this->cmp)
        {

            tripst= "Completed";
            cout<<"End Reading :"<<this->enReading<<endl;
            cout<< "total run : "<<this->enReading - this->stReading<<endl;
            cout<<endl;
            cout<< "Total Fare : "<<this->fare<<endl;

        }
        cout<< "Trip status : "<<tripst<<endl;




    }

   string Trip:: toString() const
    {


        stringstream ss;
        ss  <<recordID << DELIMETER
        << vehicle->getRecordID() << DELIMETER
        << user->getRecordID() << DELIMETER
        << stDate.toString()<< DELIMETER
        << enDate.toString() << DELIMETER
        <<stReading << DELIMETER
        << enReading <<DELIMETER
        << fare <<DELIMETER
        <<cmp;

        return ss.str();
    }

    void Trip::setDataFrom(Storable *s)
    {
        Trip *t =dynamic_cast<Trip*>(s);
        if(t)
        {

            this->vehicle = t->vehicle;
            this->user = t->user;
            this->stDate = t->stDate;
            this->enDate = t->enDate;
            this->stReading = t->stReading;
            this->enReading = t->enReading;
            this->fare = t->fare;
            this->cmp = t->cmp;
        }

    }

