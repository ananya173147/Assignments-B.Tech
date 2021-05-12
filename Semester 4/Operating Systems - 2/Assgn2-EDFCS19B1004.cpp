#include <fstream>
#include <bits/stdc++.h> 
using namespace std;

class Process{
public:
        int pid;
        long p_time;
        long period;
        long executed_till;
        long arrival;
        long deadline;
        double waiting_sum;
        int repeats;
        int runtimes_left;
        Process(){};
        ~Process(){};
};

bool compare(Process &a , Process &b)
{       if(a.deadline!=b.deadline)
	        return (a.deadline < b.deadline);
        else
                return (a.pid < b.pid);
};

int main(){
        int n, i, j; 
        long curr_time, end, preempt, total=0, completed=0, missed=0;
        double avg_time=0;
        double context_switch=0;
        
        ifstream input;         //taking input from inp-params.txt file
        ofstream out1, out2;
        input.open("inp-params.txt");
        out1.open("EDF-Log.txt");
        out2.open("EDF-Stats.txt");
        input>>n;

        Process p[n];
        //initialising array of proccesses
        for(i=0;i<n;i++){
                input>>p[i].pid>>p[i].p_time>>p[i].period>>p[i].repeats;
                p[i].deadline = p[i].period;
                p[i].executed_till = 0;
                p[i].arrival = 0;
                p[i].waiting_sum = 0;
                p[i].runtimes_left = p[i].repeats;

                if(end < (p[i].period*p[i].repeats))
                        end = p[i].period*p[i].repeats;            //end = maximum time till all these processes will run
                
                if(p[i].runtimes_left>0)
                        out1<<"Process P"<<p[i].pid<<": processing time="<<p[i].p_time<<"; deadline:"<<p[i].period<<"; period:"<<p[i].period<<" joined the system at time 0"<<endl;

                total += p[i].repeats;
        }

        input.close();
        
        sort(p,p+n,compare);

        bool running = true;
        
        int preempted[2];
        int curr, prev = 1;

        for(curr_time=1; curr_time<=end; curr_time++){
                curr = -1;
                for(i=0;i<n;i++){
			if(p[i].runtimes_left>0 && (p[i].arrival < curr_time)){
				if(running == false){
					out1<<"CPU is idle till time "<< curr_time-1 << "." << endl;
					running = true;	
				} 
				if(prev!=i && p[prev].executed_till!=0){
                                        preempt = p[prev].p_time - p[prev].executed_till;
					out1<<"Process P"<<p[prev].pid<<" is preempted by Process P"<<p[i].pid<<" at time "<<curr_time-1<<". Remaining processing time:"<< preempt << "." << endl;
//                                        context_switch += 0.01;
                                        preempted[0] = 1;
                                        preempted[1] = p[prev].pid;
				}    
				if((prev!=i && p[i].executed_till==0) || (prev==i && p[i].executed_till==0)){
                                        if(p[i].p_time - p[i].executed_till > p[i].deadline - curr_time){
                                                out1<<"Process P"<<p[i].pid<<" will miss its deadline at time "<< p[i].deadline << ", so we skip its execution." << endl;
				                p[i].waiting_sum += p[i].period;
                                                p[i].executed_till = 0;
                                                p[i].runtimes_left--;
                                                p[i].deadline += p[i].period;
		        		        p[i].arrival += p[i].period;
			        	        missed++;
                                                curr_time--; 
                                        }
                                        else{   
                                                out1<<"Process P"<<p[i].pid<<" starts execution at time "<< curr_time-1 << "." << endl;
//                                                context_switch += 0.02;
                                        }
                                }

				curr = i;
				prev = i;

				break;
			}
		}
                if(i==n)
			running = false;
                
                if(curr!=-1)
                        p[curr].executed_till++;

                for(i=0;i<n;i++){
			if(curr!=-1){
                                if(p[curr].p_time==p[curr].executed_till){
			                out1<<"Process P" << p[curr].pid << " finishes execution at time " << curr_time << "." << endl;
			                p[curr].waiting_sum += curr_time - p[curr].arrival - p[curr].p_time;
                                        p[curr].executed_till = 0;
                                        p[curr].runtimes_left--;
                                        p[curr].arrival += p[curr].period;
                                        p[curr].deadline += p[curr].period;
                                        completed++;

                                        if(preempted[0]==1){
                                                out1 <<"Process P"<<preempted[1]<<" resumes its execution at time " << curr_time << "." << endl;
                                                preempted[0] = 0;
//                                                context_switch += 0.02;
                                        }
		                }
                                else if (curr_time >= p[i].deadline && p[i].runtimes_left>0){
				        out1<<"Process P"<<p[i].pid<<" missed its deadline at time "<< curr_time << "." << endl;
				        p[i].waiting_sum += p[i].period;
                                        p[i].executed_till = 0;
                                        p[i].runtimes_left--;
                                        p[i].deadline += p[i].period;
		        		p[i].arrival += p[i].period;
			        	missed++;
			        }       
                        }
		}

                if(completed+missed==total)
                        break;

                sort(p,p+n,compare);

                if(context_switch>=1){
                        curr_time++;
                        context_switch = context_switch-1;
                }  
        }
        out1.close();

        out2<<"Number of processes that came into the system: "<<total<<endl;
	out2<<"Number of processes that successfully completed execution: "<<completed<<endl;
	out2<<"Number of processes that missed their deadlines: "<<missed<<endl;

        for(i=0;i<n;i++){
                p[i].waiting_sum = p[i].waiting_sum/(double)p[i].repeats;
                out2<<"Average waiting time for Process P"<<p[i].pid<<": "<<p[i].waiting_sum<<endl;
                avg_time += p[i].waiting_sum;
        }

//        out2<<"Average Waiting Time for all processes with context switch time: "<<(avg_time+context_switch)/(double)n<<" Milliseconds"<<endl;
        avg_time = avg_time/(double)n;
	out2<<"Average Waiting Time for all processes: "<<avg_time<<" Milliseconds"<<endl;

	out2.close();
        return 0;
}