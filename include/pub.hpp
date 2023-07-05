
#ifndef PUB_H
#define PUB_H

#include <iostream>
#include <string>
#include <unordered_map>
// #include <queue>
// #include <vector>
#include <boost/circular_buffer.hpp>
// #include <stdatomic.h>
#include <atomic>
#include <forward_list>
#include <sub.hpp>

using std::forward_list;
// using std::queue;
using std::string;

// struct Broker_entry;
// class Broker;
// template <typename Topic_type>
// class Publisher;

struct Broker_entry
{
    bool locked; // check if notifying, registing subscriber, removing subscriber
    forward_list<void *> subscriber_ptrs;
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
     */
    std::unordered_map<string, Broker_entry> broker_map; // topic name --> pointer of Subscriber<type> pointer

    /**
     * regist or subscribe
     */
    template <typename Subscriber_intf_datatype>
    void regist_subscriber(Subscriber_intf_datatype &subscriber)
    {
        // Broker_entry entry = this->broker_map[subscriber.topic_name];
        Broker_entry* entry_ptr=&(this->broker_map[subscriber.topic_name]);
        
        while (entry_ptr->locked)
        {
        } // sping lock

        entry_ptr->locked = true;
        // entry_ptr->subscriber_ptrs.push((void*)&subscriber);
        entry_ptr->subscriber_ptrs.insert_after(entry_ptr->subscriber_ptrs.before_begin(), (void *)&subscriber);  //insert at head
        entry_ptr->locked = false;

        int size = distance(entry_ptr->subscriber_ptrs.begin(), entry_ptr->subscriber_ptrs.end());
        // printf("registry:%d\n",size);
    }

    /**
     * unregist or unsubscribe
     * not yet implement
     * should subscriber have name to simplify this process?
     * @todo implement
     */
    template <typename Subscriber_intf_datatype>
    void remove_subscriber(Subscriber_intf_datatype subscriber)
    {
        Broker_entry entry = broker_map[subscriber.topic_name];
        while (entry.locked)
        {
        } // sping lock
        entry.locked = true;
        // entry.subscriber_ptrs.push((void*)&subscriber);
        entry.locked = false;
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
        Broker_entry entry = broker.broker_map[this->topic_name];
        while (entry.locked)
        {
        }
        entry.locked = true;

        int size = distance(entry.subscriber_ptrs.begin(), entry.subscriber_ptrs.end());
        // printf("publish:%d\n",size);
        for (auto it = entry.subscriber_ptrs.cbegin(); it != entry.subscriber_ptrs.cend(); it++)
        {
            ((Subscriber_intf<Topic_type> *)(*it))->update(data); // cast to subscirber_intf ptr then operate.
            // printf("*");
        }
        // printf("\n");
        entry.locked = false;
    }

private:
};

#endif