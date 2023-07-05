
#include <pub.hpp>
#include <sub.hpp>
#include <topic.hpp>
// #include <pthread.h>
#include <iostream>
#include <thread>
#include <random>
#include <chrono>

using std::thread;

Broker broker;

void thread1()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Publisher<Concrete_topic1> pub1("xyz");
    printf("thread1 start\n");
    using namespace std;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    Concrete_topic1 data = {.x = 1, .y = 2.0, .z = 3.0};

    for (int i = 0; i < 5; ++i)
    {
        int rand_num=dist(gen);
        // cout << rand_num << " "; // pass the generator to the distribution.
        data.x=rand_num;
        // cout<<"thread 1 pub:"<<endl;
        printf("thread 1 pub topic: %d, %f, %f\n",data.x, data.y, data.z);
        pub1.publish(broker, data);
        printf("\n");
    }
};
void thread3()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Publisher<Concrete_topic1> pub3("xyz");
    printf("thread3 start\n");
    using namespace std;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(11, 20);

    Concrete_topic1 data = {.x = 1, .y = 2.0, .z = 3.0};

    for (int i = 0; i < 5; ++i)
    {
        int rand_num=dist(gen);
        // cout << rand_num << " "; // pass the generator to the distribution.
        data.y=(float)rand_num;
        // cout<<"thread 1 pub:"<<endl;
        printf("thread 3 pub topic: %d, %f, %f\n",data.x, data.y, data.z);
        pub3.publish(broker, data);
        printf("\n");
    }
};


void cb(Concrete_topic1 data){
    printf("thread 2 sub topic: %d, %f, %f\n",data.x, data.y, data.z);
};
void thread2(){
    Subr_cb<Concrete_topic1> sub2("xyz", cb);
    broker.regist_subscriber<Subr_cb<Concrete_topic1>>(sub2);
    printf("thread2 start\n");
    while(true){
        // printf("thread 2 sub topic: %d, %f, %f",data.x, data.y, data.z);
    }
};

void cb2(Concrete_topic1 data){
    printf("thread 4 sub topic: %d, %f, %f\n",data.x, data.y, data.z);
};
void thread4(){
    Subr_cb<Concrete_topic1> sub4("xyz", cb2);
    broker.regist_subscriber<Subr_cb<Concrete_topic1>>(sub4);
    printf("thread4 start\n");
    while(true){
        // printf("thread 4 sub topic: %d, %f, %f",data.x, data.y, data.z);
    }
};

int main()
{
    printf("program start\n");
    printf("barrier\n");
    // borker.
    thread t1(thread1);
    thread t2(thread2);
    thread t3(thread3);
    thread t4(thread4);
    
    t1.join();
    t3.join();

    Broker_entry entry = broker.broker_map["xyz"];
    int size = distance(entry.subscriber_ptrs.begin(), entry.subscriber_ptrs.end());
    printf("main:%d\n",size);

    return 0;
}