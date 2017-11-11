+-----------------------------------------+
|        TEAM 24 - HUE APPLICATION        |
+-----------------------------------------+

README.txt

============================
I. SUBMISSION INFORMATION
============================

Prepared By:
    TEAM 24:
    Anthony Tran (atran94),
    Omar Abdel-Qader (oabdelqa),
    Usant Kajendirarajah (ukajendi),
    Zhengyang Pan (zpan45),
    Jacob Fryer (jfryer6)

Prepared For:
    Professor Mike Katchabaw
    CS3307A - Object-Oriented Design and Analysis
    Western University

Date Submitted:
    Friday, November 10, 2017


============================
II. BUILD INSTRUCTIONS
============================

Our progress as of Stage 2 is currently divided into two directories: data/ and frontend/.
These should be tested independently from one another.

II.i. data/ Directory

    The data/ directory corresponds to all back end objects (User, Bridge, Light, etc) 
    and the database that contains them for persistence.
    
    To build, a makefile has been assembled. Simply run the command:
        make app
    and the back end will compile into an executable called "app"
    
    To run, use the command:
        ./app

II.ii. frontend/ Directory
    The frontend/ directory contains all progress on the Wt front end.
    
    To build, a makefile has been assembled. Simply run the command:
        make frontend
    and the front end will compile into an executable called "frontend"
    
    To run, we have been using the command:
        ./frontend --docroot usr/local/share/Wt --http-address 0.0.0.0 --http-port 8080
