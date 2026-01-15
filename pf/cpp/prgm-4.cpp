#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

/**
 * Inherited Stack that enforces Hanoi Rules:
 * A value can only be pushed if it is smaller than the current top.
 */
class SpecialStack : public std::stack<int> {
public:
    // Shadowing the push method to add the constraint
    void push(const int& val) {
        if (this->empty() || val < this->top()) {
            std::stack<int>::push(val);
        } else {
            // This prevents illegal moves during the Hanoi process
            std::cout << "  [Constraint Violation] Cannot push " << val 
                      << " onto " << this->top() << std::endl;
        }
    }

    // Helper to see what's inside without destroying the stack (for visualization)
    void display() {
        if (this->empty()) {
            std::cout << "[ Empty ]";
            return;
        }
        std::stack<int> temp = *this;
        while (!temp.empty()) {
            std::cout << temp.top() << " ";
            temp.pop();
        }
    }
};

/**
 * Logic to solve the Tower of Hanoi problem
 */
class HanoiSolver {
private:
    int total_moves = 0;

public:
    void solve(int n, SpecialStack& src, SpecialStack& dest, SpecialStack& aux, 
               char s_name, char d_name, char a_name) {
        if (n == 0) return;

        // 1. Move n-1 disks from Source to Aux
        solve(n - 1, src, aux, dest, s_name, a_name, d_name);

        // 2. Move the largest disk from Source to Destination
        int disk = src.top();
        src.pop();
        dest.push(disk); // This call is validated by our SpecialStack logic
        total_moves++;
        
        std::cout << "Move " << disk << " from " << s_name << " to " << d_name << std::endl;

        // 3. Move n-1 disks from Aux to Destination
        solve(n - 1, aux, dest, src, a_name, d_name, s_name);
    }

    int getMoves() const { return total_moves; }
};

int main() {
    // 1. Haphazard input sequence
    std::vector<int> haphazardNumbers = {15, 3, 9, 22, 1};
    int n = haphazardNumbers.size();

    // 2. Prepare the numbers
    // To satisfy the SpecialStack rule (smaller on top), we must push them 
    // onto the source stack in descending order.
    std::sort(haphazardNumbers.begin(), haphazardNumbers.end(), std::greater<int>());

    SpecialStack source, auxiliary, destination;

    std::cout << "--- Initializing Source Stack with Haphazard Numbers ---" << std::endl;
    for (int val : haphazardNumbers) {
        source.push(val);
    }

    std::cout << "Initial Source: "; source.display();
    std::cout << "\n\n--- Starting Recursive Hanoi Transfer ---" << std::endl;

    // 3. Solve the puzzle
    HanoiSolver solver;
    solver.solve(n, source, destination, auxiliary, 'A', 'C', 'B');

    // 4. Final Output
    std::cout << "\n--- Transfer Complete ---" << std::endl;
    std::cout << "Final Destination (Top to Bottom): "; 
    destination.display();
    std::cout << "\nTotal Moves: " << solver.getMoves() << " (Expected: 2^n - 1 = " << (1 << n) - 1 << ")" << std::endl;

    return 0;
}
