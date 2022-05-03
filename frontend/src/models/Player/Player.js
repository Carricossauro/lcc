import React from "react";

import { useParams } from "react-router-dom";
import Main from "./Main";

export default function Player({ setShowNavBar, size }) {
  const { playerPath } = useParams();
  switch (playerPath) {
    case "main":
      setShowNavBar(true);
      return <Main size={size} />;
  }
}
