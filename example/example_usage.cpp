
#include <pub.hpp>
#include <sub.hpp>
#include <topic.hpp>
// #include <pthread.h>
#include <iostream>
#include <thread>
#include <random>

using std::thread;

Broker broker;

Publisher<Concrete_topic1> pub1("xyz");
Subr_buffer<Concrete_topic1> sub2("xyz", 5);

void thread1()
{
    using namespace std;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 6);

    Concrete_topic1 data = {.x = 1, .y = 2.0, .z = 3.0};

    for (int i = 0; i < 5; ++i)
    {
        int rand_num=dist(gen);
        // cout << rand_num << " "; // pass the generator to the distribution.
        data.x=rand_num;
        // cout<<"thread 1 pub:"<<endl;
        printf("thread 1 pub topic: %d, %f, %f\n",data.x, data.y, data.z);
        pub1.publish(broker, data);
    }
};

void thread2(){
    while(true){
        // printf("thread 1 sub topic: %d, %f, %f",data.x, data.y, data.z);
    }
};

int main()
{
    broker.regist_subscriber<Subr_buffer<Concrete_topic1>>(sub2);
    // borker.
    thread t1(thread1);
    thread t2(thread2);
    
    t1.join();

    return 0;
}