
#include "DataBase.h"

template <class T> void Database::addNewRecord(T* record) throw
(IOError,MemoryError)
{

    try
    {

        Vehicle *v = dynamic_cast <Vehicle*>(record);
        if(v)
        {

            auto saverec = this->vehicleTable->addNewRecord( *v);
            record->recordID = saverec->recordID;
            return;
        }
        User *u = dynamic_cast<User*> (record);
        if(u)
        {
            auto saverec = this->userTable->addNewRecord( * u);
            record->recordID = saverec->recordID;
            return;

        }
        Trip *t = dynamic_cast<Trip *>(record);
        if(t)
        {
            auto saverec = this->tripTable->addNewRecord( * t);
            record->recordID = saverec->recordID;
            return;
        }
    }
    catch(...)
    {
        throw;
    }

}
template <class T> void Database::updateRecord(T * record) throw
(IOError,MemoryError)
{

    try
    {
        Vehicle *v = dynamic_cast<Vehicle *>(record);
        if(v)
        {

            this->vehicleTable->updateRecord(*v);
            return;
        }
        User *u = dynamic_cast<User*> (record);
        if(u)
        {

            this->userTable->updateRecord(*u);
            return;
        }
        Trip *t = dynamic_cast<Trip *>(record);
        if(t)
        {
            this->tripTable->updateRecord(*t);
            return;
        }
    }
    catch(...)
    {

        throw;
    }
}
