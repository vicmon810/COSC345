[![Continous Integration CMAKE](https://github.com/vicmon810/COSC345/actions/workflows/cmake.yaml/badge.svg)](https://github.com/vicmon810/COSC345/actions/workflows/cmake.yaml)
[![Documentation](https://codedocs.xyz/vicmon810/COSC345.svg)](https://codedocs.xyz/vicmon810/COSC345/)
[![codecov](https://codecov.io/gh/vicmon810/COSC345/graph/badge.svg?token=P25HQT144Q)](https://codecov.io/gh/vicmon810/COSC345)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/db37ffc37f4b44fdb96f0b6e863c1410)](https://app.codacy.com/gh/vicmon810/COSC345/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)

# Movies and Food:
We developed an application that recommends movies and suggests suitable food pairings based on the movie's genre. 

This was for our group project for the paper [COSC345](https://www.otago.ac.nz/courses/papers?papercode=COSC345#t-2024)

![application display](https://i.imgur.com/2LmEOjw.png)
![application display 2](https://i.imgur.com/n7XlZN0.png)

The application contains details of over 7000 movies. The posters can be displayed and by clicking on the poster image, the movie details will be displayed
on a separate window. There is a food pairing option where a food pairing recommendation will appear containing the food recipe details.

This application can be used if the user has absolutely no idea what to watch or wants a suggestion of what to eat while watching a specific movie.

The application has a menu where there is a home button, a shuffle button, and a search bar that allows the user to search for movie titles or genres.
There are also page-turning buttons and the current page will be displayed on the menu.

### Current issues:
If a button on the application menu is spammed, the application will crash. Currently working on a fix.

## Contributors: 
[Kris Mao](https://github.com/vicmon810) <br>
[Andrew Goh](https://github.com/andre2410) <br>
[Andrew Booth](https://github.com/boo13103) <br>
[Tommy Light](https://github.com/tlite4) <br>

## Current Implementation
Written in C++ using the QT5 GUI library.

## Sources Requirement : 
[qt open source software](https://www.qt.io/)

## References:
1. [Food recipes lists](https://www.kaggle.com/datasets/paultimothymooney/recipenlg/code?resource=download)
2. [Food Ingredients](https://www.kaggle.com/datasets/pes12017000148/food-ingredients-and-recipe-dataset-with-images)
3. [Movies lists](https://www.kaggle.com/datasets/rounakbanik/the-movies-dataset)
4. [Qt with CMake](https://doc.qt.io/qt-6/cmake-get-started.html#building-a-c-console-application)
5
