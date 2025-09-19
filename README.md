# 🥢 Philo (Dining Philosophers)

An implementation of the **Dining Philosophers Problem** in C as part of the [42 curriculum](https://42.fr/).  
The goal of this project is to explore multithreading, synchronization, and timing by simulating philosophers who alternate between **eating, sleeping, and thinking** without running into race conditions or deadlocks.

---

## 📖 Problem Overview

Five philosophers sit around a table with one fork between each of them.  
Each philosopher must:

1. **Take two forks** (mutexes) to eat.  
2. **Eat** for a given amount of time.  
3. **Sleep**, then **think**.  
4. Repeat until they either die of starvation or reach the required number of meals.

The challenge is to **safely manage concurrency** so no philosopher starves or causes deadlock.

---

## ✨ Features

- ✅ Each philosopher runs in its own **thread**.  
- ✅ Forks are managed using **mutexes** to prevent race conditions.  
- ✅ Precise timing for eating, sleeping, and dying.  
- ✅ Optional argument: stop when all philosophers have eaten `N` times.  
- ✅ Logs each action with timestamps:
  - `has taken a fork`
  - `is eating`
  - `is sleeping`
  - `is thinking`
  - `died`

---

## ⚙️ Usage

### 1. Clone the repository
```bash
git clone https://github.com/MossaJehad/Philo.git
cd Philo
make
```

### 2. Run
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

