#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <iostream>

enum SortAlgo { BUBBLE, SELECTION, INSERTION, QUICK, SHELL, MERGE, RADIX, HEAP };
std::vector<SortAlgo> algorithms = {BUBBLE, SELECTION, INSERTION, QUICK, SHELL, MERGE, RADIX, HEAP};

class SortingVisualizer {
private:
    sf::RenderWindow window;
    std::vector<int> arr;
    int numBars;
    int barWidth;
    int i = 0, j = 0; // bubble/insertion step counters
    int k = 0;        // selection/insertion step counter
    // Keep track of which algorithm to run
    int currentAlgo = 0;  
    bool isSorting = false;
    bool isSorted = false;
    int height;
    sf::SoundBuffer buffer;
    sf::Sound sound;

public:
    SortingVisualizer(int width, int height, int numBars)
    : window(sf::VideoMode(sf::Vector2u(static_cast<unsigned int>(width),
                                        static_cast<unsigned int>(height))),
             "Sorting Visualizer"),
      numBars(numBars),
      barWidth(width / numBars),
      arr(numBars),
      sound(buffer),
      height(height)
    {
        // Load sound
        if (!buffer.loadFromFile("../assets/beep2.mp3")) {
            std::cerr << "Failed to load sound\n";
        }
        sound.setBuffer(buffer);

        // Seed and generate random array
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        for (int i = 0; i < numBars; i++)
            arr[i] = std::rand() % height;

        isSorted = false;
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();

            if (!isSorted && !isSorting) {
                isSorting = true;  // prevent re-entry

                switch (algorithms[currentAlgo]) {
                    case BUBBLE:    bubbleSort(); break;
                    case SELECTION: selectionSort(); break;
                    case INSERTION: insertionSort(); break;
                    case QUICK:     quickSort(0, numBars-1); break;
                    case SHELL:     shellSort(); break;
                    case MERGE:     mergeSort(0, numBars-1); break;
                    case RADIX:     radixSort(); break;
                    case HEAP:      heapSort(); break;
                }

                // After algorithm completes, check if sorted
                if (isSorted) {
                    isSorting = false;

                    // Small pause so you can see result
                    sf::sleep(sf::seconds(1));

                    // Move to next algorithm
                    currentAlgo++;
                    if (currentAlgo >= algorithms.size()) {
                        currentAlgo = 0; // restart sequence (loop forever)
                    }

                    // Reset array with random values for next algorithm
                    resetArray();
                    isSorted = false;
                }
            }

            render();
        }
    }

