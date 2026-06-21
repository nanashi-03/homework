#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <string>

#define MAX_GANTT_SIZE 45

bool verbose = false;

using namespace std;

struct Process {
    int id;
    int priority;
    int arrival_time;
    vector<int> bursts;

    int current_burst_idx = 0;
    int remaining_time = 0;
    int completion_time = 0;
    int turnaround_time = 0;
    int waiting_time = 0;
    int io_end_time = 0;

    int current_quantum_used = 0;

    void reset() {
        current_burst_idx = 0;
        if (!bursts.empty()) remaining_time = bursts[0];
        completion_time = 0;
        turnaround_time = 0;
        waiting_time = 0;
        io_end_time = 0;
        current_quantum_used = 0;
    }
};

string decor = "------------------------------------------------------------------";

void print_queue_state(int current_time, queue<int> q, int running_idx, const vector<Process>& processes) {
    cout << "   Time " << setw(2) << current_time << " | Ready Queue: [";
    while (!q.empty()) {
        cout << "P" << processes[q.front()].id;
        q.pop();
        if (!q.empty()) cout << ", ";
    }
    cout << "] | CPU: ";
    if (running_idx != -1) {
        cout << "P" << processes[running_idx].id << " (rem: " << processes[running_idx].remaining_time << ")\n";
    } else {
        cout << "IDLE\n";
    }
}

void increment_waiting_time(queue<int>& q, vector<Process>& processes) {
    queue<int> temp = q;
    while (!temp.empty()) {
        processes[temp.front()].waiting_time++;
        temp.pop();
    }
}

void print_gantt_chart(const vector<string>& timeline) {
    cout << "Gantt Chart Timeline:\n ";
    for (size_t i = 0; i < timeline.size(); ++i) cout << "----";
    cout << "\n|";
    for (size_t i = 0; i < timeline.size(); ++i) cout << setw(3) << timeline[i] << "|";
    cout << "\n ";
    for (size_t i = 0; i < timeline.size(); ++i) cout << "----";
    cout << "\n0";
    for (size_t i = 1; i <= timeline.size(); ++i) cout << setw(4) << i;
    cout << "\n";
}

void print_metrics(const string& algo_name, const vector<Process>& processes, const vector<string>& timeline) {
    cout << decor << "\n";
    cout << setw((decor.size() - algo_name.size() - 2) / 2) << "  " << algo_name << "\n";
    cout << decor << "\n";
    cout << setw(8) << "Job ID" << setw(10) << "Priority" << setw(14) << "Arrival Time"
         << setw(18) << "Turnaround Time" << setw(15) << "Waiting Time" << "\n";

    double avg_tat = 0, avg_wt = 0;
    for (const auto& p : processes) {
        cout << setw(8) << p.id << setw(10) << p.priority << setw(14) << p.arrival_time
             << setw(18) << p.turnaround_time << setw(15) << p.waiting_time << "\n";
        avg_tat += p.turnaround_time;
        avg_wt += p.waiting_time;
    }
    cout << decor << "\n";
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << avg_tat / processes.size() << "\n";
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avg_wt / processes.size() << "\n\n";

    if(timeline.size() <= MAX_GANTT_SIZE) {
        print_gantt_chart(timeline);
    }
    cout << "\n";
}

vector<Process> load_processes(const string& filename) {
    vector<Process> processes;
    ifstream infile(filename);
    if (!infile.is_open()) return processes;

    int id, priority, arrival;
    while (infile >> id >> priority >> arrival) {
        Process p; p.id = id; p.priority = priority; p.arrival_time = arrival;
        int burst;
        while (infile >> burst && burst != -1) {
            p.bursts.push_back(burst);
        }
        p.reset();
        processes.push_back(p);
    }
    return processes;
}

