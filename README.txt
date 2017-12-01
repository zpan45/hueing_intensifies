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
    Thursday, November 30, 2017


============================
II. BUILD INSTRUCTIONS
============================

frontend/ Directory

    The frontend/ directory contains the whole application.

    To build, a makefile has been assembled. Simply run the command:
        make frontend
    and the front end will compile into an executable called "frontend"

    To run, we have been using the command:
        ./frontend --docroot usr/local/share/Wt --http-address 0.0.0.0 --http-port 8080

    Calling the command clean will remove all object files as well as the HUE_USERS database.
