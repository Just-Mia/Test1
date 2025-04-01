// Лаб6Чернетка.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Video {
    string title;
    string channel;
    int likes;
};

const string ADMIN_PASSWORD = "123";
const string ADMIN_FILE = "admin_data.txt";
const string USER_HISTORY_FILE = "user_history.txt";

void saveVideo(const Video& video) {
    ofstream file(ADMIN_FILE, ios::app);
    if (file.is_open()) {
        file << video.title << "|" << video.channel << "|" << video.likes << "\n";
        file.close();
    }
}

vector<Video> loadVideos() {
    vector<Video> videos;
    ifstream file(ADMIN_FILE);
    if (file.is_open()) {
        string title, channel, likes;
        while (getline(file, title, '|') && getline(file, channel, '|') && getline(file, likes)) {
            videos.push_back({ title, channel, stoi(likes) });
        }
        file.close();
    }
    return videos;
}

void viewVideos() {
    vector<Video> videos = loadVideos();
    for (const auto& video : videos) {
        cout << "Name: " << video.title << ", Channel: " << video.channel << ", Likes: " << video.likes << endl;
    }
}

void editVideo() {
    vector<Video> videos = loadVideos();
    string searchTitle;
    cout << "Enter name of the video for edit: ";
    cin.ignore();
    getline(cin, searchTitle);

    bool found = false;
    for (auto& video : videos) {
        if (video.title == searchTitle) {
            cout << "Enter new name: ";
            getline(cin, video.title);
            cout << "Enter new channel name: ";
            getline(cin, video.channel);
            cout << "Likes: ";
            cin >> video.likes;
            found = true;
            break;
        }
    }

    if (found) {
        ofstream file(ADMIN_FILE, ios::trunc);
        for (const auto& video : videos) {
            file << video.title << "|" << video.channel << "|" << video.likes << "\n";
        }
        file.close();
        cout << "!\n";
    }
    else {
        cout << "Error.\n";
    }
}

void searchVideo() {
    vector<Video> videos = loadVideos();
    string searchTitle;
    cout << "Enter video name for search: ";
    cin.ignore();
    getline(cin, searchTitle);

    ofstream historyFile(USER_HISTORY_FILE, ios::app);
    historyFile << searchTitle << "\n";
    historyFile.close();

    bool found = false;
    for (const auto& video : videos) {
        if (video.title == searchTitle) {
            cout << "Name: " << video.title << ", Channel: " << video.channel << ", Likes: " << video.likes << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Error.\n";
    }
}

void adminMenu() {
    string password;
    cout << "Enter password: ";
    cin >> password;

    if (password != ADMIN_PASSWORD) {
        cout << "Wrong!\n";
        return;
    }

    int choice;
    do {
        cout << "\n1. Add video\n2. Edit video\n3. See more videos\n4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Video video;
            cin.ignore();
            cout << "Enter video name: ";
            getline(cin, video.title);
            cout << "Enter channel name: ";
            getline(cin, video.channel);
            cout << "Enter likes number: ";
            cin >> video.likes;
            saveVideo(video);
            break;
        }
        case 2:
            editVideo();
            break;
        case 3:
            viewVideos();
            break;
        }
    } while (choice != 4);
}

void userMenu() {
    int choice;
    do {
        cout << "\n1. See all videos\n2. search\n3. exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewVideos();
            break;
        case 2:
            searchVideo();
            break;
        }
    } while (choice != 3);
}

int main() {
    int role;
    cout << "Who are you??:\n1. Admin\n2. User\nThe choice: ";
    cin >> role;

    if (role == 1) {
        adminMenu();
    }
    else if (role == 2) {
        userMenu();
    }
    else {
        cout << "Error?? \n";
    }

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
