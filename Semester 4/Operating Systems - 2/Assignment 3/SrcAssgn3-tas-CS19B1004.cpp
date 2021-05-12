#include <fstream>
#include <thread>
#include <atomic>
#include <iostream>
#include <random>
#include <chrono>
#include <unistd.h>
#include <string>

using namespace std;

int n, k;
double l1, l2, waiting_time = 0, worstcase_time = -1;
atomic_flag lock = ATOMIC_FLAG_INIT;
ofstream output;
ofstream output1;

void testCS(int tid){

	default_random_engine gen;
	exponential_distribution<double> ex_di_1((double)1/l1);
	exponential_distribution<double> ex_di_2((double)1/l2);  

	for(int i=0;i<k;i++){

    	string suffix;
    	if(i == 0) suffix = "st";
    	else if(i == 1) suffix = "nd";
    	else if(i == 2) suffix = "rd";
    	else suffix = "th";
	string temp;
    	char timestring[9];
//Entry section
	auto reqEnterTime = chrono::system_clock::now();
    	time_t t_start = chrono::system_clock::to_time_t (reqEnterTime);

   	struct tm* time = localtime(&t_start);
    	sprintf(timestring, "%.2d:%.2d:%.2d", time->tm_hour, time->tm_min, time->tm_sec);
    	temp = to_string(i+1) + suffix + " CS Requested at " + (string)timestring + " by thread " + to_string(tid)+"\n";
    	output << temp;

//Critical section
	while(std::atomic_flag_test_and_set_explicit(&lock, std::memory_order_acquire));
	auto actEntryTime = chrono::system_clock::now();
	auto time_taken = chrono::duration_cast<chrono::milliseconds> (actEntryTime - reqEnterTime);
	waiting_time += (double)time_taken.count();
	if ((double)time_taken.count() > worstcase_time)
		worstcase_time = waiting_time;

	time_t t_end = chrono::system_clock::to_time_t(actEntryTime);
	time = localtime(&t_end);
	sprintf(timestring, "%.2d:%.2d:%.2d", time->tm_hour, time->tm_min, time->tm_sec);
    	temp = to_string(i+1) + suffix + " CS Entry at " + (string)timestring + " by thread " + to_string(tid) +"\n";
    	output << temp;
	usleep(ex_di_1(gen)*1000);

	atomic_flag_clear_explicit(&lock, memory_order_release);

//Remainder section
	auto exitTime = chrono::system_clock::now();
    	time_t t_exit = chrono::system_clock::to_time_t(exitTime);
    	time = localtime(&t_exit);
    	time = localtime(&t_end);
    	sprintf(timestring, "%.2d:%.2d:%.2d", time->tm_hour, time->tm_min, time->tm_sec);
    	temp = to_string(i+1) + suffix + " CS Exited at " + (string)timestring + " by thread " + to_string(tid)+"\n";
    	output << temp;
	usleep(ex_di_2(gen)*1000);
    }
}

int main(){

int i;
ifstream input;

input.open("inp-params.txt");
input >> n >> k >> l1 >> l2;
input.close();
output.open("TAS.txt");
output << "TAS ME Output:"<<endl;

thread threads[n];

	for(int i=0;i<n;i++){
		threads[i] = thread(testCS,i+1);
	}
	for(int i=0;i<n;i++){
		threads[i].join();
	}

double avg_waiting_time = (double)waiting_time/(double)(n*k);
output1.open("TAS-Stats.txt");
output1 << "The average time taken by a thread to enter CS is " << avg_waiting_time << " milliseconds"<<endl;
output1 << "The worst case time taken among threads to enter the CS in this simulation is " << worstcase_time << " milliseconds"<<endl;
output.close();
output1.close();
return 0;

}
