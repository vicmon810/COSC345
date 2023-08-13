const express = require("express");
const dbo = require("../db/conn");
const { getDB } = require("../db/conn");
const ObjectID = require("mongodb").ObjectID;

const getAllMovies = async (req, res) => {
  try {
    let db_connect = dbo.getDB();
    const movies = await db_connect
      .collection("Movies")
      .find()
      .toArray(function (err, result) {
        if (err) throw err;
        res.status(200).json(result);
      });
  } catch (err) {
    console.error(err);
    res.status(500).json({
      message: "Internal server error",
    });
  }
};

const getMovie = async (req, res) => {
  try {
    let db_connect = dbo.getDB();
    const my_query = {
      _id: ObjectID(req.params.id),
    };
    db_connect.collections("Movies").findOne(my_query, function (err, result) {
      if (err) throw err;
      res.status(200).json(result);
    });
  } catch (err) {
    console.error(err);
    res.status(500).json({
      message: "Internal server error",
    });
  }
};
//create a new moive
const createMovie = async (req, res) => {
  try {
    let db_connect = dbo.getDB();
    let movie = {
      title: req.body.title,
      genres: req.body.genres,
      imdb_id: req.body.imdb_id,
      overview: req.body.overview,
      release_date: req.body.release_date,
      runtime: req.body.runtime,
      rating: req.body.rating,
    };
    db_connect.collections("Movies").insertOne(movie, function (err, result) {
      if (err) throw err;
      res.json(result);
    });
  } catch (err) {
    console.error(err);
    res.status(500).json({
      message: "Internal server error",
    });
  }
};

const updateMovie = async (req, res) => {
  try {
    let db_connect = dbo.getDB();
    let movie = {
      title: req.body.title,
      genres: req.body.genres,
      imdb_id: req.body.imdb_id,
      overview: req.body.overview,
      release_date: req.body.release_date,
      runtime: req.body.runtime,
      rating: req.body.rating,
    };
    db_connect
      .collections("Movies")
      .updateOne(my_query, movie, function (err, result) {
        if (err) throw err;
        res.status(200).json(result);
      });
  } catch (err) {
    console.error(err);
    res.status(500).json({
      message: "Internal server error",
    });
  }
};

const deleteMovie = async (req, res) => {
  try {
    let db_connect = dbo.getDB();
    let my_query = { _id: ObjectID(req.params.id) };
    db_connect
      .collections("Movies")
      .deleteOne(my_query, function (err, result) {
        if (err) throw err;
        res.status(204).json(result);
      });
  } catch (err) {
    console.error(err);
    res.status(500).json({
      message: "Internal server error",
    });
  }
};

const searchMovie = async (req, res) => {
  try {
    const db_connect = dbo.getDB();
    const query = { title: { $regex: req.params.searchInput, $options: "i" } };
    const moive = await db_connect.collections("Movies").find(query).toArray();
    if (moive.length === 0) {
      return res.status(404).json({
        message: "NOT FOUND",
      });
    }
    res.status(200).json(moive);
  } catch (err) {
    console.error(err);
    res.status(500).json({
      message: "Internal server error",
    });
  }
};

module.exports = {
  getAllMovies,
  getMovie,
  updateMovie,
  createMovie,
  deleteMovie,
};
