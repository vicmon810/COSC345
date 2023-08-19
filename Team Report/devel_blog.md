# Stage report:

### 17/Aug/2023
- Version : A 0.7 
- structure: Full stack interaction Application, using mongodb as database, mongo-cxx-driver for back-end data query tool. Qt base on C++ for front-end interaction. 
- current feature: able to view full list of movie dataset on GUI interface. 
- TODO: <br>- currently using Qtable to display datalist, should change it asap. <br>
        - Apply search function on GUI<br>
        - update algorithm<br>

![example](A_0.7.png)


TODO alpha:

        read movie.csv (done)
        display movie detials (done)
        read food.csv
        display poster on GUI 
        recommend function 

|root
|.github
        |-workflows
                |- cmake.yaml
|cmakelist.txt
|data
    |-Movies.csv
|src
   |-main.cpp