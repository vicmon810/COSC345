//import lib
const express = require("express");
const dbo = require("../db/conn");

//THIS ObjectID to help us avoid duplicate item with same name
const ObjectID = require("mongodb").ObjectID;

//Read all foods by title
const getAllTitle = async (req, res) => {
  try {
    let db_connect = dbo.getDB("MOVIE_APP");
    const foods = await db_connect
      .collection("Food")
      .find()
      .toArray(function (err, result) {
        if (err) throw err;
        res.status(200).json(result);
      });
  } catch (err) {
    console.log(err);
    res.status(500).json({
      message: "Internal sever error (Error Code:4396)",
    });
  }
};
//Read one food by title
const getTitle = async (req, res) => {
  try {
    const db_connect = dbo.getDB();
    const my_query = {
      _id: ObjectID(req.params.id),
    };
    db_connect.collection("Food").findOne(my_query, function (err, result) {
      if (err) throw err;
      res.status(200).json(result);
    });
  } catch (err) {
    console.log(err);
    res.status(500).json({
      message: "Internal sever error (Error Code:4396)",
    });
  }
};

//Create a new food with title
const createTitle = async (req, res) => {
  try {
    let db_connect = dbo.getDB();
    let food = {
      //Please match this with mongodb existing row head
      title: req.body.title,
      ingredients: req.body.ingredients,
      directions: req.body.directions,
      NER: req.body.NER,
    };
    db_connect.collection("Food").insertOne(food, function (err, result) {
      if (err) throw err;
      res.json(result); // Corrected typo here
    });
  } catch (err) {
    console.error(err);
    res.status(500).json({
      message: `Internal Sever error (ERROR CODE: 960)`,
    });
  }
};

//Update foods info MAY NOT WORK
const updateTitle = async (req, res) => {
  try {
    let db_connect = dbo.getDB();
    let food = {
      //Please match this with mongodb existing row head
      title: req.body.title,
      ingredients: req.body.ingredients,
      directions: req.body.directions,
      NER: req.body.NER,
    };
    db_connect.collection("Food").updateOne(food, function (err, result) {
      if (err) throw err;
      res.status(200).josn(result);
    });
  } catch (err) {
    console.error(err);
    res.status(500).json({
      message: `Internal Sever error (ERROR CODE: 430)`,
    });
  }
};
//delete an item
const deleteTitle = async (req, res) => {
  try {
    let db_connection = dbo.getDb();
    let myquery = {
      _id: ObjectId(req.params.id),
    };
    db_connection.collection("Food").deleteOne(myquery, function (err, result) {
      if (err) throw err;
      console.log("1 item deleted successfully");
      res.status(204).json(result);
    });
  } catch (err) {
    console.error(err);
    res.status(500).json({
      message: "Internal server error (ERROR CODE: 5)",
    });
  }
};
//Search a food with title
const searchTitle = async (req, res) => {
  try {
    const db_connection = dbo.getDb("MOVIE_APP");
    const query = { title: { $regex: req.params.searchInput, $options: "i" } };
    console.log(query);
    const items = await db_connection.collection("Food").find(query).toArray();

    if (items.length === 0) {
      return res.status(404).json({
        message: "No food found",
      });
    }
    res.status(200).json(items);
  } catch (err) {
    res.status(500).json({
      message: "Internal Server Error(ERROD CODE5: 570)",
      error: err.message,
    });
  }
};

//Exports function
module.exports = {
  getAllTitle,
  getTitle,
  createTitle,
  updateTitle,
  deleteTitle,
  searchTitle,
};
