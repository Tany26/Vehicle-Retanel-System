#include "USER.h"

#include "STRING_HELPER.h"
#include<iostream>

const char DELIMETER =';';

User::User(string name,string contact,string email,long recordId) :
     Storable(recordId)
     {
         this->name=name;
         this->email= email;
         this->contact = contact;

     }

     string User::getname() const
     {
         return this->name;
     }
     string User::getcontact() const
     {

         return this->contact;
     }

     string User::getemail() const
     {
         return this->email;
     }

     void User::setname(string newName)
     {
         this->name=newName;
     }

     void User::setcontact(string newContact)
     {

         this->contact=newContact;
     }

     void User::setemail(string newemail)
     {

         this->email=newemail;
     }
     void User::display() const
     {

         cout<< "User Detail:"<<endl;
         cout<< "Name:"<<this->name<<endl;
         cout<< "Contact" <<this->contact<<endl;

         cout<< "Email :"<<this->email<<endl;

     }

     string User::toString() const
     {

         stringstream ss;
         ss<<recordID<<DELIMETER<<name<<DELIMETER<<contact<<DELIMETER<<email;
         return ss.str();
     }

     void User::setDataFrom(Storable *s)
     {
         User *u = dynamic_cast<User *>(s);
         if(u)
         {
             this->contact = u->contact;
             this->email = u->email;
             this->name = u->name;
         }
     }

