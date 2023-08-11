//Lib import
const mongose = require("mongoose");
const express = require("express");
const app = express();
const cors = require("cors");

//setup local port
require("dotenv").config({ path: "./config.env" });
const port = process.env.PORT || 8080;
app.use(cors());
app.use(express.json());
const dbo = require("./db/conn");

//router address for query actions
const MovieRoute = require("./routes/movie_routes.js");
const foodRoute = require("./routes/food_routes.js");
//Font-end access routed info
app.use("/api/movie_routes", MovieRoute);
app.use("/api/food_routes", foodRoute);

app.listen(port, () => {
  dbo.connectToServer(function (err) {
    if (err) console.error(err);
  });
  console.log(`Server is runing on port: ${port}`);
});
