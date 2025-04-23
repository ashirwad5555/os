#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

int main()
{
    int fd[2];
    char buffer[100];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        // parent will write
        close(fd[0]); // close the reader

        string message;
        cout << "Enter the message" << endl;
        getline(cin, message); // Get message dynamically from user
        write(fd[1], message.c_str(), message.length());
        close(fd[1]);

        wait(NULL);
    }
    else
    {
        // child reading
        close(fd[1]); // close the writing end

        int n = read(fd[0], buffer, sizeof(buffer));

        string receivedMsg = "";
        if (n > 0)
        {
            buffer[n] = '\0';

            cout << "message recieved : " << buffer << endl;
        }

        // unique strings in the message
        vector<string> words;
        istringstream iss(buffer);
        string word;
        string uniquemessage;

        while (iss >> word)
        {
            // insert only unique words in the words vector
            if (find(words.begin(), words.end(), word) == words.end())
            {
                words.push_back(word);
            }
        }

        sort(words.begin(), words.end());

        for (int i = 0; i < words.size(); i++)
        {
            uniquemessage += words[i] + " ";
        }
        if (!uniquemessage.empty())
        {
            uniquemessage.pop_back();
        }

        cout << " unique and sorted message" << endl;
        for (const auto w : uniquemessage)
        {
            cout << w;
        }
    }
}