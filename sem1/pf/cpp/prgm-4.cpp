#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

class SpecialStack : public std::stack<int> {
public:
    void push(const int& val) {
        if (this->empty() || val < this->top()) {
            std::stack<int>::push(val);
        } else {
            std::cout << "Cannot push " << val << " onto " << this->top() << std::endl;
        }
    }

    void display() {
        if (this->empty()) {
            std::cout << "Empty";
            return;
        }
        std::stack<int> temp = *this;
        while (!temp.empty()) {
            std::cout << temp.top() << " ";
            temp.pop();
        }
    }
};

class HanoiSolver {
private:
    int total_moves = 0;

public:
    void solve(int n, SpecialStack& src, SpecialStack& dest, SpecialStack& aux, 
               char s_name, char d_name, char a_name) {
        if (n == 0) return;
        solve(n - 1, src, aux, dest, s_name, a_name, d_name);

        int disk = src.top();
        src.pop();
        dest.push(disk); 
        total_moves++;
        std::cout << "Move " << disk << " from " << s_name << " to " << d_name << std::endl;

        solve(n - 1, aux, dest, src, a_name, d_name, s_name);
    }

    int getMoves() const { return total_moves; }
};

int main() {
    std::vector<int> haphazardNumbers = {15, 3, 9, 22, 1};
    int n = haphazardNumbers.size();
    std::sort(haphazardNumbers.begin(), haphazardNumbers.end(), std::greater<int>());

    SpecialStack source, auxiliary, destination;

    std::cout << "Initializing Source Stack with Haphazard Numbers" << std::endl;
    for (int val : haphazardNumbers) {
        source.push(val);
    }

    std::cout << "Initial Source: "; source.display();
    std::cout << "\n\nStarting Recursive Hanoi Transfer" << std::endl;
    HanoiSolver solver;
    solver.solve(n, source, destination, auxiliary, 'A', 'C', 'B');

    std::cout << "\nTransfer Complete" << std::endl;
    std::cout << "Final Destination (Top to Bottom): "; 
    destination.display();
    std::cout << "\nTotal Moves: " << solver.getMoves() << " (Expected: 2^n - 1 = " << (1 << n) - 1 << ")" << std::endl;

    return 0;
}
