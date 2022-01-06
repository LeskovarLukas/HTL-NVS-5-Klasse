#include <iostream>
#include <sstream>
#include <thread>

#include "../include/clock.h"
#include "../include/pipe.h"
#include "CLI11.hpp"


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


    void set_clock_interval(long interval)
    {
        clock.set_interval(interval);
    }

    void set_time_monotone(bool set_monotone)
    {
        this->is_monotone = set_monotone;
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
                long slave_time = clock.to_time();

                if (is_monotone && value < slave_time) {
                    println({name, "[", std::to_string(slave_time), "]: slowing down clock\n\n"});
                    clock.set_time_monotone(true);
                } else {
                    clock.set_time_monotone(false);
                    clock.from_time(value);

                    if (is_monotone)
                        println({name, "[", std::to_string(slave_time), "]: time corrected\n\n"});
                    else
                        println({name, "[", std::to_string(slave_time), "]: setting time to ", std::to_string(value), "\n\n"});
                }
            }
        }

        clock_thread.join();
    }

private:
    std::string name;
    Clock clock;
    Channel *channel = new Channel();
    bool is_monotone = false;
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


    void set_clock_interval(long interval)
    {
        this->clock.set_interval(interval);
    }

    void set_time_monotone(bool set_monotone)
    {
        this->is_monotone = set_monotone;
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

            long master_time = clock.to_time();
            if (is_monotone && newTime < master_time) {
                println({"master[", std::to_string(master_time), "]: slowing down clock\n\n"});
                clock.set_time_monotone(true);
            } else {
                clock.set_time_monotone(false);
                clock.from_time(newTime);
                if (is_monotone)
                    println({"master[", std::to_string(master_time), "]: time corrected\n\n"});
                else 
                    println({"master[", std::to_string(master_time), "]: setting time to ", std::to_string(newTime), "\n\n"});


            }
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
    bool is_monotone = false;
};


int main(int argc, char const *argv[])
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

    // 8) - 15)
    // TimeMaster master("master", 12, 20, 0);
    // TimeSlave slave1("slave1", 12, 19, 0);
    // TimeSlave slave2("slave2", 12, 21, 0);

    // master.set_clock_interval(1000);
    // master.set_time_monotone(true);
    // slave1.set_clock_interval(1000);
    // slave1.set_time_monotone(true);
    // slave2.set_clock_interval(1000);
    // slave2.set_time_monotone(true);

    // master.set_channel1(slave1.get_channel()); // master -> slave1
    // slave1.get_channel()->set_latency(1000); 

    // master.set_channel2(slave2.get_channel()); // master -> slave2
    // slave2.get_channel()->set_latency(2000);

    // std::thread master_thread(std::ref(master));
    // std::thread slave1_thread(std::ref(slave1));
    // std::thread slave2_thread(std::ref(slave2));

    // master_thread.join();
    // slave1_thread.join();
    // slave2_thread.join();

    // 16)
    CLI::App app{"Simulate the berkeley-algo"};

    bool is_monotone = false;
    unsigned int latency1 = 0;
    unsigned int latency2 = 0;
    int slave1_deviation = 0;
    int slave2_deviation = 0;
    int master_deviation = 0;

    app.add_flag("--monotone", is_monotone, "set monotone mode");
    app.add_option("--latency1", latency1, "latency to channel 1 (both directions)");
    app.add_option("--latency2", latency2, "latency to channel 2 (both directions)");
    app.add_option("--deviation1", slave1_deviation, "deviation of clock of slave1");
    app.add_option("--deviation2", slave2_deviation, "deviation of clock of slave2");
    app.add_option("--deviationm", master_deviation, "deviation of clock of master");

    CLI11_PARSE(app, argc, argv);

    TimeMaster master("master", 12, 20, 0);
    TimeSlave slave1("slave1", 12, 19, 0);
    TimeSlave slave2("slave2", 12, 21, 0);

    master.set_clock_interval(1000 + master_deviation);
    master.set_time_monotone(is_monotone);
    slave1.set_clock_interval(1000 + slave1_deviation);
    slave1.set_time_monotone(is_monotone);
    slave2.set_clock_interval(1000 + slave2_deviation);
    slave2.set_time_monotone(is_monotone);

    master.set_channel1(slave1.get_channel()); // master -> slave1
    slave1.get_channel()->set_latency(latency1); 

    master.set_channel2(slave2.get_channel()); // master -> slave2
    slave2.get_channel()->set_latency(latency2);

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