// 1. First-Come, First-Served (FCFS) Simulation
void simulate_FCFS(vector<Process> processes) {
    int current_time = 0;
    queue<int> ready_queue;
    vector<int> blocked_pool;
    vector<int> job_pool;
    vector<string> timeline;

    for(size_t i = 0; i < processes.size(); ++i) job_pool.push_back(i);

    int completed = 0;
    int running_idx = -1;

    while (completed < processes.size()) {
        auto it = job_pool.begin();
        while (it != job_pool.end()) {
            if (processes[*it].arrival_time == current_time) {
                ready_queue.push(*it);
                it = job_pool.erase(it);
            } else ++it;
        }

        auto bit = blocked_pool.begin();
        while (bit != blocked_pool.end()) {
            if (processes[*bit].io_end_time == current_time) {
                processes[*bit].current_burst_idx++;
                processes[*bit].remaining_time = processes[*bit].bursts[processes[*bit].current_burst_idx];
                ready_queue.push(*bit);
                bit = blocked_pool.erase(bit);
            } else ++bit;
        }

        if (running_idx == -1 && !ready_queue.empty()) {
            running_idx = ready_queue.front();
            ready_queue.pop();
        }

        if(verbose) {
            print_queue_state(current_time, ready_queue, running_idx, processes);
        }

        increment_waiting_time(ready_queue, processes);

        if (running_idx != -1) {
            timeline.push_back("P" + to_string(processes[running_idx].id));
            processes[running_idx].remaining_time--;
            if (processes[running_idx].remaining_time == 0) {
                int curr_idx = processes[running_idx].current_burst_idx;
                if (curr_idx + 1 < processes[running_idx].bursts.size()) {
                    processes[running_idx].current_burst_idx++;
                    int io_duration = processes[running_idx].bursts[processes[running_idx].current_burst_idx];
                    processes[running_idx].io_end_time = current_time + 1 + io_duration;
                    blocked_pool.push_back(running_idx);
                } else {
                    processes[running_idx].completion_time = current_time + 1;
                    processes[running_idx].turnaround_time = processes[running_idx].completion_time - processes[running_idx].arrival_time;
                    completed++;
                }
                running_idx = -1;
            }
        } else {
            timeline.push_back("-");
        }
        current_time++;
    }
    print_metrics("First-Come, First-Served (FCFS)", processes, timeline);
}

void simulate_Round_Robin(vector<Process> processes, int quantum) {
    int current_time = 0;
    queue<int> ready_queue;
    vector<int> blocked_pool;
    vector<int> job_pool;
    vector<string> timeline;

    for(size_t i = 0; i < processes.size(); ++i) job_pool.push_back(i);

    int completed = 0;
    int running_idx = -1;

    while (completed < processes.size()) {
        vector<int> newly_ready;

        // Arrivals
        auto it = job_pool.begin();
        while (it != job_pool.end()) {
            if (processes[*it].arrival_time == current_time) {
                newly_ready.push_back(*it);
                it = job_pool.erase(it);
            } else ++it;
        }

        auto bit = blocked_pool.begin();
        while (bit != blocked_pool.end()) {
            if (processes[*bit].io_end_time == current_time) {
                processes[*bit].current_burst_idx++;
                processes[*bit].remaining_time = processes[*bit].bursts[processes[*bit].current_burst_idx];
                processes[*bit].current_quantum_used = 0;
                newly_ready.push_back(*bit);
                bit = blocked_pool.erase(bit);
            } else ++bit;
        }

        for(int idx : newly_ready) {
            ready_queue.push(idx);
        }

        if (running_idx == -1 && !ready_queue.empty()) {
            running_idx = ready_queue.front();
            ready_queue.pop();
            processes[running_idx].current_quantum_used = 0;
        }

        if(verbose) {
            print_queue_state(current_time, ready_queue, running_idx, processes);
        }

        increment_waiting_time(ready_queue, processes);

        if (running_idx != -1) {
            timeline.push_back("P" + to_string(processes[running_idx].id));
            processes[running_idx].remaining_time--;
            processes[running_idx].current_quantum_used++;

            if (processes[running_idx].remaining_time == 0) {
                int curr_idx = processes[running_idx].current_burst_idx;
                if (curr_idx + 1 < processes[running_idx].bursts.size()) {
                    processes[running_idx].current_burst_idx++;
                    int io_duration = processes[running_idx].bursts[processes[running_idx].current_burst_idx];
                    processes[running_idx].io_end_time = current_time + 1 + io_duration;
                    blocked_pool.push_back(running_idx);
                } else {
                    processes[running_idx].completion_time = current_time + 1;
                    processes[running_idx].turnaround_time = processes[running_idx].completion_time - processes[running_idx].arrival_time;
                    completed++;
                }
                running_idx = -1;
            }
            else if (processes[running_idx].current_quantum_used == quantum) {
                int preempted_idx = running_idx;
                running_idx = -1;

                int next_time = current_time + 1;

                auto next_it = job_pool.begin();
                while (next_it != job_pool.end()) {
                    if (processes[*next_it].arrival_time == next_time) {
                        ready_queue.push(*next_it);
                        next_it = job_pool.erase(next_it);
                    } else ++next_it;
                }
                auto next_bit = blocked_pool.begin();
                while (next_bit != blocked_pool.end()) {
                    if (processes[*next_bit].io_end_time == next_time) {
                        processes[*next_bit].current_burst_idx++;
                        processes[*next_bit].remaining_time = processes[*next_bit].bursts[processes[*next_bit].current_burst_idx];
                        processes[*next_bit].current_quantum_used = 0;
                        ready_queue.push(*next_bit);
                        next_bit = blocked_pool.erase(next_bit);
                    } else ++next_bit;
                }

                ready_queue.push(preempted_idx);
            }
        } else {
            timeline.push_back("-");
        }
        current_time++;
    }
    print_metrics("Round Robin (RR) [Quantum = " + to_string(quantum) + "]", processes, timeline);
}

