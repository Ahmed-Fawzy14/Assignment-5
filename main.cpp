//
// Created by Fawzy on 11/25/2023.
//

//
// Created by Fawzy on 11/25/2023.
//



#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    double value;
    string valueString;
    string date;
    double exchangeRate;


    Node()
    {

    }


    //O(3)
    Node(double m, double q, string date)
    {
        value = q;
        this->date = date;
        exchangeRate = 0;

    }

    //O(1)
    bool operator<(const Node& x) const
    {
        return (exchangeRate < x.exchangeRate);
    }

    //O(1)
    bool operator>(const Node& x) const
    {
        return (exchangeRate > x.exchangeRate);
    }


};


//O(1)
void swap(vector<Node> &maxHeap, int i, int j)
{
    Node temp;
    temp = maxHeap[i];
    maxHeap[i] = maxHeap[j]; //up heap
    maxHeap[j] = temp; //down heap

}

//O(n) where n is the number of elements in a heap
void HeapifyMax(vector<Node> &maxHeap){

    int n = maxHeap.size();

    for (int i=(n/2)-1; i>=0; i--){

        int j = 2 * i + 1;  // Left child for current i

        while(j < n-1){
            // Compare left and right children of current i
            if (maxHeap[j] < maxHeap[j+1]){
                j = j+1;
            }

            // Compare parent and largest child
            if (maxHeap[i] < maxHeap[j]){
                swap(maxHeap, i, j);
                i = j;
                j = 2 * i + 1;
            } else {
                break;
            }
        }
    }
}

//O(n) where n is the number of elements in a heap
void HeapifyMin(vector<Node> &maxHeap){

    int n = maxHeap.size();

    for (int i=(n/2)-1; i>=0; i--){

        int j = 2 * i + 1;  // Left child for current i

        while(j < n-1){
            // Compare left and right children of current i
            if (maxHeap[j] > maxHeap[j+1]){
                j = j+1;
            }

            // Compare parent and largest child
            if (maxHeap[i] > maxHeap[j]){
                swap(maxHeap, i, j);
                i = j;
                j = 2 * i + 1;
            } else {
                break;
            }
        }
    }
}


//O(L*K) where L is the number of lines and K is the maximum
//length of a line
void fillmaxHeaprray(vector<Node> &maxHeap)
{
    fstream file("euro-dollar csv.txt");
    string line, value;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            Node newNode; // Create a new Node instance
            size_t i = 0;

            // Extract date
            while (i < line.size() && line[i] != '\t') {
                newNode.date.push_back(line[i]);
                i++;
            }
            i++; // Skip the tab character

            // Extract value
            value = line.substr(i); // Grab the rest of the line
            newNode.valueString = value;
            newNode.value = stod(value);

            // Debug print
            // cout << "Date: " << newNode.date << ", Value: " << newNode.value << endl;

            maxHeap.push_back(newNode); // Add the new Node to the vector
        }
    }
}

//gets all values and gets their mean
//O(n) where n is the number of elements in a heap
double calcMean(vector<Node> &maxHeap){

    double sum = 0;
    for(int i = 0; i<maxHeap.size(); i++)
    {
        sum += maxHeap[i].value; //using size not occupied size
    }

    sum = sum/maxHeap.size();

    return sum;
}

//O(n) where n is the number of elements in a heap
void setExchangeRate(vector<Node> &maxHeap, double sum)
{
    for(int i = 0; i<maxHeap.size(); i++)
    {
        maxHeap[i].exchangeRate = maxHeap[i].value - sum;
    }

}

//O(log(n)) where n is the number of elements in a heap
void deleteElementMax(std::vector<Node>& heap) {
    int n = heap.size() - 1; // Adjust for 0-based indexing
    if (n <= 0) {
        return; // Nothing to delete or invalid heap
    }

    // Swap the first element with the last
    swap(heap[0], heap[n]);

    // Start from the root
    int i = 0; // Root node at index 0
    int j = 2 * i + 1; // Left child index

    // Heapify down
    while (j < n) {
        // Select the larger child
        if (j + 1 < n && heap[j + 1] > heap[j]) {
            j = j + 1;
        }

        // If the parent is smaller than the larger child, swap them
        if (heap[i] < heap[j]) {
            swap(heap[i], heap[j]);
            i = j;
            j = 2 * i + 1; // Move to the next level
        } else {
            break; // Heap property satisfied
        }
    }

    // Remove the last element
    heap.pop_back();
}

