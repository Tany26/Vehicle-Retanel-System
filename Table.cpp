
#include "Table.h"

#include<iostream>

using namespace std;

template <class T> Table<T> ::Table(string fileName)
throw(MemoryError)
{


    this->fileName = fileName;
    this->records = new vector<Storable *> ();


    if(!this->records)
    {

        throw MemoryError();
    }

}

template <typename T> long Table<T> ::getNextRecordId() const
{

    return this->records->size()+1;
}


template <class T> const T* Table<T> ::addNewRecord (T record) const throw (IOError)
{

    T *newRecord = new T(record);

    if(!newRecord)
    {

        throw new MemoryError();
    }

    newRecord->recordId = this->getNextRecordId();

    this->records->push_back(newRecord);

    try
    {
        this->writeToFile();
    }
    catch(IOError error)
    {

        this->records->pop_back();
        delete newRecord;
        throw;
    }
    return newRecord;
}




template <class T> void Table<T> ::updateRecord(T updateRecord) const throw(IOError)
{

    for(auto & record:*this->records)
    {

        if(record->getRecordID()== updateRecord.getRecordID())
        {
            T * ptr = dynamic_cast<T*> (record);
            if(ptr)
            {
                T oldRecord = T(* ptr);
                record->setDataFrom(&updateRecord);
                try
                {
                    this->writeToFile();
                    return;
                }
                catch(IOError error)
                {
                    record->setDataFrom (&oldRecord);
                    throw;
                }
            }
        }
    }
    throw MemoryError();
}


template <class T> void Table<T> ::writeToFile() throw (IOError)
{

    this->fileStream.open(fileName,ios::out | ios::trunc);

    if(!this->fileStream)
    {

        throw IOError();
    }
    for(auto & record: *records)
    {

        fileStream <<record->toString()<<endl;

    }

    this->fileStream.close();

}



template <class T> const T* const Table<T> ::getRecordForld(long recordId) const throw(IOError)
{

    try
    {
        return this->getRefOfRecord(recordId);
    }
    catch(IOError)
    {

        throw;
    }

}


template <class T> T* Table<T> ::getRefOfRecord(long recordId) const throw (IOError)
{


    for(auto &record :*records)
    {

        if(record->getRecordID()== recordId)
        {

            return dynamic_cast<T*> (record);
        }
    }
    throw IOError();

}

template <class T> Table<T> ::~Table()
{

    for(auto & record : *this->records)
    {

        delete dynamic_cast<T*> (record);
    }
    this->records->clear();

    this->records->shrink_to_fit();


    delete this->records;
}

