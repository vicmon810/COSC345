const express = require("express");
const {
  getAllMovies,
  getMovie,
  updateMovie,
  createMovie,
  deleteMovie,
} = require("../controller/movieController");

const routes = express.Router();

//GET all moives
routes.get("movie", getAllMovies);
//GET one moives
routes.get("/movie", getMovie);
//Update one moive
routes.patch("/movie/:id", updateMovie);
//Create one movie
routes.post("/movie", createMovie);
//delete one moive
routes.delete("/movie/:id", deleteMovie);

module.exports = routes;
