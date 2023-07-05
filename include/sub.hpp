
#ifndef SUB_H
#define SUB_H

#include <string>
// #include <unordered_map>
// #include <queue>
// #include <vector>
#include <boost/circular_buffer.hpp>
#include <forward_list>

using std::forward_list;
// using std::queue;
using std::string;

// template <typename Topic_type>
// class Subscriber_intf;
// template <typename Topic_type>
// class Subr_cb;
// template <typename Topic_type>
// class Subr_buffer;

/**
 * @interface Subscriber
 */
template <typename Topic_type>
class Subscriber_intf
{
public:
    string topic_name;

    /**
     * some use topic_name, queue_size, callback
     */
    // Subscriber_intf(string topic_name) : topic_name(topic_name) {}   //interface no abstract class

    /**
     * sometimes called handle()
     */
    virtual void update(Topic_type data) = 0;
};

/**
 * subscriber that user can pass in callback
 * @memberof Subscriber_intf
 */
template <typename Topic_type>
class Subr_cb : public Subscriber_intf<Topic_type>
{
public:
    string topic_name;
    Subr_cb(string topic_name, void (*cb)(Topic_type data)) : topic_name(topic_name), cb(cb) {}
    void update(Topic_type data)
    {
        this->cb(data);
    }

private:
    void (*cb)(Topic_type data);
};

/**
 * subscriber that have data queue
 * @memberof Subscriber_intf
 */
template <typename Topic_type>
class Subr_buffer : public Subscriber_intf<Topic_type>
{
public:
    boost::circular_buffer<Topic_type> data_queue; // this should up to user own implement
    string topic_name;

    /**
     * some use topic_name, queue_size, callback
     */
    Subr_buffer(string topic_name, int queue_size): topic_name(topic_name) , data_queue(queue_size){}

    /**
     * sometimes called handle()
     */
    void update(Topic_type data)
    {
        this->data_queue.push_back(data);
    }
};

#endif