// 3. Preemptive Priority Simulation
void simulate_Preemptive_Priority(vector<Process> processes) {
    int current_time = 0;
    queue<int> ready_queue;
    vector<int> blocked_pool;
    vector<int> job_pool;
    vector<string> timeline;

    for(size_t i = 0; i < processes.size(); ++i) job_pool.push_back(i);

    int completed = 0;
    int running_idx = -1;

    while (completed < processes.size()) {
        vector<int> current_pool;

        auto it = job_pool.begin();
        while (it != job_pool.end()) {
            if (processes[*it].arrival_time == current_time) {
                current_pool.push_back(*it);
                it = job_pool.erase(it);
            } else ++it;
        }

        auto bit = blocked_pool.begin();
        while (bit != blocked_pool.end()) {
            if (processes[*bit].io_end_time == current_time) {
                processes[*bit].current_burst_idx++;
                processes[*bit].remaining_time = processes[*bit].bursts[processes[*bit].current_burst_idx];
                current_pool.push_back(*bit);
                bit = blocked_pool.erase(bit);
            } else ++bit;
        }

        if (running_idx != -1) {
            current_pool.push_back(running_idx);
            running_idx = -1;
        }

        while(!ready_queue.empty()) {
            current_pool.push_back(ready_queue.front());
            ready_queue.pop();
        }

        if (!current_pool.empty()) {
            sort(current_pool.begin(), current_pool.end(), [&](int a, int b) {
                if(processes[a].priority == processes[b].priority)
                    return processes[a].arrival_time < processes[b].arrival_time;
                return processes[a].priority < processes[b].priority;
            });

            running_idx = current_pool.front();
            for(size_t i = 1; i < current_pool.size(); ++i) {
                ready_queue.push(current_pool[i]);
            }
        }

        if(verbose) {
            print_queue_state(current_time, ready_queue, running_idx, processes);
        }

        increment_waiting_time(ready_queue, processes);

        if (running_idx != -1) {
            timeline.push_back("P" + to_string(processes[running_idx].id));
            processes[running_idx].remaining_time--;
            if (processes[running_idx].remaining_time == 0) {
                int curr_idx = processes[running_idx].current_burst_idx;
                if (curr_idx + 1 < processes[running_idx].bursts.size()) {
                    processes[running_idx].current_burst_idx++;
                    int io_duration = processes[running_idx].bursts[processes[running_idx].current_burst_idx];
                    processes[running_idx].io_end_time = current_time + 1 + io_duration;
                    blocked_pool.push_back(running_idx);
                } else {
                    processes[running_idx].completion_time = current_time + 1;
                    processes[running_idx].turnaround_time = processes[running_idx].completion_time - processes[running_idx].arrival_time;
                    completed++;
                }
                running_idx = -1;
            }
        } else {
            timeline.push_back("-");
        }
        current_time++;
    }
    print_metrics("Preemptive Priority Scheduling", processes, timeline);
}

int main(int argc, char** argv) {
    string filename = "profile.txt";

    if(argc == 1) {
        verbose = false;
    }
    else if(argc == 2 && argv[1] == string("verbose")) {
        verbose = true;
    }
    else if(argc > 2 || argv[1] != string("verbose")) {
        cout << "Usage: Either ./executable or ./executable verbose\n";
        return 1;
    }

    vector<Process> processes = load_processes(filename);
    if (processes.empty()) return 1;

    simulate_FCFS(processes);
    simulate_Round_Robin(processes, 2);
    simulate_Preemptive_Priority(processes);

    return 0;
}
