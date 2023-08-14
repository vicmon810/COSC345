import React from "react";
import { Route, Routes } from "react-router-dom";
import "./App.css";
// import all components we need in our app
import Home from "./components/Home";

function App() {
  return (
    <div className="App">
      <header className="Edit me">
        <Routes>
          <Route exact path="/" element={<Home />} />
        </Routes>
      </header>
    </div>
  );
}

export default App;
