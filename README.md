[![Continous Integration CMAKE](https://github.com/vicmon810/COSC345/actions/workflows/cmake.yaml/badge.svg)](https://github.com/vicmon810/COSC345/actions/workflows/cmake.yaml)
[![Documentation](https://codedocs.xyz/vicmon810/COSC345.svg)](https://codedocs.xyz/vicmon810/COSC345/)
[![codecov](https://codecov.io/gh/vicmon810/COSC345/graph/badge.svg?token=P25HQT144Q)](https://codecov.io/gh/vicmon810/COSC345)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/db37ffc37f4b44fdb96f0b6e863c1410)](https://app.codacy.com/gh/vicmon810/COSC345/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)

# Movies and Food:
For our COSC345 Team Project: We are developing an application that recommends movies and suggests suitable food pairings based on the movie's genre and user feedback.

## Team members: 
[Kris Mao](https://github.com/vicmon810) 7248988 <br>
[Andrew Goh](https://github.com/andre2410) 3457439 <br>
[Andrew Booth](https://github.com/boo13103) 8539924 <br>
[Tommy Light](https://github.com/tlite4) 1589489 <br>

## Assignment submission
### [A3 beta]
For our beta version of the application, we can display a list of movie posters with a gridlayout format. You can click on the movie poster to 
see more movie details. A food pairing button is available and once clicked, a food recipe details would be shown
providing the name of the food, ingredients list and directions to make the food.

The images below shows the current application.

![app display](https://i.imgur.com/NLk3bU4.png)
![app display2](https://i.imgur.com/dnbCD0k.png)

For the assignment requirements, the CI, doxygen, codecov and codacy details can be assessed by clicking the hyperlinks on the badges on top of the README.md file.
The code coverage has improved over the alpha version

For testing, please run UnitTest.exe instead of MovieAndFood.exe when running the project on Visual Studio. This would require the project to be built first which can be done by having 
CMake installed and building it in the Visual Studio IDE.

For our Questionnaire for user feedback, it can be assessed [here](https://forms.office.com/r/13M44QcMks)

Currently we could not figure out how to test the GUI code by simulating mouse clicks without the entire CI failing.
Therefore, we resulted to a simple user test below:

|Test Case | Test Summary | Test Start | Test result | Test Status|
|:---------|:-------------|:-----------|:------------|:-----------|
| 1  | Image is clickable | Click on movie poster| Pop up new dialog displaying specified movie's details| OK|
| 2  | Recommending food | Click on "Food pairing" button a few times| Pops out a new dialog where it recommends a different food | OK|
| 3 | Searchbar test | Enter key words to search Movies| return all movies that matches words in searchbar| OK|

## Project Overview:
Our goal is to create a user-friendly app that provides personalized movie recommendations and food suggestions to enhance the user's entertainment experience.

## Current Implementation
Read description of Assignment submission.

## Sources Rquirement : 
[qt open source software](https://www.qt.io/)

## References:
1. [Food recipes lists](https://www.kaggle.com/datasets/paultimothymooney/recipenlg/code?resource=download)
2. [Food Ingredients](https://www.kaggle.com/datasets/pes12017000148/food-ingredients-and-recipe-dataset-with-images)
3. [Movies lists](https://www.kaggle.com/datasets/rounakbanik/the-movies-dataset)
4. [Qt with CMake](https://doc.qt.io/qt-6/cmake-get-started.html#building-a-c-console-application)
5. [Qt called by main class](https://stackoverflow.com/questions/17450039/qt-c-gui-call-from-another-class)

