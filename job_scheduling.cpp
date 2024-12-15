#include <iostream>
#include <string>
#include <vector>
#include <climits>
using namespace std;

struct Process {
    string name;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
    int remaining_time;
    int priority;
};

int idle_time = 0;
int total_burst = 0;

void read(Process &prcs) {
    cout << "Enter Process Name: "; cin >> prcs.name;
    cout << "Enter Arrival Time: "; cin >> prcs.arrival_time;
    cout << "Enter Burst Time  : "; cin >> prcs.burst_time;
    cout << "Enter Priority    : "; cin >> prcs.priority;
    prcs.completion_time = prcs.turn_around_time = prcs.waiting_time = prcs.response_time = 0;
    prcs.remaining_time = prcs.burst_time;
    total_burst += prcs.burst_time;
    cout << endl;
}

void printdata(int num_of_process, vector<Process> &prcs_list) {
    float avg_waiting_time = 0;
    float utilization = 0;
    
    cout << " _______________________________________________________________________________________________________________\n";
    cout << "|  Process Name  | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time | Response Time |\n";
    cout << "|________________|______________|____________|_________________|_________________|______________|_______________|\n";
    for (const auto &prcs : prcs_list) {
        cout << "|" << prcs.name
             << string(16 - prcs.name.length(), ' ')
             << "|" << prcs.arrival_time
             << string(14 - to_string(prcs.arrival_time).length(), ' ')
             << "|" << prcs.burst_time
             << string(12 - to_string(prcs.burst_time).length(), ' ')
             << "|" << prcs.completion_time
             << string(17 - to_string(prcs.completion_time).length(), ' ')
             << "|" << prcs.turn_around_time
             << string(17 - to_string(prcs.turn_around_time).length(), ' ')
             << "|" << prcs.waiting_time
             << string(14 - to_string(prcs.waiting_time).length(), ' ')
             << "|" << prcs.response_time
             << string(15 - to_string(prcs.response_time).length(), ' ')
             << "|" << endl;
        avg_waiting_time += prcs.waiting_time;
    }
    cout << "|________________|______________|____________|_________________|_________________|______________|_______________|\n";
    avg_waiting_time /= num_of_process;
    utilization = (1.0 * total_burst / (idle_time + total_burst)) * 100.0;
    cout << "Average waiting time : " << avg_waiting_time << endl;
    cout << "CPU utilization      : " << utilization << "%\n";
}

void resetRemainingTime(int num_of_process, vector<Process> &prcs_list) {
    for (auto &prcs : prcs_list) {
        prcs.remaining_time = prcs.burst_time;
    }
}

bool allDone(int num_of_process, vector<bool> &done) {
    for (bool is_done : done) {
        if (!is_done) return false;
    }
    return true;
}

int firstJob(int num_of_process, vector<Process> &prcs_list, int time_elapsed, vector<bool> &done) {
    int jobIndex = -1;
    int earliest = INT_MAX;
    for (int i = 0; i < num_of_process; i++) {
        if (!done[i] && prcs_list[i].arrival_time <= earliest && prcs_list[i].arrival_time <= time_elapsed) {
            jobIndex = i;
            earliest = prcs_list[i].arrival_time;
        }
    }
    return jobIndex;
}

void FCFS(int num_of_process, vector<Process> &prcs_list) {
    idle_time = 0;
    vector<bool> done(num_of_process, false);
    int time_elapsed = 0;

    while (!allDone(num_of_process, done)) {
        int i = firstJob(num_of_process, prcs_list, time_elapsed, done);
        if (i == -1) {
            time_elapsed++;
            idle_time++;
            continue;
        }
        time_elapsed += prcs_list[i].burst_time;
        prcs_list[i].completion_time = time_elapsed;
        prcs_list[i].turn_around_time = prcs_list[i].completion_time - prcs_list[i].arrival_time;
        prcs_list[i].waiting_time = prcs_list[i].turn_around_time - prcs_list[i].burst_time;
        prcs_list[i].response_time = prcs_list[i].waiting_time;
        done[i] = true;
    }
}

int main() {
    int num_of_process;
    int time_quantum;

    cout << "Enter number of processes: ";
    cin >> num_of_process;
    cout << "Enter time quantum for round-robin: ";
    cin >> time_quantum;

    vector<Process> processes(num_of_process);
    for (int i = 0; i < num_of_process; i++) {
        read(processes[i]);
    }

    cout << "First Come First Serve Output: \n";
    FCFS(num_of_process, processes);
    printdata(num_of_process, processes);

    // Add further algorithms (e.g., SJF, Round Robin) here as needed, following a similar structure.

    return 0;
}

