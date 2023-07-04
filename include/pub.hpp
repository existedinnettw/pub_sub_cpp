
#ifndef PUB_H
#define PUB_H


#include <string>
#include <unordered_map>
#include <queue>
#include <sub.hpp>
// #include <vector>
#include <boost/circular_buffer.hpp>
// #include <stdatomic.h>
#include <atomic>
// #include <forward_list>

using std::queue;
using std::string;
// using std::forward_list;


struct Broker_entry
{
    bool locked;  //check if notifying, registing subscriber, removing subscriber
    queue<void *> subscribers_ptr;
};


/**
 * singleton across all thread, module
 */
class Broker
{
public:
    /**
     * 
     * this map record the relation between topic to all the subscriber
     * 
     * @todo may replace queue to forward_list
     */
    std::unordered_map<string, Broker_entry> broker_map; // topic name --> pointer of Subscriber<type> pointer

    /**
     * regist or subscribe
    */
    template <typename Subscriber_intf_datatype >
    void regist_subscriber(Subscriber_intf_datatype subscriber)
    {
        Broker_entry entry = broker_map[subscriber.topic_name];
        while (entry.locked)
        {}//sping lock
        entry.locked=true;
        entry.subscribers_ptr.push(&subscriber);
        entry.locked=false;
    }

    /**
     * unregist or unsubscribe
     * not yet implement
     * should subscriber have name to simplify this process?
     * @todo implement
     */
    template <typename Data_type>
    void remove_subscriber()
    {
        Broker_entry entry = broker_map[subscriber.topic_name];
        while (entry.locked)
        {}//sping lock
        entry.locked=true;
        // entry.subscribers_ptr.push(&subscriber);
        entry.locked=false;
    }

};

/**
 * @interface Publisher
 */
template <typename Topic_type>
class Publisher
{
public:
    string topic_name;

    Publisher(string topic_name) : topic_name(topic_name) {}

    /**
     * publish data in assigned type.
     * sometimes called advertise.
     */
    void publish(Broker broker, Topic_type data)
    {
        Broker_entry entry=broker.broker_map[this->topic_name]
        while (entry.locked)
        {}
        entry.locked=true;
        for (auto it = entry.subscribers_ptr.cbegin(); it != entry.subscribers_ptr.cend(); it++)
        {
            it->update(data); //subscirber_intf
        }
        entry.locked=false;
    }

private:
};


#endif