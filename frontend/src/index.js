import { React, useState, useEffect } from "react";
import ReactDOM from "react-dom";
import "./index.css";
import LoginPopUp from "./models/LoginPopUp/LoginPopUp";
import NavBar from "./models/NavBar/NavBar";

const Index = () => {
  const [size, setSize] = useState(window.innerWidth);
  const [loginPopUp, setLoginPopUp] = useState(false);
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
      <NavBar size={size} setPopUp={changePopUpState} />
      {loginPopUp && <LoginPopUp setPopUp={changePopUpState} />}
    </>
  );
};

ReactDOM.render(
  <>
    <Index />
  </>,

  document.getElementById("root")
);
