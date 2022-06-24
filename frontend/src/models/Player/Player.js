import React from "react";

import { useParams } from "react-router-dom";
import Main from "./Main";
import Game from "./Game/Game";

export default function Player({ setShowNavBar, size }) {
  const { playerPath } = useParams();
  switch (playerPath) {
    case "Game":
      return <Game size={size} />;
    default:
      setShowNavBar(true);
      return <Main size={size} />;
  }
}
