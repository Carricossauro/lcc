import { React, useState, useEffect } from "react";
import ReactDOM from "react-dom";
import "./index.css";
import NavBar from "./models/NavBar/NavBar";

const Index = () => {
  const [size, setSize] = useState(window.innerWidth);
  const checkSize = () => {
    setSize(window.innerWidth);
  };
  useEffect(() => {
    window.addEventListener("resize", checkSize);
    return () => {
      window.removeEventListener("resize", checkSize);
    };
  }, []);

  return (
    <>
      <NavBar size={size} />
    </>
  );
};

ReactDOM.render(
  <>
    <Index />
  </>,

  document.getElementById("root")
);