private:
    void handleEvents() {
        while (auto eventOpt = window.pollEvent()) {
            auto event = *eventOpt;
            if (event.is<sf::Event::Closed>()) {
                window.close();
            }
        }
    }


    void render() {
        window.clear(sf::Color(60, 60, 100));
        for (int idx = 0; idx < numBars; idx++) {
            sf::RectangleShape bar;
            bar.setSize(sf::Vector2f(barWidth - 1, static_cast<float>(arr[idx])));
            std::uint8_t shade = static_cast<std::uint8_t>(
                255.0f * arr[idx] / window.getSize().y
            );
            bar.setFillColor(sf::Color(shade, shade, shade));
            bar.setPosition(sf::Vector2f(idx * barWidth, window.getSize().y - arr[idx]));
            window.draw(bar);
        }
        window.display();
    }

    void resetArray() {
        arr.clear();
        for (int i = 0; i < numBars; i++) {
            arr.push_back(rand() % height);  // generate random bar heights
        }
    }

    void bubbleSort() {
        for (int i = 0; i < numBars - 1; i++) {
            for (int j = 0; j < numBars - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);

                    float pitch = 0.5f + static_cast<float>(arr[j]) / 600;
                    sound.setPitch(pitch);
                    sound.play();
                    render();
                    //sf::sleep(sf::milliseconds(1));
                }
            }
        }
        isSorted = true;
    }


    void selectionSort() {
        for (int k = 0; k < numBars - 1; k++) {
            int posSmallest = k;
            for (int idx = k + 1; idx < numBars; idx++) {
                if (arr[idx] < arr[posSmallest])
                    posSmallest = idx;
            }

            std::swap(arr[k], arr[posSmallest]);

            float pitch = 0.5f + static_cast<float>(arr[posSmallest]) / 600;
            sound.setPitch(pitch);
            sound.play();
            render();
            sf::sleep(sf::milliseconds(50));
        }
        isSorted = true;
    }


    void insertionSort() {
        for (int k = 1; k < numBars; k++) {
            int temp = arr[k];
            int idx = k - 1;

            while (idx >= 0 && arr[idx] > temp) {
                arr[idx + 1] = arr[idx];

                float pitch = 0.5f + static_cast<float>(arr[idx]) / 600;
                sound.setPitch(pitch);
                sound.play();
                render();
                //sf::sleep(sf::milliseconds(1));

                idx--;
            }
            arr[idx + 1] = temp;
        }
        isSorted = true;
    }


    int partition(int beg, int end){
        int left = beg, right = end;
        int loc = beg;
        bool flag = false;

        while(!flag){
            while(arr[loc]<=arr[right] && loc!=right){
                right--;
            }

            if(loc == right){
                flag = true;
                break;
            }else if(arr[loc]> arr[right]){
                std::swap(arr[loc], arr[right]);

                float pitch = 0.5f + static_cast<float>(arr[loc]) / 600;
                sound.setPitch(pitch);
                sound.play();
                render();
                sf::sleep(sf::milliseconds(20));

                loc = right;
            }
            
            while(arr[loc]>=arr[left] && loc!= left){
                left ++;
            }

            if(loc == left){
                flag = true;
                break;
            }else if(arr[loc]< arr[left]){
                std::swap(arr[loc], arr[left]);

                float pitch = 0.5f + static_cast<float>(arr[loc]) / 600;
                sound.setPitch(pitch);
                sound.play();
                render();
                sf::sleep(sf::milliseconds(20));

                loc = left;
            }
        }

        return loc;
    }

    void quickSort(int beg, int end){
        if(beg < end){
            int loc = partition(beg, end);
            quickSort(beg, loc-1);
            quickSort(loc+1, end);
        }
        isSorted = true;
    }


    void shellSort(){
        int gap = numBars/2;
        while(gap > 0){
            for(int i = gap; i< numBars;i++){
                int temp = arr[i];;
                int j = i;
                while(j >= gap && arr[j-gap]>temp){
                    arr[j] = arr[j-gap];
                    j = j - gap;

                    float pitch = 0.5f + static_cast<float>(arr[j]) / 600;
                    sound.setPitch(pitch);
                    sound.play();
                    render();
                    sf::sleep(sf::milliseconds(10));

                }
                arr[j] = temp;
            }
            gap = gap/2;
        }
        isSorted = true;
    }

    void merge(int beg, int mid, int end){
        int i = beg, j = mid + 1, index = 0;
        std::vector<int> temp(end - beg + 1); // allocate space

        while(i <= mid && j <= end){
            if(arr[i] < arr[j]){
                temp[index++] = arr[i++];
            } else {
                temp[index++] = arr[j++];
            }
        }

        while(i <= mid) temp[index++] = arr[i++];
        while(j <= end) temp[index++] = arr[j++];

        for(int k = 0; k < index; k++){
            arr[beg + k] = temp[k];

            // pitch-based sound
            float pitch = 0.5f + static_cast<float>(arr[beg + k]) / 600;
            sound.setPitch(pitch);
            sound.play();
            render();
            sf::sleep(sf::milliseconds(10));
        }

    }

    void mergeSort(int beg, int end){
        if(beg<end){
            int mid = (beg+end)/2;
            mergeSort(beg, mid);
            mergeSort(mid+1, end);
            merge(beg,mid,end);
        }
        isSorted = true;
    }

    void radixSort(){
        int largest = *std::max_element(arr.begin(), arr.end());
        int divisor = 1;

        while(largest / divisor > 0) {
            std::vector<std::vector<int>> buckets(10);

            // distribute elements into buckets
            for(int i = 0; i < numBars; i++) {
                int digit = (arr[i] / divisor) % 10;
                buckets[digit].push_back(arr[i]);
            }

            // collect back into arr
            int index = 0;
            for(int i = 0; i < 10; i++) {
                for(int num : buckets[i]) {
                    arr[index++] = num;

                    // play sound with pitch based on value
                    float pitch = 0.5f + static_cast<float>(num) / 600;
                    sound.setPitch(pitch);
                    sound.play();

                   
                    render();
                    sf::sleep(sf::milliseconds(20));
                    
                }
            }

            divisor *= 10;
        }

        // final render to show fully sorted array
        render();
        isSorted = true;
    }

    void heapify(int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if(left < n && arr[left] > arr[largest])
            largest = left;

        if(right < n && arr[right] > arr[largest])
            largest = right;

        if(largest != i) {
            std::swap(arr[i], arr[largest]);

            // 🔊 sound and visual
            float pitch = 0.5f + static_cast<float>(arr[largest]) / 600;
            sound.setPitch(pitch);
            sound.play();
            render();
            sf::sleep(sf::milliseconds(15));

            // recursively heapify the affected subtree
            heapify(n, largest);
        }
    }

    void heapSort() {
        int n = numBars;

        // Step 1: Build max heap
        for(int i = n / 2 - 1; i >= 0; i--) {
            heapify(n, i);
        }

        // Step 2: Extract elements one by one
        for(int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);

            // 🔊 sound and visual
            float pitch = 0.5f + static_cast<float>(arr[i]) / 600;
            sound.setPitch(pitch);
            sound.play();
            render();
            sf::sleep(sf::milliseconds(15));

            // call max heapify on the reduced heap
            heapify(i, 0);
        }
        isSorted = true;
    }

};


int main() {
    SortingVisualizer visualizer(800, 600, 200);
    visualizer.run();
    return 0;
}
