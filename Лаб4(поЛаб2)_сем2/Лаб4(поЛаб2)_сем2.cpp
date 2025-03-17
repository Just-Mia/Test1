// Лаб4(поЛаб2)_сем2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <string>
using namespace std;

class Media {
protected:
    string title;
    int year;

public:
    Media() : title("No-title"), year(2000) {}
    Media(string t, int y) : title(t), year(y) {}
    virtual ~Media() { cout << "Deleting media: " << title << endl; }
    virtual void display() const {
        cout << "Media: " << title << ", Year: " << year << endl;
    }
};

class Video : public Media {
private:
    int likes;
    static int videoCount;

public:
    Video() : Media(), likes(0) { videoCount++; }
    Video(string t, int a, int y) : Media(t, y), likes(a) { videoCount++; }
    Video(string t) : Video(t, 0, 2000) {}
    Video(const Video& other) : Media(other), likes(other.likes) {
        cout << "Copy constructor called for " << title << endl;
    }
    Video(Video&& other) noexcept : Media(move(other)), likes(other.likes) {
        other.likes = 0;
        cout << "Move constructor called for " << title << endl;
    }
    ~Video() { cout << "Deleting video: " << title << endl; }
    Video& operator=(const Video& other) {
        if (this != &other) {
            title = other.title;
            year = other.year;
            likes = other.likes;
        }
        return *this;
    }
    void display() const override {
        cout << "Video: " << title << ", Likes: " << likes << ", Year: " << year << endl;
    }
    static int getVideoCount() { return videoCount; }
};

int Video::videoCount = 0;

class Movie : public Video {
private:
    string director;
public:
    Movie(string t, int a, int y, string d) : Video(t, a, y), director(d) {}
    void display() const override {
        cout << "Movie: " << title << ", Directed by " << director << ", Year: " << year << endl;
    }
};

class YouTubeVideo : public Video {
private:
    string channelName;
public:
    YouTubeVideo(string t, int a, int y, string c) : Video(t, a, y), channelName(c) {}
    void display() const override {
        cout << "YouTube Video: " << title << ", Channel: " << channelName << ", Year: " << year << endl;
    }
};

int main() {
    Video v1("All about Git in 1 minute", 1000, 2020);
    Video v2 = v1;
    Video v3 = move(v1);
    v2.display();

    Movie m1("Inception", 10000, 2010, "Christopher Nolan");
    m1.display();

    YouTubeVideo yt1("C++ Tutorial", 5000, 2021, "Programming Hub");
    yt1.display();

    cout << "Total videos: " << Video::getVideoCount() << endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
