import { React, useState, useEffect } from "react";
import ReactDOM from "react-dom";
import "./index.css";
import LoginPopUp from "./models/LoginPopUp/LoginPopUp";
import NavBar from "./models/NavBar/NavBar";
import SignUp from "./models/SignUp/SignUp";
import {
  BrowserRouter as Router,
  Route,
  Routes,
  Navigate,
} from "react-router-dom";
import Player from "./models/Player/Player";
import Author from "./models/Author/Author";
import PlayerLogin from "./models/Player/PlayerLogin";

const Index = () => {
  const [size, setSize] = useState(window.innerWidth);
  const [loginPopUp, setLoginPopUp] = useState(false);
  const [showNavBar, setShowNavBar] = useState(true);
  const [isAuthor, setIsAuthor] = useState(true);
  const checkSize = () => {
    setSize(window.innerWidth);
  };

  const changePopUpState = () => {
    setLoginPopUp((state) => {
      return !state;
    });
  };
  useEffect(() => {
    window.addEventListener("resize", checkSize);
    return () => {
      window.removeEventListener("resize", checkSize);
    };
  }, []);

  return (
    <>
      <Router>
        {showNavBar && <NavBar size={size} setPopUp={changePopUpState} />}
        {loginPopUp && <LoginPopUp setPopUp={changePopUpState} />}
        <Routes>
          <Route
            path="/Player/:playerPath"
            element={<Player setShowNavBar={setShowNavBar} size={size} />}
          ></Route>
          <Route
            path="/Author/:authorPath"
            element={<Author setShowNavBar={setShowNavBar} size={size} />}
          ></Route>
          <Route
            path="/SignUp"
            element={
              <SignUp
                setShowNavBar={setShowNavBar}
                size={size}
                setIsAuthor={setIsAuthor}
                isAuthor={isAuthor}
              />
            }
          ></Route>
        </Routes>
      </Router>
    </>
  );
};

ReactDOM.render(
  <>
    <Index />
  </>,

  document.getElementById("root")
);