//O(log(n)) where n is the number of elements in a heap
void deleteElementMin(std::vector<Node>& heap) {
    int n = heap.size() - 1; // Adjust for 0-based indexing
    if (n <= 0) {
        return; // Nothing to delete or invalid heap
    }

    // Swap the first element with the last
    swap(heap[0], heap[n]);

    // Start from the root
    int i = 0; // Root node at index 0
    int j = 2 * i + 1; // Left child index

    // Heapify down
    while (j < n) {
        // Check if right child exists and select the smaller child
        if (j + 1 < n && heap[j + 1] < heap[j]) {
            j = j + 1;
        }

        // If the parent is larger than the smaller child, swap them
        if (heap[i] > heap[j]) {
            swap(heap[i], heap[j]);
            i = j;
            j = 2 * i + 1; // Move to the next level
        } else {
            break; // Heap property satisfied
        }
    }

    // Remove the last element
    heap.pop_back();
}


//O(N*log(m)) where n is the number enterted by the user
// and where m is the inital number of elements in the heap
void getNmax(vector<Node> &maxHeap, vector<Node> &maxHeapN, int n)
{
    for(int i = 0; i<n; i++)
    {
        maxHeapN.push_back(maxHeap[0]);
        deleteElementMax(maxHeap);
    }

}

//O(N*log(m)) where n is the number enterted by the user
// and where m is the inital number of elements in the heap
void getNmin(vector<Node> &minHeap, vector<Node> &minHeapN, int n)
{
    for(int i = 0; i<n; i++)
    {
        minHeapN.push_back(minHeap[0]);
        deleteElementMin(minHeap);
    }


}
//function from https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
//not from slides because I understood the algorithm from the website
//O(n) where n is the number of elements in a heap
void maxSubArraySum(vector<Node> &heap)
{
    double max_so_far = -32000, max_ending_here = 0;
    int start = 0, end = 0, s = 0;

    for (int i = 0; i < heap.size(); i++) {
        max_ending_here += heap[i].exchangeRate;

        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }

        if (max_ending_here < 0) {
            max_ending_here = 0;
            s = i + 1;
        }
    }
    cout << "Maximum contiguous sum is " << max_so_far
         << endl;
    //starting from zero index
    cout << "Starting index " << start<< " date: "<<heap[start].date << endl
         << "Ending index " << end<<" date: "<<heap[end].date<< endl;
}

//x==1 O(N*log(m))
//x==2 O(N*log(m))
//x=3 O(n)
void runProgramProblemOne(vector<Node> &maxHeap, vector<Node> &minHeap,vector<Node> &data)
{
    int x = 0;
    int n = 0;
    vector<Node> maxHeapN;
    vector<Node> minHeapN;


    cout<<"Choose the program you want to run:"<<endl;
    cout<<"1: Find the N highest exchange rates of the data set."<<endl;
    cout<<"2: Find the N lowest exchange rates of the data set."<<endl;
    cout<<"3: Find the dates and indicies of the maximum contigious sum."<<endl;
    cin>> x;


    if(x==1)
    {
        cout<<"Enter N: "<<endl;
        cin>>n;
        getNmax(maxHeap, maxHeapN, n);
        for(int i = 0; i<maxHeapN.size(); i++)
        {
            cout<<"The "<<i+1<<" ordered element date is: "<<maxHeapN[i].date<<"and value is: "<<maxHeapN[i].exchangeRate<<endl;
        }
    }
    else if(x==2)
    {
        cout<<"Enter N: "<<endl;
        cin>>n;
        getNmin(minHeap, minHeapN, n);
        for(int i = 0; i<minHeapN.size(); i++)
        {
            cout<<"The "<<i+1<<" ordered element date is: "<<minHeapN[i].date<<"and value is: "<<minHeapN[i].exchangeRate<<endl;
        }
    }
    else if(x==3)
    {
        maxSubArraySum(data);

    }



}






int main(){

    vector<Node> maxHeap;
    vector<Node> minHeap;
    vector<Node> data;

    double sum = 0;
    fillmaxHeaprray(maxHeap);

    sum = calcMean(maxHeap);
    setExchangeRate(maxHeap, sum);
    minHeap = maxHeap;
    data = maxHeap;

    HeapifyMax(maxHeap);
    HeapifyMin(minHeap);

   runProgramProblemOne(maxHeap, minHeap, data);







    return 0;
}