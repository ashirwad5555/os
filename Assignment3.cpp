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
    char buff[100];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t p = fork();

    if (p < 0)
    {
        perror("fork");
        return 1;
    }
    else if (p > 0)
    {
        // parent
        close(fd[0]);

        string message;
        cout << "Enter a message: ";
        getline(cin, message); // Get message dynamically from user

        write(fd[1], message.c_str(), message.length());
        close(fd[1]);

        wait(NULL);
    }
    else
    {
        // child
        close(fd[1]);

        int n = read(fd[0], buff, sizeof(buff));
        if (n > 0)
        {
            buff[n] = '\0';
            printf("Child received: %s\n", buff);

            // Here's how you can do it
            vector<string> words;
            istringstream iss(buff);
            string word;

            // Read all words
            while (iss >> word)
            {
                // Only add if not already in the vector (inefficient but preserves order)
                if (find(words.begin(), words.end(), word) == words.end())
                {
                    words.push_back(word);
                }
            }

            // Print unique words (unsorted/original order)
            string uniqueMessage;
            for (const auto &w : words)
            {
                uniqueMessage += w + " ";
            }
            if (!uniqueMessage.empty())
            {
                // extraa trailling space is removed from end
                uniqueMessage.pop_back();
            }
            printf("Unique Words (original order): %s\n", uniqueMessage.c_str());

            // Sort for the sorted message
            sort(words.begin(), words.end());

            // Create sorted message
            string sortedMessage;
            for (size_t i = 0; i < words.size(); i++)
            {
                sortedMessage += words[i];
                if (i < words.size() - 1)
                {
                    sortedMessage += " ";
                }
            }
            printf("Sorted Message: %s\n", sortedMessage.c_str());
        }
        else
        {
            printf("Child read failed or empty message\n");
        }

        close(fd[0]);
    }

    return 0;
}
