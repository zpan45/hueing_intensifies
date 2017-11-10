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
    
    
    User testHash("u1", "testPW", "foo", "bar");
    User testHash2("u2", "", "baz", "bop");
    std::cout << "Creating test Users..." << std::endl;
    std::cout << testHash.constructGreetingString() << std::endl;
    std::cout << testHash2.constructGreetingString() << std::endl << std::endl;
    
    std::cout << "U1 Password: " << testHash.getPassword() << " Hashed Password: " << testHash.hashPassword(testHash.getPassword()) << std::endl;
    
    std::string secondPW;
    std::cout << "Enter the above test password a second time: " << std::endl;
    std::cin >> secondPW;
    
    testHash2.setPassword(secondPW);
    std::cout << "Setting " << testHash2.getUsername() << "'s password... " << (testHash.getPassword() != "") << std::endl;
    std::cout << testHash2.getUsername() << "'s password is: " << testHash2.getPassword() << std::endl;
    
    std::cout << "U2 Password: " << testHash2.getPassword() << " Hashed Password: " << testHash2.hashPassword(testHash2.getPassword()) << std::endl;
    
    std::cout << "Testing if the password hashes were the same... " << (testHash.hashPassword(testHash.getPassword()) == testHash2.hashPassword(testHash2.getPassword())) << std::endl;

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
}
