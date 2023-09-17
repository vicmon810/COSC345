[![Continous Integration CMAKE](https://github.com/vicmon810/COSC345/actions/workflows/cmake.yaml/badge.svg)](https://github.com/vicmon810/COSC345/actions/workflows/cmake.yaml)
[![Documentation](https://codedocs.xyz/vicmon810/COSC345.svg)](https://codedocs.xyz/vicmon810/COSC345/)
[![codecov](https://codecov.io/gh/vicmon810/COSC345/graph/badge.svg?token=P25HQT144Q)](https://codecov.io/gh/vicmon810/COSC345)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/db37ffc37f4b44fdb96f0b6e863c1410)](https://app.codacy.com/gh/vicmon810/COSC345/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)

# TEST CASE(Currently we didn't figure out how to test GUI thought code, therefore just a simple user test instead) :
|Test Case | Test Summary | Test Start | Test result | Test Status|
|:---------|:-------------|:-----------|:------------|:-----------|
| 1  | Image clickable | Press mouse on movie poster| Pop up new dialog display all full movie's details| OK|
| 2  | Recommanding food | Right click on "Recommanding Food" button a few times| Pop out a new dialog, each time recommanding different food | OK|
| 3 | Searching Movies | Enter key words to search Movies| return all movies that contains key words| OK|

![CI memes](CI%20meme.png)

# Movies and Food:
For our COSC345 Team Project: We are aiming to develop an application that recommends movies and suggests suitable meal/snack pairings based on the user's preferences.

## Team members: 
[Kris Mao](https://github.com/vicmon810) 7248988 <br>
[Andrew Goh](https://github.com/andre2410) 3457439 <br>
[Andrew Booth](https://github.com/boo13103) 8539924 <br>
[Tommy Light](https://github.com/tlite4) 1589489 <br>

## Assignment submission
### [A2 alpha]<br>
For our alpha version of the application, we can display all 7000 movies with a recommended food of popcorn and ice cream. You can click on the movie details to expand the card showing 
said details. Additionally, the movie poster image can be displayed although it is abit small.

For the assignment requirements, the CI, doxygen, codecov and codacy details can be assessed by clicking the hyperlinks on the badges on top of the README.md file.

For testing, please run UnitTest.exe instead of MovieAndFood.exe when running the project on Visual Studio. This would require the project to be built first which can be done by having 
CMake installed and building it in the Visual Studio IDE.

For our Questionnaire to be reviewed, it can be assessed [here](https://forms.office.com/r/13M44QcMks)

## Project Overview:
Our goal is to create a user-friendly app that provides personalized movie recommendations and food suggestions to enhance the user's entertainment experience.

## Key Features:
1: Movie Recommendation: The app will analyze the user's movie preferences, ratings, and history to suggest new movies that align with their interests. It will consider factors like genre, cast, ratings, and release year.

2: Food Pairing Suggestions: In addition to movie recommendations, the app will suggest suitable food options that complement the user's selected movie. It will provide recipes based on the movie chosen.

## Current Implementation
The application can display 7000 movie details with a recommended food of popcorn and ice cream.

## Sources Rquirement : 
[qt open source software](https://www.qt.io/)

## References:
* [Food recipes lists](https://www.kaggle.com/datasets/paultimothymooney/recipenlg/code?resource=download)
* [Food Ingredients](https://www.kaggle.com/datasets/pes12017000148/food-ingredients-and-recipe-dataset-with-images)
* [Movies lists](https://www.kaggle.com/datasets/rounakbanik/the-movies-dataset)
* [Qt with CMake](https://doc.qt.io/qt-6/cmake-get-started.html#building-a-c-console-application)
* [Qt called by main class](https://stackoverflow.com/questions/17450039/qt-c-gui-call-from-another-class)

