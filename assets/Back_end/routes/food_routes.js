const express = require("express");

const {
  getTitle,
  getAllTitle,
  deleteTitle,
  createTitle,
  searchTitle,
  updateTitle, // Add this import for updating titles
} = require("../controller/foodController");

const routes = express.Router();

// GET ALL titles
routes.get("/food", getAllTitle);

// GET Single title
routes.get("/food/:id", getTitle);

// Update a title
routes.patch("/food/:id", updateTitle); // Use the appropriate update function

// Delete a title
routes.delete("/food/:id", deleteTitle);

// Create a title
routes.post("/food", createTitle);

// Search a title
routes.get("/food/search/:searchInput", searchTitle);

module.exports = routes;
