// NOTES
// File Manager needs to:
//        1. Create a usable database at runtime (load users)
//        2. Manipulate database during runtime (add, remove, update a user)
//        3. Convert the runtime database to a text file for persistence (save users)
//        4. clear the file after loading so as to write to blank file

// Methods to implement:

//    1. Write to file     saveUsers()
//    2. Clear file

//    3. Read from file --> to where?     loadUsers()
//        - how do you know when a line is done?
//    4. Search file!!!! some sort of tree implementation

//    5. Add user
//    6. Remove user

#include "DBFileManager.h"

/* CONSTRUCTORS */

DBFileManager::DBFileManager()
{
    DBFileManager::userFileStream.std::ofstream::open("UserDatabase.txt"); //open output stream to database file
}

/* PUBLIC METHODS */

void saveUsers(std::vector<User> users)
{
    if (!DBFileManager::userFileStream.std::ofstream::is_open()) //check that file is open
    {
        std::cout << "File failed to open." << std::endl;
        return 1;
    }
    else
    {
        writeToFile();
    }
}

void loadUsers()
{
    if (!DBFileManager::userFileStream.std::ofstream::is_open()) //check that file is open
    {
        std::cout << "File failed to open." << std::endl;
        return 1;
    }
    else
    {
        buildActiveDB();
    }
}

void writeToFile()
{
    if (!userFile.std::ofstream::is_open()) //check that file is open
    {
        std::cout << "File failed to open." << std::endl;
        return 1;
    }
    else
    {
        for (std::vector<User>::iterator it = DBFileManager::listOfUsers.begin() ; it != DBFileManager::listOfUsers.end(); ++it)
        {
            randomUser = *it;
            DBFileManager::userFileStream << randomUser.User::toString() << std::endl; //write info to a single line
        }
    }
}

void buildActiveDB()
{
    std::ifstream infile("UserDatabase.txt");
    User tempUser;

    std::string username;
    std::string password;
    std::string firstName;
    std::string lastName;

    while(infile >> username >> password >> firstName >> lastName)
    {
        tempUser.setUsername(username);
        tempUser.setPassword(password);
        tempUser.setFirstName(firstName);
        tempUser.setLastName(lastName);

        DBFileManager::listOfUsers.std::vector<User>.push_back(tempUser);
    }
}


