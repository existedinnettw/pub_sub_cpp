# pub_sub_cpp
Validating pub sub implementation concept in cpp, and later in pure c.

This project is try to implement a pub sub pattern within a process across multiple thread and whole program.  
It's validation in cpp and targeting to be finally implemented in c for MCU project with or without RTOS.  


## structure
Whenever 
1. publisher `publish`,  
2. subscriber `regist`,  
3. subscriber `unregist`,  
we need an entry lock to prevent multithread operation at the same time.
![](./README.assets/structure.dio.svg)

The important thing here is broker doesn't need to know topic data type. But on the other side, it means you have to assign the template datatype right.  

### other possible structure
The structure below take a further step to prevent lock during publishing. If we put a ring buffer before notifing all the client, then problem solves. However, this method require additional thread to handle streaming, which introduce non-necessary complexity for MCU.
![](./README.assets/structure_queue.dio.svg)