#include <atomic>
#include <condition_variable>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

template <typename T> class SyncQueue {
  public:
    void push(const T &item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
        condition_.notify_one();
    }
    bool pop(T &item) {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this]() { return !queue_.empty() || done_; });
        if (queue_.empty())
            return false;
        item = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    void set_done() {
        std::lock_guard<std::mutex> lock(mutex_);
        done_ = true;
        condition_.notify_all();
    }

  private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool done_ = false;
};

std::atomic<int> ans = 0;

void producer(std::string filename, SyncQueue<std::string> &queue) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        queue.push(line);
    }
    queue.set_done();
}

std::vector<int> convert(std::string &line) {
    std::vector<int> levels;
    std::istringstream is(line);
    int i;
    while (is >> i) {
        levels.push_back(i);
    }
    return levels;
}

bool isSafe(std::vector<int> levels) {
    std::size_t n = levels.size();
    if (n < 2) {
        return true;
    }
    enum class ORDER {
        ASC,
        DESC,
    };
    ORDER ord = levels[0] < levels[1] ? ORDER::ASC : ORDER::DESC;
    bool ok = true;
    for (size_t i = 0; i < n - 1; i++) {
        int diff = levels[i] - levels[i + 1];
        ORDER tmp = diff < 0 ? ORDER::ASC : ORDER::DESC;
        if (tmp != ord || std::abs(diff) < 1 || std::abs(diff) > 3) {
            ok = false;
            break;
        }
    }
    return ok;
}

void consumer(SyncQueue<std::string> &queue) {
    std::string line;
    while (queue.pop(line)) {
        std::vector<int> levels = convert(line);
        bool ok = isSafe(levels);
        if (ok)
            ans += 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        std::cerr << "Usage: " << argv[0]
                  << " <input_filename> [<num_threads>]\n";
        return 1;
    }
    std::string filename = argv[1];
    int num_consumers = 4;
    if (argc == 3) {
        num_consumers = std::stoi(argv[2]);
    }
    SyncQueue<std::string> q;

    std::thread producer_thread(producer, filename, std::ref(q));

    std::vector<std::thread> consumer_threads;
    for (int i = 0; i < num_consumers; ++i) {
        consumer_threads.emplace_back(consumer, std::ref(q));
    }

    producer_thread.join();
    for (auto &thread : consumer_threads) {
        thread.join();
    }
    std::cout << ans << std::endl;

    return 0;
}
