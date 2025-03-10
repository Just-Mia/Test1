// Лаб 3 (по лаб 2)_сем2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

class Video {
private:
    string title;
    int likes;
    int year;
    static int videoCount;

public:
    Video() : title("No-title"), likes(0), year(2000) { videoCount++; }
    Video(string t, int a, int y) : title(t), likes(a), year(y) { videoCount++; }
    Video(string t) : Video(t, 0, 2000) {}

    // Конструктор копіювання
    Video(const Video& other) : title(other.title), likes(other.likes), year(other.year) {
        cout << "Copy constructor called for " << title << endl;
    }

    // Конструктор переміщення
    Video(Video&& other) noexcept : title(move(other.title)), likes(other.likes), year(other.year) {
        other.likes = 0;
        other.year = 0;
        cout << "Move constructor called for " << title << endl;
    }

    ~Video() { cout << "Deleting video: " << title << endl; }

    // Використання вказівника this
    Video& setTitle(string t) {
        this->title = t;
        return *this;
    }

    void display() const {
        cout << "Video: " << title << ", Likes: " << likes << ", Year: " << year << endl;
    }

    static int getVideoCount() { return videoCount; }

    // Перевантаження унарного оператора -
    void operator-() { likes -= 10; }

    // Перевантаження бінарного оператора +
    Video operator+(const Video& other) {
        return Video(title, likes + other.likes, year);
    }

    // Дружні оператори
    friend ostream& operator<<(ostream& out, const Video& v) {
        out << "Video: " << v.title << ", Likes: " << v.likes << ", Year: " << v.year;
        return out;
    }
    friend istream& operator>>(istream& in, Video& v) {
        cout << "Enter title, likes, and year: ";
        in >> v.title >> v.likes >> v.year;
        return in;
    }
};

int Video::videoCount = 0;

int main() {
    Video v1("All about Git in 1 minute", 1000, 2020);
    Video v2 = v1; // Викликає конструктор копіювання
    Video v3 = move(v1); // Викликає конструктор переміщення

    v2.setTitle("Git Basics");

    const Video v4("Const Video", 500, 2019);
    v4.display(); // Працює, бо метод display() має const

    cout << "Total videos: " << Video::getVideoCount() << endl;

    -v2; // Викликає унарний оператор -
    Video v5 = v2 + v3; // Викликає оператор +

    cout << v5 << endl; // Вивід через оператор <<

    Video v6;
    cin >> v6; // Ввід через оператор >>
    cout << v6 << endl;

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
