// pubsub_another_example.cpp : Defines the entry point for the console application.
//
#pragma warning (disable : 4996)
#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <map>

#include "boost/signals2.hpp"

/* This class holds the parameters and is the class that I want to set
 * observable. It holds a std::map of the parameters and a simple accessor*/
class kPublisher
{      
    typedef std::map<std::string, float> myMap_t; 
    typedef boost::signals2::signal<void (kPublisher&)> signal_t;

    myMap_t topic;    


public:            
    signal_t sig;

    kPublisher()
    {
        topic["a0"] = 1.f;
        topic["a1"] = 2.f;                
    }


    float getParam( std::string key, float const & defaultVal ) 
    {        
        myMap_t::iterator it = topic.find(key); 
        if ( it == topic.end() ) 
            return defaultVal; 
        else 
            return it->second; 
    }

    void changePars()
    {
        topic["a0"] = 11.f;
        topic["a1"] = 22.f;
        sig(*this);
    }    
};

/* This is an example of a processing class that I would like to have
 * subscribe to the parameter class.*/
class kSubscriber
{
    float parameter;
    int id;

public:
    kSubscriber(kPublisher &Publisher, int id_) :  parameter (80.f), id(id_)
    { 
        updatePars(Publisher);
        // Something like Publisher.sig.connect ... here
        Publisher.sig.connect(boost::bind(&kSubscriber::updatePars, this, _1));
    }

    void updatePars(kPublisher &Publisher) 
    {
        std::stringstream idStream;
        idStream << id;        
        std::string key = std::string( "a" + idStream.str() );                      

        parameter = Publisher.getParam( key, parameter );
    }

    float getParam() {return parameter;}
};


/* This is a very simple main function used here for testing. It 
 * instantiates 2 processing objects. The parameters are then changed
 * in the observable parameter object. The processing objects should
 * then update themselves and so the last "cout" calls should reveal the 
 * new parameters. At least, this is what I would like to happen!*/
int main(int argc, char *argv[])
{
    kPublisher Publisher;       

    kSubscriber temp0(Publisher, 0);
    kSubscriber temp1(Publisher, 1);

    std::cout << "Processing unit "  << 0 << " param = " << temp0.getParam() << std::endl;
    std::cout << "Processing unit "  << 1 << " param = " << temp1.getParam() << std::endl;

    Publisher.changePars();

    std::cout << "Processing unit "  << 0 << " param = " << temp0.getParam() << std::endl;
    std::cout << "Processing unit "  << 1 << " param = " << temp1.getParam() << std::endl;   
    std::cin.get();
}