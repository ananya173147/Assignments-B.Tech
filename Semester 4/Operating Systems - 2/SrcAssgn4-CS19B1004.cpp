#include <iostream>
#include <semaphore.h>
#include <thread>
#include <random>
#include <unistd.h>
#include <algorithm>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

int eating = 0;
int waiting = 0;
sem_t mutex, block;
bool must_wait = false, exec = false;
int n, x;
double lambda, r, lambda2, waiting_time = 0;
exponential_distribution<double> ex_di_2;
default_random_engine gen, gen1, gen2;
ofstream output;
ofstream output1;

void test(int id){

  string suffix, temp;
  int value;
    	if(id == 0) suffix = "st";
    	else if(id == 1) suffix = "nd";
    	else if(id == 2) suffix = "rd";
    	else suffix = "th";
  char timestring[6];

  sem_wait(&mutex);
  auto reqEnterTime = chrono::system_clock::now();
    time_t t_enter = chrono::system_clock::to_time_t (reqEnterTime);
    struct tm* time = localtime(&t_enter);
    sprintf(timestring, "%.2d:%.2d",time->tm_min, time->tm_sec);
    temp = to_string(id+1) + suffix + " customer access request at " + (string)timestring + "\n";
    output << temp;

  if(must_wait==true||eating+1>x){
    
    waiting++;
    must_wait = true;
    sem_post(&mutex);
    sem_wait(&block);
    auto accessGivenTime = chrono::system_clock::now();
    time_t t_access = chrono::system_clock::to_time_t (accessGivenTime);
    time = localtime(&t_access);
    sprintf(timestring, "%.2d:%.2d",time->tm_min, time->tm_sec);
    temp = to_string(id+1) + suffix + " customer given access at " + (string)timestring + "\n";
    output << temp;

    auto time_taken = chrono::duration_cast<chrono::microseconds> (accessGivenTime - reqEnterTime);
    waiting_time += (double)time_taken.count();
    exec = true;
    must_wait = (eating==x && waiting>0);
    
  }
  else{
    eating++;
    auto accessGivenTime1 = chrono::system_clock::now();
    time_t t_access1 = chrono::system_clock::to_time_t (accessGivenTime1);
    time = localtime(&t_access1);
    sprintf(timestring, "%.2d:%.2d",time->tm_min, time->tm_sec);
    temp = to_string(id+1) + suffix + " customer given access at " + (string)timestring + "\n";
    output << temp;
    auto time_taken = chrono::duration_cast<chrono::microseconds> (accessGivenTime1 - reqEnterTime);
    waiting_time += (double)time_taken.count();
    exec = true;
    must_wait = (eating==x && waiting>0);
    sem_post(&mutex);
  }
  
  if(exec){
      double delay=ex_di_2(gen2);
      usleep(delay*1000);
      sem_wait(&mutex);
      auto exitTime = chrono::system_clock::now();
      time_t t_exit = chrono::system_clock::to_time_t (exitTime);
      time = localtime(&t_exit);
      sprintf(timestring, "%.2d:%.2d",time->tm_min, time->tm_sec);
      temp = to_string(id+1) + suffix + " customer exited at " + (string)timestring + "\n";
      output << temp;
      eating--;
      exec = false;
      sem_post(&mutex);      
  }
   
    if(eating==0){
      sem_wait(&mutex);
      int k = min(x, waiting);
      waiting -= k;
      eating += k;
      must_wait = (eating==x && waiting>0);
      for(int i=0; i<k; i++)
        sem_post(&block);
      sem_post(&mutex);
    }
}

int main(){
  ifstream in("input.txt");
  in >> n >> x >> lambda >> r >> lambda2;
  in.close();

  exponential_distribution<double> ex_di_1((double)1/lambda);
  ex_di_2 = exponential_distribution<double> ((double)1/lambda2);
  output.open("log.txt");

  sem_init(&mutex, 0, 1);
  sem_init(&block, 0, 0);

  thread threads[n];
  uniform_int_distribution<int> uni(1, r*x);

  for(int i=0; i<n;){
        usleep(ex_di_1(gen)*1000);
        int k = uni(gen1);
        int s = min(k, max(n-i, 1));
        for (int j=0; j<s; j++)
        {
            threads[i] = thread(test, i);
            i++;
            if(i==n) break;
        }
    } 


	for(int i=0;i<n;i++){
		threads[i].join();
	}

  output.close();

  double avg = (double)waiting_time/(double)n;
  output1.open("Stats.txt");
  output1 << "The average waiting time for all the threads is "<< avg << " microseconds.";
  output1.close();
  return 0;
}