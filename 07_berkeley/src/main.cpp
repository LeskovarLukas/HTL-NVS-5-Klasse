#include <iostream>
#include <sstream>
#include <thread>

#include "../include/clock.h"
#include "../include/pipe.h"


void println(const std::initializer_list<std::string>&);

std::mutex print_mtx;


class Channel
{
public:
    Pipe<long> &get_pipe1()
    {
        return pipe1;
    }

    Pipe<long> &get_pipe2()
    {
        return pipe2;
    }

    void set_latency(long latency)
    {
        pipe1.set_latency(latency);
        pipe2.set_latency(latency);
    }

private:
    Pipe<long> pipe1; // master
    Pipe<long> pipe2; // slave
};

class TimeSlave
{
public:
    TimeSlave(std::string name, int hour, int minute, int second) : name(name), clock(Clock(name, hour, minute, second))
    {
    }

    Channel *get_channel()
    {
        return channel;
    }

    void operator()()
    {
        // 11)
        // long value;
        // Pipe<long>& pipe = this->channel->get_pipe1();
        // while (pipe >> value) {
        //     std::cout << name << ": " << value << std::endl;
        // }
        // std::cout << name << ": end" << std::endl;

        std::thread clock_thread(std::ref(this->clock));

        Pipe<long>& pipe = this->channel->get_pipe1();
        long value;

        while (pipe >> value) {
            if (value == 0) {
                long slave_time = clock.to_time();
                println({name, "[", std::to_string(slave_time), "]: sending time\n\n"});

                this->channel->get_pipe2() << slave_time;
            } else {
                println({name, "[", std::to_string(clock.to_time()), "]: setting time to ", std::to_string(value), "\n\n"});
                clock.from_time(value);
            }
        }

        clock_thread.join();
    }

private:
    std::string name;
    Clock clock;
    Channel *channel = new Channel();
};

class TimeMaster
{
public:
    TimeMaster(std::string name, int hour, int minute, int second) : name(name), clock(Clock(name, hour, minute, second))
    {
    }

    void set_channel1(Channel *channel)
    {
        this->channel1 = channel;
    }

    void set_channel2(Channel *channel)
    {
        this->channel2 = channel;
    }

    void operator()()
    {
        // 11)
        // for (int i = 0; i < 3; i++) {
        //     this->channel1->get_pipe1() << i;
        //     this->channel2->get_pipe1() << i;
        // }
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));
        // this->channel1->get_pipe1().close();
        // this->channel2->get_pipe1().close();
        // std::cout << "master: end" << std::endl;

        std::thread clock_thread(std::ref(this->clock));

        long slave1Time;
        long slave2Time;
        long newTime;

        while (true)
        {
            // send master time to slaves
            println({"master[", std::to_string(clock.to_time()), "]: requesting time from slaves\n\n"});
            this->channel1->get_pipe1() << 0;
            this->channel2->get_pipe1() << 0;

            // wait for slaves to receive time
            this->channel1->get_pipe2() >> slave1Time;
            println({
                "master[", std::to_string(clock.to_time()), "]: received time from slave 1 is ", std::to_string(slave1Time), "\n\n"
            });

            this->channel2->get_pipe2() >> slave2Time;
            println({
                "master[", std::to_string(clock.to_time()), "]: received time from slave 2 is ", std::to_string(slave2Time), "\n\n"
            });

            // calculate adjustment
            newTime = (slave1Time + slave2Time + clock.to_time()) / 3;

            // send new time to slaves
            println({
                "master[", std::to_string(clock.to_time()), "]: new time is ", std::to_string(newTime), 
                " => sending new time to slaves\n\n"
            });

            clock.from_time(newTime);
            this->channel1->get_pipe1() << newTime;
            this->channel2->get_pipe1() << newTime;

            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        }

        clock_thread.join();
    }

private:
    std::string name;
    Clock clock;
    Channel *channel1;
    Channel *channel2;
};


int main()
{
    // 1)
    // std::thread clock{Clock("testclock")};
    // clock.join();

    // 2)
    // Clock clock("testclock", 12, 20, 0);
    // std::thread clock_thread(std::ref(clock));
    // clock_thread.join();

    // 3)
    // Clock clock("testclock");
    // clock.set_time(12, 20, 0);
    // std::thread clock_thread(std::ref(clock));
    // clock_thread.join();

    // 5) & 6)
    // TimeMaster master("master", 12, 10, 0);
    // TimeSlave slave1("slave1", 12, 20, 0);
    // TimeSlave slave2("slave2", 12, 30, 0);

    // std::thread master_thread(std::ref(master));
    // std::thread slave1_thread(std::ref(slave1));
    // std::thread slave2_thread(std::ref(slave2));

    // master_thread.join();
    // slave1_thread.join();
    // slave2_thread.join();

    // 7) Pipe test
    // int i{};
    // Pipe<int> pipe;

    // pipe << i++;
    // int value;
    // if (pipe >> value) {
    //     std::cout << "value: " << value << std::endl;
    // }
    // pipe.close();
    // pipe << i++;
    // if (pipe >> value) {
    //     std::cout << "value: " << value << std::endl;
    // }

    // 8)
    TimeMaster master("master", 12, 10, 0);
    TimeSlave slave1("slave1", 12, 20, 0);
    TimeSlave slave2("slave2", 12, 30, 0);

    master.set_channel1(slave1.get_channel()); // master -> slave1
    slave1.get_channel()->set_latency(1000); 

    master.set_channel2(slave2.get_channel()); // master -> slave2
    slave2.get_channel()->set_latency(2000);

    std::thread master_thread(std::ref(master));
    std::thread slave1_thread(std::ref(slave1));
    std::thread slave2_thread(std::ref(slave2));

    master_thread.join();
    slave1_thread.join();
    slave2_thread.join();

    return 0;
}


void println(const std::initializer_list<std::string>& text) {
    //std::lock_guard<std::mutex> lock(print_mtx);
    std::ostringstream buffer;

    for (auto& elem : text) {
        buffer << elem;
    }

    std::cout << buffer.str() << std::flush;
    buffer.str("");
}

