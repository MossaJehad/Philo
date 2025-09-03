🍝 Philosophers_Pthread — Dining Philosophers Problem Using POSIX Threads (42 Amman Project)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  
🧠 Project Overview  
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  

This project implements the classic Dining Philosophers problem using C and POSIX threads (pthreads).  
It simulates philosophers sitting around a table, each alternating between philo_eat, philo_thinking, and sleeping, while avoiding concurrency issues like deadlocks and table races.

✨ Achievement: Ready for Evaluation

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  
📌 Learning Objectives  
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  

• Understand classic concurrency problems  
• Manage threads using pthreads in C  
• Use mutexes to synchronize access to shared resources  
• Prevent deadlocks by controlling fork acquisition order  
• Avoid table races by ensuring safe thread interactions  
• Implement time-based state monitoringing for each philosopher  
• Follow Norminette coding standards  
• Ensure memory safety (valgrind-clean code)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  
⚙️ How to Use  
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  

1️⃣ Clone the Repository  
    clone...
    cd Philosophers_Pthread

2️⃣ Build the Program  
    make

3️⃣ Run the Simulation  
    ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

💡 Example  
    ./philo 5 800 200 200  
    (5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  
🔄 Key Concurrency Challenges  
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  

🔐 Deadlock  
Occurs when every philosopher picks up one fork and waits forever for the second, causing a standstill.

✅ Prevention Strategies  
• Odd/even philosophers pick up forks in different orders  
• Use a waiter or semaphore to limit access  
• Lock both forks simultaneously (when possible)

⚠️ Data Race  
Occurs when multiple threads access shared table without synchronization, potentially modifying it simultaneously.

✅ Prevention Strategies  
• Use mutexes to protect shared variables (e.g., writing to stdout, tracking last_meal times)  
• Always lock before accessing/modifying shared state  
• Avoid unnecessary shared state when possible

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  
📁 Project Structure  
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  

📂 Philosophers_Pthread/  
 ┣ 📄 Makefile         — Build instructions  
 ┣ 📄 philo.c          — Main execution logic  
 ┣ 📄 utils.c          — Utility functions  
 ┣ 📄 philo.h          — Header file with structs and declarations  
 ┣ 📄 README.txt       — Project documentation (this file)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  
🧪 Testing & Validation  
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  

✔️ Works with 1 to 200 philosophers  
✔️ Tested with and without optional meal limits  
✔️ Detects philosopher death in real-time  
✔️ No deadlocks  
✔️ No table races (confirmed with ThreadSanitizer and valgrind)  
✔️ Norm-compliant and memory-safe

