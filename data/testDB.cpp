#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <stdlib.h>
#include <vector>

#include "User.h"

int main(void)
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "------------- Password Hash Test --------------" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    // STEP ONE: Create Users

    User testHash("u1", "testPW", "foo", "bar");
    User testHash2("u2", "", "baz", "bop");
    std::cout << "Creating test Users..." << std::endl;
    std::cout << testHash.constructGreetingString() << std::endl;
    std::cout << testHash2.constructGreetingString() << std::endl << std::endl;

    // show user's password and its associated hash
    std::cout << "U1 Password:\t" << testHash.getPassword() << "\tHashed Password:\t" << testHash.hashPassword(testHash.getPassword()) << std::endl;

    // STEP TWO: Test Password Hashing

    // prompt the user to write the same password as above
    std::string secondPW;
    std::cout << "Enter the above test password a second time to test if password hashes are equal: " << std::endl;
    std::cin >> secondPW; // store entered password in "secondPW" string

    testHash2.setPassword(secondPW);
    std::cout << "Setting " << testHash2.getUsername() << "'s password... ";

    // test if password was set properly -- if empty string, password setting failed
    if(testHash.getPassword() != "") {
        std::cout << "SUCCESS" << std::endl;
    }
    else {
        std::cout << "Failure, password not set successfully." << std::endl;
    }
    std::cout << testHash2.getUsername() << "'s password is: " << testHash2.getPassword() << std::endl;

    std::cout << "U2 Password:\t" << testHash2.getPassword() << "\tHashed Password:\t" << testHash2.hashPassword(testHash2.getPassword()) << std::endl;

    // Test if the hashed passwords are equal
    std::cout << "Testing if the password hashes were the same... ";
    if(testHash.hashPassword(testHash.getPassword()) == testHash2.hashPassword(testHash2.getPassword())) {
        std::cout << "SUCCESS" << std::endl;
    }
    else {
        std::cout << "Failure, passwords were unequal." << std::endl;
    }

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "--------- User Database Test Program ----------" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    ///////////////////////////////////////////////////
    //   STEP 1  --> Create a vector of generic users /
    ///////////////////////////////////////////////////

    /*
    Generic user containers and set of users
    */
    std::string userName = "";
    std::string firstName = "";
    std::string lastName = "";
    std::string password = "";

    //std::set<User> currentUsers;    <-- will implement after overloading the comparison operator for User
    std::vector<User> currentUsers;

    /*
    Pick number of users to create
    */
    int numOfUsers = 0;

    std::cout << "Enter a number of users to generate: " << std::endl;
    std::cin >> numOfUsers;

    /*
    create users and fill the vector
    */

    User randomUser;

    for(int i = 0; i < numOfUsers; i++)
    {
        userName = "user";
        userName.std::string::append(std::to_string(i+1));
        randomUser.setUsername(userName);

        firstName = "First";
        firstName.std::string::append(std::to_string(i+1));
        randomUser.setFirstName(firstName);

        lastName = "Last";
        lastName.std::string::append(std::to_string(i+1));
        randomUser.setLastName(lastName);

        password = "pass";
        password.std::string::append(std::to_string(i+1));
        randomUser.setPassword(password);

        currentUsers.std::vector<User>::push_back(randomUser);
    }

    /*
    Check that vector isn't empty and display contents
    */
    if(currentUsers.std::vector<User>::empty())
    {
        std::cout << "Vector was not filled, check your code." << std::endl;
    }
    else
    {
        //Print confirmation
        User tempUser;

        std::cout << "User Generation Successful." << std::endl;
        std::cout << "Vector has been filled with " << currentUsers.std::vector<User>::size() << " users:" << std::endl;

        //Print for verification
        for (std::vector<User>::iterator it = currentUsers.begin() ; it != currentUsers.end(); ++it)
        {
            tempUser = *it;
            std::cout << tempUser.User::toString() << std::endl;
        }
    }

    ////////////////////////////////////////////////////////////
    //   STEP 2  --> Iterate through vector and write to file  /
    ////////////////////////////////////////////////////////////

    std::ofstream userFile("UserDatabase.txt"); //open output stream to database file

    if (!userFile.std::ofstream::is_open()) //check that file is open
    {
        std::cout << "File failed to open." << std::endl;
        return 1;
    }
    else
    {
        for (std::vector<User>::iterator it = currentUsers.begin() ; it != currentUsers.end(); ++it)
        {
            randomUser = *it;
            userFile << randomUser.User::toString() << std::endl; //write info to a single line
        }
        std::cout << "Writing to file complete. Verify that there are " << currentUsers.std::vector<User>::size() << " users in the file." << std::endl;
    }

    /////////////////////////////////////////////////////
    //   STEP 3 --> Read lines from file and display    /
    /////////////////////////////////////////////////////

    std::cout << "Now printing users from text file: " << std::endl;
    std::string currentLine;
    std::ifstream file("UserDatabase.txt");

    if (!file.std::ifstream::is_open()) //check that file is open
    {
        std::cout << "File failed to open." << std::endl;
        return 1;
    }
    else
    {
        while(!file.std::ifstream::eof())
        {
            std::getline(file, currentLine);
            std::cout << currentLine << std::endl;
        }

    }

    /* Need Boost library installed to run this bit and
    #include <boost/filesystem.hpp>

    code works, but commenting out for now

    //////////////////////////////////////////////////////////////////
    //   STEP 4 --> Test Boost exists() and create files/directories   /
    //////////////////////////////////////////////////////////////////

    std::string dirName = "Test_Dir";
    std::string dirName2 = "Directory1";

    std::cout << "Creating a directory called Test_Dir. Verify that it exists." << std::endl;
    boost::filesystem::create_directory(dirName);

    std::cout << "Creating another directory within original. Verify that it exists." << std::endl;
    std::string path = dirName.std::string::append("/");
    path.std::string::append(dirName2);
    boost::filesystem::create_directory(path);

    std::cout << "Creating a file in Directory 1. Verify that it exists and contains info." << std::endl;
    path.std::string::append("/userinfo.txt");

    std::ofstream testUserFile(path);
    testUserFile << "TESTING BITCH" << std::endl;
    testUserFile.std::ofstream::close();
    userFile.std::ofstream::clear();

    std::cout << "Testing exists function... " << std::endl;

    if(boost::filesystem::exists(path))
    {
        std::cout << "\tFile successfully detected." << std::endl;
    }
    else
    {
        std::cout << "Couldn't detect file." << std::endl;
    }
*/


}
